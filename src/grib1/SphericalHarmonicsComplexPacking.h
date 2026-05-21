#pragma once

#include "DataDefinition.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"

namespace SmartMet
{
namespace GRIB1
{

/*
  --------------------------------------------------------------------------------------
  Spherical Harmonics Complex packing (Section 4 - Binary data section)
  --------------------------------------------------------------------------------------
  Octet     Contents
  --------------------------------------------------------------------------------------
  12-13     N (relative to the beginning of the BDS, except for ECMWF fields where it is
               relative to the beginning of the GRIB record)
  14-15     IP (where IP = int (1000 x P))
  16        J1
  17        K1
  18        M1
  19        Binary data
  --------------------------------------------------------------------------------------
*/

// ====================================================================================
/*! \brief GRIB 1 spherical harmonics complex-packing decoder.
 *
 *  Decodes grid values encoded using the ECMWF-style spherical harmonics complex
 *  packing scheme.  Spectral coefficients within truncation (J1, K1, M1) are stored
 *  unpacked in floating point; remaining coefficients are simple-packed. */
// ====================================================================================

class SphericalHarmonicsComplexPacking : public DataDefinition
{
  public:
                    SphericalHarmonicsComplexPacking();
                    SphericalHarmonicsComplexPacking(const SphericalHarmonicsComplexPacking& other);
    virtual         ~SphericalHarmonicsComplexPacking();

    DataDefinition* createDataDefinition() const;
    void            decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    PackingMethod   getPackingMethod() const;

    void            read(MemoryReader& memoryReader);
    void            write(DataWriter& dataWriter);
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

  protected:

    std::uint16_t   mN;   //!< Offset N (relative to BDS start, or GRIB record start for ECMWF).
    std::uint16_t   mIP;  //!< Integer representation of P: IP = int(1000 * P).
    std::uint8_t    mJ1;  //!< Pentagonal resolution parameter J.
    std::uint8_t    mK1;  //!< Pentagonal resolution parameter K.
    std::uint8_t    mM1;  //!< Pentagonal resolution parameter M.
};

}  // namespace GRIB1
}  // namespace SmartMet
