#if 0
#include "CdmParameterDef.h"
#include <macgyver/Exception.h>
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}
*/




CdmParameterDef::~CdmParameterDef()
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}


#endif
