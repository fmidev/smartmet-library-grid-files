#include "ProcessingTypeDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


ProcessingTypeDef::ProcessingTypeDef()
{
  try
  {
    mProcessingTypeId = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




ProcessingTypeDef::~ProcessingTypeDef()
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





void ProcessingTypeDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "ProcessingTypeDef\n";
    stream << space(level) << "- mProcessingTypeId = " << mProcessingTypeId << "\n";
    stream << space(level) << "- mName             = " << mName << "\n";
    stream << space(level) << "- mDescription      = " << mDescription << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

