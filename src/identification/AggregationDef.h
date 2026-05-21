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

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    int             mAggregationId;   //!< Numeric aggregation type identifier
    std::string     mName;            //!< Short name (e.g. "mean", "max")
    std::string     mDescription;     //!< Human-readable description
};


typedef std::vector<AggregationDef> AggregationDef_vec;   //!< Ordered list of aggregation definitions
typedef const AggregationDef* AggregationDef_cptr;        //!< Non-owning const pointer


}
}
