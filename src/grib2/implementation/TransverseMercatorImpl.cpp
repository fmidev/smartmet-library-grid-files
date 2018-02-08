#include "TransverseMercatorImpl.h"
#include "common/Exception.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

TransverseMercatorImpl::TransverseMercatorImpl()
{
  mGridProjection = T::GridProjection::TransverseMercator;
}





/*! \brief The copy constructor of the class. */

TransverseMercatorImpl::TransverseMercatorImpl(const TransverseMercatorImpl& other)
:TransverseMercator(other)
{
}





/*! \brief The destructor of the class. */

TransverseMercatorImpl::~TransverseMercatorImpl()
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

void TransverseMercatorImpl::read(MemoryReader& memoryReader)
{
  try
  {
    TransverseMercator::read(memoryReader);
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

T::Coordinate_vec TransverseMercatorImpl::getGridCoordinates() const
{
  throw SmartMet::Spine::Exception(BCP, "The method not implemented!");
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions_opt TransverseMercatorImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions{*mNi, *mNj};
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
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

bool TransverseMercatorImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    // TODO: We should probably do our own implementation instead of using the parent implementation,
    // which might be slow or does not even work if the spatial reference is not correctly initialized.

    return GridDefinition::getGridPointByLatLonCoordinates(lat,lon,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void TransverseMercatorImpl::initSpatialReference()
{
  try
  {
    // ### Check that we have all necessary values needed by this method.

    auto dfCenterLat = mLatitudeOfReferencePoint;
    if (!dfCenterLat)
      throw SmartMet::Spine::Exception(BCP, "The 'latitudeOfReferencePoint' value is missing!");

    auto dfCenterLong = mLongitudeOfReferencePoint;
    if (!dfCenterLong)
      throw SmartMet::Spine::Exception(BCP, "The 'longitudeOfReferencePoint' value is missing!");

    auto dfScale = mScaleFactorAtReferencePoint;

    auto dfFalseEasting = mXR;
    if (!dfFalseEasting)
      throw SmartMet::Spine::Exception(BCP, "The 'xR' value is missing!");

    auto dfFalseNorthing = mYR;
    if (!dfFalseNorthing)
      throw SmartMet::Spine::Exception(BCP, "The 'yR' value is missing!");

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

    mSpatialReference.SetGeogCS(pszGeogName, pszDatumName, pszSpheroidName, dfSemiMajor,
                                dfInvFlattening);

    // ### Set the projection and the linear units for the projection.

    double centerLat = *dfCenterLat / 1000000;
    double centerLon = *dfCenterLong / 1000000;
    double falseEasting = *dfFalseEasting / 1000;
    double falseNorthing = *dfFalseNorthing / 1000;
    double scale = (double)(dfScale);

    mSpatialReference.SetTM(centerLat, centerLon, scale, falseEasting,
                            falseNorthing);
    mSpatialReference.SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);

    // ### Validate the spatial reference.

    auto errorCode = mSpatialReference.Validate();
    if (errorCode != OGRERR_NONE)
    {
      SmartMet::Spine::Exception exception(BCP, "The spatial reference is not valid!");
      exception.addParameter("ErrorCode", std::to_string(errorCode));
      throw exception;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}


}
}
