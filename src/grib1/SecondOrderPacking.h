#pragma once

#include "DataDefinition.h"
#include "../common/MemoryReader.h"

namespace SmartMet
{
namespace GRIB1
{

/*
  --------------------------------------------------------------------------------------
  SecondOrder packing (Section 4 - Binary data section)
  --------------------------------------------------------------------------------------
  Octet     Contents
  --------------------------------------------------------------------------------------
  12-13     N1 - octet number at which first-order packed data begin
  14        Extended flags (see Code table 11)
  15-16     N2 - octet number at which second-order packed data begin
  17-18     P1 - number of first-order packed values (the same as the number of sub-sections)
  19-20     P2 - number of second-order packed values
  21        Reserved
  22-(xx-1) Width(s) in bits of second-order packed values; each width is contained in 1 octet
  xx-(N1-1) Secondary bit-map, at least P2 bits long, padded to a whole number of octets with binary 0
  N1-(N2-1) P1 first-order packed values, padded to a whole number of octets with binary 0
  N2-...    P2 second-order packed values
  --------------------------------------------------------------------------------------
*/

class SecondOrderPacking : public DataDefinition
{
  public:
                  SecondOrderPacking();
//                  SecondOrderPacking(MemoryReader& memoryReader);
    virtual       ~SecondOrderPacking();

    PackingMethod getPackingMethod() const;
    void          decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void          print(std::ostream& stream,uint level,uint optionFlags) const;
    void          read(MemoryReader& memoryReader);

  private:

    std::uint16_t mN1;
    std::uint8_t  mExtendedFlags;
    std::uint16_t mN2;
    std::uint16_t mP1;
    std::uint16_t mP2;
    std::uint8_t  mExtraValues;

  private:

    void decodeValues_rowByRow(
        std::size_t numOfValues,
        T::Dimensions_opt dimensions,
        T::Data_ptr data,
        std::size_t dataSize,
        T::Data_ptr bitmap,
        std::size_t bitmapSizeInBytes,
        std::int16_t binaryScaleFactor,
        std::uint16_t decimalScaleFactor,
        std::float_t referenceValue,
        std::uint8_t bitsPerValue,
        std::uint8_t flags,
        T::ParamValue_vec& decodedValues) const;

    void decodeValues_constantWidth(
        std::size_t numOfValues,
        T::Dimensions_opt dimensions,
        T::Data_ptr data,
        std::size_t dataSize,
        T::Data_ptr bitmap,
        std::size_t bitmapSizeInBytes,
        std::int16_t binaryScaleFactor,
        std::uint16_t decimalScaleFactor,
        std::float_t referenceValue,
        std::uint8_t bitsPerValue,
        std::uint8_t flags,
        T::ParamValue_vec& decodedValues) const;

    void decodeValues_differentWidth(
        std::size_t numOfValues,
        T::Dimensions_opt dimensions,
        T::Data_ptr data,
        std::size_t dataSize,
        T::Data_ptr bitmap,
        std::size_t bitmapSizeInBytes,
        std::int16_t binaryScaleFactor,
        std::uint16_t decimalScaleFactor,
        std::float_t referenceValue,
        std::uint8_t bitsPerValue,
        std::uint8_t flags,
        T::ParamValue_vec& decodedValues) const;

    void decodeValues_SPD(
        std::size_t numOfValues,
        T::Dimensions_opt dimensions,
        T::Data_ptr data,
        std::size_t dataSize,
        T::Data_ptr bitmap,
        std::size_t bitmapSizeInBytes,
        std::int16_t binaryScaleFactor,
        std::uint16_t decimalScaleFactor,
        std::float_t referenceValue,
        std::uint8_t bitsPerValue,
        std::uint8_t flags,
        T::ParamValue_vec& decodedValues,
        uint orderOfSPD) const;
};

}  // namespace GRIB1
}  // namespace SmartMet
