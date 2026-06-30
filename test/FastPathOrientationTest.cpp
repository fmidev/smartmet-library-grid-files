// Regression test for the full-grid geometry "direct copy" fast path orientation.
//
// Message::getGridValueVectorByGeometry returns the original grid by a direct copy of
// the message values when the requested geometryId matches the message geometry. For a
// grid stored north-to-south (reverseYDirection()==true, e.g. ECMWF) the fast path
// reverses the data rows to south-to-north. The grid.llbox / grid.bbox latitudes it
// reports MUST then also run south-to-north (first latitude < last latitude); otherwise
// the download encoder builds a north-to-south GRIB header (jScansPositively=0) over
// south-to-north data and the field comes out vertically flipped.
//
// This guards the 26.6.30 fix: the 26.6.24 grid.llbox longitude-wrap fix (a4385d2 /
// ecafd1b) had dropped the reverseYDirection latitude reordering, regressing the
// orientation while leaving the longitude handling correct.
//
// The test needs the ECMWF global thunderstorm-probability grid from smartmet-test-data
// and a grid-files configuration with FMI geometry definitions (provided by the
// smartmet-engine-grid-test fixtures). It SKIPS (does not fail) when either is absent so
// it never breaks builds on hosts without the test fixtures installed.

#include "../src/grid/GridFile.h"
#include "../src/grid/Message.h"
#include "../src/common/AttributeList.h"
#include "../src/identification/GridDef.h"

#include <sys/stat.h>
#include <cstdio>
#include <cstdlib>
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

std::vector<double> parseCsv(const char *s)
{
  std::vector<double> v;
  if (!s)
    return v;
  std::string str(s);
  size_t pos = 0;
  while (pos <= str.size())
  {
    size_t comma = str.find(',', pos);
    if (comma == std::string::npos)
      comma = str.size();
    v.push_back(std::atof(str.substr(pos, comma - pos).c_str()));
    if (comma == str.size())
      break;
    pos = comma + 1;
  }
  return v;
}
}  // namespace

int main()
{
  if (!exists(CONFIG) || !exists(GRIB))
  {
    printf("SKIP FastPathOrientationTest: test fixtures not installed\n");
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
      fprintf(stderr, "FAIL FastPathOrientationTest: no messages in grib\n");
      return 1;
    }

    GRID::Message *msg = gf.getMessageByIndex(0);
    T::Dimensions d = msg->getGridDimensions();
    T::GeometryId geomId = msg->getGridGeometryId();

    if (!msg->reverseYDirection())
    {
      fprintf(stderr,
              "FAIL FastPathOrientationTest: expected a north-to-south stored grid "
              "(reverseYDirection); fixture changed?\n");
      return 1;
    }

    // Drive the direct-copy fast path: crs=data + matching geometryId.
    T::AttributeList attr;
    attr.setAttribute("grid.crs", "data");
    attr.setAttribute("grid.geometryId", std::to_string((int)geomId).c_str());

    T::ParamValue_vec values;
    msg->getGridValueVectorByGeometry(attr, values);

    if (values.size() != (size_t)d.nx() * d.ny())
    {
      fprintf(stderr,
              "FAIL FastPathOrientationTest: fast path returned %zu values, expected %u\n",
              values.size(), d.nx() * d.ny());
      return 1;
    }

    auto b = parseCsv(attr.getAttributeValue("grid.llbox"));
    if (b.size() != 4)
    {
      fprintf(stderr, "FAIL FastPathOrientationTest: could not parse grid.llbox\n");
      return 1;
    }

    const double firstLat = b[1];
    const double lastLat = b[3];

    if (firstLat >= lastLat)
    {
      fprintf(stderr,
              "FAIL FastPathOrientationTest: grid.llbox latitudes run north-to-south "
              "(%.3f -> %.3f) while the data rows were flipped to south-to-north; the "
              "download output would be vertically flipped\n",
              firstLat, lastLat);
      return 1;
    }

    printf("PASS FastPathOrientationTest: geometryId=%d %ux%u, grid.llbox lat %.3f -> %.3f "
           "(south-to-north), consistent with the row-flipped data\n",
           (int)geomId, d.nx(), d.ny(), firstLat, lastLat);
    return 0;
  }
  catch (const std::exception &e)
  {
    fprintf(stderr, "FAIL FastPathOrientationTest: exception: %s\n", e.what());
    return 1;
  }
}
