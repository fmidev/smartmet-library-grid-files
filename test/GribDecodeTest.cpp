// Decoding tests against independent ecCodes references.
//
// Every synthetic/NAME.grib has a NAME.ref written by synthetic/make_synthetic.cpp: the field as
// decoded by ecCodes (storage order index, latitude, longitude, value). The fixtures cover
// GRIB1/GRIB2, the common grid types (regular, rotated, polar stereographic, Lambert, Mercator,
// LAEA, regular and reduced Gaussian) and packing methods (simple, JPEG2000, CCSDS, complex,
// complex with spatial differencing, IEEE, GRIB1 second order), with and without bitmaps and in
// both row orders.
//
// For each fixture the test checks that grid-files
//
//   * decodes the original values exactly like ecCodes (missing values included)
//   * maps every grid point (i,j) to the same storage index and coordinates as ecCodes
//   * finds the grid point back from its coordinates (inverse projection)
//   * reports the expected dimensions, projection and forecast time

#define BOOST_TEST_MODULE GribDecodeTest
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/included/unit_test.hpp>

#include "TestCommon.h"
#include "../src/grid/GridFile.h"
#include "../src/grid/Message.h"
#include "../src/identification/GridDef.h"

#include <boost/algorithm/string.hpp>
#include <filesystem>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace SmartMet;
using namespace GridTest;
namespace bdata = boost::unit_test::data;

namespace
{
const std::string DIR = "synthetic";

struct RefPoint
{
  double lat;
  double lon;
  double value;  // NaN = missing
};

struct Reference
{
  std::map<std::string, std::string> meta;
  std::vector<RefPoint> points;
};

Reference readReference(const std::string &file)
{
  Reference ref;
  std::ifstream in(file);
  BOOST_TEST_REQUIRE(in.good(), "cannot read " << file);
  std::string line;
  while (std::getline(in, line))
  {
    if (line.empty())
      continue;
    if (line[0] == '#')
    {
      auto pos = line.find('=');
      ref.meta[line.substr(2, pos - 2)] = line.substr(pos + 1);
      continue;
    }
    std::istringstream s(line);
    std::size_t index = 0;
    std::string lat, lon, value;
    s >> index >> lat >> lon >> value;
    BOOST_TEST_REQUIRE(index == ref.points.size());
    ref.points.push_back({std::stod(lat), std::stod(lon),
                          value == "nan" ? std::nan("") : std::stod(value)});
  }
  return ref;
}

std::vector<std::string> fixtureNames()
{
  std::vector<std::string> names;
  for (const auto &entry : std::filesystem::directory_iterator(DIR))
  {
    if (entry.path().extension() == ".ref")
      names.push_back(entry.path().stem().string());
  }
  std::sort(names.begin(), names.end());
  return names;
}

double lonDiff(double a, double b)
{
  double d = std::fmod(std::fabs(a - b), 360.0);
  return std::min(d, 360.0 - d);
}

T::GridProjection expectedProjection(const std::string &gridType)
{
  static const std::map<std::string, T::GridProjection> projections = {
      {"regular_ll", T::GridProjectionValue::LatLon},
      {"rotated_ll", T::GridProjectionValue::RotatedLatLon},
      {"polar_stereographic", T::GridProjectionValue::PolarStereographic},
      {"lambert", T::GridProjectionValue::LambertConformal},
      {"mercator", T::GridProjectionValue::Mercator},
      {"lambert_azimuthal_equal_area", T::GridProjectionValue::LambertAzimuthalEqualArea},
      {"regular_gg", T::GridProjectionValue::Gaussian},
      {"reduced_gg", T::GridProjectionValue::Gaussian}};
  auto it = projections.find(gridType);
  BOOST_TEST_REQUIRE((it != projections.end()), "unknown gridType " << gridType);
  return it->second;
}

// Values are 16-bit packed by ecCodes; both decoders must agree to float precision
bool sameValue(double ref, T::ParamValue value)
{
  if (std::isnan(ref))
    return value == ParamValueMissing;
  return std::fabs(ref - value) <= 1e-4 * std::max(1.0, std::fabs(ref));
}

struct GridDefInit
{
  GridDefInit()
  {
    if (exists(CONFIG))
      Identification::gridDef.init(CONFIG);
  }
};

}  // namespace

BOOST_TEST_GLOBAL_FIXTURE(GridDefInit);

BOOST_AUTO_TEST_CASE(fixtures_exist)
{
  // Guard against the data driven cases below silently running over an empty directory
  BOOST_TEST(fixtureNames().size() >= 20U);
}

