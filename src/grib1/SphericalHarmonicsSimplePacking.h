#pragma once

#include "DataDefinition.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"

namespace SmartMet
{
namespace GRIB1
{


// ====================================================================================
/*! \brief GRIB 1 spherical harmonics simple-packing decoder.
 *
 *  Decodes spectral data encoded with the simpler spherical harmonics packing variant.
 *  All coefficients are uniformly packed using the standard simple-packing scale
 *  parameters from the Data Section (no complex unpacked coefficient sub-range). */
// ====================================================================================

class SphericalHarmonicsSimplePacking : public DataDefinition
{
  public:
                    SphericalHarmonicsSimplePacking();
                    SphericalHarmonicsSimplePacking(const SphericalHarmonicsSimplePacking& other);
    virtual         ~SphericalHarmonicsSimplePacking();

    DataDefinition* createDataDefinition() const;
    void            decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    PackingMethod   getPackingMethod() const;

    void            print(std::ostream& stream,uint level,uint optionFlags) const;
};

}  // namespace GRIB1
}  // namespace SmartMet
