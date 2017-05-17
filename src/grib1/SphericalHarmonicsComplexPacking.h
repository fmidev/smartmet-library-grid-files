#pragma once

#include "DataDefinition.h"
#include "common/MemoryReader.h"

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

class SphericalHarmonicsComplexPacking : public DataDefinition
{
  public:
                  SphericalHarmonicsComplexPacking();
    virtual       ~SphericalHarmonicsComplexPacking();

    PackingMethod getPackingMethod() const;
    void          decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void          print(std::ostream& stream,uint level,uint optionFlags) const;
    void          read(MemoryReader& memoryReader);

  protected:

    std::uint16_t mN;
    std::uint16_t mIP;
    std::uint8_t  mJ1;
    std::uint8_t  mK1;
    std::uint8_t  mM1;
};

}  // namespace GRIB1
}  // namespace SmartMet
