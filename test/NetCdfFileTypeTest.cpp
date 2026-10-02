// NetCDF-4 (HDF5) files must be rejected with a clear error: the NetCDF reader
// only supports the classic formats. GRIB messages inside an HDF5 container are
// still found.

#include "../src/grid/GridFile.h"
#include <fstream>
#include <iterator>
#include <vector>
#include "../src/identification/GridDef.h"
#include <macgyver/Exception.h>

#include <sys/stat.h>
#include <cstdio>
#include <string>
#include <unistd.h>

using namespace SmartMet;

namespace
{
const char *CONFIG = "/usr/share/smartmet/test/grid/library/grid-files.conf";
const char *GRIB = "/usr/share/smartmet/test/data/grib/ecgmta/ecgmta_pot_prcnt.grib";
const char *HDF5_FIXTURE =
    "/usr/share/smartmet/test/data/qdtools/input/netcdf/"
    "C3S-SOILMOISTURE-L3S-SSMV-PASSIVE-DAILY-20160831000000-TCDR-v201706.0.0.nc";

bool exists(const char *path)
{
  struct stat st;
  return stat(path, &st) == 0 && st.st_size > 0;
}

bool rejected(const std::string &filename)
{
  try
  {
    GRID::GridFile gf;
    gf.read(filename);
    return false;
  }
  catch (...)
  {
    return true;
  }
}
}  // namespace

int main()
{
  if (!exists(CONFIG))
  {
    printf("SKIP NetCdfFileTypeTest: %s not installed\n", CONFIG);
    return 0;
  }

  try
  {
    Identification::gridDef.init(CONFIG);

    // A file with just the HDF5 signature
    char tmpname[] = "/tmp/netcdf4-XXXXXX";
    int fd = mkstemp(tmpname);
    if (fd < 0)
    {
      fprintf(stderr, "FAIL NetCdfFileTypeTest: cannot create a temporary file\n");
      return 1;
    }
    unsigned char data[512] = {0x89, 'H', 'D', 'F', '\r', '\n', 0x1A, '\n'};
    const bool written = (write(fd, data, sizeof(data)) == sizeof(data));
    close(fd);
    const bool ok = written && rejected(tmpname);
    unlink(tmpname);
    if (!ok)
    {
      fprintf(stderr, "FAIL NetCdfFileTypeTest: HDF5 signature was not rejected\n");
      return 1;
    }

    // An HDF5 container with GRIB messages inside it
    if (exists(GRIB))
    {
      std::ifstream in(GRIB, std::ios::binary);
      std::vector<char> grib((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
      char tmpname2[] = "/tmp/hdf5grib-XXXXXX";
      int fd2 = mkstemp(tmpname2);
      if (fd2 < 0)
      {
        fprintf(stderr, "FAIL NetCdfFileTypeTest: cannot create a temporary file\n");
        return 1;
      }
      bool ok2 = (write(fd2, data, sizeof(data)) == sizeof(data));
      ok2 = ok2 && (write(fd2, grib.data(), grib.size()) == static_cast<ssize_t>(grib.size()));
      close(fd2);
      std::size_t n = 0;
      if (ok2)
      {
        GRID::GridFile gf;
        gf.read(std::string(tmpname2));
        n = gf.getNumberOfMessages();
      }
      unlink(tmpname2);
      if (n == 0)
      {
        fprintf(stderr, "FAIL NetCdfFileTypeTest: GRIB inside an HDF5 container was not found\n");
        return 1;
      }
    }

    if (exists(HDF5_FIXTURE) && !rejected(HDF5_FIXTURE))
    {
      fprintf(stderr, "FAIL NetCdfFileTypeTest: NetCDF-4 file was not rejected\n");
      return 1;
    }

    printf("OK NetCdfFileTypeTest\n");
    return 0;
  }
  catch (...)
  {
    Fmi::Exception e(BCP, "NetCdfFileTypeTest failed", nullptr);
    e.printError();
    return 1;
  }
}
