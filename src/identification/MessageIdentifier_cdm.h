#pragma once

#include "MessageIdentifier.h"
#include "Parameter_grib1_cdm.h"
#include "LevelDef.h"
#include "TimeRangeDef.h"


namespace SmartMet
{
namespace Identification
{

class MessageIdentifier_cdm : public MessageIdentifier
{
  public:
                              MessageIdentifier_cdm();
    virtual                   ~MessageIdentifier_cdm();

    T::ParamId                getParamIdByName(std::string gribParamName);

    T::ParamId                getParamId(GRIB1::Message& message);
    T::ParamLevelId           getParamLevelId(GRIB1::Message& message);
    std::string               getParamName(GRIB1::Message& message);
    std::string               getParamDescription(GRIB1::Message& message);
    std::string               getParamUnits(GRIB1::Message& message);
    T::InterpolationMethod    getParamInterpolationMethod(GRIB1::Message& message);

    T::ParamId                getParamId(GRIB2::Message& message);
    T::ParamLevelId           getParamLevelId(GRIB2::Message& message);
    std::string               getParamName(GRIB2::Message& message);
    std::string               getParamDescription(GRIB2::Message& message);
    std::string               getParamUnits(GRIB2::Message& message);
    T::InterpolationMethod    getParamInterpolationMethod(GRIB2::Message& message);
};


}
}
