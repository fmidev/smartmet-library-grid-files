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


// The name of the environment variable that is usually used in order to store the location
// of the GridDef configuration file.

#define SMARTMET_GRID_CONFIG_FILE "SMARTMET_GRID_CONFIG_FILE"


namespace SmartMet
{
namespace Identification
{

struct CoordinateRec
{
  public:
    T::Coordinate_svec latlonCoordinates;
    T::Coordinate_svec originalCoordinates;
};

typedef std::unordered_map<std::size_t,CoordinateRec> CoordinateCache;
typedef std::unordered_map<std::size_t,CoordinateRec>::iterator CoordinateCacheIterator;
typedef std::unordered_map<uint,std::string> GeometryNames;
typedef std::unordered_map<uint,uint> IdMap;
typedef std::unordered_map<std::string,uint> StringIdMap;


class GridDef
{
  public:
                        GridDef();
    virtual             ~GridDef();

    void                init(const char* configFile);

    bool                getGribParameterDefById(T::GribParamId gribParamId,GribParameterDef&  paramDef);
    bool                getGribParameterDefByName(const std::string& gribParamName,GribParameterDef&  paramDef);
    T::GribParamId      getGribParameterId(GRIB1::Message& message);
    T::GribParamId      getGribParameterId(GRIB2::Message& message);
    bool                getGribParameterMappingByFmiId(T::FmiParamId fmiParamId,FmiParameterId_grib& def);
    std::string         getGribParameterName(GRIB1::Message& message);
    std::string         getGribParameterName(GRIB2::Message& message);

    GRIB1::GridDef_sptr getGrib1DefinitionByGeometryId(int geometryId);
    GRIB1::GridDef_sptr getGrib1DefinitionByGeometryString(const char *geometryStr);
    GRIB1::GridDef_sptr getGrib1DefinitionByGeometryString(std::string& geometryStr);
    int                 getGrib1GeometryId(GRIB1::Message& message);
    bool                getGrib1LevelDef(uint fmiLevelId,FmiLevelId_grib& def);
    uint                getGrib1ParameterDefCount();
    bool                getGrib1ParameterDefById(T::GribParamId gribParamId,Grib1ParameterDef& paramDef);
    bool                getGrib1ParameterDefByFmiId(T::FmiParamId fmiParamId,Grib1ParameterDef& paramDef);
    bool                getGrib1ParameterDefByIndex(uint index,Grib1ParameterDef& paramDef);

    GRIB2::GridDef_sptr getGrib2DefinitionByGeometryId(int geometryId);
    GRIB2::GridDef_sptr getGrib2DefinitionByGeometryString(const char *geometryStr);
    GRIB2::GridDef_sptr getGrib2DefinitionByGeometryString(std::string& geometryStr);
    int                 getGrib2GeometryId(GRIB2::Message& message);
    bool                getGrib2LevelDef(uint fmiLevelId,FmiLevelId_grib& def);
    uint                getGrib2ParameterDefCount();
    bool                getGrib2ParameterDefById(T::GribParamId gribParamId,Grib2ParameterDef& paramDef);
    bool                getGrib2ParameterDefByFmiId(T::FmiParamId fmiParamId,Grib2ParameterDef& paramDef);
    bool                getGrib2ParameterDefByIndex(uint index,Grib2ParameterDef& paramDef);

    bool                getFmiAggregationDef(int aggregationId,AggregationDef& aggregationDef);
    bool                getFmiLevelDef(uint levelId,LevelDef& levelDef);
    T::ParamLevelId     getFmiLevelId(GRIB1::Message& message);
    T::ParamLevelId     getFmiLevelId(GRIB2::Message& message);
    uint                getFmiLevelIdByNewbaseLevelId(uint newbaseLevelId);
    bool                getFmiForecastTypeDef(int forecastTypeId,ForecastTypeDef& forecastTypeDef);
    bool                getFmiParameterDefById(T::FmiParamId fmiParamId,FmiParameterDef& paramDef);
    bool                getFmiParameterDefByGribId(T::GribParamId gribParamId,FmiParameterDef& paramDef);
    bool                getFmiParameterDefByNewbaseId(T::NewbaseParamId newbaseParamId,FmiParameterDef& paramDef);
    bool                getFmiParameterDefByNetCdfName(std::string& netCdfParamName,FmiParameterDef& paramDef);
    bool                getFmiParameterDefByName(const std::string& fmiParamName,FmiParameterDef& paramDef);
    T::FmiParamId       getFmiParameterId(GRIB1::Message& message);
    T::FmiParamId       getFmiParameterId(GRIB2::Message& message);
    T::FmiParamId       getFmiParameterIdByFmiName(const std::string& fmiParamName);
    T::FmiParamId       getFmiParameterIdByNewbaseName(const std::string& newbaseParamName);
    T::FmiParamId       getFmiParameterIdByNetCdfName(const std::string& netCdfParamName);
    T::FmiParamId       getFmiParameterIdByNewbaseId(T::NewbaseParamId newbaseParamId);
    T::FmiParamId       getFmiParameterIdByGribId(T::GribParamId gribParamId);
    short               getFmiParameterInterpolationMethod(GRIB1::Message& message);
    short               getFmiParameterInterpolationMethod(GRIB2::Message& message);
    std::string         getFmiParameterName(GRIB1::Message& message);
    std::string         getFmiParameterName(GRIB2::Message& message);
    std::string         getFmiParameterDescription(GRIB1::Message& message);
    std::string         getFmiParameterDescription(GRIB2::Message& message);
    std::string         getFmiParameterUnits(GRIB1::Message& message);
    std::string         getFmiParameterUnits(GRIB2::Message& message);
    bool                getFmiProcessingTypeDef(int processingTypeId,ProcessingTypeDef& processingTypeDef);

