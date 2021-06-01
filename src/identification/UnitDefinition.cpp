#include "UnitDefinition.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"


namespace SmartMet
{
namespace Identification
{


/*! \brief The constructor of the class. */

UnitDefinition::UnitDefinition()
{
  try
  {
    mPreferredAreaInterpolationMethod = T::AreaInterpolationMethod::Undefined;
    mPreferredTimeInterpolationMethod = T::TimeInterpolationMethod::Undefined;
    mPreferredLevelInterpolationMethod = T::LevelInterpolationMethod::Undefined;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

UnitDefinition::~UnitDefinition()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void UnitDefinition::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "UnitDefinition\n";
    stream << space(level) << "- OriginalUnits                     = " << mOriginalUnits << "\n";
    stream << space(level) << "- PreferredUnits                    = " << mPreferredUnits << "\n";
    stream << space(level) << "- PreferredAreaInterpolationMethod  = " << toString(mPreferredAreaInterpolationMethod) << "\n";
    stream << space(level) << "- PreferredTimeInterpolationMethod  = " << toString(mPreferredTimeInterpolationMethod) << "\n";
    stream << space(level) << "- PreferredLevelInterpolationMethod = " << toString(mPreferredLevelInterpolationMethod) << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}
}
