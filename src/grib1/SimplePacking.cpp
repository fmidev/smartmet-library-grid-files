#include "SimplePacking.h"
#include "Message.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../common/GeneralDefinitions.h"
#include "../common/BitArrayWriter.h"
#include <macgyver/StringConversion.h>
#include <macgyver/FastMath.h>


namespace SmartMet
{
namespace GRIB1
{

const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};


/*! \brief The constructor of the class. */

SimplePacking::SimplePacking()
{
  try
  {
    mNumOfValues = 0;
    mData = nullptr;
    mDataSize = 0;
    mBinaryScaleFactor = 0;
    mDecimalScaleFactor = 0;
    mReferenceValue = 0;
    mBitsPerValue = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

SimplePacking::SimplePacking(const SimplePacking& other)
:DataDefinition(other)
{
  try
  {
    mNumOfValues = 0;
    mData = nullptr;
    mDataSize = 0;
    mBinaryScaleFactor = 0;
    mDecimalScaleFactor = 0;
    mReferenceValue = 0;
    mBitsPerValue = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

SimplePacking::~SimplePacking()
{
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





PackingMethod SimplePacking::getPackingMethod() const
{
  try
  {
    return PackingMethod::SIMPLE_PACKING;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





DataDefinition* SimplePacking::createDataDefinition() const
{
  try
  {
    return (DataDefinition*) new SimplePacking(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SimplePacking::init(Message *message) const
{
  try
  {
    if (mInitialized)
      return;

    mNumOfValues = message->getGridOriginalValueCount();
    mData = message->getDataPtr();
    mDataSize = message->getDataSize();
    mBinaryScaleFactor = message->getBinaryScaleFactor();
    mDecimalScaleFactor = message->getDecimalScaleFactor();
    mReferenceValue = message->getReferenceValue();
    mBitsPerValue = message->getBitsPerValue();

    mEfac = std::pow(2.0, mBinaryScaleFactor);
    mDfac = std::pow(10, -mDecimalScaleFactor);
    mRDfac = mReferenceValue * mDfac;
    mEDfac = mEfac * mDfac;

    std::size_t ss = ((mNumOfValues * mBitsPerValue) / 8) + 1;
    if (mDataSize < ss)
      mDataSize = message->getDataSizeMax();

    mInitialized = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool SimplePacking::getValueByIndex(Message *message,uint index,T::ParamValue& value) const
{
  try
  {
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    if (bitmap != nullptr && (bitmap[index / 8] & bitmask[index % 8]) == 0)
      return false;

    if (message->getDataPtr() == nullptr || message->getDataSize() == 0)
    {
      if (!mBitsPerValue)
      {
        // If 'bitsPerValue' is zero then all values are same as the reference value
        value = mReferenceValue;
        return true;
      }

      return false;
    }

    if (index >= message->getGridOriginalValueCount())
      return false;

    if (!mInitialized)
      init(message);

    if (!mBitsPerValue)
    {
      // If 'bitsPerValue' is zero then all values are same as the reference value
      value = mReferenceValue;
      return true;
    }

    uint X = 0;
    uint a = mBitsPerValue % 8;

    if (a != 0)
    {
      BitArrayReader bitArrayReader(mData,mDataSize*8);
      bitArrayReader.setReadPosition(index*mBitsPerValue);
      bitArrayReader.readBits(mBitsPerValue,X);
    }
    else
    {
      uint b = mBitsPerValue / 8;
      MemoryReader memoryReader(mData,mDataSize);
      memoryReader.setReadPosition(index * b);
      switch (b)
      {
        case 1:
          X = memoryReader.read_uint8();
          break;

        case 2:
          X = memoryReader.read_uint16();
          break;

        case 3:
          X = memoryReader.read_uint24();
          break;

        case 4:
          X = memoryReader.read_uint32();
          break;
      }
    }

    double Y = mRDfac + X * mEDfac;

    if (Fmi::floor(Y+0.5) == 9999)
      value = ParamValueMissing;
    else
      value = Y;

    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SimplePacking::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Dimensions dimensions = message->getGridDimensions();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();
    std::int16_t binaryScaleFactor = message->getBinaryScaleFactor();
    std::uint16_t decimalScaleFactor = message->getDecimalScaleFactor();
    std::float_t referenceValue = message->getReferenceValue();
    std::uint8_t bitsPerValue = message->getBitsPerValue();

    // Vector to return
    decodedValues.clear();
    decodedValues.reserve(numOfValues);


    if (numOfValues == 0)
      return;

    if (bitmap != nullptr  &&  numOfValues > (bitmapSizeInBytes*8))
    {
      Fmi::Exception exception(BCP,"The bitmap does not contain enough bits!");
      exception.addParameter("Number of values",Fmi::to_string(numOfValues));
      exception.addParameter("MaxBits in bitmap",Fmi::to_string(bitmapSizeInBytes*8));
      throw exception;
    }


    if (!bitsPerValue)
    {
      // If 'bitsPerValue' is zero then all values are same as the reference value
      for (std::uint32_t i = 0; i < numOfValues; i++)
      {
        if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
        {
          decodedValues.emplace_back(ParamValueMissing);
        }
        else
        {
          decodedValues.emplace_back(referenceValue);
        }
      }
      return;
    }

    // Reference value R, IEEE 32-bit floating point value
    // TODO: GRIB1 USES IBM-FLOATS INSTEAD OF IEEE-754!!!!!
    double R = referenceValue;

    // Binary scale factor E, possibly negative
    std::int16_t E = binaryScaleFactor;

    // Decimal scale factor D, possibly negative
    std::int16_t D = decimalScaleFactor;

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

    uint a = bitsPerValue % 8;

    if (a != 0)
    {
      BitArrayReader bitArrayReader(data,dataSize*8);

      if (bitmap == nullptr)
      {
        for (std::uint32_t i = 0; i < numOfValues; i++)
        {
          uint X = 0;
          bitArrayReader.readBits(bitsPerValue,X);

          double Y = RDfac + X * EDfac;
          if (Fmi::floor(Y+0.5) == 9999)
            decodedValues.emplace_back(ParamValueMissing);
          else
            decodedValues.emplace_back(Y);
        }
      }
      else
      {
        for (std::uint32_t i = 0; i < numOfValues; i++)
        {
          if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
            decodedValues.emplace_back(ParamValueMissing);
          else
          {
            uint X = 0;
            bitArrayReader.readBits(bitsPerValue,X);

            double Y = RDfac + X * EDfac;
            if (Fmi::floor(Y+0.5) == 9999)
              decodedValues.emplace_back(ParamValueMissing);
            else
              decodedValues.emplace_back(Y);
          }
        }
      }
    }
    else
    {
      uint b = bitsPerValue / 8;
      MemoryReader memoryReader(data,dataSize);
      switch (b)
      {
        case 1:
          if (bitmap == nullptr)
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              uint X = memoryReader.read_uint8();
              double Y = RDfac + X * EDfac;
              if (Fmi::floor(Y+0.5) == 9999)
                decodedValues.emplace_back(ParamValueMissing);
              else
                decodedValues.emplace_back(Y);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
                decodedValues.emplace_back(ParamValueMissing);
              else
              {
                uint X = memoryReader.read_uint8();
                double Y = RDfac + X * EDfac;
                if (Fmi::floor(Y+0.5) == 9999)
                  decodedValues.emplace_back(ParamValueMissing);
                else
                  decodedValues.emplace_back(Y);
              }
            }
          }
          break;

        case 2:
          if (bitmap == nullptr)
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              uint X = memoryReader.read_uint16();
              double Y = RDfac + X * EDfac;
              if (Fmi::floor(Y+0.5) == 9999)
                decodedValues.emplace_back(ParamValueMissing);
              else
                decodedValues.emplace_back(Y);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
                decodedValues.emplace_back(ParamValueMissing);
              else
              {
                uint X = memoryReader.read_uint16();
                double Y = RDfac + X * EDfac;
                if (Fmi::floor(Y+0.5) == 9999)
                  decodedValues.emplace_back(ParamValueMissing);
                else
                  decodedValues.emplace_back(Y);
              }
            }
          }
          break;

        case 3:
          if (bitmap == nullptr)
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              uint X = memoryReader.read_uint24();
              double Y = RDfac + X * EDfac;
              if (Fmi::floor(Y+0.5) == 9999)
                decodedValues.emplace_back(ParamValueMissing);
              else
                decodedValues.emplace_back(Y);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
                decodedValues.emplace_back(ParamValueMissing);
              else
              {
                uint X = memoryReader.read_uint24();
                double Y = RDfac + X * EDfac;
                if (Fmi::floor(Y+0.5) == 9999)
                  decodedValues.emplace_back(ParamValueMissing);
                else
                  decodedValues.emplace_back(Y);
              }
            }
          }
          break;

        case 4:
          if (bitmap == nullptr)
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              uint X = memoryReader.read_uint32();
              double Y = RDfac + X * EDfac;
              if (Fmi::floor(Y+0.5) == 9999)
                decodedValues.emplace_back(ParamValueMissing);
              else
                decodedValues.emplace_back(Y);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if (bitmap != nullptr && (bitmap[i / 8] & bitmask[i % 8]) == 0)
                decodedValues.emplace_back(ParamValueMissing);
              else
              {
                uint X = memoryReader.read_uint32();
                double Y = RDfac + X * EDfac;
                if (Fmi::floor(Y+0.5) == 9999)
                  decodedValues.emplace_back(ParamValueMissing);
                else
                  decodedValues.emplace_back(Y);
              }
            }
          }
          break;
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SimplePacking::encodeValues(Message *message,T::ParamValue_vec& values)
{
  try
  {
    std::int16_t binaryScaleFactor = message->getBinaryScaleFactor();
    std::uint16_t decimalScaleFactor = message->getDecimalScaleFactor();
    std::float_t referenceValue = message->getReferenceValue();
    std::uint8_t bitsPerValue = message->getBitsPerValue();

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


    std::int16_t E = binaryScaleFactor;
    std::int16_t D = decimalScaleFactor;

    referenceValue = minValue;
    double R = referenceValue;


    uint bits = 0;

    if (!bitsPerValue)
    {
      T::ParamValue diff = maxValue - minValue;
      ulonglong valuesInRange = diff / std::pow(2.0, E);

      while (C_UINT64(1 << bits) < valuesInRange)
        bits++;
    }
    else
    {
      bits = bitsPerValue;
    }

    if (missingCount > 0)
    {
      // Bitmap required
    }


    const double Efac = std::pow(2.0, E);
    const double Dfac = std::pow(10, -D);

    const double RDfac = R * Dfac;
    const double EDfac = Efac * Dfac;

    uint totalBits = (valueCount * bits);

    uint dataSize = totalBits / 8;
    //if ((totalBits % 8) != 0)
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

    if (dataSection)
    {
      dataSection->setData(data,dataSize);
      dataSection->setReferenceValue(R);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
