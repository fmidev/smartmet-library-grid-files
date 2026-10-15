#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief Processing type definition record loaded from the processing type definitions CSV.
 *
 *  Describes a grid processing type (e.g. instantaneous, minimum, maximum, mean) with
 *  a numeric identifier, a short name, and a human-readable description. */
// ====================================================================================

class ProcessingTypeDef
{
  public:
                    ProcessingTypeDef();
    virtual         ~ProcessingTypeDef();
    ProcessingTypeDef(const ProcessingTypeDef&) = default;
    ProcessingTypeDef& operator=(const ProcessingTypeDef&) = default;

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    int             mProcessingTypeId;  //!< Numeric processing type identifier
    std::string     mName;              //!< Short name (e.g. "instantaneous", "min", "mean")
    std::string     mDescription;       //!< Human-readable description
};


using ProcessingTypeDef_vec = std::vector<ProcessingTypeDef>;  //!< Ordered list of processing type definitions
using ProcessingTypeDef_cptr = const ProcessingTypeDef*;       //!< Non-owning const pointer


}
}
