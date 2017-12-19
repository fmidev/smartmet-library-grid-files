#pragma once

#include "ParameterDefinition.h"
#include "TableValue.h"
#include "UnitDefinition.h"
#include "MessageIdentifier_cdm.h"
#include "MessageIdentifier_fmi.h"
#include "MessageIdentifier_grib1.h"
#include "MessageIdentifier_grib2.h"
#include "LevelDef.h"
#include "TimeRangeDef.h"
#include "common/AutoThreadLock.h"
#include "grid/Typedefs.h"
#include "grib2/GridDefinition.h"
#include <set>



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

    The GribDef class is used in order to access information in these attributeList files.
    In practice there is one global instance of this class (SmartMet::GRIB:def), which should
    be initialized in the main program. After that all GRIB definition related information can
    be fetched from this instance.
*/

class GribDef
{
  public:
                  GribDef();
    virtual       ~GribDef();

    void          init(const char* configDir);

    std::string   getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,std::uint32_t number);
    std::string   getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt8_opt number);
    std::string   getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt16_opt number);
    std::string   getPreferredUnits(std::string originalUnits);

    bool          getGribParamDefById(T::ParamId gribParamId,ParameterDefinition&  paramDef);
    bool          getGribParamDefByName(std::string gribParamName,ParameterDefinition&  paramDef);
    bool          getGribParamDef(uint discipline,uint category,uint number,ParameterDefinition&  paramDef);
    bool          getGridLatLonCoordinatesByGeometryId(T::GeometryId  geometryId,T::Coordinate_vec& coordinates);
    bool          getGridDimensionsByGeometryId(T::GeometryId  geometryId,uint& cols,uint& rows);

    int           getGrib1GeometryIdByHash(T::Hash hash);
    bool          getGrib1LevelDef(uint levelId,LevelDef& levelDef);
    uint          getGrib1ParameterDefCount();
    bool          getGrib1ParameterDefById(T::ParamId gribParamId,Parameter_grib1& paramDef);
    bool          getGrib1ParameterDefByIndex(uint index,Parameter_grib1& paramDef);
    bool          getGrib1ParameterDefByName(std::string gribParamName,Parameter_grib1& paramDef);
    bool          getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter,Parameter_grib1& paramDef);
    bool          getGrib1TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef);

    int           getGrib2GeometryIdByHash(T::Hash hash);
    bool          getGrib2LevelDef(uint levelId,LevelDef& levelDef);
    uint          getGrib2ParameterDefCount();
    bool          getGrib2ParameterDefById(T::ParamId gribParamId,Parameter_grib2& paramDef);
    bool          getGrib2ParameterDefByIndex(uint index,Parameter_grib2& paramDef);
    bool          getGrib2ParameterDefByName(std::string gribParamName,Parameter_grib2& paramDef);
    bool          getGrib2TimeRangeDef(uint timeRangeId,TimeRangeDef& timeRangeDef);

    void          getGeometryIdListByLatLon(double lat,double lon,std::set<T::GeometryId>& geometryIdList);
    bool          getGeometryNameById(T::GeometryId  geometryId,std::string& name);

    T::InterpolationMethod  getPreferredInterpolationMethodByUnits(std::string originalUnits);

  public:

    MessageIdentifier_cdm   mMessageIdentifier_cdm;
    MessageIdentifier_fmi   mMessageIdentifier_fmi;
    MessageIdentifier_grib1 mMessageIdentifier_grib1;
    MessageIdentifier_grib2 mMessageIdentifier_grib2;

  protected:

    ParamDef_cptr           getGribParamDefById(T::ParamId gribParamId);
    ParamDef_cptr           getGribParamDefByName(std::string gribParamName);
    ParamDef_cptr           getGribParamDef(uint discipline,uint category,uint number);

    GRIB1::GridDef_ptr      getGrib1DefinitionByGeometryId(int geometryId);
    GRIB1::GridDef_ptr      getGrib1DefinitionByHash(T::Hash hash);
    LevelDef_cptr           getGrib1LevelDef(uint levelId);
    Parameter_grib1_cptr    getGrib1ParameterDefById(T::ParamId gribParamId);
    Parameter_grib1_cptr    getGrib1ParameterDefByIndex(uint index);
    Parameter_grib1_cptr    getGrib1ParameterDefByName(std::string gribParamName);
    Parameter_grib1_cptr    getGrib1ParameterDefByTable(uint tableVersion,uint indicatorOfParameter);
    TimeRangeDef_cptr       getGrib1TimeRangeDef(uint timeRangeId);

    GRIB2::GridDef_ptr      getGrib2DefinitionByGeometryId(int geometryId);
    GRIB2::GridDef_ptr      getGrib2DefinitionByHash(T::Hash hash);
    LevelDef_cptr           getGrib2LevelDef(uint levelId);
    Parameter_grib2_cptr    getGrib2ParameterDefById(T::ParamId gribParamId);
    Parameter_grib2_cptr    getGrib2ParameterDefByName(std::string gribParamName);
    TimeRangeDef_cptr       getGrib2TimeRangeDef(uint timeRangeId);

    void                    loadGeometryDefinitions(const char *filename);
    void                    loadParameterDefinitions(const char *filename);
    void                    loadTableValues(const char *filename);
    void                    loadUnitDefinitions(const char *filename);

    void                    loadGrib1LevelDefinitions(const char *filename);
    void                    loadGrib1ParameterDefinitions(const char *filename);
    void                    loadGrib1TimeRangeDefinitions(const char *filename);

    void                    loadGrib2ParameterDefinitions(const char *filename);
    void                    loadGrib2LevelDefinitions(const char *filename);
    void                    loadGrib2TimeRangeDefinitions(const char *filename);

    void                    updateCheck();

    std::string             mConfigDir;
    TableValue_vec          mTableValues;
    ParamDef_vec            mParameterDefs;
    UnitDefinition_vec      mUnitDefs;
    LevelDef_vec            mLevelDefs_grib1;
    LevelDef_vec            mLevelDefs_grib2;
    TimeRangeDef_vec        mTimeRangeDefs_grib1;
    TimeRangeDef_vec        mTimeRangeDefs_grib2;
    Parameter_grib1_vec     mParameters_grib1;
    Parameter_grib2_vec     mParameters_grib2;
    GRIB1::GridDef_pvec     mGridDefinitions1;
    GRIB2::GridDef_pvec     mGridDefinitions2;
    time_t                  mTableValues_modificationTime;
    time_t                  mParameterDefs_modificationTime;
    time_t                  mUnitDefs_modificationTime;
    time_t                  mLevelDefs_grib1_modificationTime;
    time_t                  mLevelDefs_grib2_modificationTime;
    time_t                  mTimeRangeDefs_grib1_modificationTime;
    time_t                  mTimeRangeDefs_grib2_modificationTime;
    time_t                  mParameters_grib1_modificationTime;
    time_t                  mParameters_grib2_modificationTime;
    time_t                  mGridDefinitions_modificationTime;
    time_t                  mGridDefinitionsExt_modificationTime;
    bool                    mInitialized;
    time_t                  mLastCheckTime;
    ThreadLock              mThreadLock;

};

extern GribDef gribDef;


}  // namespace Identification
}  // namespace SmartMet
