#pragma once

#include "GribParameterDef.h"
#include "GribTableValue.h"
#include "Grib1ParameterDef.h"
#include "Grib2ParameterDef.h"
#include "FmiLevelId_grib.h"
#include "FmiParameterDef.h"
#include "FmiParameterId_grib.h"
#include "FmiParameterId_grib1.h"
#include "FmiParameterId_grib2.h"
#include "FmiParameterId_newbase.h"
#include "FmiProducerId_grib.h"
#include "LevelDef.h"
#include "ForecastTypeDef.h"
#include "NewbaseParameterDef.h"
#include "TimeRangeDef.h"
#include "UnitDefinition.h"

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



/*! The GridDef class is used for accessing different kind of definitions relating
    to the GRIB1/GRIB2 files.

    When using the GRIB_API, all GRIB 1 / GRIB 2 related information is defined in
    several definition and table files, which are distributed in several directories.
    We have used the "createAttributeListFiles.php" script for copying the most essential
    information from these files into our own attributeList files. This simplifies the reading
    and handling of the GRIB definitions. In addition, it means that we do not need to install
    the GRIB_API into the production environment, because all necessary information can be
    found from our own attributeList files.

    The "createAttributeListFiles.php" script creates the following files:

    | File                   | Description                                                            |
    | ---------------------- | ---------------------------------------------------------------------- |
    | parameterDef.csv       | Defines global parameterIds, categories, names and units.              |
    | tables.csv             | Contains all table values defined for GRIB 1 and GRIB 2.               |
    | units.csv              | Contains original units defined in GRIB 1 and GRIB 2 definition files. |

    The GridDef class is used in order to access information in these attributeList files.
    In practice there is one global instance of this class (SmartMet::GRIB:def), which should
    be initialized in the main program. After that all GRIB definition related information can
    be fetched from this instance.
*/


class GridDef
{
  public:
                        GridDef();
    virtual             ~GridDef();

    void                init(const char* configFile);

