#pragma once

#include "grid/Typedefs.h"


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

class ParameterDefinition
{
  public:
                  ParameterDefinition();
                  ParameterDefinition(const ParameterDefinition& parameterDefinition);
    virtual       ~ParameterDefinition();

    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId    mGribParameterId;
    uint          mDiscipline;
    uint          mParameterCategory;
    uint          mParameterNumber;
    std::string   mParameterName;
    std::string   mParameterDescription;
    std::string   mParameterUnits;
};

typedef std::vector<ParameterDefinition> ParameterDefinition_vec;
typedef const ParameterDefinition* ParameterDefinition_cptr;

}
}
