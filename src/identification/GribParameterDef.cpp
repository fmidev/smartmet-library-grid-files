#include "GribParameterDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"


namespace SmartMet
{
namespace Identification
{


/*! \brief The constructor of the class. */

GribParameterDef::GribParameterDef()
{
  try
  {
    mDiscipline = 0;
    mParameterCategory = 0;
    mParameterNumber = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The copy constructor of the class. */

GribParameterDef::GribParameterDef(const GribParameterDef& parameterDefinition)
{
  try
  {
    mGribParameterId = parameterDefinition.mGribParameterId;
    mDiscipline = parameterDefinition.mDiscipline;
    mParameterCategory = parameterDefinition.mParameterCategory;
    mParameterNumber = parameterDefinition.mParameterNumber;
    mParameterName = parameterDefinition.mParameterName;
    mParameterDescription = parameterDefinition.mParameterDescription;
    mParameterUnits = parameterDefinition.mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The destructor of the class. */

GribParameterDef::~GribParameterDef()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GribParameterDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "GribParameterDef\n";
    stream << space(level) << "- mGribParameterId      = " << mGribParameterId << "\n";
    stream << space(level) << "- mDiscipline           = " << toString(mDiscipline) << "\n";
    stream << space(level) << "- mParameterCategory    = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- mParameterNumber      = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- mParameterName        = " << mParameterName << "\n";
    stream << space(level) << "- mParameterDescription = " << mParameterDescription << "\n";
    stream << space(level) << "- mParameterUnits       = " << mParameterUnits << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}



}
}
