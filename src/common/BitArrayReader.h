#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>

namespace SmartMet
{


/*!
  \brief The class is used for reading data in bits. The idea is that we
  can read one or several bits at the same time and the read position is updated
  every time when bits are read.

  This class is very useful for example for handling bitmap information or to read
  data which must be handled as bits rather than bytes. For example, when data is
  compressed it is quite typical that information is stored as a sequence of bits
  without caring the byte borders.
*/

class BitArrayReader
{
  public:
               BitArrayReader(const unsigned char *data,ulonglong numberOfBits);
    virtual    ~BitArrayReader();

    ulonglong  getNumberOfBits();
    ulonglong  getReadPosition();
    void       setReadPosition(ulonglong readPosition);
    //bool       readBit();
    void       readBits(unsigned int numberOfBits,int& value);
    // void       readBits(unsigned int numberOfBits,unsigned int& value);
    void       readBits(unsigned int numberOfBits,ulonglong& value);
    void       readBits(unsigned int numberOfBits,int *_array,unsigned int arraySize);

  protected:

    //bool       readBitNoCheck();

    /*! \brief The size of the bit array/stream. */
    ulonglong  mNumberOfBits;

    /*! \brief The current read position of the bit array/stream. */
    ulonglong  mReadPosition;

    /*! \brief The pointer to the beginning of the bit array/stream. */
    const unsigned char*  mData;

  public:

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

        ulonglong byt = mReadPosition / 8;
        ulonglong bit = 7 - (mReadPosition % 8);

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

    inline bool readBitNoCheck()
    {
      try
      {
        ulonglong byt = mReadPosition / 8;
        ulonglong bit = 7 - (mReadPosition % 8);

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


    /*! \brief The method reads a number of bits from the bit array/stream and
        returns the result in the 'value' parameter.

            \param numberOfBits   The number of bits to read.
            \param value          The result value of the read bits.
    */

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
