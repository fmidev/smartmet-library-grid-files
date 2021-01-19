#include "GridDataRepresentationImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/BitArrayWriter.h"
#include "../../common/MemoryReader.h"
#include "../Message.h"

#include <limits>

namespace SmartMet
{
namespace GRIB2
{

const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};


/*! \brief The constructor of the class. */

GridDataRepresentationImpl::GridDataRepresentationImpl()
{
  try
  {
    mData = nullptr;
    mDataSize = 0;
    mBitmap = nullptr;
    mBinaryScaleFactor = 0;
    mDecimalScaleFactor = 0;
    mReferenceValue = 0;
    mBitsPerValue = 0;
    mEfac = 0;
    mDfac = 0;
    mRDfac = 0;
    mEDfac = 0;
    mInitialized = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

GridDataRepresentationImpl::GridDataRepresentationImpl(const GridDataRepresentationImpl& other)
:GridDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

GridDataRepresentationImpl::~GridDataRepresentationImpl()
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





/*! \brief The method creates a duplicate of the current object. */

RepresentationDefinition* GridDataRepresentationImpl::createRepresentationDefinition() const
{
  try
  {
    return (RepresentationDefinition*) new GridDataRepresentationImpl(*this);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridDataRepresentationImpl::init(Message *message) const
{
  try
  {
    mData = message->getDataPtr();
    mDataSize = message->getDataSize();
    mBinaryScaleFactor = *(mPacking.getBinaryScaleFactor());
    mDecimalScaleFactor = *(mPacking.getDecimalScaleFactor());
    mReferenceValue = mPacking.getReferenceValue();
    mBitsPerValue = *(mPacking.getBitsPerValue());

    mEfac = std::pow(2.0, mBinaryScaleFactor);
    mDfac = std::pow(10, -mDecimalScaleFactor);
    mRDfac = mReferenceValue * mDfac;
    mEDfac = mEfac * mDfac;

    mBitmap = message->getBitmapDataPtr();

    mInitialized = true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridDataRepresentationImpl::getValueByIndex(Message *message,uint index,T::ParamValue& value) const
{
  try
  {
    if (!mInitialized)
      init(message);

    if (mBitmap != nullptr &&  (mBitmap[index / 8] & bitmask[index % 8]) == 0)
      return false;

    if (mData == nullptr || mDataSize == 0)
    {
      if (!mBitsPerValue)
      {
        value = mReferenceValue;
        return true;
      }

      return false;
    }


    // If 'bitsPerValue' is zero then all values are same as the reference value

    if (!mBitsPerValue)
    {
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
      //MemoryReader memoryReader(mData,mDataSize);
      //memoryReader.setReadPosition(index * b);
      switch (b)
      {
        case 1:
          X = read_uint8(mData,mDataSize,index * b);
          break;

        case 2:
          X = read_uint16(mData,mDataSize,index * b);
          break;

        case 3:
          X = read_uint24(mData,mDataSize,index * b);
          break;

        case 4:
          X = read_uint32(mData,mDataSize,index * b);
          break;
      }
    }

    value = (mRDfac + X * mEDfac);
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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


    if (numOfValues == 0)
      return;

    // Vector to return
    decodedValues.clear();
    decodedValues.reserve(numOfValues);

    // Reference value R, IEEE 32-bit floating point value
    double R = mPacking.getReferenceValue();

    auto bits_per_value = mPacking.getBitsPerValue();
    if (!bits_per_value  ||  *bits_per_value == 0 ||  data == nullptr || dataSize == 0)
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
          decodedValues.emplace_back(R);
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

    uint a = nbits % 8;

    if (a != 0)
    {
      BitArrayReader bitArrayReader(data,dataSize*8);

      if (bitmap == nullptr)
      {
        for (std::uint32_t i = 0; i < numOfValues; i++)
        {
          ulonglong X = 0;
          bitArrayReader.readBits(nbits,X);

          // Output the caclulated value
          double Y = RDfac + X * EDfac;
          decodedValues.emplace_back(Y);
        }
      }
      else
      {
        for (std::uint32_t i = 0; i < numOfValues; i++)
        {
          if ((bitmap[i / 8] & bitmask[i % 8]) == 0)
          {
            decodedValues.emplace_back(ParamValueMissing);
          }
          else
          {
            ulonglong X = 0;
            bitArrayReader.readBits(nbits,X);

            // Output the caclulated value
            double Y = RDfac + X * EDfac;
            decodedValues.emplace_back(Y);
          }
        }
      }
    }
    else
    {
      uint b = nbits / 8;
      MemoryReader memoryReader(data,dataSize);

      switch (b)
      {
        case 1:
          if (bitmap == nullptr)
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              ulonglong X = memoryReader.read_uint8();
              double Y = RDfac + X * EDfac;
              decodedValues.emplace_back(Y);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if ((bitmap[i / 8] & bitmask[i % 8]) == 0)
              {
                decodedValues.emplace_back(ParamValueMissing);
              }
              else
              {
                ulonglong X = memoryReader.read_uint8();
                double Y = RDfac + X * EDfac;
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
              ulonglong X = memoryReader.read_uint16();
              double Y = RDfac + X * EDfac;
              decodedValues.emplace_back(Y);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if ((bitmap[i / 8] & bitmask[i % 8]) == 0)
              {
                decodedValues.emplace_back(ParamValueMissing);
              }
              else
              {
                ulonglong X = memoryReader.read_uint16();
                double Y = RDfac + X * EDfac;
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
              ulonglong X = memoryReader.read_uint24();
              double Y = RDfac + X * EDfac;
              decodedValues.emplace_back(Y);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if ((bitmap[i / 8] & bitmask[i % 8]) == 0)
              {
                decodedValues.emplace_back(ParamValueMissing);
              }
              else
              {
                ulonglong X = memoryReader.read_uint24();
                double Y = RDfac + X * EDfac;
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
              ulonglong X = memoryReader.read_uint32();
              double Y = RDfac + X * EDfac;
              decodedValues.emplace_back(Y);
            }
          }
          else
          {
            for (std::uint32_t i = 0; i < numOfValues; i++)
            {
              if ((bitmap[i / 8] & bitmask[i % 8]) == 0)
              {
                decodedValues.emplace_back(ParamValueMissing);
              }
              else
              {
                ulonglong X = memoryReader.read_uint32();
                double Y = RDfac + X * EDfac;
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
    float R = referenceValue;


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
      bits = (*bitsPerValue);
    }


    if (missingCount > 0)
    {
      // Bitmap required
    }

    const float Efac = std::pow(2.0, E);
    const float Dfac = std::pow(10, -D);

    const float RDfac = R * Dfac;
    const float EDfac = Efac * Dfac;

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
        float Y = *it;
        float X = (Y - RDfac) / EDfac;

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

    RepresentSect_sptr repSect = message->getRepresentationSection();
    if (repSect)
      repSect->setNumberOfValues(values.size());


    mPacking.setReferenceValue(R);
    mPacking.setBinaryScaleFactor(E);
    mPacking.setDecimalScaleFactor(D);
    mPacking.setBitsPerValue(bits);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}



}
}
