#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief Mapping record between an FMI parameter ID and a GRIB parameter ID.
 *
 *  Loaded from the FMI-to-GRIB parameter mapping CSV.  When the GRIB and FMI units
 *  differ, optional conversion function strings allow transforming values in both
 *  directions (e.g. temperature K↔°C). */
// ====================================================================================

class FmiParameterId_grib
{
  public:
                    FmiParameterId_grib();
    virtual         ~FmiParameterId_grib();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId   mFmiParameterId;              //!< FMI parameter identifier
    T::GribParamId  mGribParameterId;             //!< Corresponding GRIB parameter identifier
    std::string     mConversionFunction;          //!< Expression to convert GRIB value → FMI value (empty = no-op)
    std::string     mReverseConversionFunction;   //!< Expression to convert FMI value → GRIB value (empty = no-op)
};


typedef std::vector<FmiParameterId_grib> FmiParamId_grib_vec;             //!< Ordered list of FMI↔GRIB mappings
typedef std::unordered_map<uint,FmiParameterId_grib> FmiParamId_grib_umap; //!< Hash map keyed by FMI parameter ID
typedef const FmiParameterId_grib* FmiParamId_grib_cptr;                  //!< Non-owning const pointer


}
}
