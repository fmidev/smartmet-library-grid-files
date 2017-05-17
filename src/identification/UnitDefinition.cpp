#include "UnitDefinition.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"


namespace SmartMet
{
namespace Identification
{


/*! \brief The constructor of the class. */

UnitDefinition::UnitDefinition()
{
  try
  {
    mPreferredInterpolationMethod = T::InterpolationMethod::Linear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The copy constructor of the class. */

UnitDefinition::UnitDefinition(const UnitDefinition& unitDefinition)
{
  try
  {
    mOriginalUnits = unitDefinition.mOriginalUnits;
    mPreferredUnits = unitDefinition.mPreferredUnits;
    mPreferredInterpolationMethod = unitDefinition.mPreferredInterpolationMethod;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    stream << space(level) << "- OriginalUnits                = " << mOriginalUnits << "\n";
    stream << space(level) << "- PreferredUnits               = " << mPreferredUnits << "\n";
    stream << space(level) << "- PreferredInterpolationMethod = " << toString((int)mPreferredInterpolationMethod) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}



}
}
