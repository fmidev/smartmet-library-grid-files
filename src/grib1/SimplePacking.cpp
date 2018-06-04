#include "SimplePacking.h"
#include "Message.h"
#include "GribFile.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/BitArrayReader.h"


namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

SimplePacking::SimplePacking()
{
}





/*! \brief The destructor of the class. */

SimplePacking::~SimplePacking()
{
}





PackingMethod SimplePacking::getPackingMethod() const
{
  try
  {
    return PackingMethod::SIMPLE_PACKING;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




bool SimplePacking::getValueByIndex(Message *message,uint index,T::ParamValue& value) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    std::int16_t binaryScaleFactor = message->getBinaryScaleFactor();
    std::uint16_t decimalScaleFactor = message->getDecimalScaleFactor();
    std::float_t referenceValue = message->getReferenceValue();
    std::uint8_t bitsPerValue = message->getBitsPerValue();

    if (data == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'data' pointer points to NULL!");

    // If 'bitsPerValue' is zero then all values are same as the reference value

    if (!bitsPerValue)
    {
      value = referenceValue;
      return true;
    }

    double R = referenceValue;
    std::int16_t E = binaryScaleFactor;
    std::int16_t D = decimalScaleFactor;

    // Optimization: (R + X * Efac) * Dfac = RDfac + X * EDFac

    const double Efac = std::pow(2.0, E);
    const double Dfac = std::pow(10, -D);

    const double RDfac = R * Dfac;
    const double EDfac = Efac * Dfac;
    uint X = 0;

    std::size_t ss = ((numOfValues * bitsPerValue) / 8) + 1;
    if (dataSize < ss)
      dataSize = message->getDataSizeMax();

    BitArrayReader bitArrayReader(data,dataSize*8);
    bitArrayReader.setReadPosition(index*bitsPerValue);
    bitArrayReader.readBits(bitsPerValue,X);

    value = (T::ParamValue)(RDfac + X * EDfac);
    //printf("VAL %f\n",value);
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




void SimplePacking::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Dimensions_opt dimensions = message->getGridDimensions();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();
    std::int16_t binaryScaleFactor = message->getBinaryScaleFactor();
    std::uint16_t decimalScaleFactor = message->getDecimalScaleFactor();
    std::float_t referenceValue = message->getReferenceValue();
    std::uint8_t bitsPerValue = message->getBitsPerValue();
    // std::uint8_t flags = message->getFlags();

    const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};

    // Vector to return
    decodedValues.clear();
    decodedValues.reserve(numOfValues);


    if (numOfValues == 0)
      return;

    if (bitmap != nullptr  &&  numOfValues > (bitmapSizeInBytes*8))
    {
      SmartMet::Spine::Exception exception(BCP,"The bitmap does not contain enough bits!");
      exception.addParameter("Number of values",std::to_string(numOfValues));
      exception.addParameter("MaxBits in bitmap",std::to_string(bitmapSizeInBytes*8));
      throw exception;
    }


    if (!bitsPerValue)
    {
      // If 'bitsPerValue' is zero then all values are same as the reference value
      for (std::uint32_t i = 0; i < numOfValues; i++)
      {
        if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
        {
          decodedValues.push_back(ParamValueMissing);
        }
        else
        {
          decodedValues.push_back(referenceValue);
        }
      }
      return;
    }

    // Number of bits per value
    unsigned int nbits = bitsPerValue;

    // Reference value R, IEEE 32-bit floating point value
    // TODO: GRIB1 USES IBM-FLOATS INSTEAD OF IEEE-754!!!!!
    double R = referenceValue;

    // Binary scale factor E, possibly negative
    std::int16_t E = binaryScaleFactor;

    // Decimal scale factor D, possibly negative
    std::int16_t D = decimalScaleFactor;

    // Optimization: (R + X * Efac) * Dfac = RDfac + X * EDFac

    const double Efac = std::pow(2.0, E);
    const double Dfac = std::pow(10, -D);

    const double RDfac = R * Dfac;
    const double EDfac = Efac * Dfac;

    // Note: It would be nice to just read a full 64-bit value and shift it all at once.
    // However, the data section is only guaranteed to be followed by the 4 bytes of an
    // End section. If we are extremely unlucky, the minimum one byte required by the
    // packed value plus the 4 bytes of the End section are very close to a memory block
    // mapped to the program, and reading the 3 extra bytes could in theory cause a
    // segmentation fault. If not, we'd get a bus error. However, assuming that the have
    // validated the message, we know there should be at least 8+32 = 40 bits left in
    // the memory mapped file.
    // For now we'll settle for the safe option of reading one byte at a time.
    // TODO: Optimize for speed.

    unsigned int bitsleft = 0;  // How many bits in register
    unsigned int bits = 0;      // The actual bits in register
    std::uint64_t bytepos = 0;  // Byte position

    std::size_t ss = ((numOfValues * bitsPerValue) / 8) + 1;
    if (dataSize < ss)
      dataSize = message->getDataSizeMax();

    for (std::uint32_t i = 0; i < numOfValues; i++)
    {
      if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
        decodedValues.push_back(ParamValueMissing);
      else
      {
        // Read bits still missing from completing the request
        while (bitsleft < nbits)
        {
          if (bytepos >= dataSize)
          {
            SmartMet::Spine::Exception exception(BCP,"Trying to access data outside of the memory area!");
            exception.addParameter("Data size",std::to_string(dataSize));
            exception.addParameter("Requested position",std::to_string(bytepos));
            throw exception;
          }

          bits = (bits << 8) | data[bytepos++];
          bitsleft += 8;
        }

        // Calculate the value, keeping only the highest nbits
        unsigned int X = (bits >> (bitsleft - nbits));  //  & ((1 << nbits) - 1);

        // We used nbits many bits
        bitsleft -= nbits;
        bits = bits & ((1 << bitsleft) - 1);

        // Output the calculated value
        double Y = RDfac + X * EDfac;
        decodedValues.push_back((T::ParamValue)Y);
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void SimplePacking::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SimplePacking\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
