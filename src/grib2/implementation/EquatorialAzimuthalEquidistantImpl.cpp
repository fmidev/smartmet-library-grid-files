#include "EquatorialAzimuthalEquidistantImpl.h"
#include <macgyver/Exception.h>

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

EquatorialAzimuthalEquidistantImpl::EquatorialAzimuthalEquidistantImpl()
{
  mGridProjection = T::GridProjectionValue::EquatorialAzimuthalEquidistant;
}





/*! \brief The copy constructor of the class. */

EquatorialAzimuthalEquidistantImpl::EquatorialAzimuthalEquidistantImpl(const EquatorialAzimuthalEquidistantImpl& other)
:EquatorialAzimuthalEquidistant(other)
{
}





/*! \brief The destructor of the class. */

EquatorialAzimuthalEquidistantImpl::~EquatorialAzimuthalEquidistantImpl()
{
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* EquatorialAzimuthalEquidistantImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new EquatorialAzimuthalEquidistantImpl(*this);
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

void EquatorialAzimuthalEquidistantImpl::read(MemoryReader& memoryReader)
{
  try
  {
    EquatorialAzimuthalEquidistant::read(memoryReader);
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

T::Coordinate_svec EquatorialAzimuthalEquidistantImpl::getGridOriginalCoordinatesNoCache() const
{
  throw Fmi::Exception(BCP,"The method not implemented!");
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions EquatorialAzimuthalEquidistantImpl::getGridDimensions() const
{
  try
  {
    if (!mNumberOfPointsAlongXAxis || ! mNumberOfPointsAlongYAxis)
      return T::Dimensions();

    return T::Dimensions(*mNumberOfPointsAlongXAxis,*mNumberOfPointsAlongYAxis);
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

bool EquatorialAzimuthalEquidistantImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
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





/*! \brief The method initializes the spatial reference (mSpatialReference) of the grid. */

void EquatorialAzimuthalEquidistantImpl::initSpatialReference()
{
  try
  {
    mSpatialReference = getSpatialReference();
    if (!mSpatialReference)
    {
      mSpatialReference.reset(new T::SpatialRef());
      addSpatialReference(mSpatialReference);

      // ### Check that we have all necessary values needed by this method.

      auto dfCenterLat = mLatitudeOfTangencyPoint;
      if (!dfCenterLat)
        throw Fmi::Exception(BCP,"The 'latitudeOfTangencyPoint' value is missing!");

      auto dfCenterLong = mLongitudeOfTangencyPoint;
      if (!dfCenterLong)
        throw Fmi::Exception(BCP,"The 'longitudeOfTangencyPoint' value is missing!");


      // ### Set geographic coordinate system.

      const char *pszGeogName = "UNKNOWN";
      const char *pszDatumName = "UNKNOWN";
      const char *pszSpheroidName = "UNKNOWN";
      double dfSemiMajor = getMajorAxis(mEarthShape);
      double dfFlattening = getFlattening(mEarthShape);
      double dfInvFlattening = 0;
      if (dfFlattening != 0)
        dfInvFlattening = 1/dfFlattening;

      mSpatialReference->SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);


      // ### Set the projection and the linear units for the projection.

      *dfCenterLat /= 1000000;
      *dfCenterLong /= 1000000;
      double dfFalseEasting = 0.0;
      double dfFalseNorthing = 0.0;

      mSpatialReference->SetAE(*dfCenterLat,*dfCenterLong,dfFalseEasting,dfFalseNorthing);
      mSpatialReference->SetTargetLinearUnits("PROJCS", SRS_UL_METER, 1.0);
      mSpatialReference->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);


      // ### Validate the spatial reference.

      auto errorCode = mSpatialReference->Validate();
      if (errorCode != OGRERR_NONE)
      {
        Fmi::Exception exception(BCP,"The spatial reference is not valid!");
        exception.addParameter("ErrorCode",std::to_string(errorCode));
        throw exception;
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
