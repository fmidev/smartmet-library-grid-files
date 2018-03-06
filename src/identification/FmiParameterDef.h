#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiParameterDef
{
  public:
                                FmiParameterDef();
                                FmiParameterDef(const FmiParameterDef& parameterDef);
    virtual                     ~FmiParameterDef();

    void                        print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId                  mFmiParameterId;
    uint                        mVersion;
    std::string                 mParameterName;
    std::string                 mParameterUnits;
    std::string                 mParameterDescription;
    T::AreaInterpolationMethod  mAreaInterpolationMethod;
    T::TimeInterpolationMethod  mTimeInterpolationMethod;
    T::LevelInterpolationMethod mLevelInterpolationMethod;
};

typedef std::vector<FmiParameterDef> FmiParamDef_vec;
typedef const FmiParameterDef* FmiParamDef_cptr;

}
}

