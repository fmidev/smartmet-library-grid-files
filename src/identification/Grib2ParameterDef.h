#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{

// ====================================================================================
/*! \brief GRIB edition 2 parameter definition record loaded from \c paramDef_grib2.csv.
 *
 *  Maps a numeric GRIB parameter ID to the set of GRIB 2 key/value pairs (discipline,
 *  category, parameter number, etc.) that together identify the parameter inside a
 *  GRIB 2 message.  Because GRIB 2 has no single unique parameter ID, matching is done
 *  by comparing all key/value pairs in ParameterList against the message fields.
 *  The definition file is generated from eccodes \c paramId.def template files. */
// ====================================================================================

/*! \brief List of GRIB key/value pairs (key as uint code, value as string) used to
 *  identify a parameter or level in a GRIB message. */
typedef std::vector<std::pair<uint,std::string>> ParameterList;

class Grib2ParameterDef
{
  public:

                    Grib2ParameterDef();
    virtual         ~Grib2ParameterDef();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::GribParamId  mGribParameterId;  //!< Numeric GRIB parameter identifier
    ParameterList   mParameterList;    //!< GRIB 2 key/value pairs that identify this parameter
};

typedef const Grib2ParameterDef* Grib2ParamDef_cptr;          //!< Non-owning const pointer
typedef std::vector<Grib2ParameterDef> Grib2ParamDef_vec;      //!< Ordered list of GRIB 2 parameter definitions
typedef std::list<Grib2ParameterDef> Grib2ParamDef_list;       //!< List used as a lookup cache


}
}
