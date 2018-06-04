#include "MercatorImpl.h"
#include "../../common/Exception.h"

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

MercatorImpl::MercatorImpl()
{
  try
  {
    mGridProjection = T::GridProjection::Mercator;
    mSr_mercator = NULL;
    mCt_latlon2mercator = NULL;
    mCt_mercator2latlon = NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The copy constructor of the class. */

MercatorImpl::MercatorImpl(const MercatorImpl& other)
:Mercator(other)
{
  try
  {
    mSr_mercator = NULL;
    mCt_latlon2mercator = NULL;
    mCt_mercator2latlon = NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The destructor of the class. */

MercatorImpl::~MercatorImpl()
{
  try
  {
    if (mSr_mercator != NULL)
      mSpatialReference.DestroySpatialReference(mSr_mercator);

    if (mCt_latlon2mercator != NULL)
      OCTDestroyCoordinateTransformation(mCt_latlon2mercator);

    if (mCt_mercator2latlon != NULL)
      OCTDestroyCoordinateTransformation(mCt_mercator2latlon);
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

void MercatorImpl::read(MemoryReader& memoryReader)
{
  try
  {
    Mercator::read(memoryReader);
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

T::Coordinate_vec MercatorImpl::getGridCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    uint ni = (uint)mNi;
    uint nj = (uint)mNj;

    double latitudeOfFirstGridPoint = (double)mGridArea.getLatitudeOfFirstGridPoint() / 1000;
    double longitudeOfFirstGridPoint = (double)mGridArea.getLongitudeOfFirstGridPoint() / 1000;

    double di = (double)mDiInMetres;
    double dj = (double)mDjInMetres;

    unsigned char scanningMode = (unsigned char)mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      di = -di;

    if ((scanningMode & 0x40) == 0)
      dj = -dj;

    mCt_latlon2mercator->Transform(1,&longitudeOfFirstGridPoint,&latitudeOfFirstGridPoint);

    double y = latitudeOfFirstGridPoint;
    for (uint j=0; j < nj; j++)
    {
      double x = longitudeOfFirstGridPoint;

      for (uint i=0; i < ni; i++)
      {
        T::Coordinate coord(x,y);
        coordinateList.push_back(coord);
        x += di;
      }
      y += dj;
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

T::Dimensions_opt MercatorImpl::getGridDimensions() const
{
  try
  {
    uint ni = (uint)mNi;
    uint nj = (uint)mNj;
    return T::Dimensions{ni,nj};
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

bool MercatorImpl::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  try
  {
    uint ni = (uint)mNi;
    uint nj = (uint)mNj;

    double latitudeOfFirstGridPoint = (double)mGridArea.getLatitudeOfFirstGridPoint() / 1000;
    double longitudeOfFirstGridPoint = (double)mGridArea.getLongitudeOfFirstGridPoint() / 1000;

    double di = (double)mDiInMetres;
    double dj = (double)mDjInMetres;

    unsigned char scanningMode = (unsigned char)mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      di = -di;

    if ((scanningMode & 0x40) == 0)
      dj = -dj;

    double aX = x;
    double aY = y;
    double fX = longitudeOfFirstGridPoint;
    double fY = latitudeOfFirstGridPoint;

    mCt_latlon2mercator->Transform(1,&fX,&fY);

    double xDiff = aX - fX;
    double yDiff = aY - fY;

    double i = xDiff / di;
    double j = yDiff / dj;

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





bool MercatorImpl::reverseXDirection() const
{
  try
  {
    unsigned char scanMode = (unsigned char)mScanningMode.getScanningMode();

    if ((scanMode & 0x80) != 0)
      return true;

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool MercatorImpl::reverseYDirection() const
{
  try
  {
    unsigned char scanMode = (unsigned char)mScanningMode.getScanningMode();

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

void MercatorImpl::initSpatialReference()
{
  try
  {
    auto dfCenterLat = mGridArea.getLatitudeOfFirstGridPoint();
    auto dfCenterLong = mGridArea.getLongitudeOfFirstGridPoint();

    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = 6371229;
    double dfInvFlattening = 0.0;

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


    // ### Set the projection and the linear units for the projection.

    dfCenterLat /= 1000;
    dfCenterLong /= 1000;
    double dfFalseEasting = 0.0;
    double dfFalseNorthing = 0.0;

    mSpatialReference.SetMercator(dfCenterLat,dfCenterLong,1.0,dfFalseEasting,dfFalseNorthing);
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
    mSr_mercator = mSpatialReference.Clone();

    mCt_latlon2mercator = OGRCreateCoordinateTransformation(&sr_latlon,mSr_mercator);
    if (mCt_latlon2mercator == NULL)
      throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");

    mCt_mercator2latlon = OGRCreateCoordinateTransformation(mSr_mercator,&sr_latlon);
    if (mCt_mercator2latlon == NULL)
      throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
