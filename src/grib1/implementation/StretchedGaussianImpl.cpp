#include "StretchedGaussianImpl.h"
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

StretchedGaussianImpl::StretchedGaussianImpl()
{
  mGridProjection = T::GridProjectionValue::StretchedGaussian;
}





/*! \brief The copy constructor of the class. */

StretchedGaussianImpl::StretchedGaussianImpl(const StretchedGaussianImpl& other)
:StretchedGaussian(other)
{
}





/*! \brief The destructor of the class. */

StretchedGaussianImpl::~StretchedGaussianImpl()
{
}





/*! \brief The method returns a duplicate of the current object. */

GridDefinition* StretchedGaussianImpl::createGridDefinition() const
{
  try
  {
    return (GridDefinition*)new StretchedGaussianImpl(*this);
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

void StretchedGaussianImpl::read(MemoryReader& memoryReader)
{
  try
  {
    StretchedGaussian::read(memoryReader);
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

T::Coordinate_svec StretchedGaussianImpl::getGridOriginalCoordinatesNoCache() const
{
  throw Fmi::Exception(BCP, "Not implemented!");
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.

        \return   The grid dimensions.
*/

T::Dimensions StretchedGaussianImpl::getGridDimensions() const
{
  try
  {
    return T::Dimensions(mNi, mNj);
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

bool StretchedGaussianImpl::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
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

void StretchedGaussianImpl::initSpatialReference()
{
  try
  {
    // TODO: The method should be implemented.

    // Let's print the error message. We do not necessary want to terminate the program by throwing
    // an exception, because we can use quite many functionalities without a valid spatial reference.

    std::cout << __FILE__ << ":" << __LINE__ << ": The method '" << __FUNCTION__ << "' not implemented!\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
