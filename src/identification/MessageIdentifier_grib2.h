#pragma once

#include "MessageIdentifier.h"
#include "Parameter_grib2.h"


namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief This class is used for finding out GRIB 2 specific parameter information
 * related to the given GRIB 1 and GRIB 2 messages. The class can return the following
 * information about the given GRIB 1 / GRIB 2 message:
 *
 *  - gribParameterId
 *  - gribParameterName
 *  - grib2ParameterLevelId
 *  - parameterUnits
 *  - interpolationMethod (based on unit definitions)
 */
// ====================================================================================

class MessageIdentifier_grib2 : public MessageIdentifier
{
  public:
                            MessageIdentifier_grib2();
    virtual                 ~MessageIdentifier_grib2();

    T::ParamId              getParamIdByName(std::string gribParamName);

    T::ParamId              getParamId(GRIB1::Message& message);
    T::ParamLevelId         getParamLevelId(GRIB1::Message& message);
    std::string             getParamName(GRIB1::Message& message);
    std::string             getParamDescription(GRIB1::Message& message);
    std::string             getParamUnits(GRIB1::Message& message);
    T::InterpolationMethod  getParamInterpolationMethod(GRIB1::Message& message);

    T::ParamId              getParamId(GRIB2::Message& message);
    T::ParamLevelId         getParamLevelId(GRIB2::Message& message);
    std::string             getParamName(GRIB2::Message& message);
    std::string             getParamDescription(GRIB2::Message& message);
    std::string             getParamUnits(GRIB2::Message& message);
    T::InterpolationMethod  getParamInterpolationMethod(GRIB2::Message& message);

  protected:

    virtual uint            countParameterMatchPoints(GRIB2::Message& message,const Parameter_grib2& p);
};


}
}
