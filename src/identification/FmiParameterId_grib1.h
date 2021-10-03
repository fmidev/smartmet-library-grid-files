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
    virtual         ~FmiParameterId_grib1();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId   mFmiParameterId;
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


using FmiParamId_grib1_vec = std::vector<FmiParameterId_grib1>;
using FmiParamId_grib1_cptr = const FmiParameterId_grib1 *;


}
}