    bool                getNetCdfParameterDefByFmiId(T::FmiParamId fmiParamId,NetCdfParameterDef& paramDef);
    bool                getNetCdfParameterDefByName(const std::string& netCdfParamName,NetCdfParameterDef& paramDef);
    bool                getNetCdfParameterMappingByFmiId(T::FmiParamId fmiParamId,FmiParameterId_netCdf& paramMapping);
    std::string         getNetCdfParameterName(GRIB1::Message& message);
    std::string         getNetCdfParameterName(GRIB2::Message& message);

    bool                getNewbaseParameterDefById(T::NewbaseParamId newbaseParamId,NewbaseParameterDef& paramDef);
    bool                getNewbaseParameterDefByName(const std::string& newbaseParamName,NewbaseParameterDef& paramDef);
    bool                getNewbaseParameterDefByFmiId(T::FmiParamId fmiParamId,NewbaseParameterDef& paramDef);
    bool                getNewbaseParameterMappingByFmiId(T::FmiParamId fmiParamId,FmiParameterId_newbase& paramMapping);
    T::NewbaseParamId   getNewbaseParameterId(GRIB1::Message& message);
    T::NewbaseParamId   getNewbaseParameterId(GRIB2::Message& message);
    std::string         getNewbaseParameterName(GRIB1::Message& message);
    std::string         getNewbaseParameterName(GRIB2::Message& message);

    bool                getGridDimensionsByGeometryId(T::GeometryId  geometryId,uint& cols,uint& rows);
    bool                getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId,T::Coordinate_svec& coordinates);
    T::Coordinate_svec  getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId);
    void                getGridLatLonCoordinatesByGeometry(T::AttributeList& attributeList,T::Coordinate_svec& latLonCoordinates,uint& width,uint& height);
    T::Coordinate_svec  getGridLatLonCoordinateLinePointsByGeometryId(T::GeometryId  geometryId);
    T::Coordinate_svec  getGridOriginalCoordinatesByGeometryId(T::GeometryId  geometryId);
    void                getGridOriginalCoordinatesByGeometry(T::AttributeList& attributeList,T::Coordinate_svec& latLonCoordinates,T::CoordinateType coordinateType,T::Coordinate_svec& coordinates,uint& width,uint& height);
    bool                getGridPointByGeometryIdAndLatLonCoordinates(T::GeometryId  geometryId,double lat,double lon,double& grid_i,double& grid_j);
    bool                getGridLatLonAreaByGeometryId(T::GeometryId geometryId,T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    bool                getGridCellAverageSizeByGeometryId(T::GeometryId geometryId,double& width,double& height);
    bool                getGridDirectionsByGeometryId(T::GeometryId geometryId,bool& reverseXDirection,bool& reverseYDirection);

    void                getGeometryIdList(std::set<T::GeometryId>& geometryIdList);
    void                getGeometryIdListByLatLon(double lat,double lon,std::set<T::GeometryId>& geometryIdList);
    bool                getGeometryNameById(T::GeometryId  geometryId,std::string& name);

    GRIB1::GridDefinition*  createGrib1GridDefinition(const char *str);
    GRIB2::GridDefinition*  createGrib2GridDefinition(const char *str);


  protected:

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

    CoordinateCache         mCoordinateCache;
    ModificationLock        mCoordinateCacheModificationLock;

    GeometryNames           mGeometryNames;
};

extern GridDef gridDef;


}  // namespace Identification
}  // namespace SmartMet
