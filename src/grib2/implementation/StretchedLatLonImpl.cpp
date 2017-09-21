#include "StretchedLatLonImpl.h"
#include "common/Exception.h"
#include "grid/Dimensions.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

StretchedLatLonImpl::StretchedLatLonImpl()
{
  mGridProjection = T::GridProjection::StretchedLatLon;
}





/*! \brief The copy constructor of the class. */

StretchedLatLonImpl::StretchedLatLonImpl(const StretchedLatLonImpl& other)
:StretchedLatLon(other)
{
}





/*! \brief The destructor of the class. */

StretchedLatLonImpl::~StretchedLatLonImpl()
{
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void StretchedLatLonImpl::read(MemoryReader& memoryReader)
{
  try
  {
    StretchedLatLon::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the first and the last latlon coordinates used in the grid.

        \param firstLat   The returned latitude of the top-left corner.
        \param firstLon   The returned longitude of the top-left corner.
        \param lastLat    The returned latitude of the bottom-right corner.
        \param lastLon    The returned longitude of the bottom-right corner.
*/

void StretchedLatLonImpl::getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const
{
  try
  {
    firstLat = (double)(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000;
    firstLon = (double)(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
    lastLat = (double)(*mLatLon.getGrid()->getLatitudeOfLastGridPoint()) / 1000000;
    lastLon = (double)(*mLatLon.getGrid()->getLongitudeOfLastGridPoint()) / 1000000;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_vec StretchedLatLonImpl::getGridCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    uint ni = (uint)(*mLatLon.getGrid()->getNi());
    uint nj = (uint)(*mLatLon.getGrid()->getNj());

    double latitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint());
    double longitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint());
    double iDirectionIncrement = (double)(*mLatLon.getIDirectionIncrement());
    double jDirectionIncrement = (double)(*mLatLon.getJDirectionIncrement());

    unsigned char scanningMode = (unsigned char)(mLatLon.getScanningMode()->getScanningMode());

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanningMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;


    double y = latitudeOfFirstGridPoint;
    for (uint j=0; j < nj; j++)
    {
      double x = longitudeOfFirstGridPoint;
      if (longitudeOfFirstGridPoint >= 180000000)
        x = longitudeOfFirstGridPoint - 360000000;

      for (uint i=0; i < ni; i++)
      {
        double cx = x/1000000;
        double cy = y/1000000;
        T::Coordinate coord(cx,cy);
        coordinateList.push_back(coord);
        x += iDirectionIncrement;
      }
      y += jDirectionIncrement;
    }

    return coordinateList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions_opt StretchedLatLonImpl::getGridDimensions() const
{
  try
  {
    const auto defs = mLatLon.getGrid();
    uint nx = *defs->getNi();
    uint ny = *defs->getNj();
    return T::Dimensions{nx, ny};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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

bool StretchedLatLonImpl::getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    return getGridPointByOriginalCoordinates(lon,lat,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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

bool StretchedLatLonImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    uint ni = (uint)(*mLatLon.getGrid()->getNi());
    uint nj = (uint)(*mLatLon.getGrid()->getNj());

    double iDirectionIncrement = (double)(*mLatLon.getIDirectionIncrement()) / 1000000;
    double jDirectionIncrement = (double)(*mLatLon.getJDirectionIncrement()) / 1000000;

    unsigned char scanningMode = (unsigned char)(mLatLon.getScanningMode()->getScanningMode());

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanningMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    double latitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000 + 90;
    double longitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;

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

    if (i < 0 ||  j < 0  ||  i >= (double)ni ||  j > (double)nj)
      return false;

    grid_i = i;
    grid_j = j;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void StretchedLatLonImpl::initSpatialReference()
{
  try
  {
    // TODO: This is probably not correct. It is directly copied from LatLonImpl


    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = 0.0;
    double dfInvFlattening = 0.0;

    auto radius = mEarthShape.getScaledValueOfRadiusOfSphericalEarth();

    if ((!radius) || (*radius == 0))
    {
      T::UInt32_opt majorAxis(0);
      majorAxis = mEarthShape.getScaledValueOfEarthMajorAxis();

      T::UInt32_opt minorAxis(0);
      minorAxis = mEarthShape.getScaledValueOfEarthMinorAxis();

      if (!(majorAxis  &&  minorAxis && *majorAxis > 0 && *minorAxis > 0))
      {
        // TODO: Use code table 3.2 based values
        //
        dfSemiMajor = dfInvFlattening = 0.0;
        dfSemiMajor = 6371229;
      }
      else
      {
        if (majorAxis)
          dfSemiMajor = *majorAxis;

        if (minorAxis)
          dfInvFlattening = 1.0 / (1.0 - (*minorAxis / dfSemiMajor));
      }
    }
    else
    {
      dfSemiMajor = *radius;
      dfInvFlattening = 0.0;
    }

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      SmartMet::Spine::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}
}
