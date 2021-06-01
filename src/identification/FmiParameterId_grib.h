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
    virtual         ~FmiParameterId_grib();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId   mFmiParameterId;
    T::GribParamId  mGribParameterId;
    std::string     mConversionFunction;
    std::string     mReverseConversionFunction;
};


typedef std::vector<FmiParameterId_grib> FmiParamId_grib_vec;
typedef const FmiParameterId_grib* FmiParamId_grib_cptr;


}
}

