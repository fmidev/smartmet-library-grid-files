#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class Parameter_grib1_fmi
{
  public:
                    Parameter_grib1_fmi();
                    Parameter_grib1_fmi(const Parameter_grib1_fmi& parameter);
    virtual         ~Parameter_grib1_fmi();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mDbId;
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


typedef std::vector<Parameter_grib1_fmi> Parameter_grib1_fmi_vec;
typedef const Parameter_grib1_fmi* Parameter_grib1_fmi_cptr;


}
}

