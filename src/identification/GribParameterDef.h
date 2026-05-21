#pragma once

#include "../grid/Typedefs.h"


namespace SmartMet
{
namespace Identification
{

// ====================================================================================
/*! \brief Common GRIB parameter definition record loaded from \c paramDef.csv.
 *
 *  Stores the GRIB parameter identifier together with a parameter name, description,
 *  and physical units.  This record is shared between GRIB edition 1 and edition 2
 *  and provides the format-neutral metadata for a GRIB parameter. */
// ====================================================================================

class GribParameterDef
{
  public:
                    GribParameterDef();
    virtual         ~GribParameterDef();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    virtual void    print(std::ostream& stream,uint level,uint optionFlags) const;

    T::GribParamId  mGribParameterId;       //!< Numeric GRIB parameter identifier
    std::string     mParameterName;         //!< Short parameter name
    std::string     mParameterDescription;  //!< Human-readable description
    std::string     mParameterUnits;        //!< Physical units (e.g. "K", "m s**-1")
};

typedef std::vector<GribParameterDef> GribParamDef_vec;  //!< Ordered list of GRIB parameter definitions
typedef const GribParameterDef* GribParamDef_cptr;       //!< Non-owning const pointer

}
}
