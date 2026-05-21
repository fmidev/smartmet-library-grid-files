#pragma once

#include "MessageSection.h"
#include "Typedefs.h"
#include "GridPointValue.h"
#include "GridPointValueList.h"
#include "GridValueList.h"
#include "../common/AttributeList.h"
#include "../common/Coordinate.h"
#include "../common/Dimensions.h"
#include "../common/GraphFunctions.h"
#include "../common/AutoThreadLock.h"
#include "../common/AutoWriteLock.h"
#include "../common/AutoReadLock.h"
#include "../common/ThreadLock.h"
#include "../common/RequestCounter.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/StringFactory.h"

#include <vector>
#include <string>
#include <memory>



namespace SmartMet
{
namespace GRID
{

/*! \brief Pre-parsed metadata for a single message, used during lazy message construction. */
struct MessageInfo
{
  T::FilePosition    mFilePosition;       //!< Byte offset of the message within the file
  char*              mFileMemoryPtr;      //!< Pointer to the mapped file start
  uint               mMessageType;        //!< Message format type (T::FileTypeValue)
  uint               mMessageSize;        //!< Size of the message in bytes
  T::ProducerId      mProducerId;         //!< Data producer identifier
  T::GenerationId    mGenerationId;       //!< Forecast generation (run) identifier
  T::FmiParamId      mFmiParameterId;     //!< FMI internal parameter identifier
  uint               mFmiParameterName;   //!< FMI parameter name (StringFactory index)
  T::ParamLevelId    mFmiParameterLevelId; //!< FMI level type identifier
  T::ParamLevel      mParameterLevel;     //!< Vertical level value
  time_t             mForecastTime;       //!< Forecast valid time (Unix timestamp)
  T::ForecastType    mForecastType;       //!< Forecast type (deterministic, ensemble, …)
  T::ForecastNumber  mForecastNumber;     //!< Ensemble member number, or -1 for deterministic
  T::GeometryId      mGeometryId;         //!< Grid geometry identifier
};

typedef std::map<uint,MessageInfo> MessageInfo_map; //!< Map from message index to MessageInfo


class GridFile;

// ====================================================================================
/*! \brief Abstract base class for all grid messages (GRIB1, GRIB2, NetCDF, QueryData).
 *
 *  Provides the complete public interface for accessing parameter metadata, grid
 *  geometry, coordinate conversions, packed-data retrieval, interpolation, isoband/
 *  isoline extraction, and serialisation.  Applications should work exclusively
 *  through this interface and never depend on format-specific subclasses. */
// ====================================================================================

class Message
{
  public:

                                Message();
                                /*! \brief Copy constructor. */
                                Message(const Message& message);
    virtual                     ~Message();

    /*! \brief Populate \p attributeList with all message fields as key/value pairs.
     *  \param[in]  prefix         String prepended to every attribute key.
     *  \param[out] attributeList  Receives the message attributes. */
    virtual void                getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;

    /*! \brief Look up a single attribute value by name.
     *  \param[in]  attributeName   Attribute key to look up.
     *  \param[out] attributeValue  Receives the value string.
     *  \return True if the attribute was found. */
    virtual bool                getAttributeValue(const char *attributeName, std::string& attributeValue) const;

    /*! \brief Test whether a named attribute has a specific value.
     *  \param[in] attributeName   Attribute key.
     *  \param[in] attributeValue  Expected value string.
     *  \return True if the attribute exists and equals the given value. */
    virtual bool                hasAttributeValue(const char *attributeName, const char *attributeValue) const;

    /*! \brief Return the identifier of the file that contains this message. */
    virtual T::FileId           getFileId() const;

    /*! \brief Return the file-format type of this message (T::FileTypeValue). */
    virtual T::FileType         getMessageType() const;

    /*! \brief Return the data producer identifier. */
    virtual T::ProducerId       getProducerId() const;

    /*! \brief Return the forecast generation (run) identifier. */
    virtual T::GenerationId     getGenerationId() const;

    /*! \brief Return the zero-based index of this message within its file. */
    virtual T::MessageIndex     getMessageIndex() const;

    /*! \brief Return a pointer to the start of this message's packed data in the memory map. */
    virtual char*               getMemoryPtr() const;

    /*! \brief Return the packed message size in bytes. */
    virtual uint                getMessageSize() const;

    /*! \brief Return the byte offset of this message within the file. */
    virtual T::FilePosition     getFilePosition() const;

    /*! \brief Return a pointer to the start of the mapped file (not the message). */
    virtual char*               getFileMemoryPtr() const;

    /*! \brief Return the forecast valid time as an ISO-8601 string. */
    virtual T::TimeString       getForecastTime() const;

    /*! \brief Return the forecast valid time as a Unix timestamp. */
    virtual time_t              getForecastTimeT() const;

    /*! \brief Return the forecast type code (deterministic, ensemble member, …). */
    virtual T::ForecastType     getForecastType() const;

    /*! \brief Return the ensemble member number, or -1 for deterministic forecasts. */
    virtual T::ForecastNumber   getForecastNumber() const;

    /*! \brief Return the FMI internal parameter identifier. */
    virtual T::FmiParamId       getFmiParameterId() const;

    /*! \brief Return the FMI level type identifier. */
    virtual T::ParamLevelId     getFmiParameterLevelId() const;

    /*! \brief Return the FMI parameter name string (stable pointer into StringFactory). */
    virtual const char*         getFmiParameterName() const;

    /*! \brief Return the FMI parameter units string. */
    virtual const char*         getFmiParameterUnits() const;

    /*! \brief Return the Newbase parameter identifier. */
    virtual T::NewbaseParamId   getNewbaseParameterId() const;

    /*! \brief Return the Newbase parameter name string. */
    virtual const char*         getNewbaseParameterName() const;

    /*! \brief Return the NetCDF variable name for this parameter. */
    virtual const char*         getNetCdfParameterName() const;

