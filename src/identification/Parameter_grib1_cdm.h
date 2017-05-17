#pragma once

#include "grid/Typedefs.h"


namespace SmartMet
{
namespace Identification
{


class Parameter_grib1_cdm
{
  public:
                    Parameter_grib1_cdm();
                    Parameter_grib1_cdm(const Parameter_grib1_cdm& parameter);
    virtual         ~Parameter_grib1_cdm();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mParameterNumber;
    std::string     mParameterName;
    std::string     mParameterDescription;
    std::string     mParameterUnits;
};


typedef std::vector<Parameter_grib1_cdm> Parameter_grib1_cdm_vec;
typedef const Parameter_grib1_cdm* Parameter_grib1_cdm_cptr;


}
}

