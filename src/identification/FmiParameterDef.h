#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiParameterDef
{
  public:
                  FmiParameterDef();
    virtual       ~FmiParameterDef();

    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId mFmiParameterId;
    uint          mVersion;
    std::string   mParameterName;
    std::string   mParameterUnits;
    std::string   mParameterDescription;
    short         mAreaInterpolationMethod;
    short         mTimeInterpolationMethod;
    short         mLevelInterpolationMethod;
    short         mDefaultPrecision;
};

typedef std::vector<FmiParameterDef> FmiParamDef_vec;
typedef const FmiParameterDef* FmiParamDef_cptr;

}
}

