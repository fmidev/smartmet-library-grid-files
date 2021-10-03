#include "StretchedRotatedLatLonImpl.h"
#include <macgyver/Exception.h>
#include "../../common/CoordinateConversions.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

StretchedRotatedLatLonImpl::StretchedRotatedLatLonImpl()
{
  mGridProjection = T::GridProjectionValue::StretchedRotatedLatLon;
}





/*! \brief The copy constructor of the class. */

StretchedRotatedLatLonImpl::StretchedRotatedLatLonImpl(const StretchedRotatedLatLonImpl& other)
:StretchedRotatedLatLon(other)
{
}





/*! \brief The destructor of the class. */

StretchedRotatedLatLonImpl::~StretchedRotatedLatLonImpl()
{
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* StretchedRotatedLatLonImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new StretchedRotatedLatLonImpl(*this);
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

void StretchedRotatedLatLonImpl::read(MemoryReader& memoryReader)
{
  try
  {
    StretchedRotatedLatLon::read(memoryReader);
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

T::Coordinate_svec StretchedRotatedLatLonImpl::getGridOriginalCoordinates() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return coordinateList;

    uint ni = (*mLatLon.getGrid()->getNi());
    uint nj = (*mLatLon.getGrid()->getNj());

    auto latitudeOfFirstGridPoint = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint());
    auto longitudeOfFirstGridPoint = C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint());
    auto iDirectionIncrement = C_DOUBLE(*mLatLon.getIDirectionIncrement());
    auto jDirectionIncrement = C_DOUBLE(*mLatLon.getJDirectionIncrement());

    unsigned char scanningMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanningMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    coordinateList->reserve(ni*nj);

    double y = latitudeOfFirstGridPoint;
    for (uint j=0; j < nj; j++)
    {
      double x = longitudeOfFirstGridPoint;
      //if (longitudeOfFirstGridPoint >= 180000000)
      //  x = longitudeOfFirstGridPoint - 360000000;

      for (uint i=0; i < ni; i++)
      {
        double cx = getLongitude(x/1000000);
        double cy = y/1000000;
        T::Coordinate coord(cx,cy);
        coordinateList->emplace_back(coord);
        x += iDirectionIncrement;
      }
      y += jDirectionIncrement;
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

T::Dimensions StretchedRotatedLatLonImpl::getGridDimensions() const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return T::Dimensions();

    return T::Dimensions(*mLatLon.getGrid()->getNi(), *mLatLon.getGrid()->getNj());
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

bool StretchedRotatedLatLonImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
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

bool StretchedRotatedLatLonImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    uint ni = (*mLatLon.getGrid()->getNi());
    uint nj = (*mLatLon.getGrid()->getNj());

    double iDirectionIncrement = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    double jDirectionIncrement = C_DOUBLE(*mLatLon.getJDirectionIncrement()) / 1000000;

    unsigned char scanningMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanningMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    double latitudeOfFirstGridPoint = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000 + 90;
    double longitudeOfFirstGridPoint = C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;

    if (longitudeOfFirstGridPoint > 180)
      longitudeOfFirstGridPoint -= 360;

    longitudeOfFirstGridPoint += 360;

    double aLat = y + 90;
    double aLon = x;

    if (aLon > 180)
      aLon -= 360;

    aLon += 360;

    double latDiff = aLat - latitudeOfFirstGridPoint;
    double lonDiff = aLon - longitudeOfFirstGridPoint;

    double i = lonDiff / iDirectionIncrement;
    double j = latDiff / jDirectionIncrement;

    grid_i = i;
    grid_j = j;

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(ni) ||  j > C_DOUBLE(nj))
      return false;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void StretchedRotatedLatLonImpl::initSpatialReference()
{
  try
  {
    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = getMajorAxis(mEarthShape);
    double dfFlattening = getFlattening(mEarthShape);
    double dfInvFlattening = 0;
    if (dfFlattening != 0)
      dfInvFlattening = 1/dfFlattening;

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);

    mSpatialReference.SetProjParm("latitude_of_origin",C_DOUBLE(*mRotation.getLatitudeOfSouthernPole())/1000000);
    mSpatialReference.SetProjParm("central_meridian",C_DOUBLE(*mRotation.getLongitudeOfSouthernPole())/1000000);
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

    uint ni = (*mLatLon.getGrid()->getNi());
    double iDirectionIncrement = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    double len = (ni+1)* iDirectionIncrement;

    if (len >= 360)
      mGlobal = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}

