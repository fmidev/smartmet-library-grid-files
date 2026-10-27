// A GRIB2 message may contain several fields, each repeating sections 2-7,
// 3-7 or 4-7 of the message (WMO manual on codes, GRIB2 regulation 92.1.3).
// The test assembles such a message from three single-field messages and
// checks that every field is found and decoded both when the whole file is
// read and when the fields are loaded lazily from their stored positions.

#define BOOST_TEST_MODULE Grib2RepeatedSectionsTest
#include <boost/test/included/unit_test.hpp>

#include "TestCommon.h"
#include "../src/grid/GridFile.h"
#include "../src/grid/Message.h"
#include "../src/identification/GridDef.h"

#include <cstdint>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

using namespace SmartMet;
using namespace GridTest;

namespace
{
const std::string GRIB2_FIXTURE = testData("grib/climate/tmax.grib");

using Bytes = std::vector<unsigned char>;

std::uint64_t be(const unsigned char *p, int n)
{
  std::uint64_t v = 0;
  for (int i = 0; i < n; i++)
    v = (v << 8) | p[i];
  return v;
}

// Split one GRIB2_FIXTURE message into its sections 1-7 (section 0 and 7777 excluded)
std::vector<Bytes> sections(const unsigned char *msg)
{
  std::vector<Bytes> ret(8);
  const auto total = be(msg + 8, 8);
  const unsigned char *p = msg + 16;
  while (p < msg + total - 4)
  {
    const auto len = be(p, 4);
    ret[p[4]].assign(p, p + len);
    p += len;
  }
  return ret;
}

bool same_values(GRID::Message *a, GRID::Message *b)
{
  T::ParamValue_vec va;
  T::ParamValue_vec vb;
  a->getGridValueVector(va);
  b->getGridValueVector(vb);
  return !va.empty() && va == vb;
}

// Assemble one message with three fields: field 1 has sections 1-7, field 2 repeats sections
// 4-7 and field 3 repeats sections 3-7
std::string assemble(const Bytes &file)
{
  std::vector<const unsigned char *> msgs;
  const unsigned char *p = file.data();
  for (int i = 0; i < 3; i++)
  {
    msgs.push_back(p);
    p += be(p + 8, 8);
  }

  auto s0 = sections(msgs[0]);
  auto s1 = sections(msgs[1]);
  auto s2 = sections(msgs[2]);

  Bytes body;
  for (int i = 1; i <= 7; i++)
    body.insert(body.end(), s0[i].begin(), s0[i].end());
  for (int i = 4; i <= 7; i++)
    body.insert(body.end(), s1[i].begin(), s1[i].end());
  for (int i = 3; i <= 7; i++)
    body.insert(body.end(), s2[i].begin(), s2[i].end());

  Bytes grib(msgs[0], msgs[0] + 16);
  const std::uint64_t total = 16 + body.size() + 4;
  for (int i = 0; i < 8; i++)
    grib[8 + i] = static_cast<unsigned char>(total >> (8 * (7 - i)));
  grib.insert(grib.end(), body.begin(), body.end());
  for (char c : std::string("7777"))
    grib.push_back(static_cast<unsigned char>(c));

  return std::string(grib.begin(), grib.end());
}
}  // namespace

BOOST_AUTO_TEST_CASE(repeated_sections, *fixtures({CONFIG, GRIB2_FIXTURE}))
{
  requireFixture(CONFIG);
  requireFixture(GRIB2_FIXTURE);

  withFmiErrors(
      []
      {
        Identification::gridDef.init(CONFIG);

        std::ifstream in(GRIB2_FIXTURE, std::ios::binary);
        Bytes file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        TempFile tmp(assemble(file), "grib2repeated");

        GRID::GridFile original;
        original.read(GRIB2_FIXTURE);

        GRID::GridFile gf;
        gf.read(tmp.name());
        BOOST_TEST_REQUIRE(gf.getNumberOfMessages() == 3U);

        for (uint i = 0; i < 3; i++)
          BOOST_TEST(same_values(gf.getMessageByIndex(i), original.getMessageByIndex(i)),
                     "field " << i << " differs");

        // Lazy loading from the stored positions, as the grid engine does
        GRID::GridFile lazy;
        lazy.setFileName(tmp.name());
        for (uint i = 0; i < 3; i++)
        {
          GRID::MessageInfo info;
          info.mFilePosition = gf.getMessageByIndex(i)->getFilePosition();
          info.mMessageSize = gf.getMessageByIndex(i)->getMessageSize();
          info.mMessageType = T::FileTypeValue::Grib2;
          info.mFileMemoryPtr = nullptr;
          lazy.newMessage(i, info);
        }
        for (uint i = 0; i < 3; i++)
        {
          auto *msg = lazy.getMessageByIndex(i);
          BOOST_TEST_REQUIRE(msg != nullptr);
          BOOST_TEST(same_values(msg, original.getMessageByIndex(i)),
                     "lazily loaded field " << i << " differs");
        }
      });
}
