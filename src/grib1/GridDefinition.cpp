#include "GridDefinition.h"
#include "Properties.h"
#include <macgyver/Exception.h>
#include <macgyver/Cache.h>
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/AutoWriteLock.h"
#include "../common/AutoReadLock.h"
#include "../common/ShowFunction.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <unordered_map>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRIB1
{



Fmi::Cache::CacheStats latlonCoordinateCache_stats;
Fmi::Cache::Cache<uint,T::Coordinate_svec> latlonCoordinateCache(10000);

Fmi::Cache::CacheStats originalCoordinateCache_stats;
Fmi::Cache::Cache<uint,T::Coordinate_svec> originalCoordinateCache(10000);


Fmi::Cache::CacheStats transformCache1_stats;
Fmi::Cache::Cache<std::size_t,T::Coordinate> transformCache1(1000000);

Fmi::Cache::CacheStats transformCache2_stats;
Fmi::Cache::Cache<std::size_t,T::Coordinate> transformCache2(1000000);

Fmi::Cache::CacheStats transformCache3_stats;
Fmi::Cache::Cache<std::size_t,T::Coordinate_svec> transformCache3(1000);

Fmi::Cache::Cache<std::size_t,T::SpatialRef_sptr> spatialReferenceCache(1000);

T::SpatialRef_sptr latlonSpatialReference;
T::SpatialRef_sptr sr_wgs84_world_mercator;



/*! \brief The constructor of the class. */

GridDefinition::GridDefinition()
{
  FUNCTION_TRACE
  try
  {
    mHash = 0;
    mGlobal = false;
    mGeometryId = 0;
    mGridProjection = T::GridProjectionValue::Unknown;
    mEarth_semiMajor = 0;
    mEarth_semiMinor = 0;

    if (latlonCoordinateCache_stats.maxsize == 0)
    {
      latlonCoordinateCache_stats.maxsize = 10000;
      latlonCoordinateCache_stats.starttime = Fmi::SecondClock::universal_time();

      originalCoordinateCache_stats.maxsize = 10000;
      originalCoordinateCache_stats.starttime = Fmi::SecondClock::universal_time();

      transformCache1_stats.maxsize = 1000000;
      transformCache1_stats.starttime = Fmi::SecondClock::universal_time();

      transformCache2_stats.maxsize = 1000000;
      transformCache2_stats.starttime = Fmi::SecondClock::universal_time();

      transformCache3_stats.maxsize = 1000;
      transformCache3_stats.starttime = Fmi::SecondClock::universal_time();
    }

    if (!latlonSpatialReference)
    {
      latlonSpatialReference.reset(new T::SpatialRef());
      latlonSpatialReference->importFromEPSG(4326);
      latlonSpatialReference->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
    }

    if (sr_wgs84_world_mercator)
    {
      sr_wgs84_world_mercator.reset(new T::SpatialRef());
      sr_wgs84_world_mercator->importFromEPSG(3395);
      sr_wgs84_world_mercator->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

GridDefinition::GridDefinition(const GridDefinition& other)
{
  FUNCTION_TRACE
  try
  {
    mSpatialReference = other.mSpatialReference;
    mHash = other.mHash;
    mGlobal = other.mGlobal;
    mGeometryId = other.mGeometryId;
    mGridProjection = other.mGridProjection;
    mEarth_semiMajor = other.mEarth_semiMajor;
    mEarth_semiMinor = other.mEarth_semiMinor;

    if (!latlonSpatialReference)
    {
      latlonSpatialReference.reset(new T::SpatialRef());
      latlonSpatialReference->importFromEPSG(4326);
      latlonSpatialReference->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
    }
    if (sr_wgs84_world_mercator)
    {
      sr_wgs84_world_mercator.reset(new T::SpatialRef());
      sr_wgs84_world_mercator->importFromEPSG(3395);
      sr_wgs84_world_mercator->SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GridDefinition::~GridDefinition()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed!",nullptr);
    exception.printError();
  }
}





GridDefinition* GridDefinition::createGridDefinition() const
{
  throw Fmi::Exception(BCP,"Not implemented!");
}





void GridDefinition::getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
}





/*! \brief The method returns the grid geometry identifer.

        \return   The grid geometry identifier.
*/

T::GeometryId GridDefinition::getGridGeometryId() const
{
  FUNCTION_TRACE
  try
  {
    return mGeometryId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid geometry string. This string can be used for comparing
    geometries in different grid files. For example, is is possible that a GRIB 1 message has
    the same geometry string as a GRIB 2 message, which means that they have same geometries.
    This comparison is more reliable than the hash comparison.

        \return   The grid geometry string.
*/

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method set the grid geometry identifer.

   This identifier can be used for identifying different geometries. Usually geometry identifiers are defined
   in a configuration file and when a grid file read the geometry is automatically identified. However, there might
   be cases that the geometry cannot be automatically identified (because it is not defined in the configuration file).
   It is also possible that we might want to use our own geometry identifiers and this method allows us to set it
   in place.

        \param   The grid geometry identifier.
*/

void GridDefinition::setGridGeometryId(T::GeometryId geometryId)
{
  FUNCTION_TRACE
  try
  {
    mGeometryId = geometryId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2)
      return false;

    if (!getGridLatLonArea(topLeft,topRight,bottomLeft,bottomRight))
      return false;

    OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(latlonSpatialReference.get(),sr_wgs84_world_mercator.get());

    if (transformation == nullptr)
      return false;

    double x = topLeft.x();
    double y = topLeft.y();
    transformation->Transform(1,&x,&y);
    topLeft.set(x,y);

    x = topRight.x();
    y = topRight.y();
    transformation->Transform(1,&x,&y);
    topRight.set(x,y);

    x = bottomLeft.x();
    y = bottomLeft.y();
    transformation->Transform(1,&x,&y);
    bottomLeft.set(x,y);

    x = bottomRight.x();
    y = bottomRight.y();
    transformation->Transform(1,&x,&y);
    bottomRight.set(x,y);

    OCTDestroyCoordinateTransformation(transformation);

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool GridDefinition::getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight)
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2)
      return false;

    double lat[4] = {0};
    double lon[4] = {0};

    if (getGridLatLonCoordinatesByGridPoint(0,0,lat[0],lon[0]) &&
        getGridLatLonCoordinatesByGridPoint(d.nx()-1,0,lat[1],lon[1]) &&
        getGridLatLonCoordinatesByGridPoint(0,d.ny()-1,lat[2],lon[2]) &&
        getGridLatLonCoordinatesByGridPoint(d.nx()-1,d.ny()-1,lat[3],lon[3]))
    {
      if (lat[0] > lat[2])
      {
        topLeft.set(lon[0],lat[0]);
        topRight.set(lon[1],lat[1]);
        bottomLeft.set(lon[2],lat[2]);
        bottomRight.set(lon[3],lat[3]);
      }
      else
      {
        bottomLeft.set(lon[0],lat[0]);
        bottomRight.set(lon[1],lat[1]);
        topLeft.set(lon[2],lat[2]);
        topRight.set(lon[3],lat[3]);
      }

      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDefinition:: getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const
{
  FUNCTION_TRACE
  try
  {
    uint sz = latlon.size();
    std::size_t hash = 0;
    uint geomId = getGridGeometryId();
    if (geomId != 0)
    {
      boost::hash_combine(hash,geomId);

      for (uint t=0; t<sz; t++)
      {
        auto cc = latlon[t];
        boost::hash_combine(hash,cc.x());
        boost::hash_combine(hash,cc.y());
      }

      auto it = transformCache3.find(hash);
      if (it)
      {
        transformCache3_stats.hits++;
        points = *(*it);
        return;
      }
      transformCache3_stats.misses++;
    }

    points.reserve(sz);

    double *x = new double[sz+1];
    double *y = new double[sz+1];

    std::unique_ptr<double[]> rx(x);
    std::unique_ptr<double[]> ry(y);

    for (uint t=0; t<sz; t++)
    {
      auto cc = latlon[t];
      x[t] = cc.x();
      y[t] = cc.y();
    }

    convert(latlonSpatialReference,mSpatialReference,sz,x,y);

    T::Coordinate_svec vec(new T::Coordinate_vec());
    vec->reserve(sz);

    for (uint t=0; t<sz; t++)
    {
      double i = 0,j = 0;
      if (getGridPointByOriginalCoordinates(x[t],y[t],i,j))
        vec->emplace_back(i,j);
      else
        vec->emplace_back(ParamValueMissing,ParamValueMissing);
    }

    if (hash != 0)
    {
      transformCache3.insert(hash,vec);
      transformCache3_stats.inserts++;
      transformCache3_stats.size++;
    }
    points = *vec;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

bool GridDefinition::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    auto rows = getGridRowCount();
    auto cols = getGridColumnCount();

    if (grid_i >= cols || grid_j >= rows)
      return false;

    double x = 0;
    double y = 0;
    if (getGridOriginalCoordinatesByGridPosition((double)grid_i,(double)grid_j,x,y))
    {
      if (getGridLatLonCoordinatesByOriginalCoordinates(x,y,lat,lon))
        return true;
    }

    T::Coordinate_svec coordinates = getGridLatLonCoordinates();
    uint c = grid_j*cols + grid_i;
    if (c < coordinates->size())
    {
      lon = getLongitude((*coordinates)[c].x());
      lat = (*coordinates)[c].y();
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid latlon coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return        The method return true if the latlon values were succesfully returned.
*/

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool GridDefinition::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    auto rows = getGridRowCount();
    auto cols = getGridColumnCount();

    if (grid_i >= cols || grid_j >= rows)
      return false;

    T::Coordinate_svec originalCoordinates = getGridOriginalCoordinates();
    uint c = grid_j * cols + grid_i;
    if (c >= C_UINT(originalCoordinates->size()))
      return false;

    x = (*originalCoordinates)[c].x();
    y = (*originalCoordinates)[c].y();

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates in the given grid position (= double coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param x       The x-coordinate in the original projection is returned in this parameter.
        \param y       The y-coordinate in the original projection is returned in this parameter.
        \return        The method return true if the original coordinates were succesfully returned.
*/

bool GridDefinition::getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.
    This method should be overridden in the child classes.

       \return   The grid coordinates.
*/

T::Coordinate_svec GridDefinition::getGridOriginalCoordinatesNoCache() const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}




T::Coordinate_svec GridDefinition::getGridOriginalCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    uint geomId = getGridGeometryId();
    if (geomId != 0)
    {
      auto it = originalCoordinateCache.find(geomId);
      if (it)
      {
        originalCoordinateCache_stats.hits++;
        return *it;
      }
      originalCoordinateCache_stats.misses++;
    }

    auto originalCoordinates = getGridOriginalCoordinatesNoCache();

    if (geomId != 0)
    {
      originalCoordinateCache.insert(geomId,originalCoordinates);
      originalCoordinateCache_stats.inserts++;
      originalCoordinateCache_stats.size++;
    }

    return originalCoordinates;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_svec GridDefinition::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    uint geomId = getGridGeometryId();
    if (geomId != 0)
    {
      auto it = latlonCoordinateCache.find(geomId);
      if (it)
      {
        latlonCoordinateCache_stats.hits++;
        return *it;
      }
      latlonCoordinateCache_stats.misses++;
    }

    T::Coordinate_svec originalCoordinates = getGridOriginalCoordinates();
    T::Coordinate_svec latLonCoordinates(new T::Coordinate_vec());

    int sz = originalCoordinates->size();

    double *lat = new double[sz+1];
    double *lon = new double[sz+1];

    std::unique_ptr<double[]> rlat(lat);
    std::unique_ptr<double[]> rlon(lon);

    latLonCoordinates->reserve(sz);

    for (int t=0; t<sz; t++)
    {
      auto cc = (*originalCoordinates)[t];
      lat[t] = cc.y();
      lon[t] = cc.x();
    }

    convert(mSpatialReference,latlonSpatialReference,sz,lon,lat);

    for (int t=0; t<sz; t++)
    {
      latLonCoordinates->emplace_back(lon[t],lat[t]);
    }

    if (geomId != 0)
    {
      if (latlonCoordinateCache.size() >= latlonCoordinateCache_stats.maxsize)
      {
        latlonCoordinateCache.clear();
        latlonCoordinateCache_stats.size = 0;
        latlonCoordinateCache_stats.inserts = 0;
        latlonCoordinateCache_stats.hits = 0;
        latlonCoordinateCache_stats.misses = 0;
        latlonCoordinateCache_stats.starttime = Fmi::SecondClock::universal_time();
      }

      latlonCoordinateCache.insert(geomId,latLonCoordinates);
      latlonCoordinateCache_stats.inserts++;
      latlonCoordinateCache_stats.size++;
    }

    return latLonCoordinates;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid dimensions (i.e. the width and the height).
    Notice that the grid might be irregular. For example, the number of rows might
    be specified while the number of columns is missing. This usually means that each
    row might have different number of columns.
    This method should be overridden in the child classes.

      \return   The grid dimensions.
*/

T::Dimensions GridDefinition::getGridDimensions() const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}






std::size_t GridDefinition::getGridColumnCount() const
{
  try
  {
    auto d = getGridDimensions();
    if (d.getDimensions() > 1)
      return d.nx();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::size_t GridDefinition::getGridRowCount() const
{
  try
  {
    auto d = getGridDimensions();
    if (d.getDimensions() == 2)
      return d.ny();

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid original (projection) coordinates by the given latlon position.

        \param lat  The latitude value.
        \param lon  The longitude value.
        \param x    The x-coordinate in the original projection is returned in this parameter.
        \param y    The y-coordinate in the original projection is returned in this parameter.
        \return     The method return true if the original coordinates were succesfully returned.
*/

bool GridDefinition::getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    std::size_t hash = 0;
    uint geomId = getGridGeometryId();
    if (geomId != 0)
    {
      boost::hash_combine(hash,geomId);
      boost::hash_combine(hash,lat);
      boost::hash_combine(hash,lon);

      auto it = transformCache1.find(hash);
      if (it)
      {
        transformCache1_stats.hits++;
        x = it->x();
        y = it->y();
        return true;
      }
      transformCache1_stats.misses++;
    }

    x = lon;
    y = lat;

    convert(latlonSpatialReference,mSpatialReference,1,&x,&y);

    if (hash != 0)
    {
      transformCache1.insert(hash,T::Coordinate(x,y));
      transformCache1_stats.inserts++;
      transformCache1_stats.size++;
    }

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getTransformFromCache(std::size_t hash,double lat,double lon,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    if (hash == 0)
      return false;

    boost::hash_combine(hash,lat);
    boost::hash_combine(hash,lon);

    auto it = transformCache1.find(hash);
    if (it)
    {
      transformCache1_stats.hits++;
      x = it->x();
      y = it->y();
      return true;
    }
    transformCache1_stats.misses++;
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void GridDefinition::insertTranformIntoCache(std::size_t hash,double lat,double lon,double x,double y) const
{
  FUNCTION_TRACE
  try
  {
    if (hash == 0)
      return;

    boost::hash_combine(hash,lat);
    boost::hash_combine(hash,lon);

    auto it = transformCache1.find(hash);
    if (it  &&  x == it->x() && y == it->y())
      return;

    if (hash != 0)
    {
      transformCache1.insert(hash,T::Coordinate(x,y));
      transformCache1_stats.inserts++;
      transformCache1_stats.size++;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getGridOriginalCoordinatesByLatLonCoordinatesNoCache(double lat,double lon,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    x = lon;
    y = lat;

    convert(latlonSpatialReference,mSpatialReference,1,&x,&y);

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    lon = x;
    lat = y;

    convert(mSpatialReference,latlonSpatialReference,1,&lon,&lat);

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool GridDefinition::reverseXDirection() const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool GridDefinition::reverseYDirection() const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::isRelativeUV() const
{
  FUNCTION_TRACE
  try
  {
    ResolutionFlagsSettings *resolutionFlags = getResolutionFlags();
    if (resolutionFlags)
    {
      if (resolutionFlags->getResolutionAndComponentFlags() &  0x08)
        return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





GridAreaSettings* GridDefinition::getGridArea() const
{
  FUNCTION_TRACE
  try
  {
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





ScanningModeSettings* GridDefinition::getScanningMode() const
{
  FUNCTION_TRACE
  try
  {
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





ResolutionFlagsSettings* GridDefinition::getResolutionFlags() const
{
  FUNCTION_TRACE
  try
  {
    GridAreaSettings *area = getGridArea();
    if (area)
      return area->getResolutionFlags();

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





RotationSettings* GridDefinition::getRotation() const
{
  FUNCTION_TRACE
  try
  {
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for fetching a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridDefinition::getProperty(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    if (getProperty_gridArea(propertyId,value))
      return true;

    if (getProperty_scanningMode(propertyId,value))
      return true;

    if (getProperty_resolutionFlags(propertyId,value))
      return true;

    if (getProperty_rotation(propertyId,value))
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for fetching a (double) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridDefinition::getProperty(uint propertyId,double& value)
{
  FUNCTION_TRACE
  try
  {
    if (getProperty_rotation(propertyId,value))
      return true;

    long long val = 0;
    if (getProperty_gridArea(propertyId,val))
    {
      value = val;
      return true;
    }

    if (getProperty_scanningMode(propertyId,val))
    {
      value = val;
      return true;
    }

    if (getProperty_resolutionFlags(propertyId,val))
    {
      value = val;
      return true;
    }

    if (getProperty_rotation(propertyId,val))
    {
      value = val;
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridDefinition::getProperties(T::PropertySettingVec& properties)
{
  try
  {
    getProperties_gridArea(properties);
    getProperties_scanningMode(properties);
    getProperties_resolutionFlags(properties);
    getProperties_rotation(properties);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridDefinition::getProperties_gridArea(T::PropertySettingVec& properties)
{
  try
  {
    GridAreaSettings *gridArea = getGridArea();
    if (gridArea == nullptr)
      return;

    properties.emplace_back((uint)Property::GridSection::GridArea::LatitudeOfFirstGridPoint,gridArea->getLatitudeOfFirstGridPoint());
    properties.emplace_back((uint)Property::GridSection::GridArea::LongitudeOfFirstGridPoint,gridArea->getLongitudeOfFirstGridPoint());
    properties.emplace_back((uint)Property::GridSection::GridArea::LatitudeOfLastGridPoint,gridArea->getLatitudeOfLastGridPoint());
    properties.emplace_back((uint)Property::GridSection::GridArea::LongitudeOfLastGridPoint,gridArea->getLongitudeOfLastGridPoint());

    auto resolutionFlags = gridArea->getResolutionFlags();
    if (resolutionFlags)
      properties.emplace_back((uint)Property::GridSection::ResolutionFlags::ResolutionAndComponentFlags,resolutionFlags->getResolutionAndComponentFlags());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridDefinition::getProperties_scanningMode(T::PropertySettingVec& properties)
{
  try
  {
    ScanningModeSettings* scanningMode = getScanningMode();
    if (scanningMode == nullptr)
      return;

    properties.emplace_back((uint)Property::GridSection::ScanningMode::ScanMode,scanningMode->getScanningMode());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridDefinition::getProperties_resolutionFlags(T::PropertySettingVec& properties)
{
  try
  {
    ResolutionFlagsSettings *resolutionFlags = getResolutionFlags();
    if (resolutionFlags == nullptr)
      return;

    properties.emplace_back((uint)Property::GridSection::ResolutionFlags::ResolutionAndComponentFlags,resolutionFlags->getResolutionAndComponentFlags());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



void GridDefinition::getProperties_rotation(T::PropertySettingVec& properties)
{
  try
  {
    RotationSettings *rotation = getRotation();
    if (rotation == nullptr)
      return;

    properties.emplace_back((uint)Property::GridSection::Rotation::LatitudeOfSouthernPole,rotation->getLatitudeOfSouthernPole());
    properties.emplace_back((uint)Property::GridSection::Rotation::LongitudeOfSouthernPole,rotation->getLongitudeOfSouthernPole());
    properties.emplace_back((uint)Property::GridSection::Rotation::AngleOfRotationInDegrees,rotation->getGeography_angleOfRotationInDegrees()*1000);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method is used for fetching a (long long) value for the GridAreaSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridDefinition::getProperty_gridArea(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    GridAreaSettings *gridArea = getGridArea();
    if (gridArea == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::GridArea::LatitudeOfFirstGridPoint:
        value = gridArea->getLatitudeOfFirstGridPoint();
        return true;

      case Property::GridSection::GridArea::LongitudeOfFirstGridPoint:
        value = gridArea->getLongitudeOfFirstGridPoint();
        return true;

      case Property::GridSection::GridArea::LatitudeOfLastGridPoint:
        value = gridArea->getLatitudeOfLastGridPoint();
        return true;

      case Property::GridSection::GridArea::LongitudeOfLastGridPoint:
        value = gridArea->getLongitudeOfLastGridPoint();
        return true;

      case Property::GridSection::ResolutionFlags::ResolutionAndComponentFlags:
      {
        auto resolutionFlags = gridArea->getResolutionFlags();
        if (resolutionFlags)
          value = resolutionFlags->getResolutionAndComponentFlags();
        return true;
      }
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for fetching a (long long) value for the ScanningModeSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridDefinition::getProperty_scanningMode(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    ScanningModeSettings* scanningMode = getScanningMode();
    if (scanningMode == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::ScanningMode::ScanMode:
        value = scanningMode->getScanningMode();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for fetching a (long long) value for the ResolutionFlagsSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridDefinition::getProperty_resolutionFlags(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    ResolutionFlagsSettings *resolutionFlags = getResolutionFlags();
    if (resolutionFlags == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::ResolutionFlags::ResolutionAndComponentFlags:
        value = resolutionFlags->getResolutionAndComponentFlags();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for fetching a (long long) value for the RotationSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridDefinition::getProperty_rotation(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    RotationSettings *rotation = getRotation();
    if (rotation == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::Rotation::LatitudeOfSouthernPole:
        value = rotation->getLatitudeOfSouthernPole();
        return true;

      case Property::GridSection::Rotation::LongitudeOfSouthernPole:
        value = rotation->getLongitudeOfSouthernPole();
        return true;

      case Property::GridSection::Rotation::AngleOfRotationInDegrees:
        value = rotation->getGeography_angleOfRotationInDegrees()*1000;
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for fetching a (double) value for the RotationSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridDefinition::getProperty_rotation(uint propertyId,double& value)
{
  FUNCTION_TRACE
  try
  {
    RotationSettings *rotation = getRotation();
    if (rotation == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::Rotation::LatitudeOfSouthernPole:
        value = rotation->getLatitudeOfSouthernPole();
        return true;

      case Property::GridSection::Rotation::LongitudeOfSouthernPole:
        value = rotation->getLongitudeOfSouthernPole();
        return true;

      case Property::GridSection::Rotation::AngleOfRotationInDegrees:
        value = rotation->getGeography_angleOfRotationInDegrees();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridDefinition::setProperty(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    if (setProperty_gridArea(propertyId,value))
      return true;

    if (setProperty_scanningMode(propertyId,value))
      return true;

    if (setProperty_resolutionFlags(propertyId,value))
      return true;

    if (setProperty_rotation(propertyId,value))
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (double) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridDefinition::setProperty(uint propertyId,double value)
{
  FUNCTION_TRACE
  try
  {
    if (setProperty_gridArea(propertyId,value))
      return true;

    if (setProperty_scanningMode(propertyId,value))
      return true;

    if (setProperty_resolutionFlags(propertyId,value))
      return true;

    if (setProperty_rotation(propertyId,value))
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the GridAreaSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridDefinition::setProperty_gridArea(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    GridAreaSettings *gridArea = getGridArea();
    if (gridArea == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::GridArea::LatitudeOfFirstGridPoint:
        gridArea->setLatitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::GridArea::LongitudeOfFirstGridPoint:
        gridArea->setLongitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::GridArea::LatitudeOfLastGridPoint:
        gridArea->setLatitudeOfLastGridPoint(value);
        return true;

      case Property::GridSection::GridArea::LongitudeOfLastGridPoint:
        gridArea->setLongitudeOfLastGridPoint(value);
        return true;

      case Property::GridSection::ResolutionFlags::ResolutionAndComponentFlags:
      {
        auto resolutionFlags = gridArea->getResolutionFlags();
        if (resolutionFlags)
          resolutionFlags->setResolutionAndComponentFlags(value);
        return true;
      }
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the ScanningModeSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridDefinition::setProperty_scanningMode(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    ScanningModeSettings* scanningMode = getScanningMode();
    if (scanningMode == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::ScanningMode::ScanMode:
        scanningMode->setScanningMode(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the ResolutionFlagsSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridDefinition::setProperty_resolutionFlags(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    ResolutionFlagsSettings *resolutionFlags = getResolutionFlags();
    if (resolutionFlags == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::ResolutionFlags::ResolutionAndComponentFlags:
        resolutionFlags->setResolutionAndComponentFlags(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the RotationSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridDefinition::setProperty_rotation(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    RotationSettings *rotation = getRotation();
    if (rotation == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::Rotation::LatitudeOfSouthernPole:
        rotation->setLatitudeOfSouthernPole(value);
        return true;

      case Property::GridSection::Rotation::LongitudeOfSouthernPole:
        rotation->setLongitudeOfSouthernPole(value);
        return true;

      case Property::GridSection::Rotation::AngleOfRotationInDegrees:
        rotation->setGeography_angleOfRotationInDegrees((double)value/1000);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (double) value for the RotationSettings property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool GridDefinition::setProperty_rotation(uint propertyId,double value)
{
  FUNCTION_TRACE
  try
  {
    RotationSettings *rotation = getRotation();
    if (rotation == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::Rotation::LatitudeOfSouthernPole:
        rotation->setLatitudeOfSouthernPole(C_INT64(value));
        return true;

      case Property::GridSection::Rotation::LongitudeOfSouthernPole:
        rotation->setLongitudeOfSouthernPole(C_INT64(value));
        return true;

      case Property::GridSection::Rotation::AngleOfRotationInDegrees:
        rotation->setGeography_angleOfRotationInDegrees(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method initializes the spatial reference of the current grid.

    This method should be overridden in the child classes.
*/

void GridDefinition::initSpatialReference()
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"This method should be implemented in a child class!");
}





std::string GridDefinition::getWKT()
{
  FUNCTION_TRACE
  try
  {
    std::string wkt;
    auto sr = getSpatialReference();
    if (sr)
    {
      char *out = nullptr;
      sr->exportToWkt(&out);
      wkt = out;
      CPLFree(out);
    }
    return wkt;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





std::string GridDefinition::getProj4()
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();

    double lat[4] = {0};
    double lon[4] = {0};

    getGridLatLonCoordinatesByGridPoint(0,0,lat[0],lon[0]);
    getGridLatLonCoordinatesByGridPoint(d.nx()-1,0,lat[1],lon[1]);
    getGridLatLonCoordinatesByGridPoint(0,d.ny()-1,lat[2],lon[2]);
    getGridLatLonCoordinatesByGridPoint(d.nx()-1,d.ny()-1,lat[3],lon[3]);

    std::string proj4;
    auto sr = getSpatialReference();
    if (sr)
    {
      char *out = nullptr;
      sr->exportToProj4(&out);
      proj4 = out;
      CPLFree(out);
    }
    if (lon[0] > 180 || lon[1] > 180 || lon[2] > 180 || lon[3] > 180 || (lon[1] < 0 && lon[0] > lon[1] && lon[3] < 0 && lon[2] > lon[3]))
      proj4 += " +lon_wrap=180";

    return proj4;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    throw exception;
  }
}





/*! \brief The method returns the pointer to the spatial reference of the current grid.

        \return   The pointer to the spatial reference.
*/

T::SpatialRef_sptr GridDefinition::getSpatialReference()
{
  FUNCTION_TRACE
  try
  {
    if (mSpatialReference)
      return mSpatialReference;

    std::size_t geometryHash = 0;
    boost::hash_combine(geometryHash,getGridGeometryString());

    auto sp = spatialReferenceCache.find(geometryHash);
    if (sp)
      mSpatialReference = *sp;

    return mSpatialReference;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDefinition::addSpatialReference(T::SpatialRef_sptr sp)
{
  FUNCTION_TRACE
  try
  {
    std::size_t geometryHash = 0;
    boost::hash_combine(geometryHash,getGridGeometryString());

    auto spr = spatialReferenceCache.find(geometryHash);
    if (spr)
      return;

    spatialReferenceCache.insert(geometryHash,sp);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief This method can be used for finding out the grid projection type (Mercator, LatLon, PolarStereographic, etc.).

        \return   The type of the grid projection (expressed as an enum value).
*/

T::GridProjection GridDefinition::getGridProjection() const
{
  FUNCTION_TRACE
  try
  {
    return mGridProjection;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid hash value.

        \return   The grid hash value.
*/

T::Hash GridDefinition::getGridHash() const
{
  FUNCTION_TRACE
  try
  {
    if (mHash == 0)
      mHash = countHash();

    return mHash;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::Hash GridDefinition::countHash() const
{
  FUNCTION_TRACE
  return 0;
}





void GridDefinition::getGridCellAverageSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    if (getGridMetricCellSize(width,height))
      return;

    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() == 2)
    {
      uint x = d.nx()/2;
      uint y = d.ny()/2;

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getGridMetricCellSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    width = 0;
    height = 0;
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getGridMetricSize(double& width,double& height) const
{
  FUNCTION_TRACE
  try
  {
    double w = 0;
    double h = 0;

    if (!getGridMetricCellSize(w,h))
      return false;

    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2)
      return false;

    width = d.nx() * w;
    height = d.ny() * h;
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the number of original values defined in the original grid.

      \return   The number of the values in the original grid.
*/

std::uint32_t GridDefinition::getGridOriginalValueCount() const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() == 2)
    {
      uint nx = d.nx();
      uint ny = d.ny();

      return nx * ny;
    }

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the index of given grid position in the original grid data.
    If the given grid position is outside of the grid data then the method
    returns -1. This is the case when the grid column (grid_i) is bigger than
    the length of the given grid row (grid_j), or if the given grid row (grid_j)
    is bigger than the actual number of grid rows.

      \param grid_i    The grid i-position.
      \param grid_j    The grid j-position.
      \return          The index of the original data position. If the position
                       is outside of the grid data then the method return -1.
*/

int GridDefinition::getGridOriginalValueIndex(uint grid_i,uint grid_j) const
{
  FUNCTION_TRACE
  try
  {
    auto d = getGridDimensions();
    if (d.getDimensions() == 2)
    {
      if (grid_j >= d.ny())
        return -1;

      if (grid_i >= d.nx() &&  !isGridGlobal())
        return -1;

      return (grid_j * d.nx() + (grid_i % d.nx()));
    }
    return -1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    std::size_t hash = 0;
    uint geomId = getGridGeometryId();
    if (geomId != 0)
    {
      boost::hash_combine(hash,geomId);
      boost::hash_combine(hash,lat);
      boost::hash_combine(hash,lon);

      auto it = transformCache2.find(hash);
      if (it)
      {
        transformCache2_stats.hits++;
        grid_i = it->x();
        grid_j = it->y();
        return true;
      }
      transformCache2_stats.misses++;
    }

    double x = 0, y = 0;
    getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);

    if (getGridPointByOriginalCoordinates(x,y,grid_i,grid_j))
    {
      if (hash != 0)
      {
        transformCache2.insert(hash,T::Coordinate(grid_i,grid_j));
        transformCache2_stats.inserts++;
        transformCache2_stats.size++;
      }
      return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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

bool GridDefinition::getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const
{
  FUNCTION_TRACE
  try
  {
    double x = 0, y = 0;
    getGridOriginalCoordinatesByLatLonCoordinatesNoCache(lat,lon,x,y);
    return getGridPointByOriginalCoordinates(x,y,grid_i,grid_j);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
  throw Fmi::Exception(BCP,"Not implemented!");
}





double GridDefinition::getEarthSemiMajor()
{
  try
  {
    return mEarth_semiMajor;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





double GridDefinition::getEarthSemiMinor()
{
  try
  {
    return mEarth_semiMinor;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDefinition::setEarthSemiMajor(double value)
{
  try
  {
    mEarth_semiMajor = value;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridDefinition::setEarthSemiMinor(double value)
{
  try
  {
    mEarth_semiMinor = value;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





double GridDefinition::getMajorAxis(uchar resolutionAndComponentFlags)
{
  FUNCTION_TRACE
  try
  {
    if (mEarth_semiMajor != 0) // The original value has be overridden
      return mEarth_semiMajor;

    if ((resolutionAndComponentFlags & 0x40) == 0)
      return  6367470;

    return 6378160;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





double GridDefinition::getMinorAxis(uchar resolutionAndComponentFlags)
{
  FUNCTION_TRACE
  try
  {
    if (mEarth_semiMinor != 0) // The original value has be overridden
      return mEarth_semiMinor;

    if ((resolutionAndComponentFlags & 0x40) == 0)
      return  6367470;

    return 6356775;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





double GridDefinition::getFlattening(uchar resolutionAndComponentFlags)
{
  FUNCTION_TRACE
  try
  {
    if (mEarth_semiMajor != 0  &&  mEarth_semiMinor != 0) // The original value has be overridden
      return (mEarth_semiMajor-mEarth_semiMinor)/mEarth_semiMajor;

    if ((resolutionAndComponentFlags & 0x40) == 0)
      return  0;

    return 1/297.0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




uint GridDefinition::getTemplateNumber() const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridDefinition::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void GridDefinition::write(DataWriter& dataWriter)
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridDefinition::print(std::ostream& stream,uint level,uint optionFlags) const
{
  FUNCTION_TRACE
  try
  {
    stream << space(level) << "* GridDefinition\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
