#include "LambertAzimuthalEqualAreaImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/CoordinateConversions.h"
#include "../../grid/PrintOptions.h"
#include "../Properties.h"

#include <iostream>

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

LambertAzimuthalEqualAreaImpl::LambertAzimuthalEqualAreaImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::LambertAzimuthalEqualArea;
    mInitialized = false;
    mDxx = 0;
    mDyy = 0;
    mStartX = 0;
    mStartY = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

LambertAzimuthalEqualAreaImpl::LambertAzimuthalEqualAreaImpl(const LambertAzimuthalEqualAreaImpl& other)
:LambertAzimuthalEqualArea(other)
{
}





/*! \brief The destructor of the class. */

LambertAzimuthalEqualAreaImpl::~LambertAzimuthalEqualAreaImpl()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* LambertAzimuthalEqualAreaImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new LambertAzimuthalEqualAreaImpl(*this);
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

void LambertAzimuthalEqualAreaImpl::read(MemoryReader& memoryReader)
{
  try
  {
    LambertAzimuthalEqualArea::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void LambertAzimuthalEqualAreaImpl::init() const
{
  try
  {
    if (!mNumberOfPointsAlongXAxis || !mNumberOfPointsAlongYAxis)
      return;

    if (mInitialized)
      return;

    double latitudeOfFirstGridPoint = C_DOUBLE(*mLatitudeOfFirstGridPoint) / 1000000;
    double longitudeOfFirstGridPoint = getLongitude(C_DOUBLE(*mLongitudeOfFirstGridPoint) / 1000000);

    mDxx = C_DOUBLE(*mXDirectionGridLengthInMillimetres) / 1000;
    mDyy = C_DOUBLE(*mYDirectionGridLengthInMillimetres) / 1000;

    unsigned char scanningMode = mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      mDxx = -mDxx;

    if ((scanningMode & 0x40) == 0)
      mDyy = -mDyy;

    mStartX = longitudeOfFirstGridPoint;
    mStartY = latitudeOfFirstGridPoint;

    convert(&mLatlonSpatialReference,&mSpatialReference,1,&mStartX,&mStartY);

    mInitialized = true;
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

T::Coordinate_svec LambertAzimuthalEqualAreaImpl::getGridOriginalCoordinates() const
{
  try
  {
    T::Coordinate_svec coordinateList(new T::Coordinate_vec());

    if (!mNumberOfPointsAlongXAxis || !mNumberOfPointsAlongYAxis)
      return coordinateList;

    if (!mInitialized)
      init();

    uint nx = (*mNumberOfPointsAlongXAxis);
    uint ny = (*mNumberOfPointsAlongYAxis);

    coordinateList->reserve(nx*ny);

    double y = mStartY;
    for (uint j=0; j < ny; j++)
    {
      double x = mStartX;

      for (uint i=0; i < nx; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList->push_back(coord);
        x += mDxx;
      }
      y += mDyy;
    }

    return coordinateList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

std::string LambertAzimuthalEqualAreaImpl::getGridGeometryString() const
{
  try
  {
    char buf[1000];

    double y = C_DOUBLE(*mLatitudeOfFirstGridPoint) / 1000000;
    double x = C_DOUBLE(*mLongitudeOfFirstGridPoint) / 1000000;
    uint nx = (*mNumberOfPointsAlongXAxis);
    uint ny = (*mNumberOfPointsAlongYAxis);
    double dx = C_DOUBLE(*mXDirectionGridLengthInMillimetres) / 1000;
    double dy = C_DOUBLE(*mYDirectionGridLengthInMillimetres) / 1000;
    double sp = C_DOUBLE(*mStandardParallelInMicrodegrees) / 1000000;
    double cl = C_DOUBLE(*mCentralLongitudeInMicrodegrees) / 1000000;


    unsigned char scanningMode = mScanningMode.getScanningMode();

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


    sprintf(buf,"%d;id;name;%d;%d;%.6f;%.6f;%.6f;%.6f;%s;%.6f;%.6f;description",
      T::GridProjectionValue::LambertAzimuthalEqualArea,nx,ny,x,y,fabs(dx),fabs(dy),sm,sp,cl);

    return std::string(buf);
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

T::Dimensions LambertAzimuthalEqualAreaImpl::getGridDimensions() const
{
  try
  {
    if (!mNumberOfPointsAlongXAxis || !mNumberOfPointsAlongYAxis)
      return T::Dimensions();

    return T::Dimensions(*mNumberOfPointsAlongXAxis,*mNumberOfPointsAlongYAxis);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::size_t LambertAzimuthalEqualAreaImpl::getGridColumnCount() const
{
  try
  {
    return *mNumberOfPointsAlongXAxis;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




std::size_t LambertAzimuthalEqualAreaImpl::getGridRowCount() const
{
  try
  {
    return *mNumberOfPointsAlongYAxis;
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

bool LambertAzimuthalEqualAreaImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    // TODO: We should probably do our own implementation instead of using the parent implementation,
    // which might be slow or does not even work if the spatial reference is not correctly initialized.

    return GridDefinition::getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool LambertAzimuthalEqualAreaImpl::getGridMetricCellSize(double& width,double& height) const
{
  try
  {
    width = C_DOUBLE(*mXDirectionGridLengthInMillimetres) / 1000;
    height = C_DOUBLE(*mYDirectionGridLengthInMillimetres) / 1000;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool LambertAzimuthalEqualAreaImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    if (!mNumberOfPointsAlongXAxis || !mNumberOfPointsAlongYAxis)
      return false;

    if (grid_i < 0  ||  grid_j < 0  ||  grid_i >= (*mNumberOfPointsAlongXAxis)  ||  grid_j >= (*mNumberOfPointsAlongYAxis))
      return false;

    if (!mInitialized)
      init();

    y = mStartY + grid_j * mDyy;
    x = mStartX + grid_i * mDxx;

    return true;
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

bool LambertAzimuthalEqualAreaImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (!mNumberOfPointsAlongXAxis || !mNumberOfPointsAlongYAxis)
      return false;

    if (!mInitialized)
      init();

    double xDiff = (round(x*100) - round(mStartX*100)) / 100;
    double yDiff = (round(y*100) - round(mStartY*100)) / 100;

    double i = xDiff / mDxx;
    double j = yDiff / mDyy;

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(*mNumberOfPointsAlongXAxis) ||  j > C_DOUBLE(*mNumberOfPointsAlongYAxis))
      return false;

    grid_i = i;
    grid_j = j;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool LambertAzimuthalEqualAreaImpl::reverseXDirection() const
{
  try
  {
    unsigned char scanMode = mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool LambertAzimuthalEqualAreaImpl::reverseYDirection() const
{
  try
  {
    unsigned char scanMode = mScanningMode.getScanningMode();

    if ((scanMode & 0x40) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void LambertAzimuthalEqualAreaImpl::initSpatialReference()
{
  try
  {
    // ### Check that we have all necessary values needed by this method.

    auto dfCenterLat = mStandardParallelInMicrodegrees;
    if (!dfCenterLat)
      throw Fmi::Exception(BCP,"The 'standardParallelInMicrodegrees' value is missing!");

    auto dfCenterLong = mCentralLongitudeInMicrodegrees;
    if (!dfCenterLong)
      throw Fmi::Exception(BCP,"The 'centralLongitudeInMicrodegrees' value is missing!");


    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = getMajorAxis(mEarthShape);
    double dfInvFlattening = getFlattening(mEarthShape);

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


    // ### Set the projection and the linear units for the projection.

    *dfCenterLat /= 1000000;
    *dfCenterLong /= 1000000;
    double dfFalseEasting = 0.0;
    double dfFalseNorthing = 0.0;

    mSpatialReference.SetLAEA(*dfCenterLat,*dfCenterLong,dfFalseEasting,dfFalseNorthing);
    mSpatialReference.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
    mSpatialReference.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      Fmi::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }
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

void LambertAzimuthalEqualAreaImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    LambertAzimuthalEqualArea::print(stream,level,optionFlags);

    stream << space(level+1) << "LambertAzimuthalEqualAreaImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";

      T::Coordinate_svec coordinateList = getGridOriginalCoordinates();

      // ### Printing coordinates close to the grid corners.

      if (!mNumberOfPointsAlongXAxis || !mNumberOfPointsAlongYAxis)
        return;

      int nx = C_INT(*mNumberOfPointsAlongXAxis);
      int ny = C_INT(*mNumberOfPointsAlongYAxis);

      if (coordinateList && coordinateList->size() == (std::size_t)(nx*ny))
      {
        char str[200];
        uint c = 0;
        for (int y=0; y < ny; y++)
        {
          for (int x=0; x < nx; x++)
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
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}
}
