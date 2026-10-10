#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief NetCDF parameter definition record loaded from the NetCDF parameter definitions CSV.
 *
 *  Stores the NetCDF variable name, the associated FMI level identifier string,
 *  and the physical units for a single NetCDF parameter. */
// ====================================================================================

class NetCdfParameterDef
{
  public:

                  NetCdfParameterDef();
    virtual       ~NetCdfParameterDef();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    std::string   mParameterName;  //!< NetCDF variable name used to identify the parameter
    std::string   mFmiLevelId;     //!< FMI level identifier string associated with this parameter
    std::string   mParameterUnits; //!< Physical units (e.g. "K", "m/s")
};

typedef const NetCdfParameterDef* NetCdfParamDef_cptr;                               //!< Non-owning const pointer
using NetCdfParamDef_vec = std::vector<NetCdfParameterDef>;                          //!< Ordered list of NetCDF parameter definitions
using NetCdfParamDef_umap = std::unordered_map<std::string,NetCdfParameterDef>;      //!< Hash map keyed by NetCDF variable name


}
}
