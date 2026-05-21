#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{

/*! \brief List of GRIB key/value pairs (key as uint code, value as string) that
 *  together identify a parameter or level in a GRIB message. */
typedef std::vector<std::pair<uint,std::string>> ParameterList;

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

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::GribParamId  mGribParameterId;  //!< Numeric GRIB parameter identifier
    ParameterList   mParameterList;    //!< GRIB 1 key/value pairs that identify this parameter
};

typedef const Grib1ParameterDef* Grib1ParamDef_cptr;          //!< Non-owning const pointer
typedef std::vector<Grib1ParameterDef> Grib1ParamDef_vec;      //!< Ordered list of GRIB 1 parameter definitions
typedef std::list<Grib1ParameterDef> Grib1ParamDef_list;       //!< List used as a lookup cache


}
}
