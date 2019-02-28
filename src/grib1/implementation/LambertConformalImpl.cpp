#include "LambertConformalImpl.h"
#include "../../common/Exception.h"

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

LambertConformalImpl::LambertConformalImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::LambertConformal;
    mSr_lambertConformal = nullptr;
    mCt_latlon2lambert = nullptr;
    mCt_lambert2latlon = nullptr;

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

LambertConformalImpl::LambertConformalImpl(const LambertConformalImpl& other):LambertConformal(other)
{
  try
  {
    mSr_lambertConformal = nullptr;
    mCt_latlon2lambert = nullptr;
    mCt_lambert2latlon = nullptr;
    mDx = other.mDx;
    mDy = other.mDy;
    mStartX = other.mStartX;
    mStartY = other.mStartY;
    mInitialized = other.mInitialized;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

LambertConformalImpl::~LambertConformalImpl()
{
  try
  {
    if (mSr_lambertConformal != nullptr)
      mSpatialReference.DestroySpatialReference(mSr_lambertConformal);

    if (mCt_lambert2latlon == nullptr)
      OCTDestroyCoordinateTransformation(mCt_lambert2latlon);

    if (mCt_latlon2lambert != nullptr)
      OCTDestroyCoordinateTransformation(mCt_latlon2lambert);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void LambertConformalImpl::init() const
{
  try
  {
    if (mInitialized)
      return;

    if (mCt_latlon2lambert == nullptr)
      return;

    double latitudeOfFirstGridPoint = C_DOUBLE(mLatitudeOfFirstGridPoint) / 1000;
    double longitudeOfFirstGridPoint = C_DOUBLE(mLongitudeOfFirstGridPoint) / 1000;

    mDx = C_DOUBLE(mDxInMetres);
    mDy = C_DOUBLE(mDyInMetres);

    unsigned char scanningMode = mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      mDx = -mDx;

    if ((scanningMode & 0x40) == 0)
      mDy = -mDy;

    mStartX = longitudeOfFirstGridPoint;
    mStartY = latitudeOfFirstGridPoint;

    mCt_latlon2lambert->Transform(1,&mStartX,&mStartY);

    mInitialized = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The method returns a duplicate of the current object. */

GridDefinition* LambertConformalImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new LambertConformalImpl(*this);
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

void LambertConformalImpl::read(MemoryReader& memoryReader)
{
  try
  {
    LambertConformal::read(memoryReader);
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

T::Coordinate_vec LambertConformalImpl::getGridCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    if (mCt_latlon2lambert == nullptr  ||  mCt_lambert2latlon == nullptr)
      return coordinateList;

    if (!mInitialized)
      init();

    coordinateList.reserve(mNx*mNy);

    double y = mStartY;
    for (uint j=0; j < mNy; j++)
    {
      double x = mStartX;

      for (uint i=0; i < mNx; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList.push_back(coord);
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





std::string LambertConformalImpl::getGridGeometryString() const
{
  try
  {
    char buf[1000];

    double y = C_DOUBLE(mLatitudeOfFirstGridPoint) / 1000;
    double x = C_DOUBLE(mLongitudeOfFirstGridPoint) / 1000;
    double loV = C_DOUBLE(mLoV) / 1000;
    double latin1 = C_DOUBLE(mLatin1) / 1000;
    double latin2 = C_DOUBLE(mLatin2) / 1000;
    double sx = C_DOUBLE(mLongitudeOfSouthernPole) / 1000;
    double sy = C_DOUBLE(mLatitudeOfSouthernPole) / 1000;
    double dx = C_DOUBLE(mDxInMetres);
    double dy = C_DOUBLE(mDyInMetres);

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


    sprintf(buf,"%d;id;name;%d;%d;%f;%f;%f;%f;%s;%f;%f;%f;%f;%f;%f;description",
      T::GridProjectionValue::LambertConformal,mNx,mNy,x,y,fabs(dx),fabs(dy),sm,loV,latin1,latin2,sx,sy,60.0);

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

T::Dimensions LambertConformalImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions(mNx, mNy);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool LambertConformalImpl::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  try
  {
    if (mCt_latlon2lambert == nullptr  ||  mCt_lambert2latlon == nullptr)
      return false;

    if (grid_i < 0  ||  grid_j < 0  ||  grid_i >= mNx  ||  grid_j >= mNy)
      return false;

    if (!mInitialized)
      init();

    y = mStartY + grid_j * mDy;
    x = mStartX + grid_i * mDx;

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

bool LambertConformalImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    if (mCt_latlon2lambert == nullptr  ||  mCt_lambert2latlon == nullptr)
      return false;

    if (!mNx || !mNy)
      return false;

    if (!mInitialized)
      init();

    double xDiff = (round(x*100) - round(mStartX*100)) / 100;
    double yDiff = (round(y*100) - round(mStartY*100)) / 100;

    double i = xDiff / mDx;
    double j = yDiff / mDy;

    if (i < 0 ||  j < 0  ||  i >= C_DOUBLE(mNx) ||  j > C_DOUBLE(mNy))
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





bool LambertConformalImpl::reverseXDirection() const
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool LambertConformalImpl::reverseYDirection() const
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void LambertConformalImpl::initSpatialReference()
{
  try
  {
    auto dfStdP1 = mLatin1;
    auto dfStdP2 = mLatin2;
    auto dfCenterLat = mLatin1;  // ????
    auto dfCenterLong = mLoV;
    //auto southPoleLon = mLongitudeOfSouthernPole;
    //auto southPoleLat = mLatitudeOfSouthernPole;

    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = 6371229;
    double dfInvFlattening = 0.0;

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


    // ### Set the projection and the linear units for the projection.

    double stdP1 = C_DOUBLE(dfStdP1) / 1000;
    double stdP2 = C_DOUBLE(dfStdP2) / 1000;
    double centerLat = C_DOUBLE(dfCenterLat) / 1000;
    double centerLon = C_DOUBLE(dfCenterLong) / 1000;
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

    // ### Coordinate converters

    OGRSpatialReference sr_latlon;
    sr_latlon.importFromEPSG(4326);
    mSr_lambertConformal = mSpatialReference.Clone();

    mCt_latlon2lambert = OGRCreateCoordinateTransformation(&sr_latlon,mSr_lambertConformal);
    if (mCt_latlon2lambert == nullptr)
      throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");

    mCt_lambert2latlon = OGRCreateCoordinateTransformation(mSr_lambertConformal,&sr_latlon);
    if (mCt_lambert2latlon == nullptr)
      throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
