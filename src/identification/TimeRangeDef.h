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
    virtual         ~TimeRangeDef();

    void            print(std::ostream& stream,uint timeRange,uint optionFlags) const;

    uint            mTimeRangeId;
    std::string     mName;
    std::string     mDescription;
};


using TimeRangeDef_vec = std::vector<TimeRangeDef>;
using TimeRangeDef_cptr = const TimeRangeDef *;


}
}

