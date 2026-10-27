// NetCDF-4 (HDF5) files must be rejected with a clear error: the NetCDF reader
// only supports the classic formats. GRIB messages inside an HDF5 container are
// still found.

#define BOOST_TEST_MODULE NetCdfFileTypeTest
#include <boost/test/included/unit_test.hpp>

#include "TestCommon.h"
#include "../src/grid/GridFile.h"
#include "../src/identification/GridDef.h"

#include <fstream>
#include <iterator>
#include <string>

using namespace SmartMet;
using namespace GridTest;

namespace
{
const std::string GRIB = testData("grib/ecgmta/ecgmta_pot_prcnt.grib");
const std::string HDF5_FIXTURE = testData(
    "qdtools/input/netcdf/"
    "C3S-SOILMOISTURE-L3S-SSMV-PASSIVE-DAILY-20160831000000-TCDR-v201706.0.0.nc");

// A file starting with the HDF5 signature
std::string hdf5Header()
{
  std::string data(512, '\0');
  const unsigned char sig[] = {0x89, 'H', 'D', 'F', '\r', '\n', 0x1A, '\n'};
  std::copy(std::begin(sig), std::end(sig), data.begin());
  return data;
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

BOOST_AUTO_TEST_CASE(hdf5_signature_is_rejected, *fixtures({CONFIG}))
{
  requireFixture(CONFIG);
  TempFile tmp(hdf5Header(), "netcdf4");
  BOOST_TEST(rejected(tmp.name()));
}

BOOST_AUTO_TEST_CASE(grib_inside_hdf5_container_is_found, *fixtures({CONFIG, GRIB}))
{
  requireFixture(CONFIG);
  requireFixture(GRIB);
  std::ifstream in(GRIB, std::ios::binary);
  std::string grib((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
  TempFile tmp(hdf5Header() + grib, "hdf5grib");

  withFmiErrors(
      [&]
      {
        GRID::GridFile gf;
        gf.read(tmp.name());
        BOOST_TEST(gf.getNumberOfMessages() > 0U);
      });
}

BOOST_AUTO_TEST_CASE(netcdf4_file_is_rejected, *fixtures({CONFIG, HDF5_FIXTURE}))
{
  requireFixture(CONFIG);
  requireFixture(HDF5_FIXTURE);
  BOOST_TEST(rejected(HDF5_FIXTURE));
}
