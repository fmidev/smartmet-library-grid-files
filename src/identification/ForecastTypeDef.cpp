#include "ForecastTypeDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


ForecastTypeDef::ForecastTypeDef()
{
  try
  {
    mForecastTypeId = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ForecastTypeDef::ForecastTypeDef(const ForecastTypeDef& forecastTypeDef)
{
  try
  {
    mForecastTypeId = forecastTypeDef.mForecastTypeId;
    mName = forecastTypeDef.mName;
    mDescription = forecastTypeDef.mDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ForecastTypeDef::~ForecastTypeDef()
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





void ForecastTypeDef::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "ForecastTypeDef\n";
    stream << space(level) << "- mForecastTypeId = " << mForecastTypeId << "\n";
    stream << space(level) << "- mName           = " << mName << "\n";
    stream << space(level) << "- mDescription    = " << mDescription << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}
}

