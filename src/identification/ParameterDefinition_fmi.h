#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class ParameterDefinition_fmi
{
  public:
                            ParameterDefinition_fmi();
                            ParameterDefinition_fmi(const ParameterDefinition_fmi& parameterDef);
    virtual                 ~ParameterDefinition_fmi();

    void                    print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId              mFmiParameterId;
    uint                    mVersion;
    std::string             mParameterName;
    std::string             mParameterUnits;
    std::string             mParameterDescription;
    T::InterpolationMethod  mInterpolationMethod;
    T::ParamId              mNewbaseId;
};

typedef std::vector<ParameterDefinition_fmi> ParameterDefinition_fmi_vec;
typedef const ParameterDefinition_fmi* ParameterDefinition_fmi_cptr;

}
}

