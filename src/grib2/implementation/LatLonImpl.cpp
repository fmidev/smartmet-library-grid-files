#include "LatLonImpl.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include "common/Dimensions.h"
#include "grid/PrintOptions.h"

#include <iostream>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

LatLonImpl::LatLonImpl()
{
  mGridProjection = T::GridProjection::LatLon;
}





/*! \brief The copy constructor of the class. */

LatLonImpl::LatLonImpl(const LatLonImpl& other)
:LatLon(other)
{
}





/*! \brief The destructor of the class. */

LatLonImpl::~LatLonImpl()
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

void LatLonImpl::read(MemoryReader& memoryReader)
{
  try
  {
    LatLon::read(memoryReader);
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

T::Coordinate_vec LatLonImpl::getGridCoordinates() const
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





T::Coordinate_vec LatLonImpl::getGridLatLonCoordinates() const
{
  try
  {
    return getGridCoordinates();
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

T::Dimensions_opt LatLonImpl::getGridDimensions() const
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





/*! \brief This method converts the latlon coordinates to the original coordinates.

    The original coordinates are returned in the 'x' and 'y' parameters. In this
    case the latlon coordinates are the same as the original coordinates.

        \param lat     The latitude.
        \param lon     The longitude.
        \param x       The x-coordinate of the original coordinates.
        \param y       The y-coordinate of the original coordinates.
*/

bool LatLonImpl::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  try
  {
    x = lon;
    y = lat;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method converts the original coordinates to the latlon coordinates.
    The latlon coordinates are returned in the 'lat' and 'lon' parameters. In this
    case the original coordinates are the same as the latlon coordinates.

        \param x       The original x-coordinate.
        \param y       The original y-coordinate.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool LatLonImpl::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  try
  {
    lat = x;
    lon = y;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method return the latlon coordinates of the give grid point.

        \param grid_i  The grid i-position.
        \param grid_j  The grid j-position.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool LatLonImpl::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  try
  {
    uint ni = (uint)(*mLatLon.getGrid()->getNi());
    uint nj = (uint)(*mLatLon.getGrid()->getNj());

    if ((double)grid_i > (double)ni)
      return false;

    if ((double)grid_j > (double)nj)
      return false;

    double latitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint());
    double longitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint());
    double iDirectionIncrement = (double)(*mLatLon.getIDirectionIncrement());
    double jDirectionIncrement = (double)(*mLatLon.getJDirectionIncrement());

    unsigned char scanningMode = (unsigned char)(mLatLon.getScanningMode()->getScanningMode());

    if ((scanningMode & 0x80) != 0)
      iDirectionIncrement = -iDirectionIncrement;

    if ((scanningMode & 0x40) == 0)
      jDirectionIncrement = -jDirectionIncrement;

    double y = latitudeOfFirstGridPoint + grid_j * jDirectionIncrement;
    double x = longitudeOfFirstGridPoint + grid_i * iDirectionIncrement;

    if (longitudeOfFirstGridPoint >= 180000000)
      x = longitudeOfFirstGridPoint - 360000000 + grid_i * iDirectionIncrement;

    lon = x/1000000;
    lat = y/1000000;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool LatLonImpl::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  try
  {
    return getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,y,x);
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

bool LatLonImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
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

bool LatLonImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
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

    double latitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000;
    double longitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;

    if (longitudeOfFirstGridPoint >= 180)
      longitudeOfFirstGridPoint -= 360;

    double aLat = y;
    double aLon = x;

    if (aLon < longitudeOfFirstGridPoint)
      aLon += 360;

    double latDiff = aLat - latitudeOfFirstGridPoint;
    double lonDiff = aLon - longitudeOfFirstGridPoint;

    double i = lonDiff / iDirectionIncrement;
    double j = latDiff / jDirectionIncrement;


    //printf("YY %f,%f   %f %f\n",latitudeOfFirstGridPoint,longitudeOfFirstGridPoint,iDirectionIncrement,jDirectionIncrement);

    //printf("%f,%f (%f,%f) => %f,%f (%f,%f) \n",y,x,aLat,aLon,i,j,latDiff,lonDiff);

    if (i < 0 ||  j < 0  ||  i >= (double)ni ||  j >= (double)nj)
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

void LatLonImpl::initSpatialReference()
{
  try
  {
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


    // ### Test if the grid is global

    uint ni = (uint)(*mLatLon.getGrid()->getNi());
    double iDirectionIncrement = (double)(*mLatLon.getIDirectionIncrement()) / 1000000;
    double len = (ni+1)* iDirectionIncrement;

    if (len >= 360)
      mGlobal = true;
    else
    if (!mLatLon.getGrid()->getLongitudeOfFirstGridPoint()  &&  !mLatLon.getGrid()->getLongitudeOfLastGridPoint())
    {
      double longitudeOfFirstGridPoint = (double)(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
      double longitudeOfLastGridPoint = (double)(*mLatLon.getGrid()->getLongitudeOfLastGridPoint()) / 1000000;

      if ((longitudeOfLastGridPoint-longitudeOfFirstGridPoint+2*iDirectionIncrement) >= 360)
        mGlobal = true;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void LatLonImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    LatLon::print(stream,level,optionFlags);

    stream << space(level+1) << "LatLonImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";

      T::Coordinate_vec coordinateList = getGridCoordinates();

      // ### Printing coordinates close to the grid corners.

      int nx = (int)(*mLatLon.getGrid()->getNi());
      int ny = (int)(*mLatLon.getGrid()->getNj());

      char str[200];
      uint c = 0;
      for (int y=0; y < ny; y++)
      {
        for (int x=0; x < nx; x++)
        {
          if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
          {
            T::Coordinate coord = coordinateList.at(c);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}
}
