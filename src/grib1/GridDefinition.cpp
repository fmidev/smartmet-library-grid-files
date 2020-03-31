#include "GridDefinition.h"
#include "Properties.h"
#include "../common/Exception.h"
#include "../common/CoordinateConversions.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/ShowFunction.h"
#include <iostream>


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRIB1
{

std::map<uint,T::Coordinate_vec> coordinateCache;


double gTransformCache[5];


/*! \brief The constructor of the class. */

GridDefinition::GridDefinition()
{
  FUNCTION_TRACE
  try
  {
    mGridLayout = T::GridLayoutValue::Regular;
    mHash = 0;
    mOrigSpatialReference = nullptr;
    mCoordinateTranformation_latlon2orig = nullptr;
    mCoordinateTranformation_orig2latlon = nullptr;
    mGlobal = false;
    mGeometryId = 0;
    mGridProjection = T::GridProjectionValue::Unknown;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

GridDefinition::GridDefinition(const GridDefinition& other)
{
  FUNCTION_TRACE
  try
  {
     mSpatialReference = other.mSpatialReference;
     mGridLayout = other.mGridLayout;
     mHash = other.mHash;
     mGlobal = other.mGlobal;
     mRowPositions = other.mRowPositions;
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
    SmartMet::Spine::Exception exception(BCP,"Destructor failed!",nullptr);
    exception.printError();
  }
}





GridDefinition* GridDefinition::createGridDefinition() const
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





void GridDefinition::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

    OGRSpatialReference sr_wgs84_world_mercator;
    sr_wgs84_world_mercator.importFromEPSG(3395);

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2  || grid_i >= d.nx() || grid_j >= d.ny())
      return false;

    T::Coordinate_vec coordinates = getGridLatLonCoordinates();
    uint c = grid_j*d.nx() + grid_i;
    if (c < coordinates.size())
    {
      lon = getLongitude(coordinates[c].x());
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    T::Dimensions d = getGridDimensions();
    if (d.getDimensions() != 2  || grid_i >= d.nx() || grid_j >= d.ny())
      return false;

    T::Coordinate_vec originalCoordinates = getGridOriginalCoordinates();
    uint c = grid_j * d.nx() + grid_i;
    if (c >= C_UINT(originalCoordinates.size()))
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
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns all grid coordinates as a coordinate vector.
    Notice that if the grid layout is "irregular" (i.e. its row lengths vary) then
    grid width is the same as the length of the longest grid row. I.e. the coordinates
    are returned as the grid would be a regular grid.
    This method should be overridden in the child classes.

       \return   The grid coordinates.
*/

T::Coordinate_vec GridDefinition::getGridOriginalCoordinates() const
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}






/*! \brief The method returns all grid coordinates as a latlon coordinate vector. If the grid
    original coordiantes were not latlon coordinates then the original coordinates are converted
    to the latlon coordinates.

        \return   The grid latlon coordinates.
*/

T::Coordinate_vec GridDefinition::getGridLatLonCoordinates() const
{
  FUNCTION_TRACE
  try
  {
    //printf("*** GET COORDINATES version 1\n");

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

    T::Coordinate_vec originalCoordinates = getGridOriginalCoordinates();
    T::Coordinate_vec latLonCoordinates;

    latLonCoordinates.reserve(originalCoordinates.size());


    for (auto it = originalCoordinates.begin(); it != originalCoordinates.end(); ++it)
    {
      double lat = it->y();
      double lon = it->x();

      mCoordinateTranformation_orig2latlon->Transform(1,&lon,&lat);

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
    if (mGeometryId != 0  &&  C_INT(gTransformCache[0]) == mGeometryId &&  gTransformCache[1] == lat  &&  gTransformCache[2] == lon)
    {
      x = gTransformCache[3];
      y = gTransformCache[4];
      return true;
    }

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

    gTransformCache[0] = mGeometryId;
    gTransformCache[1] = lat;
    gTransformCache[2] = lon;
    gTransformCache[3] = x;
    gTransformCache[4] = y;

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

    lon = x;
    lat = y;

    mCoordinateTranformation_orig2latlon->Transform(1,&lon,&lat);

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






/*! \brief The method returns 'true' if the grid horizontal values are in the reverse order.

        \return   The method returns 'true' if the grid horizontal values are in the reverse
                  order. Otherwise it returns 'false'
*/

bool GridDefinition::reverseXDirection() const
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method returns 'true' if the grid vertical values are in the reverse order.

        \return   The method returns 'true' if the grid vertical values are in the reverse
                  order. Otherwise it returns 'false'
*/

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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    }

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method initializes the spatial reference of the current grid.

    This method should be overridden in the child classes.
*/

void GridDefinition::initSpatialReference()
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"This method should be implemented in a child class!");
}





/*! \brief The method initializes the row start positions in the case of an irregular
    grid. The point is that each grid row might contain different number of grid columns
    (i.e the row lengths are varying).

       \param   The vector of the start positions of the grid rows.
*/

void GridDefinition::initRowPositions(std::vector<std::uint32_t>& rowPositions)
{
  FUNCTION_TRACE
  try
  {
    mRowPositions = rowPositions;
    mGridLayout = T::GridLayoutValue::Irregular;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Hash GridDefinition::countHash()
{
  FUNCTION_TRACE
  return 0;
}





void GridDefinition::getGridCellAverageSize(double& width,double& height)
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the number of rows used in the original grid.

     \return   The number of the grid rows.
*/

std::size_t GridDefinition::getGridOriginalRowCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mRowPositions.size() > 0)
      return mRowPositions.size() - 1;

    auto d = getGridDimensions();
    if (d.getDimensions() == 2)
      return d.ny();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the number of columns used in the given original grid row.

      \param row    The grid row index (= j-position).
      \return       The number of columns in the given grid row.
*/

std::size_t GridDefinition::getGridOriginalColumnCount(std::size_t row) const
{
  FUNCTION_TRACE
  try
  {
    if (mRowPositions.size() > 0)
    {
      if ((row+1) < mRowPositions.size())
        return mRowPositions[row+1] - mRowPositions[row];

      return 0;
    }

    auto d = getGridDimensions();
    if (d.getDimensions() == 2)
      return d.nx();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the maximum number of the columns used in the original grid.
    If the grid is irregular, this method returns the length of the longest row.

       \return   The maximum number of the columns in the grid.
*/

std::size_t GridDefinition::getGridOriginalColumnCount() const
{
  FUNCTION_TRACE
  try
  {
    if (mRowPositions.size() > 0)
    {
      std::size_t cnt = 0;
      std::size_t rows = getGridOriginalRowCount();
      for (std::size_t t=0; t<rows; t++)
      {
        auto len = getGridOriginalColumnCount(t);
        if (len > cnt)
          cnt = len;
      }
      return cnt;
    }

    auto d = getGridDimensions();
    if (d.getDimensions() == 2)
      return d.nx();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the index of given grid position in the original grid data.
    In the case of irregular grid the grid rows might contain different number of
    columns. If the given grid position is outside of the grid data then the method
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
    if (mRowPositions.size() > 0)
    {
      if (grid_j < mRowPositions.size()-1)
      {
        int pos = mRowPositions[grid_j] + grid_i;
        if ((std::size_t)pos < mRowPositions[grid_j+1])
          return pos;
      }
      return -1;
    }
    else
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
    }
    return -1;
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





double GridDefinition::getMajorAxis(uchar resolutionAndComponentFlags)
{
  FUNCTION_TRACE
  try
  {
    if ((resolutionAndComponentFlags & 0x40) == 0)
      return  6367470;

    return 6378160;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





double GridDefinition::getMinorAxis(uchar resolutionAndComponentFlags)
{
  FUNCTION_TRACE
  try
  {
    if ((resolutionAndComponentFlags & 0x40) == 0)
      return  6367470;

    return 6356775;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





double GridDefinition::getFlattening(uchar resolutionAndComponentFlags)
{
  FUNCTION_TRACE
  try
  {
    if ((resolutionAndComponentFlags & 0x40) == 0)
      return  0;

    return 1/297.0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




uint GridDefinition::getTemplateNumber() const
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridDefinition::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

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
  try
  {
    stream << space(level) << "* GridDefinition\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
