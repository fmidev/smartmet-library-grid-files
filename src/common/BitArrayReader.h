#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>

namespace SmartMet
{


// ====================================================================================
/*! \brief Sequential bit-level reader over a byte array.
 *
 *  Provides MSB-first single-bit and multi-bit extraction methods.  Used when
 *  GRIB data sections store values as bit-packed fields that span byte boundaries
 *  (e.g. simple-packing, bitmap sections). */
// ====================================================================================

class BitArrayReader
{
  public:
    /*! \brief Construct a reader over a bit buffer.
     *  \param[in] data          Byte array containing the bits to read.
     *  \param[in] numberOfBits  Total number of readable bits. */
               BitArrayReader(const unsigned char *data,UInt64 numberOfBits);
    virtual    ~BitArrayReader();

    /*! \brief Return the total number of bits in the buffer. */
    UInt64     getNumberOfBits();
    /*! \brief Return the current bit read position. */
    UInt64     getReadPosition();
    /*! \brief Set the current bit read position.
     *  \param[in] readPosition  New position (zero-based bit index). */
    void       setReadPosition(UInt64 readPosition);

    /*! \brief Read \p numberOfBits bits and return the signed value.
     *  \param[in]  numberOfBits  Number of bits to read (1–32).
     *  \param[out] value         Receives the decoded signed value. */
    void       readBits(unsigned int numberOfBits,int& value);

    /*! \brief Read \p numberOfBits bits and return an unsigned 64-bit value.
     *  \param[in]  numberOfBits  Number of bits to read (1–64).
     *  \param[out] value         Receives the decoded value. */
    void       readBits(unsigned int numberOfBits,UInt64& value);

    /*! \brief Read \p numberOfBits bits into each element of an array.
     *  \param[in]  numberOfBits  Bits per element.
     *  \param[out] array         Destination array.
     *  \param[in]  arraySize     Number of elements to read. */
    void       readBits(unsigned int numberOfBits,int *array,unsigned int arraySize);

  protected:

    //bool       readBitNoCheck();

    /*! \brief The size of the bit array/stream. */
    UInt64     mNumberOfBits;

    /*! \brief The current read position of the bit array/stream. */
    UInt64     mReadPosition;

    /*! \brief The pointer to the beginning of the bit array/stream. */
    const unsigned char*  mData;

  public:

    /*! \brief Read and return one bit, advancing the read position.
     *  \return True if the bit is 1; false if 0. */
    inline bool readBit()
    {
      try
      {
        if (mData == nullptr)
          throw Fmi::Exception(BCP,"The 'mData' attribute points to nullptr!");

        if ((mReadPosition + 1) > mNumberOfBits)
        {
          Fmi::Exception exception(BCP,"Cannot read a bit outside of the memory area !");
          exception.addParameter("Read position",std::to_string(mReadPosition));
          exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
          throw exception;
        }

        UInt64 byt = mReadPosition / 8;
        UInt64 bit = 7 - (mReadPosition % 8);

        mReadPosition++;

        if ((1 << bit) & mData[byt])
          return true;

        return false;
      }
      catch (...)
      {
        throw Fmi::Exception(BCP,"Operation failed!",nullptr);
      }
    }

    /*! \brief Read one bit without bounds checking (faster inner-loop variant). */
    inline bool readBitNoCheck()
    {
      try
      {
        UInt64 byt = mReadPosition / 8;
        UInt64 bit = 7 - (mReadPosition % 8);

        mReadPosition++;

        if ((1 << bit) & mData[byt])
          return true;

        return false;
      }
      catch (...)
      {
        throw Fmi::Exception(BCP,"Operation failed!",nullptr);
      }
    }


    /*! \brief Read \p numberOfBits bits and return an unsigned int value.
     *  \param[in]  numberOfBits  Number of bits to read (1–32).
     *  \param[out] value         Receives the decoded unsigned value. */
    inline void readBits(unsigned int numberOfBits,unsigned int& value)
    {
      try
      {
        if (mData == nullptr)
          throw Fmi::Exception(BCP,"The 'mData' attribute points to nullptr!");

        if (numberOfBits > 32)
        {
          Fmi::Exception exception(BCP,"Cannot read more than 32 bits into 'unsigned int'!");
          exception.addParameter("Requested bits",std::to_string(numberOfBits));
          throw exception;
        }

        if ((mReadPosition + numberOfBits) > mNumberOfBits)
        {
          Fmi::Exception exception(BCP,"Cannot read bits outside of the memory area !");
          exception.addParameter("Read position",std::to_string(mReadPosition));
          exception.addParameter("Number of bits",std::to_string(mNumberOfBits));
          exception.addParameter("Requested bits",std::to_string(numberOfBits));
          throw exception;
        }

        value = 0;
        for (unsigned int i=0; i<numberOfBits; i++)
        {
          value = value << 1;

          if (readBitNoCheck())
            value = value + 1;
        }
      }
      catch (...)
      {
        throw Fmi::Exception(BCP,"Operation failed!",nullptr);
      }
    }



};


}
