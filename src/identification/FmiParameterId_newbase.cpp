#include "FmiParameterId_newbase.h"
#include "../common/Exception.h"
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





FmiParameterId_newbase::~FmiParameterId_newbase()
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}
}

