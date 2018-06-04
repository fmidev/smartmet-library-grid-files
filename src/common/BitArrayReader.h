#pragma once

#include "Exception.h"

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
                          BitArrayReader(const unsigned char *data,unsigned long long numberOfBits);
    virtual               ~BitArrayReader();

    unsigned long long    getNumberOfBits();
    unsigned long long    getReadPosition();
    void                  setReadPosition(unsigned long long readPosition);
    bool                  readBit();
    void                  readBits(unsigned int numberOfBits,int& value);
    void                  readBits(unsigned int numberOfBits,unsigned int& value);
    void                  readBits(unsigned int numberOfBits,unsigned long long& value);
    void                  readBits(unsigned int numberOfBits,int *_array,unsigned int arraySize);

  protected:

    bool                  readBitNoCheck();

    /*! \brief The size of the bit array/stream. */
    unsigned long long    mNumberOfBits;

    /*! \brief The current read position of the bit array/stream. */
    unsigned long long    mReadPosition;

    /*! \brief The pointer to the beginning of the bit array/stream. */
    const unsigned char*  mData;
};


}