BOOST_DATA_TEST_CASE(decode, bdata::make(fixtureNames()), name)
{
  requireFixture(CONFIG);

  withFmiErrors(
      [&]
      {
        const Reference ref = readReference(DIR + "/" + name + ".ref");
        const auto &meta = ref.meta;
        const std::size_t n = ref.points.size();
        const bool reduced = (meta.at("gridType") == "reduced_gg");

        GRID::GridFile gf;
        gf.read(DIR + "/" + name + ".grib");
        BOOST_TEST_REQUIRE(gf.getNumberOfMessages() == 1U);
        GRID::Message *msg = gf.getMessageByIndex(0);

        // ---- Metadata ----

        BOOST_TEST(msg->getGridProjection() == expectedProjection(meta.at("gridType")));
        BOOST_TEST(msg->getGridOriginalValueCount() == n);
        BOOST_TEST(msg->getForecastTime() == "20260101T180000");

        // The fixtures are all 2 metre temperature. (No newbase id: T-K maps to newbase
        // Temperature only via a unit conversion.)
        BOOST_TEST(std::string(msg->getFmiParameterName()) == "T-K");
        BOOST_TEST(msg->getGridParameterLevel() == 2);

        T::Dimensions d = msg->getGridDimensions();
        if (!reduced)
        {
          BOOST_TEST(d.nx() == std::stoul(meta.at("Ni")));
          BOOST_TEST(d.ny() == std::stoul(meta.at("Nj")));
        }

        // ---- Values in storage order ----

        T::ParamValue_vec original;
        msg->getGridOriginalValueVector(original);
        BOOST_TEST_REQUIRE(original.size() == n);
        std::size_t bad = 0;
        for (std::size_t k = 0; k < n; k++)
        {
          if (!sameValue(ref.points[k].value, original[k]) && bad++ < 5)
            BOOST_ERROR("original value " << k << ": grid-files " << original[k] << ", ecCodes "
                                          << ref.points[k].value);
        }
        BOOST_TEST(bad == 0U, bad << " original values differ");

        if (reduced)
          return;  // reduced grids have no (i,j) storage index mapping

        // ---- Grid point -> storage index, coordinates and value ----

        bad = 0;
        for (uint j = 0; j < d.ny(); j++)
        {
          for (uint i = 0; i < d.nx(); i++)
          {
            const int idx = msg->getGridOriginalValueIndex(i, j);
            if (idx < 0 || static_cast<std::size_t>(idx) >= n)
            {
              if (bad++ < 5)
                BOOST_ERROR("grid point (" << i << "," << j << ") has no storage index");
              continue;
            }
            const auto &p = ref.points[idx];

            double lat = 0;
            double lon = 0;
            bool ok = msg->getGridLatLonCoordinatesByGridPoint(i, j, lat, lon);
            if (!ok || std::fabs(lat - p.lat) > 1e-3 || lonDiff(lon, p.lon) > 1e-3)
            {
              if (bad++ < 5)
                BOOST_ERROR("grid point (" << i << "," << j << ") -> index " << idx
                                           << ": grid-files " << lat << "," << lon
                                           << ", ecCodes " << p.lat << "," << p.lon);
              continue;
            }

            T::ParamValue value = msg->getGridValueByGridPoint(i, j);
            if (!sameValue(p.value, value) && bad++ < 5)
              BOOST_ERROR("grid point (" << i << "," << j << ") value " << value << ", ecCodes "
                                         << p.value);
          }
        }
        BOOST_TEST(bad == 0U, bad << " grid point checks failed");

        // ---- Coordinates -> grid point (inverse projection), away from the poles ----

        bad = 0;
        for (uint j = 0; j < d.ny(); j++)
        {
          for (uint i = 0; i < d.nx(); i++)
          {
            const auto &p = ref.points[msg->getGridOriginalValueIndex(i, j)];
            if (std::fabs(p.lat) > 89)
              continue;
            double gi = -1;
            double gj = -1;
            bool ok = msg->getGridPointByLatLonCoordinatesNoCache(p.lat, p.lon, gi, gj);
            if (!ok || std::fabs(gi - i) > 1e-3 || std::fabs(gj - j) > 1e-3)
            {
              if (bad++ < 5)
                BOOST_ERROR("latlon " << p.lat << "," << p.lon << " -> grid point " << gi << ","
                                      << gj << ", expected " << i << "," << j);
            }
          }
        }
        BOOST_TEST(bad == 0U, bad << " inverse projection checks failed");
      });
}
