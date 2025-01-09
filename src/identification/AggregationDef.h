#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


class AggregationDef
{
  public:
                    AggregationDef();
    virtual         ~AggregationDef();

    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    int             mAggregationId;
    std::string     mName;
    std::string     mDescription;
};


typedef std::vector<AggregationDef> AggregationDef_vec;
typedef const AggregationDef* AggregationDef_cptr;


}
}

