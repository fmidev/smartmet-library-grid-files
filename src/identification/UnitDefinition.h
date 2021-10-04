#pragma once

#include "../grid/Typedefs.h"


namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*!
  \brief This class contains common unit definitions that are read from
  the 'units.csv' file. Notice that the same units can be written in several ways
  (for example, "m/s" is the same as "ms-1".

  If we want to write the same unit always in the same way, then we should define
  the preferred unit mappings (for example, "ms-1" => "m/s" and "m/s" => "m/s").

  Notice also that the unit definitions are also used for finding a preferred
  interpolation method for the data. I.e if the user does not define the interpolation
  method by itself then it usually detected from the unit definitions.
*/
// ====================================================================================

class UnitDefinition
{
  public:
                  UnitDefinition();
    virtual       ~UnitDefinition();

    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;

    std::string   mOriginalUnits;
    std::string   mPreferredUnits;
    short         mPreferredAreaInterpolationMethod;
    short         mPreferredTimeInterpolationMethod;
    short         mPreferredLevelInterpolationMethod;
};

typedef std::vector<UnitDefinition> UnitDefinition_vec;

}
}

