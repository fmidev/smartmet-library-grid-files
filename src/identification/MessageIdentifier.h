#pragma once

#include "grib1/Message.h"
#include "grib2/Message.h"


namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief This is the parent class of the all message identifiers. The main purpose
 * of a message identifier is to return the identification information from the
 * identifiers point of view.
 *
 * For example, if  we are requesting a message's parameterId from MessageIdentifier_grib1
 * or MessageIdentifier_grib2 we will get a GRIB-specific parameterId. If we are requesting
 * the parameterId for the same message from the MessageIdentifier_fmi then we will
 * the parameterId used by the fmi (radon).
 *
 * The point is that different systems use different parameter identifiers about the same
 * GRIB messages. That's why we need different message identifiers that can tell us
 * which parameter identifiers are used in the current systems. This allows us to identify
 * GRIB messages as many ways as we want.
*/
// ====================================================================================

class MessageIdentifier
{
  public:
                                    MessageIdentifier();
    virtual                         ~MessageIdentifier();

    virtual T::ParamId              getParamId(GRIB1::Message& message);
    virtual T::ParamId              getParamId(GRIB2::Message& message);
    virtual T::ParamId              getParamIdByName(std::string paramName);
    virtual T::ParamLevelId         getParamLevelId(GRIB1::Message& message);
    virtual T::ParamLevelId         getParamLevelId(GRIB2::Message& message);
    virtual std::string             getParamName(GRIB1::Message& message);
    virtual std::string             getParamName(GRIB2::Message& message);
    virtual std::string             getParamDescription(GRIB1::Message& message);
    virtual std::string             getParamDescription(GRIB2::Message& message);
    virtual std::string             getParamUnits(GRIB1::Message& message);
    virtual std::string             getParamUnits(GRIB2::Message& message);
    virtual T::InterpolationMethod  getParamInterpolationMethod(GRIB1::Message& message);
    virtual T::InterpolationMethod  getParamInterpolationMethod(GRIB2::Message& message);
};


}
}
