#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class Grib1ParameterDef
{
  public:

                    Grib1ParameterDef();
    virtual         ~Grib1ParameterDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::GribParamId  mGribParameterId;
    uint            mTable2Version;
    uint            mCentre;
    uint            mIndicatorOfParameter;
    uint            mIndicatorOfTypeOfLevel;
    uint            mParameterLevel;
    std::string     mParameterUnits;
    std::string     mParameterName;
    std::string     mParameterDescription;
};

using Grib1ParamDef_cptr = const Grib1ParameterDef *;
using Grib1ParamDef_vec = std::vector<Grib1ParameterDef>;


}
}

