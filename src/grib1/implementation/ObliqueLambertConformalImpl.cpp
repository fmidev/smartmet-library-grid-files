#include "ObliqueLambertConformalImpl.h"
#include "../../common/Exception.h"

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

ObliqueLambertConformalImpl::ObliqueLambertConformalImpl()
{
  try
  {
    mGridProjection = T::GridProjectionValue::ObliqueLambertConformal;
    mSr_lambertConformal = nullptr;
    mCt_latlon2lambert = nullptr;
    mCt_lambert2latlon = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The copy constructor of the class. */

ObliqueLambertConformalImpl::ObliqueLambertConformalImpl(const ObliqueLambertConformalImpl& other)
:ObliqueLambertConformal(other)
{
  try
  {
    mSr_lambertConformal = nullptr;
    mCt_latlon2lambert = nullptr;
    mCt_lambert2latlon = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The destructor of the class. */

ObliqueLambertConformalImpl::~ObliqueLambertConformalImpl()
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





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* ObliqueLambertConformalImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new ObliqueLambertConformalImpl(*this);
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

void ObliqueLambertConformalImpl::read(MemoryReader& memoryReader)
{
  try
  {
    ObliqueLambertConformal::read(memoryReader);
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

T::Coordinate_vec ObliqueLambertConformalImpl::getGridCoordinates() const
{
  try
  {
    T::Coordinate_vec coordinateList;

    uint nx = mNx;
    uint ny = mNy;

    double latitudeOfFirstGridPoint = C_DOUBLE(mLatitudeOfFirstGridPoint) / 1000;
    double longitudeOfFirstGridPoint = C_DOUBLE(mLongitudeOfFirstGridPoint) / 1000;

    double dx = C_DOUBLE(mDxInMetres);
    double dy = C_DOUBLE(mDyInMetres);

    unsigned char scanningMode = mScanningMode.getScanningMode();
    if ((scanningMode & 0x80) != 0)
      dx = -dx;

    if ((scanningMode & 0x40) == 0)
      dy = -dy;

    mCt_latlon2lambert->Transform(1,&longitudeOfFirstGridPoint,&latitudeOfFirstGridPoint);

    coordinateList.reserve(nx*ny);

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions ObliqueLambertConformalImpl::getGridDimensions() const
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





/*! \brief This method calculates the estimated grid position by using the latlon coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.

        \param lat     The latitude.
        \param lon     The longitude.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool ObliqueLambertConformalImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    // TODO: We should probably do our own implementation instead of using the parent implementation,
    // which might be slow or does not even work if the spatial reference is not correctly initialized.

    return GridDefinition::getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void ObliqueLambertConformalImpl::initSpatialReference()
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
    double dfSemiMajor =  6367470;
    double dfInvFlattening = 0.0;

    dfSemiMajor = getMajorAxis(mResolutionFlags.getResolutionAndComponentFlags());
    dfInvFlattening = getFlattening(mResolutionFlags.getResolutionAndComponentFlags());

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
