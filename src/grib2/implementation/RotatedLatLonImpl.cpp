#include "RotatedLatLonImpl.h"
#include "../../common/Exception.h"
#include "../../common/GeneralFunctions.h"
#include "../../common/CoordinateConversions.h"
#include "../../common/Dimensions.h"
#include "../../grid/PrintOptions.h"
#include <iostream>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

RotatedLatLonImpl::RotatedLatLonImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::RotatedLatLon;
    mNi = 0;
    mNj = 0;
    mStartY = 0;
    mStartX = 0;
    mDx = 0;
    mDy = 0;
    mSouthPoleLat = 0;
    mSouthPoleLon = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy constructor of the class. */

RotatedLatLonImpl::RotatedLatLonImpl(const RotatedLatLonImpl& other)
:RotatedLatLon(other)
{
  try
  {
    mGridProjection = T::GridProjectionValue::RotatedLatLon;
    mNi = other.mNi;
    mNj = other.mNj;
    mStartY = other.mStartY;
    mStartX = other.mStartX;
    mDx = other.mDx;
    mDy = other.mDy;
    mSouthPoleLat = other.mSouthPoleLat;
    mSouthPoleLon = other.mSouthPoleLon;
    mInitialized = other.mInitialized;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

RotatedLatLonImpl::~RotatedLatLonImpl()
{
}





void RotatedLatLonImpl::init() const
{
  try
  {
    if (mInitialized)
      return;

    mNi = (*mLatLon.getGrid()->getNi());
    mNj = (*mLatLon.getGrid()->getNj());
    mStartY = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000;
    mStartX = getLongitude(C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000);
    mDx = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    mDy = C_DOUBLE(*mLatLon.getJDirectionIncrement()) / 1000000;
    mSouthPoleLat = C_DOUBLE(*mRotation.getLatitudeOfSouthernPole())/1000000;
    mSouthPoleLon = C_DOUBLE(*mRotation.getLongitudeOfSouthernPole())/1000000;

    unsigned char scanMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanMode & 0x80) != 0)
      mDx = -mDx;

    if ((scanMode & 0x40) == 0)
      mDy = -mDy;

    mInitialized = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The method returns a duplicate of the current object. */

GridDefinition* RotatedLatLonImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new RotatedLatLonImpl(*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

void RotatedLatLonImpl::read(MemoryReader& memoryReader)
{
  try
  {
    RotatedLatLon::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.

         \return   The grid coordinates.
*/

T::Coordinate_vec RotatedLatLonImpl::getGridCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return coordinateList;

    if (!mInitialized)
      init();

    if (mNi == 0 || mNj == 0)
      return coordinateList;

    coordinateList.reserve(mNi*mNj);

    double y = mStartY;
    for (uint j=0; j < mNj; j++)
    {
      double x = mStartX;
      for (uint i=0; i < mNi; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList.push_back(T::Coordinate(x,y));
        x += mDx;
      }
      y += mDy;
    }

    return coordinateList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Coordinate_vec RotatedLatLonImpl::getGridLatLonCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return coordinateList;

    if (!mInitialized)
      init();

    if (mNi == 0 || mNj == 0)
      return coordinateList;

    coordinateList.reserve(mNi*mNj);

    double y = mStartY;
    for (uint j=0; j < mNj; j++)
    {
      double x = mStartX;

      for (uint i=0; i < mNi; i++)
      {
        double lat = 0;
        double lon = 0;

        rotatedLatlon_to_latlon(y,x,mSouthPoleLat,mSouthPoleLon,lat,lon);

        coordinateList.push_back(T::Coordinate(lon,lat));
        x += mDx;
      }
      y += mDy;
    }

    return coordinateList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method return the latlon coordinates of the give grid point.

        \param grid_i  The grid i-position.
        \param grid_j  The grid j-position.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool RotatedLatLonImpl::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (!mInitialized)
      init();

    if (grid_i > mNi)
      return false;

    if (grid_j > mNj)
      return false;

    double rotated_lat = mStartY + grid_j * mDy;
    double rotated_lon = mStartX + grid_i * mDx;

    rotatedLatlon_to_latlon(rotated_lat,rotated_lon,mSouthPoleLat,mSouthPoleLon,lat,lon);

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool RotatedLatLonImpl::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (!mInitialized)
      init();

    if (grid_i > C_DOUBLE(mNi))
      return false;

    if (grid_j > C_DOUBLE(mNj))
      return false;

    double rotated_lat = mStartY + grid_j * mDy;
    double rotated_lon = mStartX + grid_i * mDx;

    rotatedLatlon_to_latlon(rotated_lat,rotated_lon,mSouthPoleLat,mSouthPoleLon,lat,lon);

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool RotatedLatLonImpl::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (!mInitialized)
      init();

    if (grid_i > mNi)
      return false;

    if (grid_j > mNj)
      return false;

    y = mStartY + grid_j * mDy;
    x = mStartX + grid_i * mDx;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool RotatedLatLonImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (!mInitialized)
      init();

    if (grid_i > C_DOUBLE(mNi))
      return false;

    if (grid_j > C_DOUBLE(mNj))
      return false;

    y = mStartY + grid_j * mDy;
    x = mStartX + grid_i * mDx;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string RotatedLatLonImpl::getGridGeometryString() const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return std::string("");

    char buf[1000];

    uint ni = (*mLatLon.getGrid()->getNi());
    uint nj = (*mLatLon.getGrid()->getNj());
    double y = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000;
    double x = C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
    double dx = C_DOUBLE(*mLatLon.getIDirectionIncrement());
    double dy = C_DOUBLE(*mLatLon.getJDirectionIncrement());

    double sy = C_DOUBLE(*mRotation.getLatitudeOfSouthernPole())/1000000;
    double sx = C_DOUBLE(*mRotation.getLongitudeOfSouthernPole())/1000000;

    double angle = C_DOUBLE(mRotation.getAngleOfRotation());

    unsigned char scanningMode = mLatLon.getScanningMode()->getScanningMode();

    char sm[100];
    char *p = sm;
    if ((scanningMode & 0x80) != 0)
    {
      dx = -dx;
      p += sprintf(p,"-x");
    }
    else
    {
      p += sprintf(p,"+x");
    }

    if ((scanningMode & 0x40) == 0)
    {
      dy = -dy;
      p += sprintf(p,"-y");
    }
    else
    {
      p += sprintf(p,"+y");
    }

    sprintf(buf,"%d;id;name;%u;%u;%f;%f;%f;%f;%s;%f;%f;%f;description",
        T::GridProjectionValue::RotatedLatLon,ni,nj,x,y,fabs(dx),fabs(dy),sm,sx,sy,angle);

    return std::string(buf);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions RotatedLatLonImpl::getGridDimensions() const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return T::Dimensions();

    return T::Dimensions(*mLatLon.getGrid()->getNi(), *mLatLon.getGrid()->getNj());
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method converts the latlon coordinates to the original coordinates.

    The original coordinates are returned in the 'x' and 'y' parameters.

        \param lat     The latitude.
        \param lon     The longitude.
        \param x       The x-coordinate of the original coordinates.
        \param y       The y-coordinate of the original coordinates.
*/

bool RotatedLatLonImpl::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  try
  {
    if (!mInitialized)
      init();

    latlon_to_rotatedLatlon(lat,lon,mSouthPoleLat,mSouthPoleLon,y,x);
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method converts the original coordinates to the latlon coordinates.
    The latlon coordinates are returned in the 'lat' and 'lon' parameters.

        \param x       The original x-coordinate.
        \param y       The original y-coordinate.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool RotatedLatLonImpl::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  try
  {
    if (!mInitialized)
      init();

    rotatedLatlon_to_latlon(y,x,mSouthPoleLat,mSouthPoleLon,lat,lon);

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

bool RotatedLatLonImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mInitialized)
      init();

    double aLon = getLongitude(x);
    if (aLon < mStartX)
      aLon += 360;

    double latDiff = (round(y*100) - round(mStartY*100)) / 100;
    double lonDiff = (round(aLon*100) - round(mStartX*100)) / 100;

    grid_i = lonDiff / mDx;
    grid_j = latDiff / mDy;

    if (grid_i < 0 ||  grid_j < 0  ||  grid_i >= C_DOUBLE(mNi) ||  grid_j >= C_DOUBLE(mNj))
      return false;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

bool RotatedLatLonImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    double x = 0, y = 0;
    getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);

    return getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool RotatedLatLonImpl::reverseXDirection() const
{
  try
  {
    unsigned char scanMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanMode & 0x80) != 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool RotatedLatLonImpl::reverseYDirection() const
{
  try
  {
    unsigned char scanMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanMode & 0x40) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void RotatedLatLonImpl::initSpatialReference()
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
        // dfSemiMajor = 6371229;
        dfSemiMajor = getMajorAxis(mEarthShape);
        dfInvFlattening = 0.0;
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

    //mSpatialReference.SetProjParm("latitude_of_origin",(double)(*rotation().latitudeOfSouthernPole())/1000000);
    //mSpatialReference.SetProjParm("central_meridian",(double)(*rotation().longitudeOfSouthernPole())/1000000);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      SmartMet::Spine::Exception exception(BCP,"The spatial reference is not valid!");
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void RotatedLatLonImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    RotatedLatLon::print(stream,level,optionFlags);

    stream << space(level+1) << "RotatedLatLonImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";

      T::Coordinate_vec coordinateList = getGridCoordinates();

      // ### Printing coordinates close to the grid corners.

      int nx = C_INT(*mLatLon.getGrid()->getNi());
      int ny = C_INT(*mLatLon.getGrid()->getNj());

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}
}
