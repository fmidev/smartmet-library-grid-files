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

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::NewbaseParamId mNewbaseParameterId;  //!< Numeric Newbase parameter identifier
    std::string       mParameterName;       //!< Newbase-native parameter name
    std::string       mFmiName;             //!< Corresponding FMI canonical parameter name
};

typedef const NewbaseParameterDef* NewbaseParamDef_cptr;                   //!< Non-owning const pointer
typedef std::vector<NewbaseParameterDef> NewbaseParamDef_vec;              //!< Ordered list of Newbase parameter definitions
typedef std::map<uint,NewbaseParameterDef> NewbaseParamDef_umap;           //!< Ordered map keyed by Newbase parameter ID


}
}
