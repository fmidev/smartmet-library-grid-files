#include "GridDefinition.h"
#include "../common/CoordinateConversions.h"
#include "../common/Exception.h"
#include "../common/ShowFunction.h"

#include <iostream>
#include <map>
#include <iostream>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRIB2
{


std::map<uint,T::Coordinate_vec> coordinateCache;




/*! \brief The constructor of the class. */

GridDefinition::GridDefinition()
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
}





T::GeometryId GridDefinition::getGridGeometryId() const
{
  FUNCTION_TRACE
  try
  {
    return mGeometryId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






std::string GridDefinition::getGridGeometryString() const
{
  FUNCTION_TRACE
  try
  {
    std::string str;
    return str;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






bool GridDefinition::getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions_opt d = getGridDimensions();
    if (!d)
      return false;

    double lat[4] = {0};
    double lon[4] = {0};

    if (getGridLatLonCoordinatesByGridPoint(0,0,lat[0],lon[0]) &&
        getGridLatLonCoordinatesByGridPoint(d->nx(),0,lat[1],lon[1]) &&
        getGridLatLonCoordinatesByGridPoint(0,d->ny(),lat[2],lon[2]) &&
        getGridLatLonCoordinatesByGridPoint(d->nx(),d->ny(),lat[3],lon[3]))
    {
      topLeft.set(lon[0],lat[0]);
      topRight.set(lon[1],lat[1]);
      bottomLeft.set(lon[2],lat[2]);
      bottomRight.set(lon[3],lat[3]);
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::GridProjection GridDefinition::getGridProjection()
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





T::Coordinate_vec GridDefinition::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    //printf("*** GET COORDINATES version 2\n");
    uint geomId = getGridGeometryId();
    if (geomId != 0)
    {
      auto it = coordinateCache.find(geomId);
      if (it != coordinateCache.end())
      {
        return it->second;
      }
    }

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

      //printf("CONV %f,%f => %f,%f\n",it->y(),it->x(),lon,lat);

      latLonCoordinates.push_back(T::Coordinate(lon,lat));
    }

    if (geomId != 0)
    {
      coordinateCache.insert(std::pair<uint,T::Coordinate_vec>(geomId,latLonCoordinates));
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in a child class!");
}





bool GridDefinition::getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method initializes the spatial reference of the current grid.

    This method should be overridden in the child classes.
*/

void GridDefinition::initSpatialReference()
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in a child class!");
}





bool GridDefinition::reverseXDirection() const
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





bool GridDefinition::reverseYDirection() const
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns 'true' if the grid is global (i.e. goes around the globe).
    If the grid is global then we should be able to interpolate over the grid borders.

        \return   The method returns 'true' if the grid data is global. Otherwise
                  it returns 'false'
*/

bool GridDefinition::isGridGlobal() const
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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

    x = lon;
    y = lat;

    mCoordinateTranformation_latlon2orig->Transform(1,&x,&y);

    //printf("COORDINATE %f,%f => %f,%f\n",lon,lat,x,y);

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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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





void GridDefinition::getGridCellAverageSize(double& width,double& height)
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions_opt d = getGridDimensions();
    if (d)
    {
      int x = d->nx()/2;
      int y = d->ny()/2;

      double lat1 = 0,lon1 = 0,lat2 = 0,lon2 = 0;;
      if (getGridLatLonCoordinatesByGridPoint(x,y,lat1,lon1)  &&  getGridLatLonCoordinatesByGridPoint(x+1,y+1,lat2,lon2))
      {
        width = latlon_distance(lat1,lon1,lat1,lon2);
        height = latlon_distance(lat1,lon1,lat2,lon1);
        return;
      }
    }
    width = 0;
    height = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




T::Hash GridDefinition::countHash()
{
  FUNCTION_TRACE
  //std::cout << "Hash not defined\n";
  return 0;
}






double GridDefinition::getMajorAxis(EarthShapeSettings& earthSettings)
{
  FUNCTION_TRACE
  try
  {
    auto shape = earthSettings.getShapeOfTheEarth();
    if (!shape)
    {
      return (double)6371229;
    }

    switch (*shape)
    {
      case 0: // Earth assumed spherical with radius = 6,367,470.0 m
        return (double)6371220;
        //return (double)6367470;

      case 1: // Earth assumed spherical with radius specified by data producer
        return (double)(*earthSettings.getScaledValueOfEarthMajorAxis());

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        return (double)6378160;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        return (double)(*earthSettings.getScaledValueOfEarthMajorAxis());

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        return (double)6378137;

      case 5: // Earth assumed represented by WGS84 (as used by ICAO since 1998)
        return (double)6378137;

      case 6: // Earth assumed spherical with radius of 6,371,229.0 m
        return (double)6371229;

      default:
        return (double)6371229;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





double GridDefinition::getMinorAxis(EarthShapeSettings& earthSettings)
{
  FUNCTION_TRACE
  try
  {
    auto shape = earthSettings.getShapeOfTheEarth();
    if (!shape)
    {
      return 0;
    }

    switch (*shape)
    {
      case 0: // Earth assumed spherical with radius = 6,367,470.0 m
        return 0;

      case 1: // Earth assumed spherical with radius specified by data producer
        return (double)(*earthSettings.getScaledValueOfEarthMinorAxis());

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        return (double)6356775;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        return (double)(*earthSettings.getScaledValueOfEarthMinorAxis());

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        return (double)6356752.314;

      case 5: // Earth assumed represented by WGS84 (as used by ICAO since 1998)
        return 0;

      case 6: // Earth assumed spherical with radius of 6,371,229.0 m
        return 0;

      default:
        return 0;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






double GridDefinition::getFlattening(EarthShapeSettings& earthSettings)
{
  FUNCTION_TRACE
  try
  {
    auto shape = earthSettings.getShapeOfTheEarth();
    if (!shape)
    {
      return 0;
    }

    switch (*shape)
    {
      case 0: // Earth assumed spherical with radius = 6,367,470.0 m
        return 0;

      case 1: // Earth assumed spherical with radius specified by data producer
        return (1.0 / (1.0 - (*earthSettings.getScaledValueOfEarthMinorAxis() / (*earthSettings.getScaledValueOfEarthMajorAxis()))));

        return (double)(*earthSettings.getScaledValueOfEarthMinorAxis());

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        return (double)1000000 * 1/297.0;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        return (1.0 / (1.0 - (*earthSettings.getScaledValueOfEarthMinorAxis() / (*earthSettings.getScaledValueOfEarthMajorAxis()))));

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        return (double)6356752.314;

      case 5: // Earth assumed represented by WGS84 (as used by ICAO since 1998)
        return (1000000 * 1/298.257222101);

      case 6: // Earth assumed spherical with radius of 6,371,229.0 m
        return 0;

      default:
        return 0;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridDefinition::print(std::ostream& stream,uint level,uint optionFlags) const
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}



}  // namespace GRIB2
}  // namespace SmartMet
