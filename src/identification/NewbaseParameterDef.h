#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief Newbase (FMI-internal) parameter definition record loaded from the Newbase
 *  parameter definitions CSV.
 *
 *  Stores the Newbase numeric parameter identifier, its native Newbase name, and the
 *  corresponding FMI canonical parameter name used for cross-format identification. */
// ====================================================================================

class NewbaseParameterDef
{
  public:

                  NewbaseParameterDef();
    virtual       ~NewbaseParameterDef();
    NewbaseParameterDef(const NewbaseParameterDef&) = default;
    NewbaseParameterDef& operator=(const NewbaseParameterDef&) = default;

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::NewbaseParamId mNewbaseParameterId;  //!< Numeric Newbase parameter identifier
    std::string       mParameterName;       //!< Newbase-native parameter name
    std::string       mFmiName;             //!< Corresponding FMI canonical parameter name
};

using NewbaseParamDef_cptr = const NewbaseParameterDef*;                   //!< Non-owning const pointer
using NewbaseParamDef_vec = std::vector<NewbaseParameterDef>;              //!< Ordered list of Newbase parameter definitions
using NewbaseParamDef_umap = std::map<uint,NewbaseParameterDef>;           //!< Ordered map keyed by Newbase parameter ID


}
}
