#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{

/*! \brief List of GRIB key/value pairs (key as uint code, value as string) that
 *  together identify a parameter or level in a GRIB message. */
using ParameterList = std::vector<std::pair<uint,std::string>>;

// ====================================================================================
/*! \brief GRIB edition 1 parameter definition record loaded from \c paramDef_grib1.csv.
 *
 *  Maps a numeric GRIB parameter ID to the set of GRIB 1 key/value pairs (indicator
 *  table, parameter number, etc.) that uniquely identify the parameter inside a GRIB 1
 *  message.  The ParameterList is used by GridDef to match messages during decoding. */
// ====================================================================================

class Grib1ParameterDef
{
  public:

                    Grib1ParameterDef();
    virtual         ~Grib1ParameterDef();
    Grib1ParameterDef(const Grib1ParameterDef&) = default;
    Grib1ParameterDef& operator=(const Grib1ParameterDef&) = default;

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::GribParamId  mGribParameterId;  //!< Numeric GRIB parameter identifier
    ParameterList   mParameterList;    //!< GRIB 1 key/value pairs that identify this parameter
};

using Grib1ParamDef_cptr = const Grib1ParameterDef*;          //!< Non-owning const pointer
using Grib1ParamDef_vec = std::vector<Grib1ParameterDef>;      //!< Ordered list of GRIB 1 parameter definitions
using Grib1ParamDef_list = std::list<Grib1ParameterDef>;       //!< List used as a lookup cache


}
}
