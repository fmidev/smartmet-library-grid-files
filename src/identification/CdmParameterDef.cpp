#include "CdmParameterDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


CdmParameterDef::CdmParameterDef()
{
  try
  {
    mParameterNumber = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





CdmParameterDef::CdmParameterDef(const CdmParameterDef& parameter)
{
  try
  {
    mParameterNumber = parameter.mParameterNumber;
    mParameterName = parameter.mParameterName;
    mParameterDescription = parameter.mParameterDescription;
    mParameterUnits = parameter.mParameterUnits;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





CdmParameterDef::~CdmParameterDef()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void CdmParameterDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "CdmParameterDef\n";
    stream << space(level) << "- mParameterNumber      = " << mParameterNumber << "\n";
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


