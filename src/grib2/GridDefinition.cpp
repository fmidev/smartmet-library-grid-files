#include "GridDefinition.h"
#include "common/Exception.h"

#include <iostream>


namespace SmartMet
{
namespace GRIB2
{



/*! \brief The constructor of the class. */

GridDefinition::GridDefinition()
{
  try
  {
    mGridProjection = T::GridProjection::Unknown;
    mGridLayout = T::GridLayout::Regular;
    mHash = 0;
    mOrigSpatialReference = NULL;
    mCoordinateTranformation_latlon2orig = NULL;
    mCoordinateTranformation_orig2latlon = NULL;
    mGlobal = false;
    mGeometryId = 0;
    getGridHash();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

GridDefinition::~GridDefinition()
{
  try
  {
    if (mCoordinateTranformation_latlon2orig != NULL)
      OCTDestroyCoordinateTransformation(mCoordinateTranformation_latlon2orig);

    if (mCoordinateTranformation_orig2latlon)
      OCTDestroyCoordinateTransformation(mCoordinateTranformation_orig2latlon);

    if (mOrigSpatialReference != NULL)
      mSpatialReference.DestroySpatialReference(mOrigSpatialReference);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Destructor failed!",NULL);
  }
}





void GridDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
}





T::GeometryId GridDefinition::getGridGeometryId() const
{
  try
  {
    return mGeometryId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






T::GridProjection GridDefinition::getGridProjection()
{
  try
  {
    return mGridProjection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






void GridDefinition::setGridGeometryId(T::GeometryId geometryId)
{
  try
  {
    mGeometryId = geometryId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string  GridDefinition::getGridGeometryName()
{
  try
  {
    return mGeometryName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GridDefinition::setGridGeometryName(std::string geometryName)
{
  try
  {
    mGeometryName = geometryName;
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
    This method should be overridden in the child classes.

        \return   The grid coordinates.
*/

T::Coordinate_vec GridDefinition::getGridCoordinates() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





T::Coordinate_vec GridDefinition::getGridLatLonCoordinates() const
{
  try
  {
    if (mCoordinateTranformation_orig2latlon == NULL)
    {
      OGRSpatialReference sr_latlon;
      sr_latlon.importFromEPSG(4326);

      if (mOrigSpatialReference == NULL)
        mOrigSpatialReference = mSpatialReference.Clone();

      mCoordinateTranformation_orig2latlon = OGRCreateCoordinateTransformation(mOrigSpatialReference,&sr_latlon);
      if (mCoordinateTranformation_orig2latlon == NULL)
        throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");
    }

    T::Coordinate_vec originalCoordinates = getGridCoordinates();
    T::Coordinate_vec latLonCoordinates;

    for (auto it = originalCoordinates.begin(); it != originalCoordinates.end(); ++it)
    {
      double lat = it->y();
      double lon = it->x();

      mCoordinateTranformation_orig2latlon->Transform(1,&lon,&lat);

      latLonCoordinates.push_back(T::Coordinate(lon,lat));
    }
    return latLonCoordinates;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDefinition::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  try
  {
    T::Dimensions_opt d = getGridDimensions();
    if (!d  || grid_i >= d->nx() || grid_j >= d->ny())
      return false;

    T::Coordinate_vec originalCoordinates = getGridCoordinates();
    uint c = grid_j * d->nx() + grid_i;
    if (c >= (uint)originalCoordinates.size())
      return false;

    x = originalCoordinates[c].x();
    y = originalCoordinates[c].y();

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDefinition::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in a child class!");
}





bool GridDefinition::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  try
  {
    double x = 0, y = 0;

    if (getGridOriginalCoordinatesByGridPosition(grid_i,grid_j,x,y))
    {
      return getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon);
    }
    return false;
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
    This method should be overridden in the child classes.

        \return   The grid dimensions.
*/

T::Dimensions_opt GridDefinition::getGridDimensions() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method initializes the spatial reference of the current grid.

    This method should be overridden in the child classes.
*/

void GridDefinition::initSpatialReference()
{
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in a child class!");
}





bool GridDefinition::reverseXDirection() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





bool GridDefinition::reverseYDirection() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns 'true' if the grid is global (i.e. goes around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

        \return   The method returns 'true' if the grid data is global. Otherwise
                  it returns 'false'
*/

bool GridDefinition::isGridGlobal() const
{
  try
  {
    return mGlobal;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method calculates the estimated grid position by using the latlon coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.
    This method could be overridden in the child classes in order to make
    the implementation faster.

        \param lat     The latitude.
        \param lon     The longitude.
        \param grid_i  The returned grid i-position.
        \param grid_j  The returned grid j-position.
        \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool GridDefinition::getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    double x = 0, y = 0;
    getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);

    return getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool GridDefinition::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  try
  {
    T::Dimensions_opt d = getGridDimensions();
    if (!d  || grid_i >= d->nx() || grid_j >= d->ny())
      return false;

    T::Coordinate_vec coordinates = getGridLatLonCoordinates();
    uint c = grid_j*d->nx() + grid_i;
    if (c < coordinates.size())
    {
      lon = coordinates[c].x();
      lat = coordinates[c].y();
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method calculates the estimated grid position by using the original coordinates.
    The estimated grid position is returned in the 'grid_i' and 'grid_j' parameters.
    This method should be overridden in the child classes.

      \param x       The original x-coordinate.
      \param y       The original y-coordinate.
      \param grid_i  The returned grid i-position.
      \param grid_j  The returned grid j-position.
      \return        Returns 'false' if the given coordinates are outside of the grid.
*/

bool GridDefinition::getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief This method converts the latlon coordinates to the original coordinates.
    The original coordinates are returned in the 'x' and 'y' parameters.
    This method could be overridden in the child classes in order to make
    the implementation faster.

        \param lat     The latitude.
        \param lon     The longitude.
        \param x       The x-coordinate of the original coordinates.
        \param y       The y-coordinate of the original coordinates.
*/

bool GridDefinition::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  try
  {
    if (mCoordinateTranformation_latlon2orig == NULL)
    {
      OGRSpatialReference sr_latlon;
      sr_latlon.importFromEPSG(4326);

      if (mOrigSpatialReference == NULL)
        mOrigSpatialReference = mSpatialReference.Clone();

      mCoordinateTranformation_latlon2orig = OGRCreateCoordinateTransformation(&sr_latlon,mOrigSpatialReference);
      if (mCoordinateTranformation_latlon2orig == NULL)
        throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");
    }

    x =lon;
    y = lat;

    mCoordinateTranformation_latlon2orig->Transform(1,&x,&y);
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method converts the original coordinates to the latlon coordinates.
    The latlon coordinates are returned in the 'lat' and 'lon' parameters.
    This method could be overridden in the child classes in order to make
    the implementation faster.

        \param x       The original x-coordinate.
        \param y       The original y-coordinate.
        \param lat     The returned latitude value.
        \param lon     The returned longitude value.
*/

bool GridDefinition::getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const
{
  try
  {
    if (mCoordinateTranformation_orig2latlon == NULL)
    {
      OGRSpatialReference sr_latlon;
      sr_latlon.importFromEPSG(4326);

      if (mOrigSpatialReference == NULL)
        mOrigSpatialReference = mSpatialReference.Clone();

      mCoordinateTranformation_orig2latlon = OGRCreateCoordinateTransformation(mOrigSpatialReference,&sr_latlon);
      if (mCoordinateTranformation_orig2latlon == NULL)
        throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");
    }

    lat = y;
    lon = x;

    mCoordinateTranformation_orig2latlon->Transform(1,&lon,&lat);

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::SpatialReference* GridDefinition::getSpatialReference()
{
  try
  {
    return &mSpatialReference;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the type of the grid layout.

        \return   The layout of the grid (expressed as an enum value).
*/

T::GridLayout GridDefinition::getGridLayout()
{
  try
  {
    return mGridLayout;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Hash GridDefinition::getGridHash()
{
  try
  {
    if (mHash == 0)
      mHash = countHash();

    //std::cout << "Hash: " << mHash << "\n";
    return mHash;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Hash GridDefinition::countHash()
{
  //std::cout << "Hash not defined\n";
  return 0;
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridDefinition::print(std::ostream& stream,uint level,uint optionFlags) const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}



}  // namespace GRIB2
}  // namespace SmartMet
