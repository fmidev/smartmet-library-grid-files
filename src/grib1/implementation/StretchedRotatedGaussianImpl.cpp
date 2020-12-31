#include "StretchedRotatedGaussianImpl.h"
#include <macgyver/Exception.h>

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

StretchedRotatedGaussianImpl::StretchedRotatedGaussianImpl()
{
  mGridProjection = T::GridProjectionValue::StretchedRotatedGaussian;
}





/*! \brief The copy constructor of the class. */

StretchedRotatedGaussianImpl::StretchedRotatedGaussianImpl(const StretchedRotatedGaussianImpl& other)
:StretchedRotatedGaussian(other)
{
}





/*! \brief The destructor of the class. */

StretchedRotatedGaussianImpl::~StretchedRotatedGaussianImpl()
{
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* StretchedRotatedGaussianImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new StretchedRotatedGaussianImpl(*this);
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

void StretchedRotatedGaussianImpl::read(MemoryReader& memoryReader)
{
  try
  {
    StretchedRotatedGaussian::read(memoryReader);
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

T::Coordinate_svec StretchedRotatedGaussianImpl::getGridOriginalCoordinates() const
{
  throw Fmi::Exception(BCP, "Not implemented!");
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions StretchedRotatedGaussianImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions(mNi,mNj);
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

bool StretchedRotatedGaussianImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
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

void StretchedRotatedGaussianImpl::initSpatialReference()
{
  try
  {
    // ### Set geographic coordinate system.

    const char *pszGeogName = "UNKNOWN";
    const char *pszDatumName = "UNKNOWN";
    const char *pszSpheroidName = "UNKNOWN";
    double dfSemiMajor =  6367470;
    double dfInvFlattening = 0.0;

    ResolutionFlagsSettings *rflags = mGridArea.getResolutionFlags();
    if (rflags != nullptr)
    {
      dfSemiMajor = getMajorAxis(rflags->getResolutionAndComponentFlags());
      dfInvFlattening = getFlattening(rflags->getResolutionAndComponentFlags());
    }

    mSpatialReference.SetGeogCS(pszGeogName,pszDatumName,pszSpheroidName,dfSemiMajor,dfInvFlattening);

    mSpatialReference.SetProjParm("latitude_of_origin",(C_DOUBLE(mRotation.getLatitudeOfSouthernPole())/1000));
    mSpatialReference.SetProjParm("central_meridian",(C_DOUBLE(mRotation.getLongitudeOfSouthernPole())/1000));
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


}  // namespace GRIB1
}  // namespace SmartMet
