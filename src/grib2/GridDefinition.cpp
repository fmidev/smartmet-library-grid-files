#include "GridDefinition.h"
#include "Properties.h"
#include "../common/CoordinateConversions.h"
#include <macgyver/Exception.h>
#include "../common/ShowFunction.h"
#include "../common/AutoWriteLock.h"
#include "../common/AutoReadLock.h"
#include <boost/functional/hash.hpp>

#include <iostream>
#include <map>
#include <unordered_map>
#include <iostream>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRIB2
{


std::unordered_map<uint,T::Coordinate_svec> coordinateCache;
std::unordered_map <std::size_t,T::Coordinate> transformCache1;
std::unordered_map <std::size_t,T::Coordinate> transformCache2;

std::size_t      mPrevHash1[10000] = {0};
T::Coordinate    mPrevCoordinate1[10000];
std::size_t      mPrevHash2[10000] = {0};
T::Coordinate    mPrevCoordinate2[10000];

ModificationLock coordinateCacheModificationLock;
ModificationLock transformCache1ModificationLock;
ModificationLock transformCache2ModificationLock;



/*! \brief The constructor of the class. */

GridDefinition::GridDefinition()
{
  FUNCTION_TRACE
  try
  {
    mGridProjection = T::GridProjectionValue::Unknown;
    mHash = 0;
    mGlobal = false;
    mGeometryId = 0;
    mLatlonSpatialReference.importFromEPSG(4326);
    mLatlonSpatialReference.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
    mEarth_semiMajor = 0;
    mEarth_semiMinor = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}




/*! \brief The copy destructor of the class. */

GridDefinition::GridDefinition(const GridDefinition& other)
{
  try
  {
    mSpatialReference = other.mSpatialReference;
    mHash = other.mHash;
    mGlobal = other.mGlobal;
    mGeometryId = other.mGeometryId;
    mGridProjection = other.mGridProjection;
    mEarth_semiMajor = other.mEarth_semiMajor;
    mEarth_semiMinor = other.mEarth_semiMinor;
    mLatlonSpatialReference.importFromEPSG(4326);
    mLatlonSpatialReference.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);
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
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





GridDefinition* GridDefinition::createGridDefinition() const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}





void GridDefinition::getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
}





EarthShapeSettings* GridDefinition::getEarthShape() const
{
  FUNCTION_TRACE
  return nullptr;
}





ResolutionSettings* GridDefinition::getResolution() const
{
  FUNCTION_TRACE
  return nullptr;
}





LatLonSettings* GridDefinition::getLatLon() const
{
  FUNCTION_TRACE
  return nullptr;
}





RotationSettings* GridDefinition::getRotation() const
{
  FUNCTION_TRACE
  return nullptr;
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

    OGRSpatialReference sr_latlon;
    sr_latlon.importFromEPSG(4326);
    sr_latlon.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    OGRSpatialReference sr_wgs84_world_mercator;
    sr_wgs84_world_mercator.importFromEPSG(3395);
    sr_wgs84_world_mercator.SetAxisMappingStrategy(OAMS_TRADITIONAL_GIS_ORDER);

    OGRCoordinateTransformation *transformation = OGRCreateCoordinateTransformation(&sr_latlon,&sr_wgs84_world_mercator);

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





/*! \brief This method can be used for finding out the grid projection type (Mercator, LatLon, PolarStereographic, etc.).

        \return   The type of the grid projection (expressed as an enum value).
*/

T::GridProjection GridDefinition::getGridProjection()
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





/*! \brief The method is used for fetching a (long long ) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool GridDefinition::getProperty(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    if (getProperty_EarthShape(propertyId,value))
      return true;

    if (getProperty_Grid(propertyId,value))
      return true;

    if (getProperty_Rotation(propertyId,value))
      return true;

    if (getProperty_LatLon(propertyId,value))
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getProperty_EarthShape(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    EarthShapeSettings *earthShape = getEarthShape();
    if (earthShape == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::EarthShape::ShapeOfTheEarth:
        value = *earthShape->getShapeOfTheEarth();
        return true;

      case Property::GridSection::EarthShape::ScaleFactorOfRadiusOfSphericalEarth:
        value = *earthShape->getScaleFactorOfRadiusOfSphericalEarth();
        return true;

      case Property::GridSection::EarthShape::ScaledValueOfRadiusOfSphericalEarth:
        value = *earthShape->getScaledValueOfRadiusOfSphericalEarth();
        return true;

      case Property::GridSection::EarthShape::ScaleFactorOfEarthMajorAxis:
        value = *earthShape->getScaleFactorOfEarthMajorAxis();
        return true;

      case Property::GridSection::EarthShape::ScaledValueOfEarthMajorAxis:
        value = *earthShape->getScaledValueOfEarthMajorAxis();
        return true;

      case Property::GridSection::EarthShape::ScaleFactorOfEarthMinorAxis:
        value = *earthShape->getScaleFactorOfEarthMinorAxis();
        return true;

      case Property::GridSection::EarthShape::ScaledValueOfEarthMinorAxis:
        value = *earthShape->getScaledValueOfEarthMinorAxis();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getProperty_Grid(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    LatLonSettings *latlon = getLatLon();
    if (latlon == nullptr)
      return false;

    GridSettings *grid = latlon->getGrid();
    if (grid == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::Grid::Ni:
        value = *grid->getNi();
        return true;

      case Property::GridSection::Grid::Nj:
        value = *grid->getNj();
        return true;

      case Property::GridSection::Grid::BasicAngleOfTheInitialProductionDomain:
        value = *grid->getBasicAngleOfTheInitialProductionDomain();
        return true;

      case Property::GridSection::Grid::SubdivisionsOfBasicAngle:
        value = *grid->getSubdivisionsOfBasicAngle();
        return true;

      case Property::GridSection::Grid::LatitudeOfFirstGridPoint:
        value = *grid->getLatitudeOfFirstGridPoint();
        return true;

      case Property::GridSection::Grid::LongitudeOfFirstGridPoint:
        value = *grid->getLongitudeOfFirstGridPoint();
        return true;

      case Property::GridSection::Grid::LatitudeOfLastGridPoint:
        value = *grid->getLatitudeOfLastGridPoint();
        return true;

      case Property::GridSection::Grid::LongitudeOfLastGridPoint:
        value = *grid->getLongitudeOfLastGridPoint();
        return true;

      case Property::GridSection::Grid::ResolutionAndComponentFlags:
      {
        ResolutionSettings *resolution = grid->getResolution();
        if (resolution != nullptr)
        {
          value = resolution->getResolutionAndComponentFlags();
          return true;
        }
        return false;
      }
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getProperty_Rotation(uint propertyId,long long& value)
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
        value = *rotation->getLatitudeOfSouthernPole();
        return true;

      case Property::GridSection::Rotation::LongitudeOfSouthernPole:
        value = *rotation->getLongitudeOfSouthernPole();
        return true;

      case Property::GridSection::Rotation::AngleOfRotation:
        value = rotation->getAngleOfRotation();
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::getProperty_LatLon(uint propertyId,long long& value)
{
  FUNCTION_TRACE
  try
  {
    LatLonSettings *latlon = getLatLon();
    if (latlon == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::LatLon::IDirectionIncrement:
        value = *latlon->getIDirectionIncrement();
        return true;

      case Property::GridSection::LatLon::JDirectionIncrement:
        value = *latlon->getJDirectionIncrement();
        return true;

      case Property::GridSection::LatLon::ScanningMode:
      {
        ScanningModeSettings *scanningMode = latlon->getScanningMode();
        if (scanningMode != nullptr)
        {
          value = scanningMode->getScanningMode();
          return true;
        }
        return false;
      }
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
    if (setProperty_EarthShape(propertyId,value))
      return true;

    if (setProperty_Grid(propertyId,value))
      return true;

    if (setProperty_Rotation(propertyId,value))
      return true;

    if (setProperty_LatLon(propertyId,value))
      return true;

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::setProperty_EarthShape(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    EarthShapeSettings *earthShape = getEarthShape();
    if (earthShape == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::EarthShape::ShapeOfTheEarth:
        earthShape->setShapeOfTheEarth(value);
        return true;

      case Property::GridSection::EarthShape::ScaleFactorOfRadiusOfSphericalEarth:
        earthShape->setScaleFactorOfRadiusOfSphericalEarth(value);
        return true;

      case Property::GridSection::EarthShape::ScaledValueOfRadiusOfSphericalEarth:
        earthShape->setScaledValueOfRadiusOfSphericalEarth(value);
        return true;

      case Property::GridSection::EarthShape::ScaleFactorOfEarthMajorAxis:
        earthShape->setScaleFactorOfEarthMajorAxis(value);
        return true;

      case Property::GridSection::EarthShape::ScaledValueOfEarthMajorAxis:
        earthShape->setScaledValueOfEarthMajorAxis(value);
        return true;

      case Property::GridSection::EarthShape::ScaleFactorOfEarthMinorAxis:
        earthShape->setScaleFactorOfEarthMinorAxis(value);
        return true;

      case Property::GridSection::EarthShape::ScaledValueOfEarthMinorAxis:
        earthShape->setScaledValueOfEarthMinorAxis(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::setProperty_Grid(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    LatLonSettings *latlon = getLatLon();
    if (latlon == nullptr)
      return false;

    GridSettings *grid = latlon->getGrid();
    if (grid == nullptr)
      return false;


    switch (propertyId)
    {
      case Property::GridSection::Grid::Ni:
        grid->setNi(value);
        return true;

      case Property::GridSection::Grid::Nj:
        grid->setNj(value);
        return true;

      case Property::GridSection::Grid::BasicAngleOfTheInitialProductionDomain:
        grid->setBasicAngleOfTheInitialProductionDomain(value);
        return true;

      case Property::GridSection::Grid::SubdivisionsOfBasicAngle:
        grid->setSubdivisionsOfBasicAngle(value);
        return true;

      case Property::GridSection::Grid::LatitudeOfFirstGridPoint:
        grid->setLatitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::Grid::LongitudeOfFirstGridPoint:
        grid->setLongitudeOfFirstGridPoint(value);
        return true;

      case Property::GridSection::Grid::LatitudeOfLastGridPoint:
        grid->setLatitudeOfLastGridPoint(value);
        return true;

      case Property::GridSection::Grid::LongitudeOfLastGridPoint:
        grid->setLongitudeOfLastGridPoint(value);
        return true;

      case Property::GridSection::Grid::ResolutionAndComponentFlags:
      {
        ResolutionSettings *resolution = grid->getResolution();
        if (resolution != nullptr)
        {
          resolution->setResolutionAndComponentFlags(value);
          return true;
        }
        return false;
      }
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::setProperty_Rotation(uint propertyId,long long value)
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

      case Property::GridSection::Rotation::AngleOfRotation:
        rotation->setAngleOfRotation(value);
        return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDefinition::setProperty_LatLon(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    LatLonSettings *latlon = getLatLon();
    if (latlon == nullptr)
      return false;

    switch (propertyId)
    {
      case Property::GridSection::LatLon::IDirectionIncrement:
        latlon->setIDirectionIncrement(value);
        return true;

      case Property::GridSection::LatLon::JDirectionIncrement:
        latlon->setJDirectionIncrement(value);
        return true;

      case Property::GridSection::LatLon::ScanningMode:
      {
        ScanningModeSettings *scanningMode = latlon->getScanningMode();
        if (scanningMode != nullptr)
        {
          scanningMode->setScanningMode(value);
          return true;
        }
        return false;
      }
    }

    return false;
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
    This method should be overridden in the child classes.

        \return   The grid coordinates.
*/

T::Coordinate_svec GridDefinition::getGridOriginalCoordinates() const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
}





uint GridDefinition::getTemplateNumber() const
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"Not implemented!");
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
      AutoReadLock lock(&coordinateCacheModificationLock);
      auto it = coordinateCache.find(geomId);
      if (it != coordinateCache.end())
      {
        return it->second;
      }
    }

    T::Coordinate_svec originalCoordinates = getGridOriginalCoordinates();
    T::Coordinate_svec latLonCoordinates(new T::Coordinate_vec());

    int sz = originalCoordinates->size();
    latLonCoordinates->reserve(sz);

    double *lat = new double[sz+1];
    double *lon = new double[sz+1];

    std::shared_ptr<double> rlat(lat);
    std::shared_ptr<double> rlon(lon);

    for (int t=0; t<sz; t++)
    {
      auto cc = (*originalCoordinates)[t];
      lat[t] = cc.y();
      lon[t] = cc.x();

    }
    convert(&mSpatialReference,&mLatlonSpatialReference,sz,lon,lat);

    for (int t=0; t<sz; t++)
    {
      latLonCoordinates->emplace_back(T::Coordinate(lon[t],lat[t]));
    }

    if (geomId != 0)
    {
      AutoWriteLock lock(&coordinateCacheModificationLock);
      coordinateCache.insert(std::pair<uint,T::Coordinate_svec>(geomId,latLonCoordinates));
    }

    return latLonCoordinates;
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
    if (c >= originalCoordinates->size())
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
  throw Fmi::Exception(BCP,"This method should be implemented in a child class!");
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





