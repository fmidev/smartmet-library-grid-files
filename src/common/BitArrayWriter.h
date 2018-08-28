#pragma once

#include "Exception.h"
#include "Typedefs.h"

namespace SmartMet
{


class BitArrayWriter
{
  public:
                BitArrayWriter(unsigned char *data,ulonglong numberOfBits);
    virtual     ~BitArrayWriter();

    ulonglong   getNumberOfBits();
    ulonglong   getWritePosition();
    void        setWritePosition(ulonglong writePosition);
    void        writeBit(bool bitOn);
    void        writeBits(unsigned int numberOfBits,ulonglong value);

  protected:

    void        writeBitNoCheck(bool bitOn);

    /*! \brief The size of the bit array/stream. */
    ulonglong   mNumberOfBits;

    /*! \brief The current write position of the bit array/stream. */
    ulonglong   mWritePosition;

    /*! \brief The pointer to the beginning of the bit array/stream. */
    unsigned char*  mData;
};


}
