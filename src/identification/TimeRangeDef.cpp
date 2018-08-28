#include "TimeRangeDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace Identification
{


TimeRangeDef::TimeRangeDef()
{
  try
  {
    mTimeRangeId = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





TimeRangeDef::TimeRangeDef(const TimeRangeDef& timeRangeDef)
{
  try
  {
    mTimeRangeId = timeRangeDef.mTimeRangeId;
    mName = timeRangeDef.mName;
    mDescription = timeRangeDef.mDescription;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





TimeRangeDef::~TimeRangeDef()
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





void TimeRangeDef::print(std::ostream& stream,uint timeRange,uint optionFlags) const
{
  try
  {
    stream << space(timeRange) << "TimeRangeDef\n";
    stream << space(timeRange) << "- mTimeRangeId = " << mTimeRangeId << "\n";
    stream << space(timeRange) << "- mName        = " << mName << "\n";
    stream << space(timeRange) << "- mDescription = " << mDescription << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}
}