/*! \brief The method initializes the spatial reference of the current grid.

    This method should be overridden in the child classes.
*/

void GridDefinition::initSpatialReference()
{
  FUNCTION_TRACE
  throw Fmi::Exception(BCP,"This method should be implemented in a child class!");
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
    ResolutionSettings *resolution = getResolution();
    if (resolution)
    {
      if (resolution->getResolutionAndComponentFlags() & 0x08)
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
    points.reserve(sz);

    double *x = new double[sz+1];
    double *y = new double[sz+1];

    std::shared_ptr<double> rx(x);
    std::shared_ptr<double> ry(y);

    for (uint t=0; t<sz; t++)
    {
      auto cc = latlon[t];
      x[t] = cc.x();
      y[t] = cc.y();
    }

    convert(&mLatlonSpatialReference,&mSpatialReference,sz,x,y);

    for (uint t=0; t<sz; t++)
    {
      double i = 0,j = 0;
      if (getGridPointByOriginalCoordinates(x[t],y[t],i,j))
        points.emplace_back(T::Coordinate(i,j));
      else
        points.emplace_back(T::Coordinate(ParamValueMissing,ParamValueMissing));
    }
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
    uint idx = 0;
    uint geomId = getGridGeometryId();
    if (geomId != 0)
    {
      boost::hash_combine(hash,geomId);
      boost::hash_combine(hash,lat);
      boost::hash_combine(hash,lon);
      idx = hash % 10000;

      {
        AutoReadLock lock(&transformCache2ModificationLock);

        if (mPrevHash2[idx] == hash)
        {
          grid_i = mPrevCoordinate2[idx].x();
          grid_j = mPrevCoordinate2[idx].y();
          return true;
        }

        auto it = transformCache2.find(hash);
        if (it != transformCache2.end())
        {
          grid_i = it->second.x();
          grid_j = it->second.y();
          mPrevHash2[idx] = hash;
          mPrevCoordinate2[idx] = it->second;
          return true;
        }
      }
    }

    double x = 0, y = 0;

    getGridOriginalCoordinatesByLatLonCoordinates(lat,lon,x,y);

    if (getGridPointByOriginalCoordinates(x,y,grid_i,grid_j))
    {
      if (hash != 0)
      {
        AutoWriteLock lock(&transformCache2ModificationLock);
        if (transformCache2.size() >= 1000000)
          transformCache2.clear();

        mPrevHash2[idx] = hash;
        mPrevCoordinate2[idx] = T::Coordinate(grid_i,grid_j);

        transformCache2.insert(std::pair<std::size_t,T::Coordinate>(hash,mPrevCoordinate2[idx]));
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





/*! \brief The method returns the grid latlon coordinates in the given grid point (= integer coordinates).

        \param grid_i  The grid i-coordinate.
        \param grid_j  The grid j-coordinate.
        \param lat     The latitude value is returned in this parameter.
        \param lon     The longitude value is returned in this parameter.
        \return   The method return true if the latlon values were succesfully returned.
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
    uint idx = 0;
    uint geomId = getGridGeometryId();
    if (geomId != 0)
    {
      boost::hash_combine(hash,geomId);
      boost::hash_combine(hash,lat);
      boost::hash_combine(hash,lon);
      idx = hash % 10000;

      {
        AutoReadLock lock(&transformCache1ModificationLock);

        if (mPrevHash1[idx] == hash)
        {
          x = mPrevCoordinate1[idx].x();
          y = mPrevCoordinate1[idx].y();
          return true;
        }

        auto it = transformCache1.find(hash);
        if (it != transformCache1.end())
        {
          x = it->second.x();
          y = it->second.y();
//          fprintf(stderr,"CACHE %f,%f => %f,%f\n",lat,lon,x,y);
          mPrevHash1[idx] = hash;
          mPrevCoordinate1[idx] = it->second;
          return true;
        }
      }
    }

    x = lon;
    y = lat;

    convert(&mLatlonSpatialReference,&mSpatialReference,1,&x,&y);

    //fprintf(stderr,"TRANSFORM %f,%f => %f,%f\n",lat,lon,x,y);
    if (hash != 0)
    {
      AutoWriteLock lock(&transformCache1ModificationLock);
      if (transformCache1.size() >= 1000000)
        transformCache1.clear();

      mPrevHash1[idx] = hash;
      mPrevCoordinate1[idx] = T::Coordinate(x,y);

      //fprintf(stderr,"INSERT %f,%f => %f,%f\n",lat,lon,x,y);
      transformCache1.insert(std::pair<std::size_t,T::Coordinate>(hash,mPrevCoordinate1[idx]));
    }

    return true;
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

    return convert(&mLatlonSpatialReference,&mSpatialReference,1,&x,&y);
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
    lat = y;
    lon = x;

    return convert(&mSpatialReference,&mLatlonSpatialReference,1,&lon,&lat);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string GridDefinition::getWKT()
{
  FUNCTION_TRACE
  try
  {
    std::string wkt;
    T::SpatialRef *sr = getSpatialReference();
    if (sr != nullptr)
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
    T::SpatialRef *sr = getSpatialReference();
    if (sr != nullptr)
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

T::SpatialRef* GridDefinition::getSpatialReference()
{
  FUNCTION_TRACE
  try
  {
    return &mSpatialReference;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid hash value.

        \return   The grid hash value.
*/

T::Hash GridDefinition::getGridHash()
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
      int x = d.nx()/2;
      int y = d.ny()/2;

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





T::Hash GridDefinition::countHash()
{
  FUNCTION_TRACE
  // Hash not defined
  return 0;
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





double GridDefinition::getMajorAxis(EarthShapeSettings& earthSettings)
{
  FUNCTION_TRACE
  try
  {
    if (mEarth_semiMajor != 0) // The original value has be overridden
      return mEarth_semiMajor;

    double defaultValue = 6367470; //  6371229;
    double value = 0;

    auto shape = earthSettings.getShapeOfTheEarth();
    if (!shape)
      return defaultValue;

    double radius_sf = *earthSettings.getScaleFactorOfRadiusOfSphericalEarth();
    double radius_v = *earthSettings.getScaledValueOfRadiusOfSphericalEarth();

    if (radius_sf == 0)
      radius_sf = 1;

    double major_sf = (*earthSettings.getScaleFactorOfEarthMajorAxis());
    double major_v = (*earthSettings.getScaledValueOfEarthMajorAxis());

    if (major_sf == 0)
      major_sf = 1;

    switch (*shape)
    {
      case 0: // Earth assumed spherical with radius = 6,367,470.0 m
        value = 6367470;
        break;

      case 1: // Earth assumed spherical with radius specified by data producer
        value = radius_sf * radius_v;
        break;

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        value = 6378160;
        break;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        value = major_sf * major_v;
        break;

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        value = 6378137;
        break;

      case 5: // Earth assumed represented by WGS84 (as used by ICAO since 1998)
        value = 6378137;
        break;

      case 6: // Earth assumed spherical with radius of 6,371,229.0 m
        value = 6371229;
        break;

      default:
        value = 6371229;
        break;
    }

    if (std::abs(value-defaultValue) < 10000)
      return value;

    return defaultValue;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





double GridDefinition::getMinorAxis(EarthShapeSettings& earthSettings)
{
  FUNCTION_TRACE
  try
  {
    if (mEarth_semiMinor != 0) // The original value has be overridden
      return mEarth_semiMinor;

    double defaultValue = 0;
    double value = 0;
    auto shape = earthSettings.getShapeOfTheEarth();
    if (!shape)
      return 0;

    double radius_sf = *earthSettings.getScaleFactorOfRadiusOfSphericalEarth();
    double radius_v = *earthSettings.getScaledValueOfRadiusOfSphericalEarth();

    if (radius_sf == 0)
      radius_sf = 1;
/*
    double major_sf = (*earthSettings.getScaleFactorOfEarthMajorAxis());
    double major_v = (*earthSettings.getScaledValueOfEarthMajorAxis());

    if (major_sf == 0)
      major_sf = 1;
*/
    double minor_sf = (*earthSettings.getScaleFactorOfEarthMinorAxis());
    double minor_v = (*earthSettings.getScaledValueOfEarthMinorAxis());

    if (minor_sf == 0)
      minor_sf = 1;

    switch (*shape)
    {
      case 0: // Earth assumed spherical with radius = 6,367,470.0 m
        value = 0;
        break;

      case 1: // Earth assumed spherical with radius specified by data producer
        value = radius_sf * radius_v;
        break;

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        value = 6356775;
        break;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        value = minor_sf * minor_v;
        break;

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        value = 6356752.314;
        break;

      case 5: // Earth assumed represented by WGS84 (as used by ICAO since 1998)
        value = 0;
        break;

      case 6: // Earth assumed spherical with radius of 6,371,229.0 m
        value = 0;
        break;

      default:
        value = 0;
        break;
    }

    if (value != 0)
      return value;

    return defaultValue;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






double GridDefinition::getFlattening(EarthShapeSettings& earthSettings)
{
  FUNCTION_TRACE
  try
  {
    if (mEarth_semiMajor != 0  &&  mEarth_semiMinor != 0) // The original value has be overridden
      return (mEarth_semiMajor-mEarth_semiMinor)/mEarth_semiMajor;

    double defaultValue = 0;
    double value = 0;

    auto shape = earthSettings.getShapeOfTheEarth();
    if (!shape)
      return 0;
/*
    double radius_sf = *earthSettings.getScaleFactorOfRadiusOfSphericalEarth();
    double radius_v = *earthSettings.getScaledValueOfRadiusOfSphericalEarth();

    if (radius_sf == 0)
      radius_sf = 1;
*/
    double major_sf = (*earthSettings.getScaleFactorOfEarthMajorAxis());
    double major_v = (*earthSettings.getScaledValueOfEarthMajorAxis());

    if (major_sf == 0)
      major_sf = 1;

    double minor_sf = (*earthSettings.getScaleFactorOfEarthMinorAxis());
    double minor_v = (*earthSettings.getScaledValueOfEarthMinorAxis());

    if (minor_sf == 0)
      minor_sf = 1;


    switch (*shape)
    {
      case 0: // Earth assumed spherical with radius = 6,367,470.0 m
        value = 0;
        break;

      case 1: // Earth assumed spherical with radius specified by data producer
        value = 0;
        break;

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        value = 1/297.0;
        break;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        if (minor_v > 0 &&  major_v > 0)
          value = ((major_sf * major_v) - (minor_sf * minor_v)) / (major_sf * major_v);
        else
          value = 0;
        break;

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        value = 1/298.257222101;
        break;

      case 5: // Earth assumed represented by WGS84 (as used by ICAO since 1998)
        value = 1/298.257222101;
        break;

      case 6: // Earth assumed spherical with radius of 6,371,229.0 m
        value = 0;
        break;

      default:
        value = 0;
        break;
    }

    if (value != 0)
      return value;

    return defaultValue;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
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
  throw Fmi::Exception(BCP,"Not implemented!");
}



}  // namespace GRIB2
}  // namespace SmartMet
