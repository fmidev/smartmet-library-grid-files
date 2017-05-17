#include "TimeRangeDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"


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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





TimeRangeDef::~TimeRangeDef()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}

}
}

