#pragma once

#include "grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class Parameter_grib1
{
  public:

                  Parameter_grib1();
                  Parameter_grib1(const Parameter_grib1& parameter);
    virtual       ~Parameter_grib1();

    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId    mGribParameterId;
    uint          mTable2Version;
    uint          mCentre;
    uint          mIndicatorOfParameter;
    uint          mIndicatorOfTypeOfLevel;
    uint          mParameterLevel;
    std::string   mParameterUnits;
    std::string   mParameterName;
    std::string   mParameterDescription;
};

typedef const Parameter_grib1* Parameter_grib1_cptr;
typedef std::vector<Parameter_grib1> Parameter_grib1_vec;


}
}

