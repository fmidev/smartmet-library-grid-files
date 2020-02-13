#include "LatLonImpl.h"
#include "../../common/Exception.h"
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/Dimensions.h"
#include "../../common/CoordinateConversions.h"
#include "../../grid/PrintOptions.h"

#include <iostream>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

LatLonImpl::LatLonImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::LatLon;
    mNi = 0;
    mNj = 0;
    mDx = 0;
    mDy = 0;
    mStartX = 0;
    mStartY = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy constructor of the class. */

LatLonImpl::LatLonImpl(const LatLonImpl& other)
:LatLon(other)
{
  try
  {
    mGridProjection = T::GridProjectionValue::LatLon;
    mNi = other.mNi;
    mNj = other.mNj;
    mDx = other.mDx;
    mDy = other.mDy;
    mStartX = other.mStartX;
    mStartY = other.mStartY;
    mInitialized = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

LatLonImpl::~LatLonImpl()
{
}





void LatLonImpl::init() const
{
  try
  {
    if (mInitialized)
      return;

    mNi = (*mLatLon.getGrid()->getNi());
    mNj = (*mLatLon.getGrid()->getNj());

    mStartY = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfFirstGridPoint()) / 1000000;
    mStartX = C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;

    double mEndY = C_DOUBLE(*mLatLon.getGrid()->getLatitudeOfLastGridPoint()) / 1000000;
    double mEndX = getLongitude(C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfLastGridPoint()) / 1000000);

    mDx = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    mDy = C_DOUBLE(*mLatLon.getJDirectionIncrement()) / 1000000;

    ResolutionSettings *rs = mLatLon.getGrid()->getResolution();
    if (rs != nullptr)
    {
      std::uint8_t flags = rs->getResolutionAndComponentFlags();
      if ((flags & 0x20) == 0  && mLatLon.getGrid()->getLongitudeOfLastGridPoint())
      {
        // i direction increment not given
        mDx = (mEndX-mStartX)/mNi;
      }

      if ((flags & 0x10) == 0 && mLatLon.getGrid()->getLatitudeOfLastGridPoint())
      {
        // j direction increment not given
        mDy = (mEndY-mStartY)/mNj;
      }
    }

    unsigned char scanningMode = mLatLon.getScanningMode()->getScanningMode();

    if ((scanningMode & 0x80) != 0)
      mDx = -mDx;

    if ((scanningMode & 0x40) == 0)
      mDy = -mDy;

    mInitialized = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* LatLonImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new LatLonImpl(*this);
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

void LatLonImpl::read(MemoryReader& memoryReader)
{
  try
  {
    LatLon::read(memoryReader);
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

T::Coordinate_vec LatLonImpl::getGridOriginalCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return coordinateList;

    if (!mInitialized)
      init();

    if (mNi == 0 ||  mNj == 0)
      return coordinateList;

    coordinateList.reserve(mNi*mNj);

    double y = mStartY;
    for (uint j=0; j < mNj; j++)
    {
      double x = mStartX;
      for (uint i=0; i < mNi; i++)
      {
        coordinateList.push_back(T::Coordinate(getLongitude(x),y));
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






/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_vec LatLonImpl::getGridLatLonCoordinates() const
{
  try
  {
    return getGridOriginalCoordinates();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string LatLonImpl::getGridGeometryString() const
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
    double dx = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    double dy = C_DOUBLE(*mLatLon.getJDirectionIncrement()) / 1000000;

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


    sprintf(buf,"%d;id;name;%u;%u;%.6f;%.6f;%.6f;%.6f;%s;description",
      T::GridProjectionValue::LatLon,ni,nj,x,y,fabs(dx),fabs(dy),sm);

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

T::Dimensions LatLonImpl::getGridDimensions() const
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





bool LatLonImpl::getGridMetricCellSize(double& width,double& height) const
{
  try
  {
    width = C_DOUBLE(*mLatLon.getIDirectionIncrement()) / 1000000;
    height = C_DOUBLE(*mLatLon.getJDirectionIncrement()) / 1000000;
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates by the given latlon position.

        \param lat  The latitude value.
        \param lon  The longitude value.
        \param x    The x-coordinate in the original projection is returned in this parameter.
        \param y    The y-coordinate in the original projection is returned in this parameter.
        \return     The method return true if the original coordinates were succesfully returned.
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates according the grid original (projection) coordinates.

        \param x       The x-coordinate in the original projection.
        \param y       The y-coordinate in the original projection.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    uint ni = (*mLatLon.getGrid()->getNi());
    uint nj = (*mLatLon.getGrid()->getNj());

    if (grid_i > ni)
      return false;

    if (grid_j > nj)
      return false;

    if (!mInitialized)
      init();

    lat = mStartY + grid_j * mDy;
    lon = getLongitude(mStartX + grid_i * mDx);

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool LatLonImpl::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (grid_i > C_DOUBLE(mNi))
      return false;

    if (grid_j > C_DOUBLE(mNj))
      return false;

    if (!mInitialized)
      init();

    lat = mStartY + grid_j * mDy;
    lon = getLongitude(mStartX + grid_i * mDx);

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool LatLonImpl::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  try
  {
    return getGridLatLonCoordinatesByGridPoint(grid_i,grid_j,y,x);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool LatLonImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    return getGridLatLonCoordinatesByGridPosition(grid_i,grid_j,y,x);
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

bool LatLonImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    return getGridPointByOriginalCoordinates(lon,lat,grid_i,grid_j);
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

bool LatLonImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
      return false;

    if (!mInitialized)
      init();

    double aLat = y;
    double aLon = x;

    if (aLon < mStartX)
      aLon += 360;

    double latDiff = aLat - mStartY;
    double lonDiff = aLon - mStartX;

    double i = lonDiff / mDx;
    double j = latDiff / mDy;

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(mNi) ||  j >= C_DOUBLE(mNj))
      return false;

    grid_i = i;
    grid_j = j;

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool LatLonImpl::reverseXDirection() const
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





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool LatLonImpl::reverseYDirection() const
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
    else
    if (!mLatLon.getGrid()->getLongitudeOfFirstGridPoint()  &&  !mLatLon.getGrid()->getLongitudeOfLastGridPoint())
    {
      double longitudeOfFirstGridPoint = C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfFirstGridPoint()) / 1000000;
      double longitudeOfLastGridPoint = C_DOUBLE(*mLatLon.getGrid()->getLongitudeOfLastGridPoint()) / 1000000;

      if ((longitudeOfLastGridPoint-longitudeOfFirstGridPoint+2*iDirectionIncrement) >= 360)
        mGlobal = true;
    }
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

void LatLonImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    LatLon::print(stream,level,optionFlags);

    stream << space(level+1) << "LatLonImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";

      T::Coordinate_vec coordinateList = getGridOriginalCoordinates();

      // ### Printing coordinates close to the grid corners.

      if (!mLatLon.getGrid()->getNi() || !mLatLon.getGrid()->getNj())
        return;

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