    /*! \brief Return the GRIB edition number (1 or 2), or 0 if not a GRIB message. */
    virtual uint                getGribVersion() const;

    /*! \brief Return the GRIB originating centre number. */
    virtual uint                getGribCentre() const;

    /*! \brief Return the GRIB originating sub-centre number. */
    virtual uint                getGribSubCentre() const;

    /*! \brief Return the GRIB generating process identifier. */
    virtual uint                getGribGeneratingProcessIdentifier() const;

    /*! \brief Return the GRIB parameter table version number. */
    virtual uint                getGribTableVersion() const;

    /*! \brief Collect the file byte positions of all sections in this message.
     *  \param[out] positions  Receives the set of section offsets. */
    virtual void                getSectionPositions(std::set<T::FilePosition>& positions);

    /*! \brief Return the GRIB parameter identifier. */
    virtual T::GribParamId      getGribParameterId() const;

    /*! \brief Return the GRIB parameter name string. */
    virtual const char*         getGribParameterName() const;

    /*! \brief Return the average cell dimensions of the grid in degrees.
     *  \param[out] width   Average cell width in degrees longitude.
     *  \param[out] height  Average cell height in degrees latitude. */
    virtual void                getGridCellAverageSize(double& width,double& height) const;

    /*! \brief Return the grid dimensions (number of columns and rows). */
    virtual T::Dimensions       getGridDimensions() const;

    /*! \brief Return the geometry identifier for this grid's projection and extent. */
    virtual T::GeometryId       getGridGeometryId() const;

    /*! \brief Return a human-readable description of the grid geometry. */
    virtual std::string         getGridGeometryString() const;

    /*! \brief Return a single-line grid geometry descriptor (for content-server registration). */
    virtual std::string         getGridGeometryLine() const;

    /*! \brief Return a hash that uniquely identifies the grid geometry. */
    virtual T::Hash             getGridHash() const;

    /*! \brief Compute isobands (filled contour polygons) on the native grid.
     *  \param[in]  contourLowValues   Lower bound of each isoband interval.
     *  \param[in]  contourHighValues  Upper bound of each isoband interval.
     *  \param[in]  attributeList      Rendering attributes (WKB output format, etc.).
     *  \param[out] contours           Encoded polygon data for each isoband. */
    virtual void                getGridIsobands(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours);

