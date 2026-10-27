// Coordinate round trips for every geometry in the repository's own configuration (cfg/).
//
// The geometry definitions in cfg/fmi_geometries*.csv are what production uses, and they cover
// latlon, rotated latlon, polar stereographic, Lambert conformal, LAEA, transverse Mercator,
// Gaussian etc. For each geometry the test samples grid points across the whole grid and checks
//
//   * grid point -> latlon succeeds and gives valid coordinates
//   * latlon -> grid point returns the original grid point (inverse projection)
//   * the bulk coordinate methods agree with the single point methods
//
// No data files are needed, so the test always runs.

#define BOOST_TEST_MODULE GeometryRoundTripTest
#include <boost/test/data/monomorphic.hpp>
#include <boost/test/data/test_case.hpp>
#include <boost/test/included/unit_test.hpp>

#include "TestCommon.h"
#include "../src/grid/Typedefs.h"
#include "../src/identification/GridDef.h"

#include <cmath>
#include <set>
#include <type_traits>
#include <vector>

using namespace SmartMet;
using namespace GridTest;
namespace bdata = boost::unit_test::data;

namespace
{


std::vector<int> geometryIds()
{
  static std::vector<int> ids;
  if (ids.empty())
  {
    std::set<T::GeometryId> idset;
    Identification::gridDef.getGeometryIdList(idset);
    ids.assign(idset.begin(), idset.end());
  }
  return ids;
}

struct GridDefInit
{
  GridDefInit() { Identification::gridDef.init(CONFIG); }
};

// Initialized before the data driven test cases are generated
GridDefInit gridDefInit;

std::vector<uint> samples(uint n)
{
  std::vector<uint> ret;
  const uint step = std::max(1U, n / 9);
  for (uint i = 0; i < n; i += step)
    ret.push_back(i);
  if (ret.back() != n - 1)
    ret.push_back(n - 1);
  return ret;
}

double lonDiff(double a, double b)
{
  double d = std::fmod(std::fabs(a - b), 360.0);
  return std::min(d, 360.0 - d);
}
}  // namespace

BOOST_AUTO_TEST_CASE(configuration_has_geometries)
{
  BOOST_TEST(geometryIds().size() >= 50U);
}

BOOST_DATA_TEST_CASE(round_trip, bdata::make(geometryIds()), geometryId)
{
  withFmiErrors(
      [&]
      {
        // Each geometry is defined for GRIB2 and/or GRIB1, test the ones that exist
        GRIB2::GridDef_sptr def2 = Identification::gridDef.getGrib2DefinitionByGeometryId(geometryId);
        GRIB1::GridDef_sptr def1 = Identification::gridDef.getGrib1DefinitionByGeometryId(geometryId);
        BOOST_TEST_REQUIRE((def2 || def1), "geometry " << geometryId << " has no definition");

        auto check = [&](auto &def, const char *edition)
        {
          BOOST_TEST_CONTEXT(edition << " geometry " << geometryId << " projection " << (int)def->getGridProjection())
          {
            T::Dimensions d = def->getGridDimensions();
            BOOST_TEST_REQUIRE(d.getDimensions() == 2U);
            const uint nx = d.nx();
            const uint ny = d.ny();
            BOOST_TEST_REQUIRE(nx > 1U);
            BOOST_TEST_REQUIRE(ny > 1U);

            // The full coordinate list is compared only for reasonably sized grids, some DEM
            // geometries have hundreds of millions of points
            const bool compareList = (static_cast<std::size_t>(nx) * ny <= 4000000);
            T::Coordinate_svec all;
            if (compareList)
            {
              all = def->getGridLatLonCoordinates();
              BOOST_TEST_REQUIRE(all->size() == static_cast<std::size_t>(nx) * ny);
            }

            std::vector<T::Point> points;
            for (uint j : samples(ny))
              for (uint i : samples(nx))
                points.emplace_back(i, j);

            // Only GRIB2 has the bulk method
            constexpr bool hasBulk =
                std::is_same_v<std::decay_t<decltype(*def)>, GRIB2::GridDefinition>;
            T::Coordinate_vec bulk;
            std::vector<bool> found;
            if constexpr (hasBulk)
            {
              def->getGridLatLonCoordinatesByGridPointList(points, bulk, found);
              BOOST_TEST_REQUIRE(bulk.size() == points.size());
            }

            std::size_t bad = 0;
            for (std::size_t k = 0; k < points.size(); k++)
            {
              const uint i = points[k].x();
              const uint j = points[k].y();
              double lat = 0;
              double lon = 0;
              bool ok = def->getGridLatLonCoordinatesByGridPoint(i, j, lat, lon);
              if (!ok || !std::isfinite(lat) || !std::isfinite(lon) || std::fabs(lat) > 90.001)
              {
                if (bad++ < 3)
                  BOOST_ERROR("grid point (" << i << "," << j << ") -> " << lat << "," << lon);
                continue;
              }

              // The full coordinate list and the bulk method must agree with the single point
              const T::Coordinate c =
                  compareList ? (*all)[static_cast<std::size_t>(j) * nx + i] : T::Coordinate(lon, lat);
              if (std::fabs(c.y() - lat) > 1e-6 || lonDiff(c.x(), lon) > 1e-6)
              {
                if (bad++ < 3)
                  BOOST_ERROR("grid point (" << i << "," << j << "): list " << c.y() << ","
                                             << c.x() << ", single " << lat << "," << lon);
              }
              if (hasBulk && (!found[k] || std::fabs(bulk[k].y() - lat) > 1e-6 ||
                              lonDiff(bulk[k].x(), lon) > 1e-6))
              {
                if (bad++ < 3)
                  BOOST_ERROR("grid point (" << i << "," << j << "): bulk " << bulk[k].y() << ","
                                             << bulk[k].x() << ", single " << lat << "," << lon);
              }

              // Inverse projection. Points at the poles have no unique longitude.
              if (std::fabs(lat) > 89.9)
                continue;
              double gi = -1;
              double gj = -1;
              ok = def->getGridPointByLatLonCoordinatesNoCache(lat, lon, gi, gj);
              bool same = ok && std::fabs(gi - i) < 1e-3 && std::fabs(gj - j) < 1e-3;
              if (ok && !same)
              {
                // A global grid may repeat the first meridian as its last column, either
                // grid point is then a correct answer
                double lat2 = 0;
                double lon2 = 0;
                const auto ri = static_cast<long>(std::lround(gi));
                const auto rj = static_cast<long>(std::lround(gj));
                same = (std::fabs(gi - ri) < 1e-3 && std::fabs(gj - rj) < 1e-3 && ri >= 0 &&
                        rj >= 0 && def->getGridLatLonCoordinatesByGridPoint(ri, rj, lat2, lon2) &&
                        std::fabs(lat2 - lat) < 1e-6 && lonDiff(lon2, lon) < 1e-6);
              }
              if (!same)
              {
                if (bad++ < 3)
                  BOOST_ERROR("latlon " << lat << "," << lon << " -> grid point " << gi << ","
                                        << gj << " (ok=" << ok << "), expected " << i << ","
                                        << j);
              }
            }
            BOOST_TEST(bad == 0U, bad << " checks failed for " << points.size() << " points");
          }
        };

        if (def2)
          check(def2, "GRIB2");
        if (def1)
          check(def1, "GRIB1");
      });
}
