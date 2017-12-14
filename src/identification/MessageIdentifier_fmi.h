#pragma once

#include "MessageIdentifier.h"
#include "Parameter_grib1_fmi.h"
#include "Parameter_grib2_fmi.h"
#include "Parameter_newbase.h"
#include "ParameterDefinition_fmi.h"
#include "LevelDef_fmi.h"


namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief This class is used for finding out FMI specific parameter information
 * related to the given GRIB 1 and GRIB 2 messages. The class can return the following
 * information about the given GRIB 1 / GRIB 2 message:
 *
 *  - fmiParameterId          (Radon: param.id)
 *  - fmiParameterName        (Radon: param.name)
 *  - fmiParameterLevelId     (Radon: level.id)
 *  - fmiParameterUnits       (Radon: param_unit.name)
 *  - fmiInterpolationMethod  (Radon: interpolation_method.id)
 */
// ====================================================================================


class MessageIdentifier_fmi : public MessageIdentifier
{
  public:
                                  MessageIdentifier_fmi();
    virtual                       ~MessageIdentifier_fmi();

    void                          init(const char* configDir);

    T::ParamId                    getParamId(GRIB1::Message& message);
    T::ParamId                    getParamId(GRIB2::Message& message);
    T::ParamId                    getNewbaseParamId(GRIB1::Message& message);
    T::ParamId                    getNewbaseParamId(GRIB2::Message& message);
    T::ParamId                    getParamIdByName(std::string gribParamName);
    T::ParamLevelId               getParamLevelId(GRIB1::Message& message);
    T::ParamLevelId               getParamLevelId(GRIB2::Message& message);
    std::string                   getParamName(GRIB1::Message& message);
    std::string                   getParamName(GRIB2::Message& message);
    std::string                   getNewbaseParamName(GRIB1::Message& message);
    std::string                   getNewbaseParamName(GRIB2::Message& message);
    std::string                   getParamDescription(GRIB1::Message& message);
    std::string                   getParamDescription(GRIB2::Message& message);
    std::string                   getParamUnits(GRIB1::Message& message);
    std::string                   getParamUnits(GRIB2::Message& message);
    T::InterpolationMethod        getParamInterpolationMethod(GRIB1::Message& message);
    T::InterpolationMethod        getParamInterpolationMethod(GRIB2::Message& message);

    ParameterDefinition_fmi_cptr  getParameterDefById(T::ParamId fmiParamId);
    ParameterDefinition_fmi_cptr  getParameterDefByName(std::string fmiParamName);
    ParameterDefinition_fmi_cptr  getParameterDefByNewbaseId(T::ParamId newbaseParamId);
    ParameterDefinition_fmi_cptr  getParameterDefByNewbaseName(std::string newbaseParamName);
    Parameter_grib1_fmi_cptr      getParameter_grib1(T::ParamId fmiParamId);
    Parameter_grib2_fmi_cptr      getParameter_grib2(T::ParamId fmiParamId);
    Parameter_newbase_cptr        getParameter_newbaseId(T::ParamId newbaseParamId);
    Parameter_newbase_cptr        getParameter_newbaseName(std::string newbaseParamName);

  protected:

    virtual void                  loadParameterDefinitions();
    virtual void                  loadExtendedParameterDefinitions();
    virtual void                  loadParameterDefinitions_grib1();
    virtual void                  loadParameterDefinitions_grib2();
    virtual void                  loadParameterDefinitions_newbase();
    virtual void                  loadLevelDefinitions_grib1();
    virtual void                  loadLevelDefinitions_grib2();
    virtual uint                  countParameterMatchPoints(GRIB2::Message& message,const Parameter_grib2_fmi& p);

    std::string                   mConfigDir;
    ParameterDefinition_fmi_vec   mParameterDefs;
    Parameter_newbase_vec         mParameters_newbase;
    Parameter_grib1_fmi_vec       mParameters_grib1;
    Parameter_grib2_fmi_vec       mParameters_grib2;
    LevelDef_fmi_vec              mLevelDefs_grib1;
    LevelDef_fmi_vec              mLevelDefs_grib2;
};


}
}
