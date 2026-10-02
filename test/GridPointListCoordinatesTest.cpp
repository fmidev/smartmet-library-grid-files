// Regression test for Message::getGridLatLonCoordinatesByGridPointList.
//
// The bulk method must return exactly the same coordinates as calling
// getGridLatLonCoordinatesByGridPoint() for each point. getGridValueListByPolygon (and hence
// getGridValueListByCircle) uses the bulk method, which transforms all the points at once
// instead of doing a separate cache lookup and coordinate transformation for each point.
//
// The test also checks that getGridValueListByCircle returns values for every point of the
// circle, i.e. that getGridValuesByPointList returns exactly one value per grid point, and that
// a repeated circle query served from the circle point cache gives the same result.
//
// The test needs the ECMWF global thunderstorm-probability grid from smartmet-test-data and the
// FMI geometry definitions in ../cfg.

#define BOOST_TEST_MODULE GridPointListCoordinatesTest
#include <boost/test/included/unit_test.hpp>

#include "TestCommon.h"
#include "../src/grid/GridFile.h"
#include "../src/grid/Message.h"
#include "../src/common/CoordinateConversions.h"
#include "../src/identification/GridDef.h"

#include <string>
#include <vector>

using namespace SmartMet;
using namespace GridTest;

namespace
{
const std::string GRIB = testData("grib/ecgmta/ecgmta_pot_prcnt.grib");
}  // namespace

BOOST_AUTO_TEST_CASE(point_list_and_circle, *fixtures({CONFIG, GRIB}))
{
  requireFixture(CONFIG);
  requireFixture(GRIB);

  withFmiErrors(
      []
      {
        Identification::gridDef.init(CONFIG);

        GRID::GridFile gf;
        gf.read(GRIB);
        BOOST_TEST_REQUIRE(gf.getNumberOfMessages() > 0);

        GRID::Message *msg = gf.getMessageByIndex(0);
        T::Dimensions d = msg->getGridDimensions();
        int nx = d.nx();
        int ny = d.ny();

        // Points all over the grid, including the borders and points outside the grid

        std::vector<T::Point> points;
        for (int j = -1; j <= ny; j += 37)
          for (int i = -1; i <= nx; i += 41)
            points.emplace_back(i, j);
        points.emplace_back(nx - 1, ny - 1);
        points.emplace_back(nx, 0);
        points.emplace_back(0, ny);

        T::Coordinate_vec coordinates;
        std::vector<bool> found;
        msg->getGridLatLonCoordinatesByGridPointList(points, coordinates, found);

        BOOST_TEST_REQUIRE(coordinates.size() == points.size());
        BOOST_TEST_REQUIRE(found.size() == points.size());

        for (std::size_t t = 0; t < points.size(); t++)
        {
          double lat = 0;
          double lon = 0;
          bool ok = msg->getGridLatLonCoordinatesByGridPoint(points[t].x(), points[t].y(), lat, lon);
          BOOST_TEST_INFO("point (" << points[t].x() << "," << points[t].y() << ")");
          BOOST_TEST(ok == found[t]);
          if (ok && found[t])
          {
            BOOST_TEST(lon == coordinates[t].x());
            BOOST_TEST(lat == coordinates[t].y());
          }
        }

        // Every circle point must carry its own value and coordinates

        const double lon0 = 25.0;
        const double lat0 = 60.0;
        const double radius = 200;

        T::GridValueList list;
        msg->getGridValueListByCircle(
            T::CoordinateTypeValue::LATLON_COORDINATES, lon0, lat0, radius, list);

        uint len = list.getLength();
        BOOST_TEST_REQUIRE(len > 0U);

        for (uint t = 0; t < len; t++)
        {
          T::GridValue rec;
          list.getGridValueByIndex(t, rec);
          BOOST_TEST_INFO("circle point (" << rec.mX << "," << rec.mY << ")");
          BOOST_TEST(latlon_distance(lat0, lon0, rec.mY, rec.mX) <= radius);
        }

        // The second call uses the cached circle points and must give exactly the same result

        T::GridValueList list2;
        msg->getGridValueListByCircle(
            T::CoordinateTypeValue::LATLON_COORDINATES, lon0, lat0, radius, list2);

        BOOST_TEST_REQUIRE(list2.getLength() == len);

        for (uint t = 0; t < len; t++)
        {
          T::GridValue rec1;
          T::GridValue rec2;
          list.getGridValueByIndex(t, rec1);
          list2.getGridValueByIndex(t, rec2);
          BOOST_TEST_INFO("cached circle point " << t);
          BOOST_TEST(rec1.mX == rec2.mX);
          BOOST_TEST(rec1.mY == rec2.mY);
          BOOST_TEST(rec1.mValue == rec2.mValue);
        }

        BOOST_TEST(GRID::circlePointCache_stats.hits > 0U, "circle point cache was not used");
      });
}
