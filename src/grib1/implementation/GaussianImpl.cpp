#include "GaussianImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../grid/GaussianLatitudeCache.h"
#include "../../grid/PrintOptions.h"

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

GaussianImpl::GaussianImpl()
{
  mGridProjection = T::GridProjectionValue::Gaussian;
}





/*! \brief The copy constructor of the class. */

GaussianImpl::GaussianImpl(const GaussianImpl& other)
:Gaussian(other)
{
}





/*! \brief The destructor of the class. */

GaussianImpl::~GaussianImpl()
{
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* GaussianImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new GaussianImpl(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GaussianImpl::read(MemoryReader& memoryReader)
{
  try
  {
    Gaussian::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_svec GaussianImpl::getGridOriginalCoordinates() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    uint ni = mNi;
    uint nj = mNj;
    long n = mN;

    double longitudeOfFirstGridPoint = mGridArea.getLongitudeOfFirstGridPoint();
    double longitudeOfLastGridPoint = mGridArea.getLongitudeOfLastGridPoint();

    if (longitudeOfLastGridPoint < 0)
      longitudeOfLastGridPoint += 360000;

    if (ni == 0xFFFF)
      ni = getGridColumnCount();

    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / C_DOUBLE(ni-1);

    unsigned char scanningMode = mScanningMode.getScanningMode();

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    double *lats = GRID::gaussianLatitudeCache.getLatitudes(nj,n);

    coordinateList->reserve(ni*nj);

    for (uint j=0; j < nj; j++)
    {
      double y = lats[j];
      double x = longitudeOfFirstGridPoint;

      for (uint i=0; i < ni; i++)
      {
        double cx = x/1000;
        double cy = y;
        T::Coordinate coord(cx,cy);
        coordinateList->emplace_back(coord);
        x += iDirectionIncrement;
      }
    }

    return coordinateList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions GaussianImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions(mNi,mNj);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method calculates the estimated grid position by using the latlon coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

        \param lat     The latitude.
        \param lon     The longitude.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool GaussianImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    return getGridPointByOriginalCoordinates(lon,lat,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method calculates the estimated grid position by using the original coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

      \param x       The original x-coordinate.
      \param y       The original y-coordinate.
      \param grid_i  The returned grid i-position.
      \param grid_j  The returned grid j-position.
      \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool GaussianImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    uint ni = mNi;
    uint nj = mNj;
    long n = (long)mN;

    double longitudeOfFirstGridPoint = C_DOUBLE(mGridArea.getLongitudeOfFirstGridPoint()) / 1000;
    double longitudeOfLastGridPoint = C_DOUBLE(mGridArea.getLongitudeOfLastGridPoint()) / 1000;

    if (longitudeOfFirstGridPoint < 0)
      longitudeOfFirstGridPoint += 360;

    if (longitudeOfLastGridPoint < 0)
      longitudeOfLastGridPoint += 360;

    if (ni == 0xFFFF)
      ni = getGridColumnCount();

    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / C_DOUBLE(ni-1);

    unsigned char scanningMode = mScanningMode.getScanningMode();

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    double aLat = y + 90;
    double aLon = x;

    if (x < 0)
      aLon = x + 360;

    if (!mGlobal  &&  (aLon < longitudeOfFirstGridPoint || aLon > longitudeOfLastGridPoint))
      return false;

    double lonDiff = aLon - longitudeOfFirstGridPoint;
    double i = lonDiff / iDirectionIncrement;

    if (i < 0 || i >= C_DOUBLE(ni))
      return false;

    double latLow = 0;
    double latHigh = 0;

    int t = GRID::gaussianLatitudeCache.getClosestLatitudes(nj,n,y,latLow,latHigh);
    if (t < 0)
      return false;

    latLow += 90;
    latHigh += 90;

    double latDiff = aLat-latLow;
    double j = t + latDiff / (latHigh-latLow);

    grid_i = i;
    grid_j = j;

    if (j < 0  ||  j > C_DOUBLE(nj))
      return false;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void GaussianImpl::initSpatialReference()
{
  try
  {
    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor =  6367470;
    double dfInvFlattening = 0.0;

    ResolutionFlagsSettings *rflags = mGridArea.getResolutionFlags();
    if (rflags != nullptr)
    {
      dfSemiMajor = getMajorAxis(rflags->getResolutionAndComponentFlags());
      double dfFlattening = getFlattening(rflags->getResolutionAndComponentFlags());
      if (dfFlattening != 0)
        dfInvFlattening = 1/dfFlattening;
    }

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);
    mSpatialReference.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      Fmi::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }


    // ### Test if the grid is global

    uint ni = mNi;
    if (ni == 0xFFFF)
      ni = getGridColumnCount();

    double longitudeOfFirstGridPoint = C_DOUBLE(mGridArea.getLongitudeOfFirstGridPoint()) / 1000;
    double longitudeOfLastGridPoint = C_DOUBLE(mGridArea.getLongitudeOfLastGridPoint()) / 1000;

    if (longitudeOfFirstGridPoint < 0)
      longitudeOfFirstGridPoint += 360;

    if (longitudeOfLastGridPoint < 0)
      longitudeOfLastGridPoint += 360;

    double iDirectionIncrement = (longitudeOfLastGridPoint - longitudeOfFirstGridPoint) / C_DOUBLE(ni-1);

    if ((ni*iDirectionIncrement) >= 360)
      mGlobal = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GaussianImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    Gaussian::print(stream,level,optionFlags);

    stream << space(level+1) << "GaussianImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";

      T::Coordinate_svec coordinateList = getGridOriginalCoordinates();

      // ### Printing coordinates close to the grid corners.

      uint nx = mNi;
      uint ny = mNj;
      if (nx == 0xFFFF)
        nx = getGridColumnCount();

      uint c = 0;

      char str[200];
      for (uint y=0; y < ny; y++)
      {
        for (uint x=0; x < nx; x++)
        {
          if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
          {
            T::Coordinate coord = coordinateList->at(c);

            sprintf(str,"* [%03d,%03d] %f,%f",x,y,coord.x(),coord.y());
            stream << space(level+2) << str << "\n";
          }
          c++;
        }
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}  // namespace GRIB1
}  // namespace SmartMet
