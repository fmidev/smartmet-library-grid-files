#include "SpectralGridDataRepresentationImpl.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralFunctions.h"
#include "../../common/BitArrayReader.h"
#include "../../common/AutoThreadLock.h"
#include "../Message.h"

extern "C"
{
  #include <libaec.h>
}


namespace SmartMet
{
namespace GRIB2
{


ThreadLock AEC_threadLock;


/*! \brief The constructor of the class. */

SpectralGridDataRepresentationImpl::SpectralGridDataRepresentationImpl()
{
}





/*! \brief The copy constructor of the class. */

SpectralGridDataRepresentationImpl::SpectralGridDataRepresentationImpl(const SpectralGridDataRepresentationImpl& other)
:SpectralGridDataRepresentation(other)
{
}





/*! \brief The destructor of the class. */

SpectralGridDataRepresentationImpl::~SpectralGridDataRepresentationImpl()
{
}





/*! \brief The method creates a duplicate of the current object. */

RepresentationDefinition* SpectralGridDataRepresentationImpl::createRepresentationDefinition() const
{
  try
  {
    return (RepresentationDefinition*) new SpectralGridDataRepresentationImpl(*this);
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

void SpectralGridDataRepresentationImpl::read(MemoryReader& memoryReader)
{
  try
  {
    SpectralGridDataRepresentation::read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void SpectralGridDataRepresentationImpl::decodeValues(Message *message,T::ParamValue_vec& decodedValues) const
{
  try
  {
    std::size_t numOfValues = message->getGridOriginalValueCount();
    T::Data_ptr data = message->getDataPtr();
    std::size_t dataSize = message->getDataSize();
    T::Data_ptr bitmap = message->getBitmapDataPtr();
    std::size_t bitmapSizeInBytes = message->getBitmapDataSizeInBytes();

    //if (data == nullptr)
      //throw Fmi::Exception(BCP,"The 'data' pointer points to nullptr!");

    long bits_per_value = *mPacking.getBitsPerValue();
    double reference_value = mPacking.getReferenceValue();

    if (dataSize == 0  || data == nullptr  ||  bits_per_value == 0)
    {
      if (bitmap != nullptr  &&  bitmapSizeInBytes > 0)
      {
        // There is no data, but there is a bitmap available.
        BitArrayReader bitmapReader(bitmap,bitmapSizeInBytes*8);
        for (std::uint32_t i=0; i<numOfValues; i++)
        {
          if (bitmapReader.readBit())
          {
            decodedValues.emplace_back(reference_value);
          }
          else
          {
            decodedValues.emplace_back(ParamValueMissing);
          }
        }
        return;
      }
      else
      {
        // All values are set to "reference_value".
        for (std::uint32_t i=0; i<numOfValues; i++)
        {
          decodedValues.emplace_back(reference_value);
        }
        return;
      }
    }

    int32_t *dest = new int32_t[numOfValues];
    for (size_t t=0; t<numOfValues; t++)
      dest[t] = 0;

    std::size_t outputBytes = 0;

    {
      AutoThreadLock lock(&AEC_threadLock);

      struct aec_stream strm;
      strm.bits_per_sample = bits_per_value;

      strm.block_size = 32;
      if (mCcsdsBlockSize)
        strm.block_size = *mCcsdsBlockSize;

      strm.rsi = 128;
      if (mCcsdsRsi)
        strm.rsi = *mCcsdsRsi;

      strm.flags = AEC_DATA_SIGNED | AEC_DATA_PREPROCESS;
      if (mCcsdsFlags)
        strm.flags = *mCcsdsFlags;

      strm.next_in = data;
      strm.avail_in = dataSize;
      strm.next_out = (unsigned char*)dest;
      strm.avail_out = numOfValues * sizeof(int32_t);

      if (aec_decode_init(&strm) != AEC_OK)
      {
        delete [] dest;
        throw Fmi::Exception(BCP,"Initialization of the decoder failed!");
      }

      if (aec_decode(&strm, AEC_FLUSH) != AEC_OK)
      {
        aec_decode_end(&strm);
        delete [] dest;
        throw Fmi::Exception(BCP,"Decoding failed!");
      }

      outputBytes = strm.total_out;
      aec_decode_end(&strm);

    }

    double R = mPacking.getReferenceValue();

    std::int16_t E = (mPacking.getBinaryScaleFactor() ? *mPacking.getBinaryScaleFactor() : 0);

    // Decimal scale factor D, possibly negative
    std::int16_t D = (mPacking.getDecimalScaleFactor() ? *mPacking.getDecimalScaleFactor() : 0);

    // Optimization: (R + X * Efac) * Dfac = RDfac + X * EDFac

    const double Efac = std::pow(2.0, E);
    const double Dfac = std::pow(10, -D);

    const double RDfac = R * Dfac;
    const double EDfac = Efac * Dfac;

    int bytes = (bits_per_value-1)/8 + 1;
    int bits = bytes*8;

    BitArrayReader bitArrayReader((unsigned char*)dest,outputBytes*8);

    if (bitmapSizeInBytes > 0)
    {
      T::Data_ptr bmap = bitmap;
      unsigned char tmp = 0;
      if (bmap == nullptr)
        bmap = &tmp;

      BitArrayReader bitmapReader(bmap,bitmapSizeInBytes*8);
      for (std::uint32_t i = 0; i < numOfValues; i++)
      {
        if (bitmapReader.readBit())
        {
          uint value = 0;
          bitArrayReader.readBits(bits,value);
          double val = RDfac + value * EDfac;
          decodedValues.emplace_back(val);
        }
        else
        {
          decodedValues.emplace_back(ParamValueMissing);
        }
      }
    }
    else
    {
      for (std::uint32_t i = 0; i < numOfValues; i++)
      {
        uint value = 0;
        bitArrayReader.readBits(bits,value);
        double val = RDfac + value * EDfac;
        decodedValues.emplace_back(val);
      }
    }

    delete [] dest;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}
}
