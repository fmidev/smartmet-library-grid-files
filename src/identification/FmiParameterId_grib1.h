#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiParameterId_grib1
{
  public:
                    FmiParameterId_grib1();
                    //FmiParameterId_grib1(const FmiParameterId_grib1& parameter);
    virtual         ~FmiParameterId_grib1();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId      mFmiParameterId;
    uint            mFmiProducerId;
    uint            mGeneratingProcessIdentifier;
    uint            mCentre;
    uint            mGribTableVersion;
    uint            mGribParameterNumber;
    uint            mGribTimerangeIndicator;
    T::UInt32_opt   mFmiParameterLevelId;
    T::UInt32_opt   mGribParameterLevelId;
    T::UInt32_opt   mParameterLevel;
};


typedef std::vector<FmiParameterId_grib1> FmiParamId_grib1_vec;
typedef const FmiParameterId_grib1* FmiParamId_grib1_cptr;


}
}

