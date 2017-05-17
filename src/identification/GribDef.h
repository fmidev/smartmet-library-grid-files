#pragma once

#include "grid/Typedefs.h"
#include "ParameterDefinition.h"
#include "TableValue.h"
#include "UnitDefinition.h"
#include "MessageIdentifier_cdm.h"
#include "MessageIdentifier_fmi.h"
#include "MessageIdentifier_grib1.h"
#include "MessageIdentifier_grib2.h"
#include "LevelDef.h"
#include "TimeRangeDef.h"



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
    virtual                   ~GribDef();

    void                      init(const char* configDir);

    std::string               getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,std::uint32_t number);
    std::string               getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt8_opt number);
    std::string               getTableValue(std::uint8_t gribVersion,std::uint8_t tableVersion,std::string table,T::UInt16_opt number);
    std::string               getPreferredUnits(std::string originalUnits);
    T::InterpolationMethod    getPreferredInterpolationMethodByUnits(std::string originalUnits);

    Parameter_grib1_cptr      getParameterDefById_grib1(T::ParamId gripParamId);
    Parameter_grib1_cptr      getParameterDefByName_grib1(std::string gripParamName);
    Parameter_grib1_cptr      getParameterDef_grib1(uint tableVersion,uint indicatorOfParameter);

    Parameter_grib2_cptr      getParameterDefById_grib2(T::ParamId gripParamId);
    Parameter_grib2_cptr      getParameterDefByName_grib2(std::string gripParamName);

    LevelDef_cptr             getLevelDef_grib1(uint levelId);
    LevelDef_cptr             getLevelDef_grib2(uint levelId);

    TimeRangeDef_cptr         getTimeRangeDef_grib1(uint timeRangeId);
    TimeRangeDef_cptr         getTimeRangeDef_grib2(uint timeRangeId);

    ParameterDefinition_cptr  getGribParamDefById(T::ParamId gribParamId);
    ParameterDefinition_cptr  getGribParamDefByName(std::string gribParamName);
    ParameterDefinition_cptr  getGribParamDef(uint discipline,uint category,uint number);

    MessageIdentifier_cdm     mMessageIdentifier_cdm;
    MessageIdentifier_fmi     mMessageIdentifier_fmi;
    MessageIdentifier_grib1   mMessageIdentifier_grib1;
    MessageIdentifier_grib2   mMessageIdentifier_grib2;

    std::string               mConfigDir;
    TableValue_vec            mTableValues;
    ParameterDefinition_vec   mParameterDefs;
    UnitDefinition_vec        mUnitDefs;
    LevelDef_vec              mLevelDefs_grib1;
    LevelDef_vec              mLevelDefs_grib2;
    TimeRangeDef_vec          mTimeRangeDefs_grib1;
    TimeRangeDef_vec          mTimeRangeDefs_grib2;
    Parameter_grib1_vec       mParameters_grib1;
    Parameter_grib2_vec       mParameters_grib2;

  protected:

    void                      loadTableValues();
    void                      loadParameterDefinitions();
    void                      loadParameterDefinitions_grib1();
    void                      loadParameterDefinitions_grib2();
    void                      loadLevelDefinitions_grib1();
    void                      loadLevelDefinitions_grib2();
    void                      loadTimeRangeDefinitions_grib1();
    void                      loadTimeRangeDefinitions_grib2();
    void                      loadUnitDefinitions();

    bool                      mInitialized;

};

extern GribDef gribDef;


}  // namespace Identification
}  // namespace SmartMet
