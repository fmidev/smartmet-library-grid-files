#include "TimeRangeDef.h"
#include <macgyver/Exception.h>
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




TimeRangeDef::~TimeRangeDef()
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}
}

