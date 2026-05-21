#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{

/*! \brief List of GRIB key/value pairs (key as uint code, value as string) used to
 *  identify a level type in a GRIB message. */
typedef std::vector<std::pair<uint,std::string>> ParameterList;


// ====================================================================================
/*! \brief Mapping record that links an FMI level ID to the GRIB key/value pairs
 *  identifying the equivalent level type in a GRIB 1 or GRIB 2 message.
 *
 *  Loaded from the FMI-level-to-GRIB mapping CSV files.  During decoding, all pairs
 *  in ParameterList are matched against the message fields to determine the FMI level
 *  type. */
// ====================================================================================

class FmiLevelId_grib
{
  public:
                    FmiLevelId_grib();
    virtual         ~FmiLevelId_grib();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    uint            mFmiLevelId;      //!< FMI level type identifier
    ParameterList   mParameterList;   //!< GRIB key/value pairs that identify this level type
};


typedef std::vector<FmiLevelId_grib> FmiLevelId_grib_vec;  //!< Ordered list of FMI↔GRIB level mappings
typedef const FmiLevelId_grib* FmiLevelId_grib_cptr;       //!< Non-owning const pointer


}
}
