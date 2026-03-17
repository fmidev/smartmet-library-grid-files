#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>

namespace SmartMet
{


class BitArrayWriter
{
  public:
                BitArrayWriter(unsigned char *data,UInt64 numberOfBits);
    virtual     ~BitArrayWriter();

    UInt64      getNumberOfBits();
    UInt64      getWritePosition();
    void        setWritePosition(UInt64 writePosition);
    void        writeBit(bool bitOn);
    void        writeBits(unsigned int numberOfBits,UInt64 value);

  protected:

    void        writeBitNoCheck(bool bitOn);

    /*! \brief The size of the bit array/stream. */
    UInt64      mNumberOfBits;

    /*! \brief The current write position of the bit array/stream. */
    UInt64      mWritePosition;

    /*! \brief The pointer to the beginning of the bit array/stream. */
    unsigned char*  mData;
};


}