    /*! \brief Compute isobands after applying a value modification operation. */
    virtual void                getGridIsobands(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Compute isobands reprojected to the geometry defined in \p attributeList. */
    virtual void                getGridIsobandsByGeometry(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,T::ByteData_vec& contours);

    //! \overload
    virtual void                getGridIsobandsByGeometry(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Compute isobands reprojected onto an explicit target grid.
     *  \param[in]  contourLowValues       Lower bound of each isoband interval.
     *  \param[in]  contourHighValues      Upper bound of each isoband interval.
     *  \param[in]  gridWidth              Target grid width in columns.
     *  \param[in]  gridHeight             Target grid height in rows.
     *  \param[in]  gridLatLonCoordinates  Lat/lon coords of the target grid points.
     *  \param[in]  projectionCoordinates  Native coords of the target grid points.
     *  \param[in]  attributeList          Rendering attributes.
     *  \param[out] contours               Encoded polygon data. */
    virtual void                getGridIsobandsByGrid(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);

    //! \overload
    virtual void                getGridIsobandsByGrid(T::ParamValue_vec& contourLowValues,T::ParamValue_vec& contourHighValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Compute isolines (contour lines) on the native grid.
     *  \param[in]  contourValues  Isoline levels.
     *  \param[in]  attributeList  Rendering attributes.
     *  \param[out] contours       Encoded polyline data for each level. */
    virtual void                getGridIsolines(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours);

    //! \overload
    virtual void                getGridIsolines(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Compute isolines reprojected to the geometry defined in \p attributeList. */
    virtual void                getGridIsolinesByGeometry(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,T::ByteData_vec& contours);

    //! \overload
    virtual void                getGridIsolinesByGeometry(T::ParamValue_vec& contourValues,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Compute isolines reprojected onto an explicit target grid.
     *  \param[in]  contourValues          Isoline threshold levels.
     *  \param[in]  gridWidth              Target grid width in columns.
     *  \param[in]  gridHeight             Target grid height in rows.
     *  \param[in]  gridLatLonCoordinates  Lat/lon coords of the target grid points.
     *  \param[in]  projectionCoordinates  Native coords of the target grid points.
     *  \param[in]  attributeList          Rendering attributes.
     *  \param[out] contours               Encoded polyline data. */
    virtual void                getGridIsolinesByGrid(T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::ByteData_vec& contours);

    //! \overload
    virtual void                getGridIsolinesByGrid(T::ParamValue_vec& contourValues,uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& contours);

    /*! \brief Compute streamlines (wind vector paths) on the native grid.
     *  \param[in]  attributeList  Rendering/computation attributes.
     *  \param[out] streamlines    Encoded polyline data. */
    virtual void                getGridStreamlines(T::AttributeList& attributeList,T::ByteData_vec& streamlines);

    //! \overload
    virtual void                getGridStreamlines(T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines);

    /*! \brief Compute streamlines reprojected to the geometry defined in \p attributeList. */
    virtual void                getGridStreamlinesByGeometry(T::AttributeList& attributeList,T::ByteData_vec& streamlines);

    //! \overload
    virtual void                getGridStreamlinesByGeometry(T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines);

    /*! \brief Compute streamlines reprojected onto an explicit target grid.
     *  \param[in]  gridWidth,gridHeight           Target grid dimensions.
     *  \param[in]  gridLatLonCoordinates          Lat/lon coords of target grid points.
     *  \param[in]  projectionCoordinates          Native coords of target grid points.
     *  \param[in]  attributeList                  Rendering/computation attributes.
     *  \param[out] streamlines                    Encoded polyline data. */
    virtual void                getGridStreamlinesByGrid(uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,T::ByteData_vec& streamlines);

    //! \overload
    virtual void                getGridStreamlinesByGrid(uint gridWidth,uint gridHeight,std::vector<T::Coordinate>& gridLatLonCoordinates,std::vector<T::Coordinate>& projectionCoordinates,T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ByteData_vec& streamlines);

    /*! \brief Return the four lat/lon corners of the grid bounding box.
     *  \param[out] topLeft,topRight,bottomLeft,bottomRight  Corner coordinates (lat/lon degrees).
     *  \return True if the bounding box could be determined. */
    virtual bool                getGridLatLonArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);

    /*! \brief Return the lat/lon coordinate of every grid point as a shared vector. */
    virtual T::Coordinate_svec  getGridLatLonCoordinates() const;

    /*! \brief Convert integer grid indices to lat/lon coordinates.
     *  \param[in]  grid_i,grid_j  Zero-based column and row indices.
     *  \param[out] lat,lon        Latitude and longitude in degrees.
     *  \return True on success. */
    virtual bool                getGridLatLonCoordinatesByGridPoint(uint grid_i,uint grid_j,double& lat,double& lon) const;

    /*! \brief Convert fractional grid position to lat/lon coordinates.
     *  \param[in]  grid_i,grid_j  Fractional column and row position.
     *  \param[out] lat,lon        Latitude and longitude in degrees.
     *  \return True on success. */
    virtual bool                getGridLatLonCoordinatesByGridPosition(double grid_i,double grid_j,double& lat,double& lon) const;

    /*! \brief Convert native projection coordinates to lat/lon.
     *  \param[in]  x,y     Native projection coordinates.
     *  \param[out] lat,lon Latitude and longitude in degrees.
     *  \return True on success. */
    virtual bool                getGridLatLonCoordinatesByOriginalCoordinates(double x,double y,double& lat,double& lon) const;

    /*! \brief Return the four metric corners of the grid bounding box (in metres).
     *  \param[out] topLeft,topRight,bottomLeft,bottomRight  Corner coordinates.
     *  \return True if the bounding box could be determined. */
    virtual bool                getGridMetricArea(T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);

    /*! \brief Return the grid cell size in metres.
     *  \param[out] width,height  Cell dimensions.
     *  \return True on success. */
    virtual bool                getGridMetricCellSize(double& width,double& height) const;

    /*! \brief Return the total grid extent in metres.
     *  \param[out] width,height  Total width and height.
     *  \return True on success. */
    virtual bool                getGridMetricSize(double& width,double& height) const;

    /*! \brief Return the native projection coordinate of every grid point as a shared vector. */
    virtual T::Coordinate_svec  getGridOriginalCoordinates() const;

    /*! \brief Convert integer grid indices to native projection coordinates.
     *  \param[in]  grid_i,grid_j  Zero-based column and row indices.
     *  \param[out] x,y            Native projection coordinates.
     *  \return True on success. */
    virtual bool                getGridOriginalCoordinatesByGridPoint(uint grid_i,uint grid_j,double& x,double& y) const;

    /*! \brief Convert fractional grid position to native projection coordinates.
     *  \param[in]  grid_i,grid_j  Fractional column and row position.
     *  \param[out] x,y            Native projection coordinates.
     *  \return True on success. */
    virtual bool                getGridOriginalCoordinatesByGridPosition(double grid_i,double grid_j,double& x,double& y) const;

    /*! \brief Convert lat/lon to native projection coordinates.
     *  \param[in]  lat,lon  Geographic coordinates in degrees.
     *  \param[out] x,y      Native projection coordinates.
     *  \return True on success. */
    virtual bool                getGridOriginalCoordinatesByLatLonCoordinates(double lat,double lon,double& x,double& y) const;

    /*! \brief Return the total number of grid points in the native packed value array. */
    virtual std::size_t         getGridOriginalValueCount() const;

    /*! \brief Return the flat index into the native packed array for grid point (grid_i, grid_j).
     *  \param[in] grid_i,grid_j  Zero-based column and row indices.
     *  \return Flat index, or -1 if the point is outside the grid. */
    virtual int                 getGridOriginalValueIndex(uint grid_i,uint grid_j) const;

    /*! \brief Return the wind/vector rotation angle at a lat/lon location.
     *  \param[in] lat,lon  Geographic coordinates in degrees.
     *  \return Rotation angle in degrees. */
    virtual float               getGridPointAngleByLatLonCoordinates(double lat,double lon) const;

    /*! \brief Return the wind/vector rotation angle at a location given in \p coordinateType.
     *  \param[in] coordinateType  Coordinate system (T::CoordinateTypeValue).
     *  \param[in] x,y             Coordinates in the specified system.
     *  \return Rotation angle in degrees. */
    virtual float               getGridPointAngle(T::CoordinateType coordinateType,double x,double y) const;

    /*! \brief Fill \p angles with the rotation angle for every grid point.
     *  \param[out] angles  Per-grid-point rotation angles in degrees. */
    virtual void                getGridPointAngles(std::vector<float>& angles) const;

    /*! \brief Map lat/lon coordinates to fractional grid positions.
     *  \param[in]  latlon   Input lat/lon coordinate pairs.
     *  \param[out] points   Corresponding fractional grid (column, row) pairs. */
    virtual void                getGridPointListByLatLonCoordinates(T::Coordinate_vec& latlon,T::Coordinate_vec& points) const;

    /*! \brief Convert a lat/lon position to fractional grid indices (cached).
     *  \param[in]  lat,lon       Geographic coordinates in degrees.
     *  \param[out] grid_i,grid_j Fractional column and row position.
     *  \return True if the point is within the grid. */
    virtual bool                getGridPointByLatLonCoordinates(double lat,double lon,double& grid_i,double& grid_j) const;

    /*! \brief Convert a lat/lon position to fractional grid indices (no cache).
     *  \param[in]  lat,lon       Geographic coordinates in degrees.
     *  \param[out] grid_i,grid_j Fractional column and row position.
     *  \return True if the point is within the grid. */
    virtual bool                getGridPointByLatLonCoordinatesNoCache(double lat,double lon,double& grid_i,double& grid_j) const;

    /*! \brief Convert native projection coordinates to fractional grid indices.
     *  \param[in]  x,y           Native projection coordinates.
     *  \param[out] grid_i,grid_j Fractional column and row position.
     *  \return True if the point is within the grid. */
    virtual bool                getGridPointByOriginalCoordinates(double x,double y,double& grid_i,double& grid_j) const;

    /*! \brief Return the map projection type of the grid (T::GridProjectionValue). */
    virtual T::GridProjection   getGridProjection() const;

    /*! \brief Populate \p attributeList with projection-specific parameters.
     *  \param[in]  prefix         Key prefix.
     *  \param[out] attributeList  Receives projection parameters. */
    virtual void                getGridProjectionAttributes(const std::string& prefix,T::AttributeList& attributeList) const;

    /*! \brief Return the number of columns (grid_i extent) in the grid. */
    virtual std::size_t         getGridColumnCount() const;

    /*! \brief Return the number of rows (grid_j extent) in the grid. */
    virtual std::size_t         getGridRowCount() const;

    /*! \brief Return the grid width (same as getGridColumnCount() as uint). */
    virtual uint                getGridWidth() const;

    /*! \brief Return the grid height (same as getGridRowCount() as uint). */
    virtual uint                getGridHeight() const;

    /*! \brief Interpolate the grid value at a single point.
     *  \param[in]  coordinateType          Coordinate system of (x, y).
     *  \param[in]  x,y                     Query coordinates.
     *  \param[in]  areaInterpolationMethod AreaInterpolationMethod constant.
     *  \param[out] value                   Interpolated parameter value. */
    virtual void                getGridValueByPoint(T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,T::ParamValue& value) const;

    //! \overload
    virtual void                getGridValueByPoint(T::CoordinateType coordinateType,double x,double y,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue& value) const;

    /*! \brief Collect all grid values within a circular area.
     *  \param[in]  coordinateType  Coordinate system of (origoX, origoY).
     *  \param[in]  origoX,origoY  Circle centre coordinates.
     *  \param[in]  radius         Circle radius (in the same units as the coordinates).
     *  \param[out] valueList      Receives matching grid values with their positions. */
    virtual void                getGridValueListByCircle(T::CoordinateType coordinateType,double origoX,double origoY,double radius,T::GridValueList& valueList) const;

    //! \overload
    virtual void                getGridValueListByCircle(T::CoordinateType coordinateType,double origoX,double origoY,double radius,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Interpolate grid values at a list of arbitrary points.
     *  \param[in]  coordinateType          Coordinate system of \p pointList.
     *  \param[in]  pointList               Query point coordinates.
     *  \param[in]  areaInterpolationMethod AreaInterpolationMethod constant.
     *  \param[out] valueList               Receives the interpolated values with positions. */
    virtual void                getGridValueListByPointList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,T::GridValueList& valueList) const;

    //! \overload
    virtual void                getGridValueListByPointList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& pointList,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Collect all grid points inside a polygon.
     *  \param[in]  coordinateType   Coordinate system of \p polygonPoints.
     *  \param[in]  polygonPoints    Polygon vertices.
     *  \param[out] valueList        Receives matching grid values with their positions. */
    virtual void                getGridValueListByPolygon(T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,T::GridValueList& valueList) const;

    //! \overload
    virtual void                getGridValueListByPolygon(T::CoordinateType coordinateType,std::vector<T::Coordinate>& polygonPoints,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Collect all grid points inside a multi-polygon (polygon with holes).
     *  \param[in]  coordinateType  Coordinate system of \p polygonPath.
     *  \param[in]  polygonPath     Outer ring + hole rings.
     *  \param[out] valueList       Receives matching grid values. */
    virtual void                getGridValueListByPolygonPath(T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,T::GridValueList& valueList) const;

    //! \overload
    virtual void                getGridValueListByPolygonPath(T::CoordinateType coordinateType,std::vector<std::vector<T::Coordinate>>& polygonPath,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Collect all grid points within a bounding rectangle.
     *  \param[in]  coordinateType  Coordinate system of (x1,y1,x2,y2).
     *  \param[in]  x1,y1,x2,y2   Bounding rectangle corners.
     *  \param[in]  gridRectangle  If true, (x1,y1,x2,y2) are grid-index bounds; otherwise coordinate bounds.
     *  \param[out] valueList      Receives matching grid values. */
    virtual void                getGridValueListByRectangle(T::CoordinateType coordinateType,double x1,double y1,double x2,double y2,bool gridRectangle,T::GridValueList& valueList) const;

    //! \overload
    virtual void                getGridValueListByRectangle(T::CoordinateType coordinateType,double x1,double y1,double x2,double y2,bool gridRectangle,uint modificationOperation,double_vec& modificationParameters,T::GridValueList& valueList) const;

    /*! \brief Decode and return all grid values as a flat vector.
     *  \param[out] values  Receives all decoded parameter values in row-major order. */
    virtual void                getGridValueVector(T::ParamValue_vec& values) const;

    //! \overload
    virtual void                getGridValueVector(uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Decode and return all grid values, using the value cache if available.
     *  \param[out] values  Receives the parameter value vector. */
    virtual void                getGridValueVectorWithCaching(T::ParamValue_vec& values) const;

    //! \overload
    virtual void                getGridValueVectorWithCaching(uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Extract a cropped sub-area of the grid as a flat value vector.
     *  \param[in]  attributeList  Crop geometry and other rendering attributes.
     *  \param[out] values         Receives the cropped parameter values. */
    virtual void                getGridValueVectorByCrop(T::AttributeList& attributeList,T::ParamValue_vec& values) const;

    //! \overload
    virtual void                getGridValueVectorByCrop(T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Resample the grid to the geometry defined in \p attributeList.
     *  \param[in]  attributeList  Target geometry and interpolation attributes.
     *  \param[out] values         Resampled parameter values. */
    virtual void                getGridValueVectorByGeometry(T::AttributeList& attributeList,T::ParamValue_vec& values) const;

    //! \overload
    virtual void                getGridValueVectorByGeometry(T::AttributeList& attributeList,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Interpolate grid values at a list of coordinates.
     *  \param[in]  coordinateType          Coordinate system of \p coordinates.
     *  \param[in]  coordinates             Query coordinates.
     *  \param[in]  areaInterpolationMethod AreaInterpolationMethod constant.
     *  \param[out] values                  Receives one interpolated value per query point. */
    virtual void                getGridValueVectorByCoordinateList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;

    //! \overload
    virtual void                getGridValueVectorByCoordinateList(T::CoordinateType coordinateType,std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Interpolate grid values at lat/lon coordinates.
     *  \param[in]  coordinates             Lat/lon query coordinates.
     *  \param[in]  areaInterpolationMethod AreaInterpolationMethod constant.
     *  \param[out] values                  Receives one interpolated value per query point. */
    virtual void                getGridValueVectorByLatLonCoordinateList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;

    //! \overload
    virtual void                getGridValueVectorByLatLonCoordinateList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Interpolate grid values at grid-coordinate points.
     *  \param[in]  coordinates             Fractional (grid_i, grid_j) query positions.
     *  \param[in]  areaInterpolationMethod AreaInterpolationMethod constant.
     *  \param[out] values                  Receives one interpolated value per query point. */
    virtual void                getGridValueVectorByGridPointList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,T::ParamValue_vec& values) const;

    //! \overload
    virtual void                getGridValueVectorByGridPointList(std::vector<T::Coordinate>& coordinates,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Return the packed (original) grid value array without any projection transform.
     *  \param[out] values  Receives the raw packed values. */
    virtual void                getGridOriginalValueVector(T::ParamValue_vec& values) const;

    /*! \brief Return the vertical level value stored in this message. */
    virtual T::ParamLevel       getGridParameterLevel() const;

    /*! \brief Return the vertical level type identifier. */
    virtual T::ParamLevelId     getGridParameterLevelId() const;

    /*! \brief Return the minimum and maximum decoded values in the grid.
     *  \param[out] minValue  Minimum parameter value.
     *  \param[out] maxValue  Maximum parameter value. */
    virtual void                getGridMinAndMaxValues(T::ParamValue& minValue,T::ParamValue& maxValue) const;

    /*! \brief Return the multi-component value vector at a single point (e.g. U+V wind).
     *  \param[in]  coordinateType          Coordinate system of (x, y).
     *  \param[in]  x,y                     Query coordinates.
     *  \param[in]  vectorType              Selects the vector component combination.
     *  \param[out] valueVector             Receives the component values. */
    virtual void                getGridValueVectorByPoint(T::CoordinateType coordinateType,double x,double y,uint vectorType,double_vec& valueVector) const;

    //! \overload
    virtual void                getGridValueVectorByPoint(T::CoordinateType coordinateType,double x,double y,uint vectorType,uint modificationOperation,double_vec& modificationParameters,double_vec& valueVector) const;

    /*! \brief Return the multi-component value vector at a fractional grid position.
     *  \param[in]  grid_i,grid_j  Fractional grid position.
     *  \param[in]  vectorType     Component combination selector.
     *  \param[out] valueVector    Receives the component values. */
    virtual void                getGridValueVectorByGridPoint(double grid_i,double grid_j,uint vectorType,double_vec& valueVector) const;

    //! \overload
    virtual void                getGridValueVectorByGridPoint(double grid_i,double grid_j,uint vectorType,uint modificationOperation,double_vec& modificationParameters,double_vec& valueVector) const;

    /*! \brief Return the multi-component value vector at a lat/lon location.
     *  \param[in]  lat,lon        Geographic coordinates in degrees.
     *  \param[in]  vectorType     Component combination selector.
     *  \param[out] valueVector    Receives the component values. */
    virtual void                getGridValueVectorByLatLonCoordinate(double lat,double lon,uint vectorType,double_vec& valueVector) const;

    //! \overload
    virtual void                getGridValueVectorByLatLonCoordinate(double lat,double lon,uint vectorType,uint modificationOperation,double_vec& modificationParameters,double_vec& valueVector) const;

    /*! \brief Return the decoded value at integer grid indices.
     *  \param[in] grid_i,grid_j  Zero-based column and row indices.
     *  \return Decoded parameter value, or ParamValueMissing. */
    virtual T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j) const;

    //! \overload
    virtual T::ParamValue       getGridValueByGridPoint(uint grid_i,uint grid_j,uint modificationOperation,double_vec& modificationParameters) const;

    /*! \brief Interpolate the value at a fractional grid position.
     *  \param[in] grid_i,grid_j            Fractional column and row position.
     *  \param[in] areaInterpolationMethod  AreaInterpolationMethod constant.
     *  \return Interpolated value. */
    virtual T::ParamValue       getGridValueByGridPoint_byInterpolation(double grid_i,double grid_j,short areaInterpolationMethod) const;

    //! \overload
    virtual T::ParamValue       getGridValueByGridPoint_byInterpolation(double grid_i,double grid_j,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters) const;

    /*! \brief Return the value at a fractional grid position using truncation (no interpolation). */
    virtual T::ParamValue       getGridValueByGridPoint_noInterpolation(double grid_i,double grid_j) const;

    //! \overload
    virtual T::ParamValue       getGridValueByGridPoint_noInterpolation(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const;

    /*! \brief Return the value at the nearest grid point to a fractional position. */
    virtual T::ParamValue       getGridValueByGridPoint_nearest(double grid_i,double grid_j) const;

    //! \overload
    virtual T::ParamValue       getGridValueByGridPoint_nearest(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const;

    /*! \brief Return the minimum of the four surrounding grid points at a fractional position. */
    virtual T::ParamValue       getGridValueByGridPoint_min(double grid_i,double grid_j) const;

    //! \overload
    virtual T::ParamValue       getGridValueByGridPoint_min(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const;

    /*! \brief Return the maximum of the four surrounding grid points at a fractional position. */
    virtual T::ParamValue       getGridValueByGridPoint_max(double grid_i,double grid_j) const;

    //! \overload
    virtual T::ParamValue       getGridValueByGridPoint_max(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const;

    /*! \brief Return the bilinearly interpolated value at a fractional grid position. */
    virtual T::ParamValue       getGridValueByGridPoint_linearInterpolation(double grid_i,double grid_j) const;

    //! \overload
    virtual T::ParamValue       getGridValueByGridPoint_linearInterpolation(double grid_i,double grid_j,uint modificationOperation,double_vec& modificationParameters) const;

    /*! \brief Return the interpolated value at a lat/lon location.
     *  \param[in] lat,lon                 Geographic coordinates in degrees.
     *  \param[in] areaInterpolationMethod AreaInterpolationMethod constant.
     *  \return Interpolated value. */
    virtual T::ParamValue       getGridValueByLatLonCoordinate(double lat,double lon,short areaInterpolationMethod) const;

    //! \overload
    virtual T::ParamValue       getGridValueByLatLonCoordinate(double lat,double lon,short areaInterpolationMethod,uint modificationOperation,double_vec& modificationParameters) const;

    /*! \brief Collect decoded values in an integer grid index rectangle.
     *  \param[in]  grid_i_start,grid_j_start  Top-left grid indices (inclusive).
     *  \param[in]  grid_i_end,grid_j_end      Bottom-right grid indices (inclusive).
     *  \param[out] gridPointValues            Receives the values with their positions. */
    virtual void                getGridValueVectorByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValue_vec& gridPointValues) const;

    //! \overload
    virtual void                getGridValueVectorByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,uint modificationOperation,double_vec& modificationParameters,T::GridPointValue_vec& gridPointValues) const;

    /*! \brief Collect decoded values in an integer grid index rectangle into a GridPointValueList.
     *  \param[in]  grid_i_start,grid_j_start  Top-left grid indices (inclusive).
     *  \param[in]  grid_i_end,grid_j_end      Bottom-right grid indices (inclusive).
     *  \param[out] gridPointValues            Receives the values with their spatiotemporal coordinates. */
    virtual void                getParameterValuesByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,T::GridPointValueList& gridPointValues) const;

    //! \overload
    virtual void                getParameterValuesByRectangle(uint grid_i_start,uint grid_j_start,uint grid_i_end,uint grid_j_end,uint modificationOperation,double_vec& modificationParameters,T::GridPointValueList& gridPointValues) const;

    /*! \brief Return the default interpolation method for this grid type. */
    virtual short               getDefaultInterpolationMethod() const;

    /*! \brief Return the model reference time (analysis time) as an ISO-8601 string. */
    virtual T::TimeString       getReferenceTime() const;

    /*! \brief Return the OGR spatial reference for the grid projection.
     *  \return Shared pointer to OGRSpatialReference. */
    virtual T::SpatialRef_sptr  getSpatialReference() const;

    /*! \brief Return the Well-Known-Text (WKT) description of the grid projection. */
    virtual std::string         getWKT() const;

    /*! \brief Return the PROJ.4 string for the grid projection. */
    virtual std::string         getProj4() const;

    /*! \brief Initialise the spatial reference from the message's projection parameters. */
    virtual void                initSpatialReference();

    /*! \brief Return true if the grid covers the full globe (360° longitude). */
    virtual bool                isGridGlobal() const;

    /*! \brief Return true if U/V wind components are relative to the grid (not geographic north). */
    virtual bool                isRelativeUV() const;

    /*! \brief Return true if the x-axis is stored in decreasing order. */
    virtual bool                reverseXDirection() const;

    /*! \brief Return true if the y-axis is stored in decreasing order. */
    virtual bool                reverseYDirection() const;

    /*! \brief Pre-load coordinate tables and spatial reference into the cache. */
    virtual void                premap() const;

    /*! \brief Increment the per-message request counter. */
    virtual void                incRequestCounter() {mRequestCounter++;}

    /*! \brief Return the current per-message request counter value. */
    virtual Int64               getRequestCounter() {return mRequestCounter;}

    /*! \brief Set the per-message request counter to an explicit value.
     *  \param[in] counter  New counter value. */
    virtual void                setRequestCounter(Int64 counter) {mRequestCounter = counter;}

    /*! \brief Apply a modification operation to all values in a vector in-place.
     *  \param[in]     modificationOperation   Operation code (see Operation).
     *  \param[in]     modificationParameters  Operation parameters.
     *  \param[in,out] values                  Values to modify. */
    virtual void                modifyGridValueVector(uint modificationOperation,double_vec& modificationParameters,T::ParamValue_vec& values) const;

    /*! \brief Set the zero-based message index within the parent file.
     *  \param[in] index  New message index. */
    virtual void                setMessageIndex(uint index);

    /*! \brief Set the back-pointer to the owning GridFile.
     *  \param[in] gridFilePtr  Pointer to the parent GridFile. */
    virtual void                setGridFilePtr(GridFile *gridFilePtr);

    /*! \brief Set the FMI parameter identifier.
     *  \param[in] fmiParameterId  FMI parameter id. */
    virtual void                setFmiParameterId(T::FmiParamId fmiParameterId);

    /*! \brief Set the FMI parameter level type.
     *  \param[in] fmiParameterLevelId  Level type identifier. */
    virtual void                setFmiParameterLevelId(T::ParamLevelId fmiParameterLevelId);

    /*! \brief Set the FMI parameter name.
     *  \param[in] fmiParameterName  Name string (interned in StringFactory). */
    virtual void                setFmiParameterName(const char* fmiParameterName);

    /*! \brief Set the FMI parameter units string.
     *  \param[in] fmiParameterUnits  Units string. */
    virtual void                setFmiParameterUnits(const char* fmiParameterUnits);

    /*! \brief Set the NetCDF variable name.
     *  \param[in] netCdfParameterName  Variable name string. */
    virtual void                setNetCdfParameterName(const char* netCdfParameterName);

    /*! \brief Set the Newbase parameter identifier.
     *  \param[in] newbaseParameterId  Newbase parameter id. */
    virtual void                setNewbaseParameterId(T::NewbaseParamId newbaseParameterId);

    /*! \brief Set the Newbase parameter name.
     *  \param[in] newbaseParameterName  Newbase name string. */
    virtual void                setNewbaseParameterName(const char* newbaseParameterName);

    /*! \brief Set the grid geometry identifier.
     *  \param[in] geometryId  Geometry id. */
    virtual void                setGridGeometryId(T::GeometryId geometryId);

    /*! \brief Replace all decoded grid values.
     *  \param[in] values  New parameter value vector (must match grid size). */
    virtual void                setGridValues(T::ParamValue_vec& values);

    /*! \brief Set the GRIB parameter identifier.
     *  \param[in] gribParameterId  GRIB parameter id. */
    virtual void                setGribParameterId(T::GribParamId gribParameterId);

    /*! \brief Set the GRIB parameter name.
     *  \param[in] gribParameterName  GRIB parameter name string. */
    virtual void                setGribParameterName(const char* gribParameterName);

    /*! \brief Set the GRIB parameter units string.
     *  \param[in] gribParameterUnits  Units string. */
    virtual void                setGribParameterUnits(const char* gribParameterUnits);

    /*! \brief Retrieve a property value by numeric property id.
     *  \param[in]  propertyId  Numeric property identifier.
     *  \param[out] value       Receives the value as Int64.
     *  \return True if the property exists and was retrieved. */
    virtual bool                getProperty(uint propertyId,Int64& value);

    /*! \brief Retrieve a property value by name.
     *  \param[in]  propertyName  Property key string.
     *  \param[out] value         Receives the value as Int64.
     *  \return True if the property was found. */
    virtual bool                getProperty(const char *propertyName,Int64& value);

    /*! \brief Collect all settable properties as a PropertySettingVec.
     *  \param[out] properties  Receives all (propertyId, value-string) pairs. */
    virtual void                getProperties(T::PropertySettingVec& properties);

    /*! \brief Set a property by numeric id.
     *  \param[in] propertyId  Numeric property identifier.
     *  \param[in] value       New value.
     *  \return True if the property was recognised and set. */
    virtual bool                setProperty(uint propertyId,char value);
    //! \overload
    virtual bool                setProperty(uint propertyId,short value);
    //! \overload
    virtual bool                setProperty(uint propertyId,int value);
    //! \overload
    virtual bool                setProperty(uint propertyId,unsigned char value);
    //! \overload
    virtual bool                setProperty(uint propertyId,unsigned short value);
    //! \overload
    virtual bool                setProperty(uint propertyId,unsigned int value);
    //! \overload
    virtual bool                setProperty(uint propertyId,UInt64 value);
    //! \overload
    virtual bool                setProperty(uint propertyId,Int64 value);
    //! \overload
    virtual bool                setProperty(uint propertyId,double value);

    /*! \brief Set a property by name.
     *  \param[in] propertyName  Property key string.
     *  \param[in] value         New value.
     *  \return True if the property was recognised and set. */
    virtual bool                setProperty(const char *propertyName,char value);
    //! \overload
    virtual bool                setProperty(const char *propertyName,short value);
    //! \overload
    virtual bool                setProperty(const char *propertyName,int value);
    //! \overload
    virtual bool                setProperty(const char *propertyName,unsigned char value);
    //! \overload
    virtual bool                setProperty(const char *propertyName,unsigned short value);
    //! \overload
    virtual bool                setProperty(const char *propertyName,unsigned int value);
    //! \overload
    virtual bool                setProperty(const char *propertyName,UInt64 value);
    //! \overload
    virtual bool                setProperty(const char *propertyName,Int64 value);
    //! \overload
    virtual bool                setProperty(const char *propertyName,double value);

    /*! \brief Acquire the data lock (prevents concurrent value decoding). */
    virtual void                lockData();

    /*! \brief Release the data lock. */
    virtual void                unlockData();

    /*! \brief Compute and return the arithmetic mean of all non-missing grid values. */
    virtual T::ParamValue       countAverageValue() const;

    /*! \brief Return true if the message data has been decoded/read from the file. */
    virtual bool                isRead();

    /*! \brief Print message metadata and optionally data to a stream.
     *  \param[in] stream      Output stream.
     *  \param[in] level       Indentation level.
     *  \param[in] optionFlags PrintFlag bit mask. */
    virtual void                print(std::ostream& stream,uint level,uint optionFlags) const;

    /*! \brief Decode and cache the packed grid data from the memory-mapped file. */
    virtual void                read();

    /*! \brief Decode from an explicit MemoryReader.
     *  \param[in] memoryReader  Reader positioned at the start of this message. */
    virtual void                read(MemoryReader& memoryReader);

    /*! \brief Serialise and write this message to a DataWriter.
     *  \param[in] dataWriter  Target writer. */
    virtual void                write(DataWriter& dataWriter);


  protected:

    /*! \brief  The index of the message in the file. */
    T::MessageIndex             mMessageIndex;

    /*! \brief  The size of the message in bytes. */
    uint                        mMessageSize;

    /*! \brief  The fmi parameter identifier.*/
    T::FmiParamId               mFmiParameterId;

    /*! \brief  The newbase parameter id string. */
    T::NewbaseParamId           mNewbaseParameterId;

    /*! \brief The grib parameter identifier. */
    T::GribParamId              mGribParameterId;

    /*! \brief  The geometry identifier. */
    T::GeometryId               mGeometryId;

    /*! \brief  The fmi parameter name. */
    uint                        mFmiParameterName;

    /*! \brief  The netcdf parameter name. */
    uint                        mNetCdfParameterName;

    /*! \brief  The newbase parameter name. */
    uint                        mNewbaseParameterName;

    /*! \brief  The grib parameter name. */
    uint                        mGribParameterName;

    /*! \brief  The fmi parameter units. */
    uint                        mFmiParameterUnits;

    /*! \brief  The grib parameter units. */
    uint                        mGribParameterUnits;

    /*! \brief  The file type. */
    T::FileType                 mFileType;

    /*! \brief  The fmi parameter level identifier. */
    T::ParamLevelId             mFmiParameterLevelId;

    /*! \brief  The parameter level. */
    T::ParamLevel               mParameterLevel;

    /*! \brief  The virtual file id. If the value is bigger that zero, then the virtual message should be used
     * instead of this message
     * */
    uint                        mRowCount;
    uint                        mColumnCount;
    GridFile*                   mGridFilePtr;
    char*                       mFileMemoryPtr;
    mutable ThreadLock          mThreadLock;
    short                       mDefaultInterpolationMethod;
    mutable bool                mPremapped;
    mutable Int64               mRequestCounter;
};


/*! \brief Numeric operation codes used by the modificationOperation parameter of value-query methods.
 *
 *  Pass an Operation constant as \p modificationOperation to transform decoded grid values
 *  on the fly.  For binary operations (ADD, MUL, …) the first element of
 *  modificationParameters is the second operand. */
class Operation
{
  public:

  enum : uint
    {
     NONE              = 0,     //!< No transformation

     GRID_ADD          = 1,     //!< Add two grids element-wise
     GRID_SUM          = 1,     //!< Alias for GRID_ADD
     GRID_DEC          = 2,     //!< Subtract two grids element-wise
     GRID_MUL          = 3,     //!< Multiply two grids element-wise
     GRID_DIV          = 4,     //!< Divide two grids element-wise
     GRID_HYPOT        = 5,     //!< Hypotenuse of two grids: sqrt(a²+b²)

     ADD               = 1001,  //!< Add a scalar: value + p[0]
     SUM               = 1001,  //!< Alias for ADD
     DEC               = 1002,  //!< Subtract a scalar: value - p[0]
     MUL               = 1003,  //!< Multiply by a scalar: value * p[0]
     DIV               = 1004,  //!< Divide by a scalar: value / p[0]

     ABS               = 2000,  //!< Absolute value: abs(value)
     NEG               = 2001,  //!< Negate: -value
     ROUND             = 2002,  //!< Round to nearest integer
     FLOOR             = 2003,  //!< Floor: floor(value)
     CEIL              = 2004,  //!< Ceiling: ceil(value)

     K2C               = 3000,  //!< Kelvin to Celsius
     C2K               = 3001,  //!< Celsius to Kelvin
     F2C               = 3002,  //!< Fahrenheit to Celsius
     C2F               = 3003,  //!< Celsius to Fahrenheit
     F2K               = 3004,  //!< Fahrenheit to Kelvin
     K2F               = 3005,  //!< Kelvin to Fahrenheit
     RAD2DEG           = 3006,  //!< Radians to degrees
     DEG2RAD           = 3007   //!< Degrees to radians
    };

    /*! \brief Populate \p names with all operation name → code mappings.
     *  \param[out] names  Receives the (name, code) pairs. */
    static void getOperatorNames(std::map<std::string,uint>& names)
    {
      names.insert(std::pair<std::string,uint>("GRID_ADD",GRID_ADD));
      names.insert(std::pair<std::string,uint>("GRID_SUM",GRID_SUM));
      names.insert(std::pair<std::string,uint>("GRID_DEC",GRID_DEC));
      names.insert(std::pair<std::string,uint>("GRID_MUL",GRID_MUL));
      names.insert(std::pair<std::string,uint>("GRID_DIV",GRID_DIV));
      names.insert(std::pair<std::string,uint>("GRID_HYPOT",GRID_HYPOT));

      names.insert(std::pair<std::string,uint>("ADD",ADD));
      names.insert(std::pair<std::string,uint>("SUM",SUM));
      names.insert(std::pair<std::string,uint>("DEC",DEC));
      names.insert(std::pair<std::string,uint>("MUL",MUL));
      names.insert(std::pair<std::string,uint>("DIV",DIV));

      names.insert(std::pair<std::string,uint>("ABS",ABS));
      names.insert(std::pair<std::string,uint>("NEG",NEG));
      names.insert(std::pair<std::string,uint>("ROUND",ROUND));
      names.insert(std::pair<std::string,uint>("FLOOR",FLOOR));
      names.insert(std::pair<std::string,uint>("CEIL",CEIL));

      names.insert(std::pair<std::string,uint>("K2C",K2C));
      names.insert(std::pair<std::string,uint>("C2K",C2K));
      names.insert(std::pair<std::string,uint>("F2C",F2C));
      names.insert(std::pair<std::string,uint>("C2F",C2F));
      names.insert(std::pair<std::string,uint>("F2K",F2K));
      names.insert(std::pair<std::string,uint>("K2F",K2F));
      names.insert(std::pair<std::string,uint>("RAD2DEG",RAD2DEG));
      names.insert(std::pair<std::string,uint>("DEG2RAD",DEG2RAD));
    }
};


typedef Message* MessagePtr;
typedef std::vector<MessagePtr> MessagePtr_vec;

extern std::vector<double> EMPTY_DOUBLE_VEC;
extern std::vector<Message*> EMPTY_MSG_VEC;



}  // namespace GRID
}  // namespace SmartMet

