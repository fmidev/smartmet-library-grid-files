#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

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

using FmiParamDef_vec = std::vector<FmiParameterDef>;
using FmiParamDef_umap = std::unordered_map<uint, FmiParameterDef>;
using FmiParamDef_cptr = const FmiParameterDef *;

}
}

