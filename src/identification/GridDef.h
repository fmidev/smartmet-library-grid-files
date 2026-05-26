#pragma once

#include "GribParameterDef.h"
#include "Grib1ParameterDef.h"
#include "Grib2ParameterDef.h"
#include "FmiLevelId_grib.h"
#include "FmiParameterDef.h"
#include "FmiParameterId_grib.h"
#include "FmiParameterId_netCdf.h"
#include "FmiParameterId_newbase.h"
#include "AggregationDef.h"
#include "LevelDef.h"
#include "FmiGeometryGroupDef.h"
#include "ProcessingTypeDef.h"
#include "ForecastTypeDef.h"
#include "NetCdfParameterDef.h"
#include "NewbaseParameterDef.h"
#include "../common/AutoWriteLock.h"
#include "../common/AutoReadLock.h"
#include "../common/ConfigurationFile.h"
#include "../grib1/Message.h"
#include "../grib2/Message.h"
#include "../grid/Typedefs.h"
#include "../grib2/GridDefinition.h"

#include <set>


/*! \brief Environment variable whose value is the path to the GridDef configuration file. */
#define SMARTMET_GRID_CONFIG_FILE "SMARTMET_GRID_CONFIG_FILE"


namespace SmartMet
{
namespace Identification
{

typedef std::unordered_map<uint,std::string> GeometryNames;  //!< Map from geometry ID to geometry name
typedef std::unordered_map<uint,uint> IdMap;                 //!< Generic uint→uint identifier mapping
typedef std::unordered_map<std::string,uint> StringIdMap;    //!< String→uint identifier mapping


// ====================================================================================
/*! \brief Central registry for all parameter, level, and geometry identifier mappings.
 *
 *  `GridDef` is the single entry point for translating between the identifier systems
 *  used by GRIB 1, GRIB 2, NetCDF, and Newbase formats and the FMI canonical parameter
 *  and level IDs.  It also manages the geometry (grid projection) registry, allowing
 *  callers to look up grid dimensions, coordinates, and projection parameters by a
 *  numeric geometry ID.
 *
 *  All mapping tables are loaded from CSV and libconfig files whose paths are given in
 *  the configuration file pointed to by `SMARTMET_GRID_CONFIG_FILE`.  The tables are
 *  hot-reloaded automatically when their files change on disk.
 *
 *  A process-wide singleton instance is available as `SmartMet::Identification::gridDef`. */
// ====================================================================================

class GridDef
{
  public:
                        GridDef();
    virtual             ~GridDef();

    /*! \brief Initialise all mapping tables from the given libconfig configuration file.
     *  \param[in] configFile  Path to the GridDef configuration file. */

    void                init(const char* configFile);

    // -----------------------------------------------------------------------
    // Common GRIB parameter lookups
    // -----------------------------------------------------------------------

