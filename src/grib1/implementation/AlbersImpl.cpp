#include "AlbersImpl.h"
#include "../../common/Exception.h"

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

AlbersImpl::AlbersImpl()
{
  mGridProjection = T::GridProjectionValue::Albers;
}





/*! \brief The copy constructor of the class. */

AlbersImpl::AlbersImpl(const AlbersImpl& other)
:Albers(other)
{
}





/*! \brief The destructor of the class. */

AlbersImpl::~AlbersImpl()
{
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* AlbersImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new AlbersImpl(*this);
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

void AlbersImpl::read(MemoryReader& memoryReader)
{
  try
  {
    Albers::read(memoryReader);
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

T::Coordinate_vec AlbersImpl::getGridCoordinates() const
{
  throw SmartMet::Spine::Exception(BCP, "Not implemented!");
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions AlbersImpl::getGridDimensions() const
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

bool AlbersImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
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

void AlbersImpl::initSpatialReference()
{
  try
  {
    // ### Check that we have all necessary values needed by this method.

    auto dfStdP1 = mLatin1;
    auto dfStdP2 = mLatin2;
    auto dfCenterLat = mLatin1; // ???????
    auto dfCenterLong = mLoV;
    auto southPoleLon = mLongitudeOfSouthernPole;
    auto southPoleLat = mLatitudeOfSouthernPole;

    if ((southPoleLon != 0) || (southPoleLat != (-90 * 1000000)))
      throw SmartMet::Spine::Exception(BCP,"A projection with a rotated pole is not supported!");


    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor = 6371229;
    double dfInvFlattening = 0.0;

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


    // ### Set the projection and the linear units for the projection.

    double stdP1 = C_DOUBLE(dfStdP1) / 1000000;
    double stdP2 = C_DOUBLE(dfStdP2) / 1000000;
    double centerLat = C_DOUBLE(dfCenterLat) / 1000000;
    double centerLon = C_DOUBLE(dfCenterLong) / 1000000;
    double dfFalseEasting = 0.0;
    double dfFalseNorthing = 0.0;

    mSpatialReference.SetACEA(stdP1,stdP2,centerLat,centerLon ,dfFalseEasting,dfFalseNorthing);
    mSpatialReference.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);


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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
