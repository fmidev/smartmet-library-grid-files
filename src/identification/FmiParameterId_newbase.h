#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief Mapping record between an FMI parameter ID and a Newbase parameter ID.
 *
 *  Loaded from the FMI-to-Newbase parameter mapping CSV.  Optional conversion function
 *  strings allow transforming values between the Newbase and FMI unit conventions. */
// ====================================================================================

class FmiParameterId_newbase
{
  public:
                      FmiParameterId_newbase();
    virtual           ~FmiParameterId_newbase();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void              print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId     mFmiParameterId;             //!< FMI parameter identifier
    T::NewbaseParamId mNewbaseParameterId;          //!< Corresponding Newbase parameter identifier
    std::string       mConversionFunction;         //!< Expression to convert Newbase value → FMI value (empty = no-op)
    std::string       mReverseConversionFunction;  //!< Expression to convert FMI value → Newbase value (empty = no-op)
};


typedef std::vector<FmiParameterId_newbase> FmiParamId_newbase_vec;              //!< Ordered list of FMI↔Newbase mappings
typedef std::unordered_map<uint,FmiParameterId_newbase> FmiParamId_newbase_umap; //!< Hash map keyed by FMI parameter ID
typedef const FmiParameterId_newbase* FmiParamId_newbase_cptr;                  //!< Non-owning const pointer


}
}
