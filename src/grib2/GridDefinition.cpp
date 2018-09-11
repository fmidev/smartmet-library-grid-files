#include "GridDefinition.h"
#include "Properties.h"
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
    mGridProjection = T::GridProjectionValue::Unknown;
    mGridLayout = T::GridLayoutValue::Regular;
    mHash = 0;
    mOrigSpatialReference = nullptr;
    mCoordinateTranformation_latlon2orig = nullptr;
    mCoordinateTranformation_orig2latlon = nullptr;
    mGlobal = false;
    mGeometryId = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}




/*! \brief The copy destructor of the class. */

GridDefinition::GridDefinition(const GridDefinition& other)
{
  try
  {
    mSpatialReference = other.mSpatialReference;
    mGridLayout = other.mGridLayout;
    mHash = other.mHash;
    mGlobal = other.mGlobal;
    mGeometryId = other.mGeometryId;
    mGeometryName = other.mGeometryName;
    mGridProjection = other.mGridProjection;
    mOrigSpatialReference = nullptr;

    if (other.mOrigSpatialReference != nullptr)
      mOrigSpatialReference = other.mOrigSpatialReference->Clone();

    mCoordinateTranformation_latlon2orig = nullptr;
    mCoordinateTranformation_orig2latlon = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GridDefinition::~GridDefinition()
{
  FUNCTION_TRACE
  try
  {
    if (mCoordinateTranformation_latlon2orig != nullptr)
      OCTDestroyCoordinateTransformation(mCoordinateTranformation_latlon2orig);

    if (mCoordinateTranformation_orig2latlon)
      OCTDestroyCoordinateTransformation(mCoordinateTranformation_orig2latlon);

    if (mOrigSpatialReference != nullptr)
      mSpatialReference.DestroySpatialReference(mOrigSpatialReference);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





GridDefinition* GridDefinition::createGridDefinition() const
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void GridDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  FUNCTION_TRACE
}





EarthShapeSettings* GridDefinition::getEarthShape() const
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





T::GeometryId GridDefinition::getGridGeometryId() const
{
  FUNCTION_TRACE
  try
  {
    return mGeometryId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
        getGridLatLonCoordinatesByGridPoint(d.nx(),0,lat[1],lon[1]) &&
        getGridLatLonCoordinatesByGridPoint(0,d.ny(),lat[2],lon[2]) &&
        getGridLatLonCoordinatesByGridPoint(d.nx(),d.ny(),lat[3],lon[3]))
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridDefinition::setProperty(uint propertyId,long long value)
{
  FUNCTION_TRACE
  try
  {
    if (propertyId >= Property::GridSection::EarthShape::FirstProperty  &&  propertyId <= Property::GridSection::EarthShape::LastProperty)
    {
      return setProperty_EarthShape(propertyId,value);
    }

    if (propertyId >= Property::GridSection::Grid::FirstProperty  &&  propertyId <= Property::GridSection::Grid::LastProperty)
    {
      return setProperty_Grid(propertyId,value);
    }

    if (propertyId >= Property::GridSection::Rotation::FirstProperty  &&  propertyId <= Property::GridSection::Rotation::LastProperty)
    {
      return setProperty_Rotation(propertyId,value);
    }

    if (propertyId >= Property::GridSection::LatLon::FirstProperty  &&  propertyId <= Property::GridSection::LatLon::LastProperty)
    {
      return setProperty_LatLon(propertyId,value);
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string GridDefinition::getGridGeometryName()
{
  FUNCTION_TRACE
  try
  {
    return mGeometryName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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





uint GridDefinition::getTemplateNumber() const
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

    if (mCoordinateTranformation_orig2latlon == nullptr)
    {
      OGRSpatialReference sr_latlon;
      sr_latlon.importFromEPSG(4326);

      if (mOrigSpatialReference == nullptr)
        mOrigSpatialReference = mSpatialReference.Clone();

      mCoordinateTranformation_orig2latlon = OGRCreateCoordinateTransformation(mOrigSpatialReference,&sr_latlon);
      if (mCoordinateTranformation_orig2latlon == nullptr)
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridDefinition::getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2  || grid_i >= d.nx() || grid_j >= d.ny())
      return false;

    T::Coordinate_vec originalCoordinates = getGridCoordinates();
    uint c = grid_j * d.nx() + grid_i;
    if (c >= originalCoordinates.size())
      return false;

    x = originalCoordinates[c].x();
    y = originalCoordinates[c].y();

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridDefinition::getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const
{
  FUNCTION_TRACE
  try
  {
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2  || grid_i >= d.nx() || grid_j >= d.ny())
      return false;

    T::Coordinate_vec coordinates = getGridLatLonCoordinates();
    uint c = grid_j*d.nx() + grid_i;
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    if (mCoordinateTranformation_latlon2orig == nullptr)
    {
      OGRSpatialReference sr_latlon;
      sr_latlon.importFromEPSG(4326);

      if (mOrigSpatialReference == nullptr)
        mOrigSpatialReference = mSpatialReference.Clone();

      mCoordinateTranformation_latlon2orig = OGRCreateCoordinateTransformation(&sr_latlon,mOrigSpatialReference);
      if (mCoordinateTranformation_latlon2orig == nullptr)
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    if (mCoordinateTranformation_orig2latlon == nullptr)
    {
      OGRSpatialReference sr_latlon;
      sr_latlon.importFromEPSG(4326);

      if (mOrigSpatialReference == nullptr)
        mOrigSpatialReference = mSpatialReference.Clone();

      mCoordinateTranformation_orig2latlon = OGRCreateCoordinateTransformation(mOrigSpatialReference,&sr_latlon);
      if (mCoordinateTranformation_orig2latlon == nullptr)
        throw SmartMet::Spine::Exception(BCP,"Cannot create coordinate transformation!");
    }

    lat = y;
    lon = x;

    mCoordinateTranformation_orig2latlon->Transform(1,&lon,&lat);

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::SpatialRef* GridDefinition::getSpatialReference()
{
  FUNCTION_TRACE
  try
  {
    return &mSpatialReference;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridDefinition::getGridCellAverageSize(double& width,double& height)
{
  FUNCTION_TRACE
  try
  {
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
      return 6371229;
    }

    switch (*shape)
    {
      case 0: // Earth assumed spherical with radius = 6,367,470.0 m
        return 6371220;
        //return 6367470;

      case 1: // Earth assumed spherical with radius specified by data producer
        return (*earthSettings.getScaledValueOfEarthMajorAxis());

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        return 6378160;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        return (*earthSettings.getScaledValueOfEarthMajorAxis());

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        return 6378137;

      case 5: // Earth assumed represented by WGS84 (as used by ICAO since 1998)
        return 6378137;

      case 6: // Earth assumed spherical with radius of 6,371,229.0 m
        return 6371229;

      default:
        return 6371229;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
        return (*earthSettings.getScaledValueOfEarthMinorAxis());

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        return 6356775;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        return (*earthSettings.getScaledValueOfEarthMinorAxis());

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        return 6356752.314;

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
        return (1.0 / (1.0 - (C_DOUBLE(*earthSettings.getScaledValueOfEarthMinorAxis()) / C_DOUBLE(*earthSettings.getScaledValueOfEarthMajorAxis()))));

        return (*earthSettings.getScaledValueOfEarthMinorAxis());

      case 2: // Earth assumed oblate spheroid with size as determined by IAU in 1965 (major axis = 6,378,160.0 m, minor axis = 6,356,775.0 m, f = 1/297.0)
        return 1000000 * 1/297.0;

      case 3: // Earth assumed oblate spheroid with major and minor axes specified by data producer
        return (1.0 / (1.0 - (C_DOUBLE(*earthSettings.getScaledValueOfEarthMinorAxis()) / C_DOUBLE(*earthSettings.getScaledValueOfEarthMajorAxis()))));

      case 4: // Earth assumed oblate spheroid as defined in IAG-GRS80 model (major axis = 6,378,137.0 m, minor axis = 6,356,752.314 m, f = 1/298.257222101)
        return 6356752.314;

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridDefinition::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void GridDefinition::write(DataWriter& dataWriter)
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
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
