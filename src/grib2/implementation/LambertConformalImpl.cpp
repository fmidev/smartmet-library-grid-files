#include "LambertConformalImpl.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include "grid/PrintOptions.h"

#include <iostream>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

LambertConformalImpl::LambertConformalImpl()
{
  try
  {
    mGridProjection = T::GridProjection::LambertConformal;
    mSr_lambertConformal = NULL;
    mCt_latlon2lambert = NULL;
    mCt_lambert2latlon = NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The copy constructor of the class. */

LambertConformalImpl::LambertConformalImpl(const LambertConformalImpl& other):LambertConformal(other)
{
  try
  {
    mSr_lambertConformal = NULL;
    mCt_latlon2lambert = NULL;
    mCt_lambert2latlon = NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The destructor of the class. */

LambertConformalImpl::~LambertConformalImpl()
{
  try
  {
    if (mSr_lambertConformal != NULL)
      mSpatialReference.DestroySpatialReference(mSr_lambertConformal);

    if (mCt_lambert2latlon == NULL)
      OCTDestroyCoordinateTransformation(mCt_lambert2latlon);

    if (mCt_latlon2lambert != NULL)
      OCTDestroyCoordinateTransformation(mCt_latlon2lambert);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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

void LambertConformalImpl::read(MemoryReader& memoryReader)
{
  try
  {
    LambertConformal::read(memoryReader);
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

T::Coordinate_vec LambertConformalImpl::getGridCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    if (mCt_latlon2lambert == NULL  ||  mCt_lambert2latlon == NULL)
      return coordinateList;

    uint nx = (uint)(*mNx);
    uint ny = (uint)(*mNy);

    coordinateList.reserve(nx*ny);

    double latitudeOfFirstGridPoint = (double)(*mLatitudeOfFirstGridPoint) / 1000000;
    double longitudeOfFirstGridPoint = (double)(*mLongitudeOfFirstGridPoint) / 1000000;

    double dx = (double)(*mDx) / 1000;
    double dy = (double)(*mDy) / 1000;

    unsigned char scanningMode = (unsigned char)(mScanningMode.getScanningMode());
    if ((scanningMode & 0x80) != 0)
      dx = -dx;

    if ((scanningMode & 0x40) == 0)
      dy = -dy;

    mCt_latlon2lambert->Transform(1,&longitudeOfFirstGridPoint,&latitudeOfFirstGridPoint);

    double y = latitudeOfFirstGridPoint;
    for (uint j=0; j < ny; j++)
    {
      double x = longitudeOfFirstGridPoint;

      for (uint i=0; i < nx; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList.push_back(coord);
        x += dx;
      }
      y += dy;
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

T::Dimensions_opt LambertConformalImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions{*mNx, *mNy};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool LambertConformalImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    if (mCt_latlon2lambert == NULL  ||  mCt_lambert2latlon == NULL)
      return false;

    uint nx = (uint)(*mNx);
    uint ny = (uint)(*mNy);

    if (grid_i < 0  ||  grid_j < 0  ||  grid_i >= nx  ||  grid_j >= ny)
      return false;

    double latitudeOfFirstGridPoint = (double)(*mLatitudeOfFirstGridPoint) / 1000000;
    double longitudeOfFirstGridPoint = (double)(*mLongitudeOfFirstGridPoint) / 1000000;

    double dx = (double)(*mDx) / 1000;
    double dy = (double)(*mDy) / 1000;

    unsigned char scanningMode = (unsigned char)(mScanningMode.getScanningMode());
    if ((scanningMode & 0x80) != 0)
      dx = -dx;

    if ((scanningMode & 0x40) == 0)
      dy = -dy;

    mCt_latlon2lambert->Transform(1,&longitudeOfFirstGridPoint,&latitudeOfFirstGridPoint);

    y = latitudeOfFirstGridPoint + grid_j * dy;
    x = longitudeOfFirstGridPoint = grid_i * dx;

    return true;
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

bool LambertConformalImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    T::Coordinate_vec coordinateList;

    if (mCt_latlon2lambert == NULL  ||  mCt_lambert2latlon == NULL)
      return false;


    uint nx = (uint)(*mNx);
    uint ny = (uint)(*mNy);

    double latitudeOfFirstGridPoint = (double)(*mLatitudeOfFirstGridPoint) / 1000000;
    double longitudeOfFirstGridPoint = (double)(*mLongitudeOfFirstGridPoint) / 1000000;

    double dx = (double)(*mDx) / 1000;
    double dy = (double)(*mDy) / 1000;

    unsigned char scanningMode = (unsigned char)(mScanningMode.getScanningMode());
    if ((scanningMode & 0x80) != 0)
      dx = -dx;

    if ((scanningMode & 0x40) == 0)
      dy = -dy;

    double fX = longitudeOfFirstGridPoint;
    double fY = latitudeOfFirstGridPoint;

    mCt_latlon2lambert->Transform(1,&fX,&fY);

    double xDiff = x - fX;
    double yDiff = y - fY;

    double i = xDiff / dx;
    double j = yDiff / dy;

    if (i < 0 ||  j < 0  ||  i >= (double)nx ||  j > (double)ny)
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





bool LambertConformalImpl::reverseXDirection() const
{
  try
  {
    unsigned char scanMode = (unsigned char)(mScanningMode.getScanningMode());

    if ((scanMode & 0x80) != 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool LambertConformalImpl::reverseYDirection() const
{
  try
  {
    unsigned char scanMode = (unsigned char)(mScanningMode.getScanningMode());

    if ((scanMode & 0x40) == 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void LambertConformalImpl::initSpatialReference()
{
  try
  {
    // ### Check that we have all necessary values needed by this method.

    auto dfStdP1 = mLatin1;
    if (!dfStdP1)
      throw SmartMet::Spine::Exception(BCP,"The 'latin1' value is missing!");

    auto dfStdP2 = mLatin2;
    if (!dfStdP2)
      throw SmartMet::Spine::Exception(BCP,"The 'latin2' value is missing!");

    auto dfCenterLat = mLaD;
    if (!dfCenterLat)
      throw SmartMet::Spine::Exception(BCP,"The 'laD' value is missing!");

    auto dfCenterLong = mLoV;
    if (!dfCenterLong)
      throw SmartMet::Spine::Exception(BCP,"The 'loV' value is missing!");

    auto southPoleLon = mLongitudeOfSouthernPole;
    auto southPoleLat = mLatitudeOfSouthernPole;

    if (!southPoleLon)
      southPoleLon = 0;

    if (!southPoleLat)
      southPoleLat = -90 * 1000000;

    //if ((*southPoleLon != 0) || (*southPoleLat != (-90 * 1000000)))
    //  throw SmartMet::Spine::Exception(BCP,"A projection with a rotated pole is not supported!");


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


    // ### Set the projection and the linear units for the projection.

    double stdP1 = *dfStdP1 / 1000000;
    double stdP2 = *dfStdP2 / 1000000;
    double centerLat = *dfCenterLat / 1000000;
    double centerLon = *dfCenterLong / 1000000;
    double dfFalseEasting = 0.0;
    double dfFalseNorthing = 0.0;

    mSpatialReference.SetLCC(stdP1,stdP2,centerLat,centerLon,dfFalseEasting,dfFalseNorthing);
    mSpatialReference.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);


    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      SmartMet::Spine::Exception exception(BCP,"The spatial reference is not valid!");
      exception.addParameter("ErrorCode",std::to_string(errorCode));
      throw exception;
    }


    // ### Creating converters

    OGRSpatialReference sr_latlon;
    sr_latlon.importFromEPSG(4326);
    mSr_lambertConformal = mSpatialReference.Clone();

    mCt_latlon2lambert = OGRCreateCoordinateTransformation(&sr_latlon,mSr_lambertConformal);
    if (mCt_latlon2lambert == NULL)
      throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");

    mCt_lambert2latlon = OGRCreateCoordinateTransformation(mSr_lambertConformal,&sr_latlon);
    if (mCt_lambert2latlon == NULL)
      throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");
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

void LambertConformalImpl::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    LambertConformal::print(stream,level,optionFlags);

    stream << space(level+1) << "LambertConformalImpl\n";

    if (optionFlags & GRID::PrintFlag::coordinates)
    {
      stream << space(level+1) << "- Coordinates (of the grid corners):\n";
      T::Coordinate_vec coordinateList = getGridCoordinates();

      // ### Printing coordinates close to the grid corners.

      int nx = (int)(*mNx);
      int ny = (int)(*mNy);

      char str[200];
      uint c = 0;
      for (int y=0; y < ny; y++)
      {
        for (int x=0; x < nx; x++)
        {
          if ((y < 3  ||  y >= ny-3)  &&  (x < 3  ||  x >= nx-3))
          {
            T::Coordinate coord = coordinateList.at(c);

            if (mCt_lambert2latlon)
            {
              double lon = coord.x();
              double lat = coord.y();
              if (mCt_lambert2latlon->Transform(1,&lon,&lat))
              {
                sprintf(str,"* [%03d,%03d] %f,%f => %f,%f",x,y,coord.x(),coord.y(),lon,lat);
                stream << space(level+2) << str << "\n";
              }
            }
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
