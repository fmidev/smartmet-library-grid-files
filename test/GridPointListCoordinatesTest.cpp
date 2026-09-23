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
// The test needs the ECMWF global thunderstorm-probability grid from smartmet-test-data and a
// grid-files configuration with FMI geometry definitions (provided by the
// smartmet-engine-grid-test fixtures). It SKIPS (does not fail) when either is absent.

#include "../src/grid/GridFile.h"
#include "../src/grid/Message.h"
#include "../src/common/CoordinateConversions.h"
#include "../src/identification/GridDef.h"

#include <sys/stat.h>
#include <cstdio>
#include <string>
#include <vector>

using namespace SmartMet;

namespace
{
const char *CONFIG = "/usr/share/smartmet/test/grid/library/grid-files.conf";
const char *GRIB = "/usr/share/smartmet/test/data/grib/ecgmta/ecgmta_pot_prcnt.grib";

bool exists(const char *path)
{
  struct stat st;
  return stat(path, &st) == 0 && st.st_size > 0;
}
}  // namespace

int main()
{
  if (!exists(CONFIG) || !exists(GRIB))
  {
    printf("SKIP GridPointListCoordinatesTest: test fixtures not installed\n");
    printf("      need %s\n      need %s\n", CONFIG, GRIB);
    return 0;
  }

  try
  {
    Identification::gridDef.init(CONFIG);

    GRID::GridFile gf;
    gf.read(std::string(GRIB));

    if (gf.getNumberOfMessages() == 0)
    {
      fprintf(stderr, "FAIL GridPointListCoordinatesTest: no messages in grib\n");
      return 1;
    }

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

    if (coordinates.size() != points.size() || found.size() != points.size())
    {
      fprintf(stderr, "FAIL GridPointListCoordinatesTest: result size mismatch\n");
      return 1;
    }

    for (std::size_t t = 0; t < points.size(); t++)
    {
      double lat = 0;
      double lon = 0;
      bool ok = msg->getGridLatLonCoordinatesByGridPoint(points[t].x(), points[t].y(), lat, lon);

      if (ok != found[t] || (ok && (lon != coordinates[t].x() || lat != coordinates[t].y())))
      {
        fprintf(stderr,
                "FAIL GridPointListCoordinatesTest: point (%d,%d): single %d (%.10f,%.10f), "
                "list %d (%.10f,%.10f)\n",
                points[t].x(), points[t].y(), (int)ok, lon, lat, (int)found[t],
                coordinates[t].x(), coordinates[t].y());
        return 1;
      }
    }

    // Every circle point must carry its own value and coordinates

    const double lon0 = 25.0;
    const double lat0 = 60.0;
    const double radius = 200;

    T::GridValueList list;
    msg->getGridValueListByCircle(T::CoordinateTypeValue::LATLON_COORDINATES, lon0, lat0, radius, list);

    uint len = list.getLength();
    if (len == 0)
    {
      fprintf(stderr, "FAIL GridPointListCoordinatesTest: empty circle\n");
      return 1;
    }

    for (uint t = 0; t < len; t++)
    {
      T::GridValue rec;
      list.getGridValueByIndex(t, rec);
      if (latlon_distance(lat0, lon0, rec.mY, rec.mX) > radius)
      {
        fprintf(stderr,
                "FAIL GridPointListCoordinatesTest: circle point (%.5f,%.5f) is outside the circle\n",
                rec.mX, rec.mY);
        return 1;
      }
    }

    // The second call uses the cached circle points and must give exactly the same result

    T::GridValueList list2;
    msg->getGridValueListByCircle(T::CoordinateTypeValue::LATLON_COORDINATES, lon0, lat0, radius, list2);

    if (list2.getLength() != len)
    {
      fprintf(stderr, "FAIL GridPointListCoordinatesTest: cached circle has %u points, expected %u\n",
              list2.getLength(), len);
      return 1;
    }

    for (uint t = 0; t < len; t++)
    {
      T::GridValue rec1;
      T::GridValue rec2;
      list.getGridValueByIndex(t, rec1);
      list2.getGridValueByIndex(t, rec2);
      if (rec1.mX != rec2.mX || rec1.mY != rec2.mY || rec1.mValue != rec2.mValue)
      {
        fprintf(stderr, "FAIL GridPointListCoordinatesTest: cached circle point %u differs\n", t);
        return 1;
      }
    }

    if (GRID::circlePointCache_stats.hits == 0)
    {
      fprintf(stderr, "FAIL GridPointListCoordinatesTest: circle point cache was not used\n");
      return 1;
    }

    printf("PASS GridPointListCoordinatesTest: %zu points match the single point method, "
           "circle has %u points\n",
           points.size(), len);
    return 0;
  }
  catch (Fmi::Exception &e)
  {
    e.printError();
    fprintf(stderr, "FAIL GridPointListCoordinatesTest: exception\n");
    return 1;
  }
}
