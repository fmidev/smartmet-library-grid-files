#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class Parameter_grib2_fmi
{
  public:
                    Parameter_grib2_fmi();
                    Parameter_grib2_fmi(const Parameter_grib2_fmi& parameter);
    virtual         ~Parameter_grib2_fmi();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mDbId;
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


typedef std::vector<Parameter_grib2_fmi> Param_grib2_fmi_vec;
typedef const Parameter_grib2_fmi* Param_grib2_fmi_cptr;


}
}

