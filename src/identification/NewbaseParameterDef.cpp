#include "NewbaseParameterDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


NewbaseParameterDef::NewbaseParameterDef()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





NewbaseParameterDef::NewbaseParameterDef(const NewbaseParameterDef& parameter)
{
  try
  {
    mNewbaseParameterId = parameter.mNewbaseParameterId;
    mParameterName = parameter.mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




NewbaseParameterDef::~NewbaseParameterDef()
{
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}




/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void NewbaseParameterDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "ParameterDefinition_newbase\n";
    stream << space(level) << "- mNewbaseParameterId     = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- mParameterName          = " << mParameterName << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace Identification
}  // namespace SmartMet
