#include "GridDataRepresentationImpl.h"
#include "../../common/Exception.h"
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/BitArrayReader.h"
#include "../../common/BitArrayWriter.h"
#include "../Message.h"

#include <limits>

namespace SmartMet
{
namespace GRIB2
{



/*! \brief The constructor of the class. */

GridDataRepresentationImpl::GridDataRepresentationImpl()
{
}





/*! \brief The copy constructor of the class. */

GridDataRepresentationImpl::GridDataRepresentationImpl(const GridDataRepresentationImpl& other)
:GridDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

GridDataRepresentationImpl::~GridDataRepresentationImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

RepresentationDefinition* GridDataRepresentationImpl::createRepresentationDefinition() const
{
  try
  {
    return (RepresentationDefinition*) new GridDataRepresentationImpl(*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current object.
    The purpose of this method is to get access to the read operation that takes place
    in the parent class (which is automatically generated). This means in practice that
    we first call the read operation in the parent class. After that we can ensure that
    the result of the read operation was correct (i.e. attribute values are valid, etc).
    We can also modify or update some attribute values if needed.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    GridDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridDataRepresentationImpl::getValueByIndex(Message *message,uint index,T::ParamValue& value) const
{
  try
  {
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    std::int16_t binaryScaleFactor = *(mPacking.getBinaryScaleFactor());
    std::uint16_t decimalScaleFactor = *(mPacking.getDecimalScaleFactor());
    std::float_t referenceValue = mPacking.getReferenceValue();
    std::uint8_t bitsPerValue = *(mPacking.getBitsPerValue());

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


    BitArrayReader bitArrayReader(data,dataSize*8);
    bitArrayReader.setReadPosition(index*bitsPerValue);
    bitArrayReader.readBits(bitsPerValue,X);

    value = (RDfac + X * EDfac);
    // printf("VAL %f\n",value);
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    //std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

    if (data == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'data' pointer points to nullptr!");

    const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};

    // Vector to return
    decodedValues.clear();
    decodedValues.reserve(numOfValues);

    if (numOfValues == 0)
      return;

    // Reference value R, IEEE 32-bit floating point value
    double R = mPacking.getReferenceValue();

    auto bits_per_value = mPacking.getBitsPerValue();
    if (!bits_per_value  ||  *bits_per_value == 0)
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
          decodedValues.push_back(R);
        }
      }
      return;
    }

    // Number of bits per value
    unsigned int nbits = *bits_per_value;


    // Binary scale factor E, possibly negative
    std::int16_t E = (mPacking.getBinaryScaleFactor() ? *mPacking.getBinaryScaleFactor() : 0);

    // Decimal scale factor D, possibly negative
    std::int16_t D = (mPacking.getDecimalScaleFactor() ? *mPacking.getDecimalScaleFactor() : 0);

    // Optimization: (R + X * Efac) * Dfac = RDfac + X * EDFac

    const double Efac = std::pow(2.0, E);
    const double Dfac = std::pow(10, -D);

    const double RDfac = R * Dfac;
    const double EDfac = Efac * Dfac;

    BitArrayReader bitArrayReader(data,dataSize*8);

    for (std::uint32_t i = 0; i < numOfValues; i++)
    {
      if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
      {
        decodedValues.push_back(ParamValueMissing);
      }
      else
      {
        ulonglong X = 0;
        bitArrayReader.readBits(nbits,X);

        // Output the caclulated value
        double Y = RDfac + X * EDfac;
        decodedValues.push_back(Y);
      }
    }

#if 0
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

    for (std::uint32_t i = 0; i < numOfValues; i++)
    {
      if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
      {
        decodedValues.push_back(ParamValueMissing);
      }
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

        // Output the caclulated value
        double Y = RDfac + X * EDfac;

        decodedValues.push_back(Y);
      }
    }
#endif
/*
    uint valueCount = 0;
    uint missingCount = 0;
    T::ParamValue minValue = ParamValueMissing;
    T::ParamValue maxValue = ParamValueMissing;

    for (auto it = decodedValues.begin(); it != decodedValues.end(); ++it)
    {
      if ((*it) != ParamValueMissing)
      {
        if (minValue == ParamValueMissing || ((*it) < minValue))
        {
          minValue = *it;
        }

        if (maxValue == ParamValueMissing || ((*it) > maxValue))
        {
          maxValue = *it;
        }
        valueCount++;
      }
      else
      {
        missingCount++;
      }
    }


    printf("*** MIN %f  MAX %f\n",minValue,maxValue);
    if (missingCount > 0)
    {
      // Bitmap required
    }

*/
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridDataRepresentationImpl::encodeValues(Message *message,T::ParamValue_vec& values)
{
  try
  {
    T::Int16_opt binaryScaleFactor = 0;
    T::Int16_opt decimalScaleFactor = 0;
    binaryScaleFactor = mPacking.getBinaryScaleFactor();
    decimalScaleFactor = mPacking.getDecimalScaleFactor();
    auto referenceValue = mPacking.getReferenceValue();
    auto bitsPerValue = mPacking.getBitsPerValue();


    uint valueCount = 0;
    uint missingCount = 0;
    T::ParamValue minValue = ParamValueMissing;
    T::ParamValue maxValue = ParamValueMissing;

    for (auto it = values.begin(); it != values.end(); ++it)
    {
      if ((*it) != ParamValueMissing)
      {
        if (minValue == ParamValueMissing || ((*it) < minValue))
        {
          minValue = *it;
        }

        if (maxValue == ParamValueMissing || ((*it) > maxValue))
        {
          maxValue = *it;
        }
        valueCount++;
      }
      else
      {
        missingCount++;
      }
    }

    std::int16_t E = 0;
    if (binaryScaleFactor)
      E =  *binaryScaleFactor;

    std::int16_t D = 0;
    if (decimalScaleFactor)
      D = *decimalScaleFactor;

    referenceValue = minValue;
    double R = referenceValue;


    uint bits = 0;

    if (!bitsPerValue)
    {
      T::ParamValue diff = maxValue - minValue;
      ulonglong valuesInRange = diff / std::pow(2.0, E);

      while (C_UINT64(1 << bits) < valuesInRange)
        (bits)++;
    }
    else
    {
      bits = (*bitsPerValue);
    }



/*
    if (!binaryScaleFactor)
    {
      ulonglong steps = (1 << bits);
      double stepSize = diff / steps;

      if (stepSize > 1)
      {

      }
      else
      {
        while (std::pow(2.0, E) > stepSize)
          E--;
      }
    }
    else
    {
      E = *binaryScaleFactor;
    }
*/


    //printf("*** MIN %f  MAX %f\n",minValue,maxValue);
    if (missingCount > 0)
    {
      // Bitmap required
    }





    //printf("R = %f  E = %d  D = %d  Bits = %u\n",R,E,D,bits);

    // Optimization: (R + X * Efac) * Dfac = RDfac + X * EDFac

    const double Efac = std::pow(2.0, E);
    const double Dfac = std::pow(10, -D);

    const double RDfac = R * Dfac;
    const double EDfac = Efac * Dfac;

    uint totalBits = (valueCount * bits);

    uint dataSize = totalBits / 8;
    if ((totalBits % 8) != 0)
      dataSize++;

    uchar *data = new uchar[dataSize];
    memset(data,0,dataSize);
    BitArrayWriter bitArrayWriter(data,totalBits);

    for (auto it = values.begin(); it != values.end(); ++it)
    {
      if ((*it) != ParamValueMissing)
      {
        double Y = *it;
        double X = (Y - RDfac) / EDfac;

        ulonglong v = C_UINT64(round(X));
        bitArrayWriter.writeBits(bits,v);
      }
    }

    DataSect_sptr dataSection = message->getDataSection();

    if (!dataSection)
    {
      DataSection *section = new DataSection();
      section->setMessagePtr(message);
      section->setData(data,dataSize);
      message->setDataSection(section);
    }
    else
    {
      dataSection->setData(data,dataSize);
    }


    mPacking.setReferenceValue(R);
    mPacking.setBinaryScaleFactor(E);
    mPacking.setDecimalScaleFactor(D);
    mPacking.setBitsPerValue(bits);

/*
    uint idx = message->getMessageIndex();

    char filename[100];
    sprintf(filename,"/tmp/data_%04d.dat",idx);
    FILE *file = fopen(filename,"we");
    fwrite(data,dataSize,1,file);
    fclose(file);
    delete data;
*/
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



}
}
