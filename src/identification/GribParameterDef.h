#pragma once

#include "../grid/Typedefs.h"


namespace SmartMet
{
namespace Identification
{

// ====================================================================================
/*!
  \brief This class contains common parameter definitions that are read from
  the 'paramDef.csv' file. These parameter definitions should be common for both
  GRIB1 and GRIB2.
*/
// ====================================================================================

class GribParameterDef
{
  public:
                    GribParameterDef();
    virtual         ~GribParameterDef();

    virtual void    print(std::ostream& stream,uint level,uint optionFlags) const;

    T::GribParamId  mGribParameterId;
    std::string     mParameterName;
    std::string     mParameterDescription;
    std::string     mParameterUnits;
};

typedef std::vector<GribParameterDef> GribParamDef_vec;
typedef const GribParameterDef* GribParamDef_cptr;

}
}

