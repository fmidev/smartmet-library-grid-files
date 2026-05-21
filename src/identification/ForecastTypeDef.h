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

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    int             mForecastTypeId;  //!< Numeric forecast type identifier
    std::string     mName;            //!< Short name (e.g. "deterministic", "ensemble")
    std::string     mDescription;     //!< Human-readable description
};


typedef std::vector<ForecastTypeDef> ForecastTypeDef_vec;  //!< Ordered list of forecast type definitions
typedef const ForecastTypeDef* ForecastTypeDef_cptr;       //!< Non-owning const pointer


}
}
