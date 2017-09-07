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





uint GridDefinition::getGridGeometryId() const
{
  try
  {
    return mGeometryId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}






void GridDefinition::setGridGeometryId(uint geometryId)
{
  try
  {
    mGeometryId = geometryId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the first and the last latlon coordinates used in the grid.
     This method could be overridden in the child classes in order to make
     the implementation faster.

        \param firstLat   The returned latitude of the top-left corner.
        \param firstLon   The returned longitude of the top-left corner.
        \param lastLat    The returned latitude of the bottom-right corner.
        \param lastLon    The returned longitude of the bottom-right corner.
*/

void GridDefinition::getGridLatlonAreaCoordinates(double& firstLat,double& firstLon,double& lastLat,double& lastLon) const
{
  try
  {
    double x1 = 0, y1 = 0, x2 = 0, y2 = 0;
    getGridOriginalAreaCoordinates(x1,y1,x2,y2);

    getLatLonByOriginalCoordinates(x1,y1,firstLat,firstLon);
    getLatLonByOriginalCoordinates(x2,y2,lastLat,lastLon);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the first and the last original coordinates used in the grid.
     This method could be overridden in the child classes in order to make
     the implementation faster.

        \param x1    The returned x-coordinate of the top-left corner.
        \param y1    The returned y-coordinate of the top-left corner.
        \param x2    The returned x-coordinate of the bottom-right corner.
        \param y2    The returned y-coordinate of the bottom-right corner.
*/

void GridDefinition::getGridOriginalAreaCoordinates(double& x1,double& y1,double& x2,double& y2) const
{
  try
  {
    // This can be implemented faster in child classes (if needed). I.e. now we are fetching
    // all coordinates, but need only the first and the last coordinates.

    T::Coordinate_vec coordinates = getGridCoordinates();
    std::size_t s = coordinates.size();
    if (s > 0)
    {
      x1 = coordinates[0].x();
      y1 = coordinates[0].y();
      x2 = coordinates[s-1].x();
      y2 = coordinates[s-1].y();
    }
    else
    {
      x1 = 0;
      y1 = 0;
      x2 = 0;
      y2 = 0;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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

bool GridDefinition::getGridPointByLatLon(double lat,double lon,double& grid_i,double& grid_j) const
{
  try
  {
    double x = 0, y = 0;
    getOriginalCoordinatesByLatLon(lat,lon,x,y);

    return getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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

void GridDefinition::getOriginalCoordinatesByLatLon(double lat,double lon,double& x,double& y) const
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
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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

void GridDefinition::getLatLonByOriginalCoordinates(double x,double y,double& lat,double& lon) const
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

    //printf("TRANSFORM %f,%f => %f,%f\n",x,y,lon,lat);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
