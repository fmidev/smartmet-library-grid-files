// A GRIB2_FIXTURE message may contain several fields, each repeating sections 2-7,
// 3-7 or 4-7 of the message (WMO manual on codes, GRIB2_FIXTURE regulation 92.1.3).
// The test assembles such a message from three single-field messages and
// checks that every field is found and decoded both when the whole file is
// read and when the fields are loaded lazily from their stored positions.

#include "../src/grid/GridFile.h"
#include "../src/grid/Message.h"
#include "../src/identification/GridDef.h"
#include <macgyver/Exception.h>

#include <sys/stat.h>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iterator>
#include <string>
#include <unistd.h>
#include <vector>

using namespace SmartMet;

namespace
{
const char *CONFIG = "/usr/share/smartmet/test/grid/library/grid-files.conf";
const char *GRIB2_FIXTURE = "/usr/share/smartmet/test/data/grib/climate/tmax.grib";

bool exists(const char *path)
{
  struct stat st;
  return stat(path, &st) == 0 && st.st_size > 0;
}

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
}  // namespace

int main()
{
  if (!exists(CONFIG) || !exists(GRIB2_FIXTURE))
  {
    printf("SKIP Grib2RepeatedSectionsTest: test fixtures not installed\n");
    return 0;
  }

  try
  {
    Identification::gridDef.init(CONFIG);

    std::ifstream in(GRIB2_FIXTURE, std::ios::binary);
    Bytes file((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());

    // The first three messages of the fixture
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

    // Field 1: sections 1-7, field 2: sections 4-7, field 3: sections 3-7
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

    char tmpname[] = "/tmp/grib2repeated-XXXXXX";
    int fd = mkstemp(tmpname);
    if (fd < 0 || write(fd, grib.data(), grib.size()) != static_cast<ssize_t>(grib.size()))
    {
      fprintf(stderr, "FAIL Grib2RepeatedSectionsTest: cannot write a temporary file\n");
      return 1;
    }
    close(fd);

    GRID::GridFile original;
    original.read(std::string(GRIB2_FIXTURE));

    int ret = 0;
    {
      GRID::GridFile gf;
      gf.read(std::string(tmpname));

      if (gf.getNumberOfMessages() != 3)
      {
        fprintf(stderr, "FAIL Grib2RepeatedSectionsTest: expected 3 fields, got %u\n",
                static_cast<unsigned>(gf.getNumberOfMessages()));
        ret = 1;
      }
      else
      {
        for (uint i = 0; i < 3; i++)
          if (!same_values(gf.getMessageByIndex(i), original.getMessageByIndex(i)))
          {
            fprintf(stderr, "FAIL Grib2RepeatedSectionsTest: field %u differs\n", i);
            ret = 1;
          }

        // Lazy loading from the stored positions, as the grid engine does
        GRID::GridFile lazy;
        lazy.setFileName(tmpname);
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
          if (msg == nullptr || !same_values(msg, original.getMessageByIndex(i)))
          {
            fprintf(stderr, "FAIL Grib2RepeatedSectionsTest: lazily loaded field %u differs\n", i);
            ret = 1;
          }
        }
      }
    }

    unlink(tmpname);
    if (ret == 0)
      printf("OK Grib2RepeatedSectionsTest\n");
    return ret;
  }
  catch (...)
  {
    Fmi::Exception e(BCP, "Grib2RepeatedSectionsTest failed", nullptr);
    e.printError();
    return 1;
  }
}