    /*! \brief Look up a GRIB parameter definition by its numeric GRIB ID.
     *  \return true on success; false if not found. */
    bool                getGribParameterDefById(T::GribParamId gribParamId,GribParameterDef&  paramDef);
    /*! \brief Look up a GRIB parameter definition by its name string.
     *  \return true on success; false if not found. */
    bool                getGribParameterDefByName(const std::string& gribParamName,GribParameterDef&  paramDef);
    /*! \brief Determine the GRIB parameter ID from the fields of a GRIB 1 message. */
    T::GribParamId      getGribParameterId(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    T::GribParamId      getGribParameterId(GRIB2::Message& message);
    /*! \brief Look up the FMI→GRIB mapping record for an FMI parameter ID.
     *  \return true on success; false if no mapping exists. */
    bool                getGribParameterMappingByFmiId(T::FmiParamId fmiParamId,FmiParameterId_grib& def);
    /*! \brief Return the GRIB parameter name for a GRIB 1 message, or empty string if unknown. */
    std::string         getGribParameterName(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    std::string         getGribParameterName(GRIB2::Message& message);

    // -----------------------------------------------------------------------
    // GRIB 1 — geometry, level, and parameter lookups
    // -----------------------------------------------------------------------

    /*! \brief Return the GRIB 1 grid definition for a geometry ID, or nullptr if unknown. */
    GRIB1::GridDef_sptr getGrib1DefinitionByGeometryId(int geometryId);
    /*! \brief Return the GRIB 1 grid definition matching a geometry string descriptor. */
    GRIB1::GridDef_sptr getGrib1DefinitionByGeometryString(const char *geometryStr);
    //! \overload
    GRIB1::GridDef_sptr getGrib1DefinitionByGeometryString(std::string& geometryStr);
    /*! \brief Determine the FMI geometry ID from a GRIB 1 message's grid definition. */
    int                 getGrib1GeometryId(GRIB1::Message& message);
    /*! \brief Look up the GRIB 1 level key/value mapping for an FMI level ID.
     *  \return true on success; false if not found. */
    bool                getGrib1LevelDef(uint fmiLevelId,FmiLevelId_grib& def);
    /*! \brief Return the total number of loaded GRIB 1 parameter definitions. */
    uint                getGrib1ParameterDefCount();
    /*! \brief Look up a GRIB 1 parameter definition by its GRIB parameter ID.
     *  \return true on success; false if not found. */
    bool                getGrib1ParameterDefById(T::GribParamId gribParamId,Grib1ParameterDef& paramDef);
    /*! \brief Look up a GRIB 1 parameter definition by an FMI parameter ID.
     *  \return true on success; false if not found. */
    bool                getGrib1ParameterDefByFmiId(T::FmiParamId fmiParamId,Grib1ParameterDef& paramDef);
    /*! \brief Return the GRIB 1 parameter definition at position \p index.
     *  \return true on success; false if index is out of range. */
    bool                getGrib1ParameterDefByIndex(uint index,Grib1ParameterDef& paramDef);

    // -----------------------------------------------------------------------
    // GRIB 2 — geometry, level, and parameter lookups
    // -----------------------------------------------------------------------

    /*! \brief Return the GRIB 2 grid definition for a geometry ID, or nullptr if unknown. */
    GRIB2::GridDef_sptr getGrib2DefinitionByGeometryId(int geometryId);
    /*! \brief Return the GRIB 2 grid definition matching a geometry string descriptor. */
    GRIB2::GridDef_sptr getGrib2DefinitionByGeometryString(const char *geometryStr);
    //! \overload
    GRIB2::GridDef_sptr getGrib2DefinitionByGeometryString(std::string& geometryStr);
    /*! \brief Determine the FMI geometry ID from a GRIB 2 message's grid definition. */
    int                 getGrib2GeometryId(GRIB2::Message& message);
    /*! \brief Look up the GRIB 2 level key/value mapping for an FMI level ID.
     *  \return true on success; false if not found. */
    bool                getGrib2LevelDef(uint fmiLevelId,FmiLevelId_grib& def);
    /*! \brief Return the total number of loaded GRIB 2 parameter definitions. */
    uint                getGrib2ParameterDefCount();
    /*! \brief Look up a GRIB 2 parameter definition by its GRIB parameter ID.
     *  \return true on success; false if not found. */
    bool                getGrib2ParameterDefById(T::GribParamId gribParamId,Grib2ParameterDef& paramDef);
    /*! \brief Look up a GRIB 2 parameter definition by an FMI parameter ID.
     *  \return true on success; false if not found. */
    bool                getGrib2ParameterDefByFmiId(T::FmiParamId fmiParamId,Grib2ParameterDef& paramDef);
    /*! \brief Return the GRIB 2 parameter definition at position \p index.
     *  \return true on success; false if index is out of range. */
    bool                getGrib2ParameterDefByIndex(uint index,Grib2ParameterDef& paramDef);

    // -----------------------------------------------------------------------
    // FMI — aggregation, geometry group, level, forecast type, parameter lookups
    // -----------------------------------------------------------------------

    /*! \brief Look up an aggregation definition by numeric ID.
     *  \return true on success; false if not found. */
    bool                getFmiAggregationDef(int aggregationId,AggregationDef& aggregationDef);
    /*! \brief Look up a geometry group definition by numeric group ID.
     *  \return true on success; false if not found. */
    bool                getFmiGeometryGroupDef(uint geometryGroupId,FmiGeometryGroupDef& geometryGroupDef);
    /*! \brief Look up a geometry group definition by producer name and group type.
     *  \return true on success; false if not found. */
    bool                getFmiGeometryGroupDef(const char *producerName,uint groupType,FmiGeometryGroupDef& geometryGroupDef);
    /*! \brief Return all geometry group IDs that contain \p geometryId. */
    void                getFmiGeometryGroupsByGeometryId(int geometryId,std::vector<uint>& groupIdentifiers);
    //! \overload (filtered by \p groupType)
    void                getFmiGeometryGroupsByGeometryId(int geometryId,uint groupType,std::vector<uint>& groupIdentifiers);
    //! \overload (result as a set)
    void                getFmiGeometryGroupsByGeometryId(int geometryId,std::set<uint>& groupIdentifiers);
    /*! \brief Look up a level definition by FMI level ID.
     *  \return true on success; false if not found. */
    bool                getFmiLevelDef(uint levelId,LevelDef& levelDef);
    /*! \brief Determine the FMI level ID for a GRIB 1 message. */
    T::ParamLevelId     getFmiLevelId(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    T::ParamLevelId     getFmiLevelId(GRIB2::Message& message);
    /*! \brief Map a Newbase level ID to the corresponding FMI level ID. */
    uint                getFmiLevelIdByNewbaseLevelId(uint newbaseLevelId);
    /*! \brief Look up a forecast type definition by numeric ID.
     *  \return true on success; false if not found. */
    bool                getFmiForecastTypeDef(int forecastTypeId,ForecastTypeDef& forecastTypeDef);
    /*! \brief Look up an FMI parameter definition by FMI parameter ID.
     *  \return true on success; false if not found. */
    bool                getFmiParameterDefById(T::FmiParamId fmiParamId,FmiParameterDef& paramDef);
    /*! \brief Look up an FMI parameter definition by GRIB parameter ID.
     *  \return true on success; false if not found. */
    bool                getFmiParameterDefByGribId(T::GribParamId gribParamId,FmiParameterDef& paramDef);
    /*! \brief Look up an FMI parameter definition by Newbase parameter ID.
     *  \return true on success; false if not found. */
    bool                getFmiParameterDefByNewbaseId(T::NewbaseParamId newbaseParamId,FmiParameterDef& paramDef);
    /*! \brief Look up an FMI parameter definition by NetCDF variable name.
     *  \return true on success; false if not found. */
    bool                getFmiParameterDefByNetCdfName(std::string& netCdfParamName,FmiParameterDef& paramDef);
    /*! \brief Look up an FMI parameter definition by FMI parameter name.
     *  \return true on success; false if not found. */
    bool                getFmiParameterDefByName(const std::string& fmiParamName,FmiParameterDef& paramDef);
    /*! \brief Determine the FMI parameter ID for a GRIB 1 message. */
    T::FmiParamId       getFmiParameterId(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    T::FmiParamId       getFmiParameterId(GRIB2::Message& message);
    /*! \brief Look up the FMI parameter ID by FMI canonical parameter name. */
    T::FmiParamId       getFmiParameterIdByFmiName(const std::string& fmiParamName);
    /*! \brief Look up the FMI parameter ID by Newbase parameter name. */
    T::FmiParamId       getFmiParameterIdByNewbaseName(const std::string& newbaseParamName);
    /*! \brief Look up the FMI parameter ID by NetCDF variable name. */
    T::FmiParamId       getFmiParameterIdByNetCdfName(const std::string& netCdfParamName);
    /*! \brief Look up the FMI parameter ID by Newbase numeric parameter ID. */
    T::FmiParamId       getFmiParameterIdByNewbaseId(T::NewbaseParamId newbaseParamId);
    /*! \brief Look up the FMI parameter ID by GRIB numeric parameter ID. */
    T::FmiParamId       getFmiParameterIdByGribId(T::GribParamId gribParamId);
    /*! \brief Return the default area interpolation method for the parameter in a GRIB 1 message. */
    short               getFmiParameterInterpolationMethod(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    short               getFmiParameterInterpolationMethod(GRIB2::Message& message);
    /*! \brief Return the FMI canonical parameter name for a GRIB 1 message, or empty string. */
    std::string         getFmiParameterName(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    std::string         getFmiParameterName(GRIB2::Message& message);
    /*! \brief Return the FMI parameter description for a GRIB 1 message, or empty string. */
    std::string         getFmiParameterDescription(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    std::string         getFmiParameterDescription(GRIB2::Message& message);
    /*! \brief Return the FMI parameter units for a GRIB 1 message, or empty string. */
    std::string         getFmiParameterUnits(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    std::string         getFmiParameterUnits(GRIB2::Message& message);
    /*! \brief Look up a processing type definition by numeric ID.
     *  \return true on success; false if not found. */
    bool                getFmiProcessingTypeDef(int processingTypeId,ProcessingTypeDef& processingTypeDef);

    // -----------------------------------------------------------------------
    // NetCDF parameter lookups
    // -----------------------------------------------------------------------

    /*! \brief Look up a NetCDF parameter definition by FMI parameter ID.
     *  \return true on success; false if not found. */
    bool                getNetCdfParameterDefByFmiId(T::FmiParamId fmiParamId,NetCdfParameterDef& paramDef);
    /*! \brief Look up a NetCDF parameter definition by NetCDF variable name.
     *  \return true on success; false if not found. */
    bool                getNetCdfParameterDefByName(const std::string& netCdfParamName,NetCdfParameterDef& paramDef);
    /*! \brief Look up the FMI→NetCDF mapping record by FMI parameter ID.
     *  \return true on success; false if not found. */
    bool                getNetCdfParameterMappingByFmiId(T::FmiParamId fmiParamId,FmiParameterId_netCdf& paramMapping);
    /*! \brief Return the NetCDF variable name for the parameter in a GRIB 1 message, or empty string. */
    std::string         getNetCdfParameterName(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    std::string         getNetCdfParameterName(GRIB2::Message& message);

    // -----------------------------------------------------------------------
    // Newbase parameter lookups
    // -----------------------------------------------------------------------

    /*! \brief Look up a Newbase parameter definition by Newbase numeric ID.
     *  \return true on success; false if not found. */
    bool                getNewbaseParameterDefById(T::NewbaseParamId newbaseParamId,NewbaseParameterDef& paramDef);
    /*! \brief Look up a Newbase parameter definition by Newbase parameter name.
     *  \return true on success; false if not found. */
    bool                getNewbaseParameterDefByName(const std::string& newbaseParamName,NewbaseParameterDef& paramDef);
    /*! \brief Look up a Newbase parameter definition by FMI parameter ID.
     *  \return true on success; false if not found. */
    bool                getNewbaseParameterDefByFmiId(T::FmiParamId fmiParamId,NewbaseParameterDef& paramDef);
    /*! \brief Look up the FMI→Newbase mapping record by FMI parameter ID.
     *  \return true on success; false if not found. */
    bool                getNewbaseParameterMappingByFmiId(T::FmiParamId fmiParamId,FmiParameterId_newbase& paramMapping);
    /*! \brief Determine the Newbase parameter ID for a GRIB 1 message. */
    T::NewbaseParamId   getNewbaseParameterId(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    T::NewbaseParamId   getNewbaseParameterId(GRIB2::Message& message);
    /*! \brief Return the Newbase parameter name for a GRIB 1 message, or empty string. */
    std::string         getNewbaseParameterName(GRIB1::Message& message);
    //! \overload (GRIB 2 message)
    std::string         getNewbaseParameterName(GRIB2::Message& message);

    // -----------------------------------------------------------------------
    // Geometry (grid projection) queries
    // -----------------------------------------------------------------------

    /*! \brief Return the column and row count for a geometry ID.
     *  \return true on success; false if the geometry is unknown. */
    bool                getGridDimensionsByGeometryId(T::GeometryId  geometryId,uint& cols,uint& rows);
    /*! \brief Return all lat/lon coordinates for a geometry ID into \p coordinates.
     *  \return true on success; false if the geometry is unknown. */
    bool                getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId,T::Coordinate_svec& coordinates);
    //! \overload (returns a shared vector; empty on failure)
    T::Coordinate_svec  getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId);
    /*! \brief Return lat/lon coordinates and grid dimensions for a geometry described by \p attributeList. */
    void                getGridLatLonCoordinatesByGeometry(T::AttributeList& attributeList,T::Coordinate_svec& latLonCoordinates,uint& width,uint& height);
    /*! \brief Return the boundary polyline (lat/lon) of a geometry, or empty on failure. */
    T::Coordinate_svec  getGridLatLonCoordinateLinePointsByGeometryId(T::GeometryId  geometryId);
    /*! \brief Return grid points in the native projection coordinates for a geometry ID. */
    T::Coordinate_svec  getGridOriginalCoordinatesByGeometryId(T::GeometryId  geometryId);
    /*! \brief Return native-projection coordinates and dimensions for a geometry described by \p attributeList. */
    void                getGridOriginalCoordinatesByGeometry(T::AttributeList& attributeList,T::Coordinate_svec& latLonCoordinates,T::CoordinateType coordinateType,T::Coordinate_svec& coordinates,uint& width,uint& height);
    /*! \brief Convert a lat/lon point to fractional grid indices for a geometry ID.
     *  \return true on success; false if the geometry is unknown or the point is outside. */
    bool                getGridPointByGeometryIdAndLatLonCoordinates(T::GeometryId  geometryId,double lat,double lon,double& grid_i,double& grid_j);
    /*! \brief Return the four corner lat/lon coordinates of a geometry's bounding box.
     *  \return true on success; false if the geometry is unknown. */
    bool                getGridLatLonAreaByGeometryId(T::GeometryId geometryId,T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    /*! \brief Return the approximate average cell size (degrees) for a geometry.
     *  \return true on success; false if the geometry is unknown. */
    bool                getGridCellAverageSizeByGeometryId(T::GeometryId geometryId,double& width,double& height);
    /*! \brief Return the axis-flip flags for a geometry.
     *  \return true on success; false if the geometry is unknown. */
    bool                getGridDirectionsByGeometryId(T::GeometryId geometryId,bool& reverseXDirection,bool& reverseYDirection);

    /*! \brief Populate \p geometryIdList with all registered geometry IDs. */
    void                getGeometryIdList(std::set<T::GeometryId>& geometryIdList);
    /*! \brief Populate \p geometryIdList with IDs of geometries that cover the given lat/lon point. */
    void                getGeometryIdListByLatLon(double lat,double lon,std::set<T::GeometryId>& geometryIdList);
    /*! \brief Look up the human-readable name for a geometry ID.
     *  \return true on success; false if the geometry is unknown. */
    bool                getGeometryNameById(T::GeometryId  geometryId,std::string& name);

    /*! \brief Create a new GRIB 1 grid definition object from a geometry string.  Caller owns the result. */
    GRIB1::GridDefinition*  createGrib1GridDefinition(const char *str);
    /*! \brief Create a new GRIB 2 grid definition object from a geometry string.  Caller owns the result. */
    GRIB2::GridDefinition*  createGrib2GridDefinition(const char *str);


  protected:

    GRIB1::GridDefinition*  createGrib1_LatLon(char* const field[], uint c);
    GRIB1::GridDefinition*  createGrib1_RotatedLatLon(char* const field[], uint c);
    GRIB1::GridDefinition*  createGrib1_Mercator(char* const field[], uint c);
    GRIB1::GridDefinition*  createGrib1_PolarStereographic(char* const field[], uint c);
    GRIB1::GridDefinition*  createGrib1_LambertConformal(char* const field[], uint c);

    GRIB2::GridDefinition*  createGrib2_LatLon(char* const field[], uint c);
    GRIB2::GridDefinition*  createGrib2_RotatedLatLon(char* const field[], uint c);
    GRIB2::GridDefinition*  createGrib2_TransverseMercator(char* const field[], uint c);
    GRIB2::GridDefinition*  createGrib2_PolarStereographic(char* const field[], uint c);
    GRIB2::GridDefinition*  createGrib2_LambertConformal(char* const field[], uint c);
    GRIB2::GridDefinition*  createGrib2_LambertAzimuthalEqualArea(char* const field[], uint c);

    void                    updateGrib();
    void                    updateGrib1();
    void                    updateGrib2();
    void                    updateFmi();
    void                    updateNetCdf();
    void                    updateNewbase();

    GribParamDef_cptr       getGribParameterDefById(T::GribParamId gribParamId);
    GribParamDef_cptr       getGribParameterDefByName(const std::string& gribParamName);
    FmiParamId_grib_cptr    getGribParameterMappingByFmiId(T::FmiParamId fmiParamId);

    GRIB1::GridDef_sptr     getGrib1Definition(GRIB1::Message& message);
    Grib1ParamDef_cptr      getGrib1ParameterDefById(T::GribParamId gribParamId);
    Grib1ParamDef_cptr      getGrib1ParameterDefByFmiId(T::FmiParamId fmiParamId);
    Grib1ParamDef_cptr      getGrib1ParameterDefByIndex(uint index);

    GRIB2::GridDef_sptr     getGrib2Definition(GRIB2::Message& message);
    Grib2ParamDef_cptr      getGrib2ParameterDefById(T::GribParamId gribParamId);
    Grib2ParamDef_cptr      getGrib2ParameterDefByFmiId(T::FmiParamId fmiParamId);

    AggregationDef_cptr     getFmiAggregationDef(int aggregationId);
    FmiParamDef_cptr        getFmiParameterDefById(T::FmiParamId fmiParamId);
    LevelDef_cptr           getFmiLevelDef(uint levelId);
    ForecastTypeDef_cptr    getFmiForecastTypeDef(int forecastTypeId);
    FmiParamDef_cptr        getFmiParameterDefByGribId(T::GribParamId gribParamId);
    FmiParamDef_cptr        getFmiParameterDefByNetCdfName(std::string& netCdfParamName);
    FmiParamDef_cptr        getFmiParameterDefByNewbaseId(T::NewbaseParamId newbaseParamId);
    FmiParamDef_cptr        getFmiParameterDefByName(const std::string& fmiParamName);
    FmiParamId_newbase_cptr getFmiParameterMappingByNewbaseId(T::NewbaseParamId newbaseParamId);
    FmiParamId_grib_cptr    getFmiParameterMappingByGribId(T::GribParamId gribParamId);
    FmiParamId_netCdf_cptr  getFmiParameterMappingByNetCdfName(std::string& netCdfParamName);
    ProcessingTypeDef_cptr  getFmiProcessingTypeDef(int processingTypeId);
    FmiGeomGroupDef_cptr    getFmiGeometryGroupDef(uint geometryGroupId);
    FmiGeomGroupDef_cptr    getFmiGeometryGroupDef(const char *producerName,uint groupType);

    NewbaseParamDef_cptr    getNewbaseParameterDefById(T::NewbaseParamId newbaseParamId);
    NewbaseParamDef_cptr    getNewbaseParameterDefByName(const std::string& newbaseParamName);
    FmiParamId_newbase_cptr getNewbaseParameterMappingByFmiId(T::FmiParamId fmiParamId);

    NetCdfParamDef_cptr     getNetCdfParameterDefByName(const std::string& netCdfParamName);
    FmiParamId_netCdf_cptr  getNetCdfParameterMappingByFmiId(T::FmiParamId fmiParamId);

    void                    loadGeometryDefinitions(const char *filename);
    void                    loadGribParameterDefinitions(const char *filename);
    void                    loadGrib1ParameterDefs(const char *filename);
    void                    loadGrib2ParameterDefs(const char *filename);

    void                    loadFmiAggregationDefinitions(const char *filename);
    void                    loadFmiLevelDefinitions(const char *filename);
    void                    loadFmiForecastTypeDefinitions(const char *filename);
    void                    loadFmiGeometryGroupDefinitions(const char *filename);
    void                    loadFmiParameterDefinitions(const char *filename);
    void                    loadFmiParameterId_grib(const char *filename);
    void                    loadFmiParameterId_netCdf(const char *filename);
    void                    loadFmiParameterId_newbase(const char *filename);
    void                    loadFmiProcessingTypeDefinitions(const char *filename);

    void                    loadNetCdfParameterDefinitions(const char *filename);
    void                    loadNewbaseParameterDefinitions(const char *filename);
    void                    loadFmiLevelId_grib1(const char *filename);
    void                    loadFmiLevelId_grib2(const char *filename);
    void                    loadFmiLevelId_newbase(const char *filename);

    void                    updateCheck();
    time_t                  getModificationTime(string_vec& files);

  protected:

    std::string             mConfigFileName;
    ConfigurationFile       mConfigurationFile;

    bool                    mInitialized;
    time_t                  mLastCheckTime;
    ModificationLock        mModificationLock;

    string_vec              mGrib_parameterDef_files;
    time_t                  mGrib_parameterDef_modificationTime;
    GribParamDef_vec        mGrib_parameterDef_records;

    string_vec              mGrib1_parameterDef_files;
    time_t                  mGrib1_parameterDef_modificationTime;
    Grib1ParamDef_vec       mGrib1_parameterDef_records;
    Grib1ParamDef_list      mGrib1_parameterDef_cache;

    string_vec              mGrib2_parameterDef_files;
    time_t                  mGrib2_parameterDef_modificationTime;
    Grib2ParamDef_vec       mGrib2_parameterDef_records;
    Grib2ParamDef_list      mGrib2_parameterDef_cache;

    string_vec              mFmi_parameterDef_files;
    time_t                  mFmi_parameterDef_modificationTime;
    FmiParamDef_umap        mFmi_parameterDef_records;

    string_vec              mFmi_geometryGroupDef_files;
    time_t                  mFmi_geometryGroupDef_modificationTime;
    FmiGeomGroupDef_vec     mFmi_geometryGroupDef_records;

    string_vec              mFmi_levelDef_files;
    time_t                  mFmi_levelDef_modificationTime;
    LevelDef_vec            mFmi_levelDef_records;

    string_vec              mFmi_forecastTypeDef_files;
    time_t                  mFmi_forecastTypeDef_modificationTime;
    ForecastTypeDef_vec     mFmi_forecastTypeDef_records;

    string_vec              mFmi_aggregationDef_files;
    time_t                  mFmi_aggregationDef_modificationTime;
    AggregationDef_vec      mFmi_aggregationDef_records;

    string_vec              mFmi_processingTypeDef_files;
    time_t                  mFmi_processingTypeDef_modificationTime;
    ProcessingTypeDef_vec   mFmi_processingTypeDef_records;

    string_vec              mFmi_parametersFromGrib_files;
    time_t                  mFmi_parametersFromGrib_modificationTime;
    FmiParamId_grib_umap    mFmi_parametersFromGrib_records;

    string_vec              mFmi_parametersFromNetCdf_files;
    time_t                  mFmi_parametersFromNetCdf_modificationTime;
    FmiParamId_netCdf_umap  mFmi_parametersFromNetCdf_records;

    string_vec              mFmi_parametersFromNewbase_files;
    time_t                  mFmi_parametersFromNewbase_modificationTime;
    FmiParamId_newbase_umap mFmi_parametersFromNewbase_records;

    string_vec              mFmi_levelsFromGrib1_files;
    time_t                  mFmi_levelsFromGrib1_modificationTime;
    FmiLevelId_grib_vec     mFmi_levelsFromGrib1_records;

    string_vec              mFmi_levelsFromGrib2_files;
    time_t                  mFmi_levelsFromGrib2_modificationTime;
    FmiLevelId_grib_vec     mFmi_levelsFromGrib2_records;

    string_vec              mFmi_levelsFromNewbase_files;
    time_t                  mFmi_levelsFromNewbase_modificationTime;
    IdMap                   mNewbaseLevelIdToFmiLevelId;

    string_vec              mFmi_geometryDef_files;
    time_t                  mFmi_geometryDef_modificationTime;
    GRIB1::GridDef_spmap    mGridDefinitions1;
    GRIB2::GridDef_spmap    mGridDefinitions2;

    string_vec              mNewbase_parameterDef_files;
    time_t                  mNewbase_parameterDef_modificationTime;
    NewbaseParamDef_umap    mNewbase_parameterDef_records;
    IdMap                   mFmiIdToNewbaseId;
    IdMap                   mNewbaseIdToFmiId;
    IdMap                   mGribIdToFmiId;
    StringIdMap             mNewbaseNameToId;
    StringIdMap             mFmiNameToId;
    StringIdMap             mNetCdfNameToFmiId;

    string_vec              mNetCdf_parameterDef_files;
    time_t                  mNetCdf_parameterDef_modificationTime;
    NetCdfParamDef_umap     mNetCdf_parameterDef_records;

    GeometryNames           mGeometryNames;
};

extern GridDef gridDef;


}  // namespace Identification
}  // namespace SmartMet
