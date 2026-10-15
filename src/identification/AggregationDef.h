#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief Aggregation type definition record loaded from the aggregation definitions CSV.
 *
 *  Describes a temporal or spatial aggregation method (e.g. mean, max, sum) with a
 *  numeric identifier, a short name, and a human-readable description. */
// ====================================================================================

class AggregationDef
{
  public:
                    AggregationDef();
    virtual         ~AggregationDef();
    AggregationDef(const AggregationDef&) = default;
    AggregationDef& operator=(const AggregationDef&) = default;

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    int             mAggregationId;   //!< Numeric aggregation type identifier
    std::string     mName;            //!< Short name (e.g. "mean", "max")
    std::string     mDescription;     //!< Human-readable description
};


using AggregationDef_vec = std::vector<AggregationDef>;   //!< Ordered list of aggregation definitions
using AggregationDef_cptr = const AggregationDef*;        //!< Non-owning const pointer


}
}
