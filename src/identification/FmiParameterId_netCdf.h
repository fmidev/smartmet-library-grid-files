#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief Mapping record between an FMI parameter ID and a NetCDF variable name.
 *
 *  Loaded from the FMI-to-NetCDF parameter mapping CSV.  Optional conversion function
 *  strings allow transforming values between the NetCDF and FMI unit conventions. */
// ====================================================================================

class FmiParameterId_netCdf
{
  public:
                      FmiParameterId_netCdf();
    virtual           ~FmiParameterId_netCdf();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void              print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId     mFmiParameterId;             //!< FMI parameter identifier
    std::string       mNetCdfParameterName;        //!< NetCDF variable name for this parameter
    std::string       mConversionFunction;         //!< Expression to convert NetCDF value → FMI value (empty = no-op)
    std::string       mReverseConversionFunction;  //!< Expression to convert FMI value → NetCDF value (empty = no-op)
};


typedef std::vector<FmiParameterId_netCdf> FmiParamId_netCdf_vec;              //!< Ordered list of FMI↔NetCDF mappings
typedef std::unordered_map<uint,FmiParameterId_netCdf> FmiParamId_netCdf_umap; //!< Hash map keyed by FMI parameter ID
typedef const FmiParameterId_netCdf* FmiParamId_netCdf_cptr;                  //!< Non-owning const pointer


}
}
