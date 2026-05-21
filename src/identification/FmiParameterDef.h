#pragma once

#include "../grid/Typedefs.h"
#include <unordered_map>

namespace SmartMet
{
namespace Identification
{


// ====================================================================================
/*! \brief FMI parameter definition record loaded from the FMI parameter definitions CSV.
 *
 *  Stores the canonical FMI parameter identifier together with the parameter's name,
 *  physical units, description, preferred interpolation methods, and display precision.
 *  FMI parameter IDs are the common currency used to cross-reference GRIB, NetCDF,
 *  and Newbase parameters. */
// ====================================================================================

class FmiParameterDef
{
  public:
                  FmiParameterDef();
    virtual       ~FmiParameterDef();

    /*! \brief Write a human-readable dump to \p stream (for debugging). */
    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::FmiParamId mFmiParameterId;            //!< FMI parameter identifier
    std::string   mParameterName;             //!< Canonical FMI parameter name
    std::string   mParameterUnits;            //!< Physical units (e.g. "K", "m/s", "%")
    std::string   mParameterDescription;      //!< Human-readable description
    short         mAreaInterpolationMethod;   //!< Default horizontal interpolation method code
    short         mTimeInterpolationMethod;   //!< Default temporal interpolation method code
    short         mLevelInterpolationMethod;  //!< Default vertical interpolation method code
    short         mDefaultPrecision;          //!< Default display precision (decimal places)
};

typedef std::vector<FmiParameterDef> FmiParamDef_vec;           //!< Ordered list of FMI parameter definitions
typedef std::unordered_map<uint,FmiParameterDef> FmiParamDef_umap; //!< Hash map keyed by FMI parameter ID
typedef const FmiParameterDef* FmiParamDef_cptr;                //!< Non-owning const pointer

}
}
