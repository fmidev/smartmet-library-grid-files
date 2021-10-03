#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


class FmiParameterId_grib
{
  public:
                    FmiParameterId_grib();
    virtual         ~FmiParameterId_grib();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId   mFmiParameterId;
    T::GribParamId  mGribParameterId;
    std::string     mConversionFunction;
    std::string     mReverseConversionFunction;
};


using FmiParamId_grib_vec = std::vector<FmiParameterId_grib>;
using FmiParamId_grib_umap = std::unordered_map<uint, FmiParameterId_grib>;
using FmiParamId_grib_cptr = const FmiParameterId_grib *;


}
}

