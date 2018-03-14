#pragma once

#include "GribParameterDef.h"
#include "GribTableValue.h"
#include "Grib1ParameterDef.h"
#include "Grib2ParameterDef.h"
#include "FmiLevelId_grib.h"
#include "FmiParameterDef.h"
#include "FmiParameterId_grib1.h"
#include "FmiParameterId_grib2.h"
#include "FmiParameterId_newbase.h"
#include "FmiProducerId_grib.h"
#include "LevelDef.h"
#include "NewbaseParameterDef.h"
#include "TimeRangeDef.h"
#include "UnitDefinition.h"

#include "common/AutoThreadLock.h"
#include "common/ConfigurationFile.h"
#include "grib1/Message.h"
#include "grib2/Message.h"
#include "grid/Typedefs.h"
#include "grib2/GridDefinition.h"

#include <set>


// The name of the environment variable that is usually used in order to store the location
// of the GridDef configuration file.

#define SMARTMET_GRID_CONFIG_FILE "SMARTMET_GRID_CONFIG_FILE"


namespace SmartMet
{
namespace Identification
{

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
    virtual           ~GridDef();

    void              init(const char* configFile);

    std::string       getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,std::uint32_t number);
    std::string       getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt8_opt number);
    std::string       getGribTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt16_opt number);
    std::string       getPreferredUnits(std::string originalUnits);

    bool              getGribParamDefById(T::ParamId gribParamId,GribParameterDef&  paramDef);
    bool              getGribParamDefByName(std::string gribParamName,GribParameterDef&  paramDef);
    bool              getGribParamDef(uint discipline,uint category,uint number,GribParameterDef&  paramDef);
    bool              getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId,T::Coordinate_vec& coordinates);
    bool              getGridDimensionsByGeometryId(T::GeometryId  geometryId,uint& cols,uint& rows);

    int               getGrib1GeometryIdByHash(T::Hash hash);
    bool              getGrib1LevelDef(uint levelId,LevelDef& levelDef);
    uint              getGrib1ParameterDefCount();
    bool              getGrib1ParameterDefById(T::ParamId gribParamId,Grib1ParameterDef& paramDef);
    bool              getGrib1ParameterDefByIndex(uint index,Grib1ParameterDef& paramDef);
    bool              getGrib1ParameterDefByName(std::string gribParamName,Grib1ParameterDef& paramDef);
    bool              getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter,Grib1ParameterDef& paramDef);
    bool              getGrib1TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef);

    int               getGrib2GeometryIdByHash(T::Hash hash);
    bool              getGrib2LevelDef(uint levelId,LevelDef& levelDef);
    uint              getGrib2ParameterDefCount();
    bool              getGrib2ParameterDefById(T::ParamId gribParamId,Grib2ParameterDef& paramDef);
    bool              getGrib2ParameterDefByIndex(uint index,Grib2ParameterDef& paramDef);
    bool              getGrib2ParameterDefByName(std::string gribParamName,Grib2ParameterDef& paramDef);
    bool              getGrib2TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef);

    void              getGeometryIdListByLatLon(double lat,double lon,std::set<T::GeometryId>& geometryIdList);
    bool              getGeometryNameById(T::GeometryId  geometryId,std::string& name);

    T::ParamId        getGribParameterId(GRIB1::Message& message);
    T::ParamId        getGribParameterId(GRIB2::Message& message);
    T::ParamLevelId   getGrib1LevelId(GRIB1::Message& message);
    T::ParamLevelId   getGrib1LevelId(GRIB2::Message& message);
    T::ParamLevelId   getGrib2LevelId(GRIB1::Message& message);
    T::ParamLevelId   getGrib2LevelId(GRIB2::Message& message);
    std::string       getGribParameterName(GRIB1::Message& message);
    std::string       getGribParameterName(GRIB2::Message& message);
    std::string       getGribParameterDescription(GRIB1::Message& message);
    std::string       getGribParameterDescription(GRIB2::Message& message);
    std::string       getGribParameterUnits(GRIB1::Message& message);
    std::string       getGribParameterUnits(GRIB2::Message& message);

    T::ParamId        getFmiParameterIdByFmiName(std::string fmiParamName);
    bool              getFmiParameterDefById(T::ParamId fmiParamId,FmiParameterDef& paramDef);
    bool              getFmiParameterDefByNewbaseId(T::ParamId newbaseParamId,FmiParameterDef& paramDef);
    bool              getFmiParameterDefByName(std::string fmiParamName,FmiParameterDef& paramDef);
    bool              getFmiProducerByName(std::string fmiProducerName,FmiProducerId_grib& producer);

    T::ParamId        getFmiParameterId(GRIB1::Message& message);
    T::ParamId        getFmiParameterId(GRIB2::Message& message);
    T::ParamLevelId   getFmiLevelId(GRIB1::Message& message);
    T::ParamLevelId   getFmiLevelId(GRIB2::Message& message);
    std::string       getFmiParameterName(GRIB1::Message& message);
    std::string       getFmiParameterName(GRIB2::Message& message);
    std::string       getFmiParameterDescription(GRIB1::Message& message);
    std::string       getFmiParameterDescription(GRIB2::Message& message);
    std::string       getFmiParameterUnits(GRIB1::Message& message);
    std::string       getFmiParameterUnits(GRIB2::Message& message);

    bool              getNewbaseParameterDefById(T::ParamId newbaseParamId,NewbaseParameterDef& paramDef);
    bool              getNewbaseParameterDefByFmiId(T::ParamId fmiParamId,NewbaseParameterDef& paramDef);
    bool              getNewbaseParameterMappingByFmiId(T::ParamId fmiParamId,FmiParameterId_newbase& paramMapping);

    T::ParamId        getCdmParameterId(GRIB1::Message& message);
    T::ParamId        getCdmParameterId(GRIB2::Message& message);
    std::string       getCdmParameterName(GRIB1::Message& message);
    std::string       getCdmParameterName(GRIB2::Message& message);

    T::ParamId        getNewbaseParameterId(GRIB1::Message& message);
    T::ParamId        getNewbaseParameterId(GRIB2::Message& message);
    std::string       getNewbaseParameterName(GRIB1::Message& message);
    std::string       getNewbaseParameterName(GRIB2::Message& message);

    T::AreaInterpolationMethod  getPreferredInterpolationMethodByUnits(std::string originalUnits);
    T::AreaInterpolationMethod  getFmiParameterInterpolationMethod(GRIB1::Message& message);
    T::AreaInterpolationMethod  getFmiParameterInterpolationMethod(GRIB2::Message& message);

  protected:

    void                    updateGrib();
    void                    updateGrib1();
    void                    updateGrib2();
    void                    updateFmi();
    void                    updateNewbase();

    GribParamDef_cptr       getGribParamDefById(T::ParamId gribParamId);
    GribParamDef_cptr       getGribParamDefByName(std::string gribParamName);
    GribParamDef_cptr       getGribParamDef(uint discipline,uint category,uint number);

    GRIB1::GridDef_ptr      getGrib1DefinitionByGeometryId(int geometryId);
    GRIB1::GridDef_ptr      getGrib1DefinitionByHash(T::Hash hash);
    LevelDef_cptr           getGrib1LevelDef(uint levelId);
    Grib1ParamDef_cptr      getGrib1ParameterDefById(T::ParamId gribParamId);
    Grib1ParamDef_cptr      getGrib1ParameterDefByIndex(uint index);
    Grib1ParamDef_cptr      getGrib1ParameterDefByName(std::string gribParamName);
    Grib1ParamDef_cptr      getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter);
    TimeRangeDef_cptr       getGrib1TimeRangeDef(uint timeRangeId);

    GRIB2::GridDef_ptr      getGrib2DefinitionByGeometryId(int geometryId);
    GRIB2::GridDef_ptr      getGrib2DefinitionByHash(T::Hash hash);
    LevelDef_cptr           getGrib2LevelDef(uint levelId);
    Grib2ParamDef_cptr      getGrib2ParameterDefById(T::ParamId gribParamId);
    Grib2ParamDef_cptr      getGrib2ParameterDefByName(std::string gribParamName);
    TimeRangeDef_cptr       getGrib2TimeRangeDef(uint timeRangeId);

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

    GribParamDef_cptr       getGribParameterDefById(T::ParamId gribParamId);
    FmiParamDef_cptr        getFmiParameterDefById(T::ParamId fmiParamId);
    FmiParamDef_cptr        getFmiParameterDefByNewbaseId(T::ParamId nwebaseParamId);
    FmiParamDef_cptr        getFmiParameterDefByName(std::string fmiParamName);
    FmiProducerId_grib_cptr getFmiProducerByName(std::string fmiProducerName);
    NewbaseParamDef_cptr    getNewbaseParameterDefById(T::ParamId newbaseParamId);
    NewbaseParamDef_cptr    getNewbaseParameterDefByName(std::string newbaseParamName);
    FmiParamId_newbase_cptr getFmiParameterIdByNewbaseId(T::ParamId newbaseParamId);
    FmiParamId_newbase_cptr getNewbaseParameterIdByFmiId(T::ParamId fmiParamId);



    std::string             mConfigFileName;
    ConfigurationFile       mConfigurationFile;

    std::string             mConfigDirectory;

    bool                    mInitialized;
    time_t                  mLastCheckTime;
    ThreadLock              mThreadLock;

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
    GRIB1::GridDef_pvec     mGridDefinitions1;
    GRIB2::GridDef_pvec     mGridDefinitions2;

    string_vec              mNewbase_parameterDef_files;
    time_t                  mNewbase_parameterDef_modificationTime;
    NewbaseParamDef_vec     mNewbase_parameterDef_records;
};

extern GridDef gridDef;


}  // namespace Identification
}  // namespace SmartMet
