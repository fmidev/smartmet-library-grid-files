#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiParameterId_grib
{
  public:
                    FmiParameterId_grib();
                    FmiParameterId_grib(const FmiParameterId_grib& parameter);
    virtual         ~FmiParameterId_grib();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId      mFmiParameterId;
    T::ParamId      mGribParameterId;
    std::string     mConversionFunction;
    std::string     mReverseConversionFunction;
};


typedef std::vector<FmiParameterId_grib> FmiParamId_grib_vec;
typedef const FmiParameterId_grib* FmiParamId_grib_cptr;


}
}

