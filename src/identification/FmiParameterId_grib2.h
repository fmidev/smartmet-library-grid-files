#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class FmiParameterId_grib2
{
  public:
                    FmiParameterId_grib2();
    virtual         ~FmiParameterId_grib2();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId   mFmiParameterId;
    uint            mFmiProducerId;
    uint            mGeneratingProcessIdentifier;
    uint            mCentre;
    uint            mDiscipline;
    uint            mParameterCategory;
    uint            mParameterNumber;
    T::UInt32_opt   mFmiParameterLevelId;
    T::UInt32_opt   mGribParameterLevelId;
    T::UInt32_opt   mParameterLevel;
};


using FmiParamId_grib2_vec = std::vector<FmiParameterId_grib2>;
using FmiParamId_grib2_cptr = const FmiParameterId_grib2 *;


}
}

