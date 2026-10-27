#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief Forecast type definition record loaded from the forecast type definitions CSV.
 *
 *  Describes a forecast type (e.g. deterministic, ensemble member, analysis) with a
 *  numeric identifier, a short name, and a human-readable description. */
// ====================================================================================

class ForecastTypeDef
{
  public:
                    ForecastTypeDef();
    virtual         ~ForecastTypeDef();
    ForecastTypeDef(const ForecastTypeDef&) = default;
    ForecastTypeDef& operator=(const ForecastTypeDef&) = default;

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    int             mForecastTypeId;  //!< Numeric forecast type identifier
    std::string     mName;            //!< Short name (e.g. "deterministic", "ensemble")
    std::string     mDescription;     //!< Human-readable description
};


using ForecastTypeDef_vec = std::vector<ForecastTypeDef>;  //!< Ordered list of forecast type definitions
using ForecastTypeDef_cptr = const ForecastTypeDef*;       //!< Non-owning const pointer


}
}
