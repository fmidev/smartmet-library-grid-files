#pragma once

#include "MessageIdentifier.h"
#include "Parameter_grib1_fmi.h"
#include "Parameter_grib2_fmi.h"
#include "Parameter_newbase.h"
#include "ParameterDefinition_fmi.h"
#include "LevelDef_fmi.h"
#include "ProducerDef_fmi.h"
#include "common/AutoThreadLock.h"


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
    virtual                 ~MessageIdentifier_fmi();

    void                    init(const char* configDir);

    T::ParamId              getParamIdByName(std::string gribParamName);

    T::ParamId              getParamId(GRIB1::Message& message);
    T::ParamLevelId         getParamLevelId(GRIB1::Message& message);
    std::string             getParamName(GRIB1::Message& message);
    T::ParamId              getNewbaseParamId(GRIB1::Message& message);
    std::string             getNewbaseParamName(GRIB1::Message& message);
    std::string             getParamDescription(GRIB1::Message& message);
    std::string             getParamUnits(GRIB1::Message& message);
    T::InterpolationMethod  getParamInterpolationMethod(GRIB1::Message& message);
    std::string             getProducerName(GRIB1::Message& message);

    T::ParamId              getParamId(GRIB2::Message& message);
    T::ParamLevelId         getParamLevelId(GRIB2::Message& message);
    std::string             getParamName(GRIB2::Message& message);
    T::ParamId              getNewbaseParamId(GRIB2::Message& message);
    std::string             getNewbaseParamName(GRIB2::Message& message);
    std::string             getParamDescription(GRIB2::Message& message);
    std::string             getParamUnits(GRIB2::Message& message);
    T::InterpolationMethod  getParamInterpolationMethod(GRIB2::Message& message);
    std::string             getProducerName(GRIB2::Message& message);

    bool                    getParameterDefById(T::ParamId fmiParamId,ParameterDefinition_fmi& paramDef);
    bool                    getParameterDefByName(std::string fmiParamName,ParameterDefinition_fmi& paramDef);
    bool                    getParameterDefByNewbaseId(T::ParamId newbaseParamId,ParameterDefinition_fmi& paramDef);
    bool                    getParameterDefByNewbaseName(std::string newbaseParamName,ParameterDefinition_fmi& paramDef);
    bool                    getParameter_grib1(T::ParamId fmiParamId,Parameter_grib1_fmi& param);
    bool                    getParameter_grib2(T::ParamId fmiParamId,Parameter_grib2_fmi& param);
    bool                    getParameter_newbaseId(T::ParamId newbaseParamId,Parameter_newbase& param);
    bool                    getParameter_newbaseName(std::string newbaseParamName,Parameter_newbase& param);
    bool                    getProducer(uint centre,uint ident,uint type,ProducerDef_fmi& producer);

  protected:

    void                    updateCheck();

    ParamDef_fmi_cptr       getParameterDefById(T::ParamId fmiParamId);
    ParamDef_fmi_cptr       getParameterDefByName(std::string fmiParamName);
    ParamDef_fmi_cptr       getParameterDefByNewbaseId(T::ParamId newbaseParamId);
    ParamDef_fmi_cptr       getParameterDefByNewbaseName(std::string newbaseParamName);
    Param_grib1_fmi_cptr    getParameter_grib1(T::ParamId fmiParamId);
    Param_grib2_fmi_cptr    getParameter_grib2(T::ParamId fmiParamId);
    Param_newbase_cptr      getParameter_newbaseId(T::ParamId newbaseParamId);
    Param_newbase_cptr      getParameter_newbaseName(std::string newbaseParamName);
    ProducerDef_fmi_cptr    getProducer(uint centre,uint ident,uint type);

    void                    loadParameterDefinitions(const char *filename);
    void                    loadGrib1ParameterDefinitions(const char *filename);
    void                    loadGrib2ParameterDefinitions(const char *filename);
    void                    loadParameterDefinitions_newbase(const char *filename);
    void                    loadGrib1LevelDefinitions(const char *filename);
    void                    loadGrib2LevelDefinitions(const char *filename);
    void                    loadProducerDefinitions(const char *filename);
    uint                    countParameterMatchPoints(GRIB2::Message& message,const Parameter_grib2_fmi& p);

    std::string             mConfigDir;
    ParamDef_fmi_vec        mParameterDefs;
    Param_newbase_vec       mParameters_newbase;
    Param_grib1_fmi_vec     mParameters_grib1;
    Param_grib2_fmi_vec     mParameters_grib2;
    LevelDef_fmi_vec        mLevelDefs_grib1;
    LevelDef_fmi_vec        mLevelDefs_grib2;
    ProducerDef_fmi_vec     mProducerDefs;
    time_t                  mLastCheckTime;
    time_t                  mParameterDefs_modificationTime;
    time_t                  mParameterDefsExt_modificationTime;
    time_t                  mParameters_newbase_modificationTime;
    time_t                  mParameters_grib1_modificationTime;
    time_t                  mParameters_grib2_modificationTime;
    time_t                  mLevelDefs_grib1_modificationTime;
    time_t                  mLevelDefs_grib2_modificationTime;
    time_t                  mProducerDefs_modificationTime;
    ThreadLock              mThreadLock;
    bool                    mInitialized;
};


}
}