    std::string         getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,const std::string& table,std::uint32_t number);
    std::string         getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,const std::string& table,T::UInt8_opt number);
    std::string         getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,const std::string& table,T::UInt16_opt number);
    std::string         getPreferredUnits(const std::string& originalUnits);

    bool                getGribParamDefById(T::GribParamId gribParamId,GribParameterDef&  paramDef);
    bool                getGribParamDefByName(const std::string& gribParamName,GribParameterDef&  paramDef);
    bool                getGribParamDef(uint discipline,uint category,uint number,GribParameterDef&  paramDef);
    bool                getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId,T::Coordinate_svec& coordinates);
    bool                getGridDimensionsByGeometryId(T::GeometryId  geometryId,uint& cols,uint& rows);

    int                 getGrib1GeometryId(GRIB1::Message& message);
    bool                getGrib1LevelDef(uint levelId,LevelDef& levelDef);
    uint                getGrib1ParameterDefCount();
    bool                getGrib1ParameterDefById(T::GribParamId gribParamId,Grib1ParameterDef& paramDef);
    bool                getGrib1ParameterDefByIndex(uint index,Grib1ParameterDef& paramDef);
    bool                getGrib1ParameterDefByName(const std::string& gribParamName,Grib1ParameterDef& paramDef);
    bool                getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter,Grib1ParameterDef& paramDef);
    bool                getGrib1TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef);

    int                 getGrib2GeometryId(GRIB2::Message& message);
    bool                getGrib2LevelDef(uint levelId,LevelDef& levelDef);
    uint                getGrib2ParameterDefCount();
    bool                getGrib2ParameterDefById(T::GribParamId gribParamId,Grib2ParameterDef& paramDef);
    bool                getGrib2ParameterDefByIndex(uint index,Grib2ParameterDef& paramDef);
    bool                getGrib2ParameterDefByName(const std::string& gribParamName,Grib2ParameterDef& paramDef);
    bool                getGrib2TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef);

    void                getGeometryIdList(std::set<T::GeometryId>& geometryIdList);
    void                getGeometryIdListByLatLon(double lat,double lon,std::set<T::GeometryId>& geometryIdList);
    bool                getGeometryNameById(T::GeometryId  geometryId,std::string& name);

    bool                getGridLatLonAreaByGeometryId(T::GeometryId geometryId,T::Coordinate& topLeft,T::Coordinate& topRight,T::Coordinate& bottomLeft,T::Coordinate& bottomRight);
    bool                getGridCellAverageSizeByGeometryId(T::GeometryId geometryId,double& width,double& height);
    bool                getGridDirectionsByGeometryId(T::GeometryId geometryId,bool& reverseXDirection,bool& reverseYDirection);

    T::Coordinate_svec  getGridOriginalCoordinatesByGeometryId(T::GeometryId  geometryId);
    void                getGridOriginalCoordinatesByGeometry(T::AttributeList& attributeList,T::Coordinate_svec& latLonCoordinates,T::CoordinateType coordinateType,T::Coordinate_svec& coordinates,uint& width,uint& height);

    T::Coordinate_svec  getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId);
    void                getGridLatLonCoordinatesByGeometry(T::AttributeList& attributeList,T::Coordinate_svec& latLonCoordinates,uint& width,uint& height);
    T::Coordinate_svec  getGridLatLonCoordinateLinePointsByGeometryId(T::GeometryId  geometryId);
    bool                getGridPointByGeometryIdAndLatLonCoordinates(T::GeometryId  geometryId,double lat,double lon,double& grid_i,double& grid_j);

    T::GribParamId      getGribParameterId(GRIB1::Message& message);
    T::GribParamId      getGribParameterId(GRIB2::Message& message);
    T::ParamLevelId     getGrib1LevelId(GRIB1::Message& message);
    T::ParamLevelId     getGrib1LevelId(GRIB2::Message& message);
    T::ParamLevelId     getGrib2LevelId(GRIB1::Message& message);
    T::ParamLevelId     getGrib2LevelId(GRIB2::Message& message);
    std::string         getGribParameterName(GRIB1::Message& message);
    std::string         getGribParameterName(GRIB2::Message& message);
    std::string         getGribParameterUnits(GRIB1::Message& message);
    std::string         getGribParameterUnits(GRIB2::Message& message);

    T::FmiParamId       getFmiParameterIdByFmiName(const std::string& fmiParamName);
    bool                getFmiParameterDefById(T::FmiParamId fmiParamId,FmiParameterDef& paramDef);
    bool                getFmiParameterDefByGribId(T::GribParamId gribParamId,FmiParameterDef& paramDef);
    bool                getFmiParameterDefByNewbaseId(T::NewbaseParamId newbaseParamId,FmiParameterDef& paramDef);
    bool                getFmiParameterDefByName(const std::string& fmiParamName,FmiParameterDef& paramDef);
    bool                getFmiProducerByName(const std::string& fmiProducerName,FmiProducerId_grib& producer);
    bool                getFmiProducerByFmiId(uint fmiProducerId,FmiProducerId_grib& producer);

    T::FmiParamId       getFmiParameterId(GRIB1::Message& message);
    T::FmiParamId       getFmiParameterId(GRIB2::Message& message);
    bool                getFmiLevelDef(uint levelId,LevelDef& levelDef);
    T::ParamLevelId     getFmiLevelId(GRIB1::Message& message);
    T::ParamLevelId     getFmiLevelId(GRIB2::Message& message);
    bool                getFmiForecastTypeDef(int forecastTypeId,ForecastTypeDef& forecastTypeDef);
    std::string         getFmiParameterName(GRIB1::Message& message);
    std::string         getFmiParameterName(GRIB2::Message& message);
    std::string         getFmiParameterDescription(GRIB1::Message& message);
    std::string         getFmiParameterDescription(GRIB2::Message& message);
    std::string         getFmiParameterUnits(GRIB1::Message& message);
    std::string         getFmiParameterUnits(GRIB2::Message& message);

    bool                getNewbaseParameterDefById(T::NewbaseParamId newbaseParamId,NewbaseParameterDef& paramDef);
    bool                getNewbaseParameterDefByName(const std::string& newbaseParamName,NewbaseParameterDef& paramDef);
    bool                getNewbaseParameterDefByFmiId(T::FmiParamId fmiParamId,NewbaseParameterDef& paramDef);
    bool                getNewbaseParameterMappingByFmiId(T::FmiParamId fmiParamId,FmiParameterId_newbase& paramMapping);

    T::NewbaseParamId   getNewbaseParameterId(GRIB1::Message& message);
    T::NewbaseParamId   getNewbaseParameterId(GRIB2::Message& message);
    std::string         getNewbaseParameterName(GRIB1::Message& message);
    std::string         getNewbaseParameterName(GRIB2::Message& message);

    short               getPreferredInterpolationMethodByUnits(const std::string& originalUnits);
    short               getFmiParameterInterpolationMethod(GRIB1::Message& message);
    short               getFmiParameterInterpolationMethod(GRIB2::Message& message);

    bool                getGribDefByFmiId(T::FmiParamId fmiParamId,FmiParameterId_grib& def);
    bool                getGrib1DefByFmiId(T::FmiParamId fmiParamId,FmiParameterId_grib1& def);
    bool                getGrib2DefByFmiId(T::FmiParamId fmiParamId,FmiParameterId_grib2& def);

    bool                getGrib1LevelDef(uint fmiLevelId,uint generatingProcessId,uint centre,FmiLevelId_grib& def);
    bool                getGrib1LevelDef(uint fmiLevelId,FmiLevelId_grib& def);
    bool                getGrib2LevelDef(uint fmiLevelId,FmiLevelId_grib& def);


    GRIB1::GridDefinition*  createGrib1GridDefinition(const char *str);
    GRIB2::GridDefinition*  createGrib2GridDefinition(const char *str);

    GRIB1::GridDef_ptr      getGrib1DefinitionByGeometryId(int geometryId);
    GRIB1::GridDef_ptr      getGrib1DefinitionByGeometryString(std::string& geometryStr);
    GRIB2::GridDef_ptr      getGrib2DefinitionByGeometryId(int geometryId);
    GRIB2::GridDef_ptr      getGrib2DefinitionByGeometryString(std::string& geometryStr);

  protected:

    void                    updateGrib();
    void                    updateGrib1();
    void                    updateGrib2();
    void                    updateFmi();
    void                    updateNewbase();

    GribParamDef_cptr       getGribParamDefById(T::GribParamId gribParamId);
    GribParamDef_cptr       getGribParamDefByName(const std::string& gribParamName);
    GribParamDef_cptr       getGribParamDef(uint discipline,uint category,uint number);

    GRIB1::GridDef_ptr      getGrib1Definition(GRIB1::Message& message);
    LevelDef_cptr           getGrib1LevelDef(uint levelId);
    Grib1ParamDef_cptr      getGrib1ParameterDefById(T::GribParamId gribParamId);
    Grib1ParamDef_cptr      getGrib1ParameterDefByIndex(uint index);
    Grib1ParamDef_cptr      getGrib1ParameterDefByName(const std::string& gribParamName);
    Grib1ParamDef_cptr      getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter);
    TimeRangeDef_cptr       getGrib1TimeRangeDef(uint timeRangeId);

    GRIB2::GridDef_ptr      getGrib2Definition(GRIB2::Message& message);
    LevelDef_cptr           getGrib2LevelDef(uint levelId);
    Grib2ParamDef_cptr      getGrib2ParameterDefById(T::GribParamId gribParamId);
    Grib2ParamDef_cptr      getGrib2ParameterDefByName(const std::string& gribParamName);
    TimeRangeDef_cptr       getGrib2TimeRangeDef(uint timeRangeId);
    FmiParameterId_grib*    getGribDefByFmiId(T::FmiParamId fmiParamId);
    FmiParameterId_grib1*   getGrib1DefByFmiId(T::FmiParamId fmiParamId);
    FmiParameterId_grib2*   getGrib2DefByFmiId(T::FmiParamId fmiParamId);

    void                    loadGeometryDefinitions(const char *filename);
    void                    loadGribParameterDefinitions(const char *filename);
    void                    loadGribTableValues(const char *filename);
    void                    loadGribUnitDefinitions(const char *filename);

    void                    loadGrib1LevelDefinitions(const char *filename);
    void                    loadGrib1ParameterDefs(const char *filename);
    void                    loadGrib1TimeRangeDefinitions(const char *filename);

    void                    loadGrib2ParameterDefs(const char *filename);
    void                    loadGrib2LevelDefinitions(const char *filename);
    void                    loadGrib2TimeRangeDefinitions(const char *filename);

    void                    loadFmiParameterDefinitions(const char *filename);
    void                    loadFmiLevelDefinitions(const char *filename);
    void                    loadFmiForecastTypeDefinitions(const char *filename);
    void                    loadFmiParameterId_grib(const char *filename);
    void                    loadFmiParameterId_grib1(const char *filename);
    void                    loadFmiParameterId_grib2(const char *filename);
    void                    loadFmiParameterId_newbase(const char *filename);

    void                    loadNewbaseParameterDefinitions(const char *filename);
    void                    loadFmiLevelId_grib1(const char *filename);
    void                    loadFmiLevelId_grib2(const char *filename);
    void                    loadFmiProducerId_grib(const char *filename);

    void                    updateCheck();
    time_t                  getModificationTime(string_vec& files);

    uint                    countParameterMatchPoints(GRIB2::Message& message,const Grib2ParameterDef& p);
    uint                    countParameterMatchPoints(GRIB2::Message& message,const FmiParameterId_grib2& p);

    GribParamDef_cptr       getGribParameterDefById(T::GribParamId gribParamId);
    FmiParamDef_cptr        getFmiParameterDefById(T::FmiParamId fmiParamId);
    LevelDef_cptr           getFmiLevelDef(uint levelId);
    ForecastTypeDef_cptr    getFmiForecastTypeDef(int forecastType);
    FmiParamDef_cptr        getFmiParameterDefByGribId(T::GribParamId gribParamId);
    FmiParamDef_cptr        getFmiParameterDefByNewbaseId(T::NewbaseParamId newbaseParamId);
    FmiParamDef_cptr        getFmiParameterDefByName(const std::string& fmiParamName);
    FmiProducerId_grib_cptr getFmiProducerByName(const std::string& fmiProducerName);
    FmiProducerId_grib_cptr getFmiProducerByFmiId(uint fmiProducerId);
    NewbaseParamDef_cptr    getNewbaseParameterDefById(T::NewbaseParamId newbaseParamId);
    NewbaseParamDef_cptr    getNewbaseParameterDefByName(const std::string& newbaseParamName);
    FmiParamId_newbase_cptr getFmiParameterIdByNewbaseId(T::NewbaseParamId newbaseParamId);
    FmiParamId_grib_cptr    getFmiParameterIdByGribId(T::GribParamId gribParamId);
    FmiParamId_newbase_cptr getNewbaseParameterIdByFmiId(T::FmiParamId fmiParamId);



    std::string             mConfigFileName;
    ConfigurationFile       mConfigurationFile;

    bool                    mInitialized;
    time_t                  mLastCheckTime;
    ModificationLock        mModificationLock;

    string_vec              mGrib_parameterDef_files;
    time_t                  mGrib_parameterDef_modificationTime;
    GribParamDef_vec        mGrib_parameterDef_records;

    string_vec              mGrib_tableDef_files;
    time_t                  mGrib_tableDef_modificationTime;
    GribTableValue_vec      mGrib_tableDef_records;

    string_vec              mGrib_unitDef_files;
    time_t                  mGrib_unitDef_modificationTime;
    UnitDefinition_vec      mGrib_unitDef_records;

    string_vec              mGrib1_parameterDef_files;
    time_t                  mGrib1_parameterDef_modificationTime;
    Grib1ParamDef_vec       mGrib1_parameterDef_records;

    string_vec              mGrib1_levelDef_files;
    time_t                  mGrib1_levelDef_modificationTime;
    LevelDef_vec            mGrib1_levelDef_records;

    string_vec              mGrib1_timeRangeDef_files;
    time_t                  mGrib1_timeRangeDef_modificationTime;
    TimeRangeDef_vec        mGrib1_timeRangeDef_records;

    string_vec              mGrib2_parameterDef_files;
    time_t                  mGrib2_parameterDef_modificationTime;
    Grib2ParamDef_vec       mGrib2_parameterDef_records;

    string_vec              mGrib2_levelDef_files;
    time_t                  mGrib2_levelDef_modificationTime;
    LevelDef_vec            mGrib2_levelDef_records;

    string_vec              mGrib2_timeRangeDef_files;
    time_t                  mGrib2_timeRangeDef_modificationTime;
    TimeRangeDef_vec        mGrib2_timeRangeDef_records;

    string_vec              mFmi_parameterDef_files;
    time_t                  mFmi_parameterDef_modificationTime;
    FmiParamDef_vec         mFmi_parameterDef_records;

    string_vec              mFmi_levelDef_files;
    time_t                  mFmi_levelDef_modificationTime;
    LevelDef_vec            mFmi_levelDef_records;

    string_vec              mFmi_forecastTypeDef_files;
    time_t                  mFmi_forecastTypeDef_modificationTime;
    ForecastTypeDef_vec     mFmi_forecastTypeDef_records;

    string_vec              mFmi_parametersFromGrib_files;
    time_t                  mFmi_parametersFromGrib_modificationTime;
    FmiParamId_grib_vec     mFmi_parametersFromGrib_records;

    string_vec              mFmi_parametersFromGrib1_files;
    time_t                  mFmi_parametersFromGrib1_modificationTime;
    FmiParamId_grib1_vec    mFmi_parametersFromGrib1_records;

    string_vec              mFmi_parametersFromGrib2_files;
    time_t                  mFmi_parametersFromGrib2_modificationTime;
    FmiParamId_grib2_vec    mFmi_parametersFromGrib2_records;

    string_vec              mFmi_parametersFromNewbase_files;
    time_t                  mFmi_parametersFromNewbase_modificationTime;
    FmiParamId_newbase_vec  mFmi_parametersFromNewbase_records;

    string_vec              mFmi_levelsFromGrib1_files;
    time_t                  mFmi_levelsFromGrib1_modificationTime;
    FmiLevelId_grib_vec     mFmi_levelsFromGrib1_records;

    string_vec              mFmi_levelsFromGrib2_files;
    time_t                  mFmi_levelsFromGrib2_modificationTime;
    FmiLevelId_grib_vec     mFmi_levelsFromGrib2_records;

    string_vec              mFmi_producersFromGrib_files;
    time_t                  mFmi_producersFromGrib_modificationTime;
    FmiProducerId_grib_vec  mFmi_producersFromGrib_records;

    string_vec              mFmi_geometryDef_files;
    time_t                  mFmi_geometryDef_modificationTime;
    GRIB1::GridDef_map      mGridDefinitions1;
    GRIB2::GridDef_map      mGridDefinitions2;

    string_vec              mNewbase_parameterDef_files;
    time_t                  mNewbase_parameterDef_modificationTime;
    NewbaseParamDef_vec     mNewbase_parameterDef_records;

    CoordinateCache         mCoordinateCache;
    ModificationLock        mCoordinateCacheModificationLock;

    GeometryNames           mGeometryNames;
};

extern GridDef gridDef;


}  // namespace Identification
}  // namespace SmartMet
