#include "FmiParameterId_newbase.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


FmiParameterId_newbase::FmiParameterId_newbase()
{
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*
FmiParameterId_newbase::FmiParameterId_newbase(const FmiParameterId_newbase& parameter)
{
  try
  {
    mFmiParameterId = parameter.mFmiParameterId;
    mNewbaseParameterId = parameter.mNewbaseParameterId;
    mConversionFunction = parameter.mConversionFunction;
    mReverseConversionFunction = parameter.mReverseConversionFunction;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}
*/




FmiParameterId_newbase::~FmiParameterId_newbase()
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





void FmiParameterId_newbase::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "FmiParameterId_newbase\n";
    stream << space(level) << "- mFmiParameterId             = " << mFmiParameterId << "\n";
    stream << space(level) << "- mNewbaseParameterId         = " << mNewbaseParameterId << "\n";
    stream << space(level) << "- mConversionFunction         = " << mConversionFunction << "\n";
    stream << space(level) << "- mReverseConversionFunction  = " << mReverseConversionFunction << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

