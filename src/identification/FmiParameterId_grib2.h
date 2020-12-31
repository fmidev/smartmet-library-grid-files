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
                    //FmiParameterId_grib2(const FmiParameterId_grib2& parameter);
    virtual         ~FmiParameterId_grib2();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId      mFmiParameterId;
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


typedef std::vector<FmiParameterId_grib2> FmiParamId_grib2_vec;
typedef const FmiParameterId_grib2* FmiParamId_grib2_cptr;


}
}

