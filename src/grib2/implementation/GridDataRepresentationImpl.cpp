#include "GridDataRepresentationImpl.h"
#include "../../common/Exception.h"
#include "../../common/GeneralFunctions.h"
#include "../../common/GeneralDefinitions.h"
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
  try
  {
    mData = nullptr;
    mDataSize = 0;
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

    mInitialized = true;
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
    if (message->getDataPtr() == nullptr || message->getDataSize() == 0)
    {
      //printf("-- no data\n");
      return false;
    }

    if (!mInitialized)
      init(message);

    // If 'bitsPerValue' is zero then all values are same as the reference value

    if (!mBitsPerValue)
    {
      value = mReferenceValue;
      return true;
    }

    uint X = 0;
    BitArrayReader bitArrayReader(mData,mDataSize*8);
    bitArrayReader.setReadPosition(index*mBitsPerValue);
    bitArrayReader.readBits(mBitsPerValue,X);

    value = (mRDfac + X * mEDfac);
    //printf("-- VAL %f\n",value);
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


    const int bitmask[] = {128, 64, 32, 16, 8, 4, 2, 1};

    if (numOfValues == 0)
      return;

    if (data == nullptr || dataSize == 0)
      return;
      //throw SmartMet::Spine::Exception(BCP,"The 'data' pointer points to nullptr!");

    // Vector to return
    decodedValues.clear();
    decodedValues.reserve(numOfValues);

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

    //printf("--- totalBits = %u  %u  %u  %u\n",totalBits,valueCount,bits,missingCount);

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
      //printf("**** Create DataSection %u\n",dataSize);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}



}
}
