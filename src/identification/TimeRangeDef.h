#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class TimeRangeDef
{
  public:
                    TimeRangeDef();
                    TimeRangeDef(const TimeRangeDef& timeRangeDef);
    virtual         ~TimeRangeDef();

    void            print(std::ostream& stream,uint timeRange,uint optionFlags) const;

    uint            mTimeRangeId;
    std::string     mName;
    std::string     mDescription;
};


typedef std::vector<TimeRangeDef> TimeRangeDef_vec;
typedef const TimeRangeDef*       TimeRangeDef_cptr;


}
}

