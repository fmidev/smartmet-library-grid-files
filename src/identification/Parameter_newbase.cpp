#include "Parameter_newbase.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


Parameter_newbase::Parameter_newbase()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





Parameter_newbase::Parameter_newbase(const Parameter_newbase& parameter)
{
  try
  {
    mNewbaseParameterId = parameter.mNewbaseParameterId;
    mParameterName = parameter.mParameterName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




Parameter_newbase::~Parameter_newbase()
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

void Parameter_newbase::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "ParameterDefinition_newbase\n";
    stream << space(level) << "- mNewbaseParameterId     = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- mParameterName          = " << mParameterName << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace Identification
}  // namespace SmartMet
