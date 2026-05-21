#pragma once

#include "Typedefs.h"
#include <macgyver/Exception.h>

namespace SmartMet
{


// ====================================================================================
/*! \brief Sequential bit-level writer into a byte array.
 *
 *  MSB-first bit packing; the complement of `BitArrayReader`.  Used by GRIB
 *  packing algorithms that write variable-width integer fields. */
// ====================================================================================

class BitArrayWriter
{
  public:
    /*! \brief Construct a writer over a bit buffer.
     *  \param[in] data          Destination byte array (caller-allocated).
     *  \param[in] numberOfBits  Total writable bit capacity. */
                BitArrayWriter(unsigned char *data,UInt64 numberOfBits);
    virtual     ~BitArrayWriter();

    /*! \brief Return the total writable bit capacity. */
    UInt64      getNumberOfBits();
    /*! \brief Return the current bit write position. */
    UInt64      getWritePosition();
    /*! \brief Set the current bit write position.
     *  \param[in] writePosition  New position (zero-based bit index). */
    void        setWritePosition(UInt64 writePosition);

    /*! \brief Write a single bit and advance the write position.
     *  \param[in] bitOn  True to write 1; false to write 0. */
    void        writeBit(bool bitOn);

    /*! \brief Write the low \p numberOfBits bits of \p value MSB-first.
     *  \param[in] numberOfBits  Number of bits to write (1–64).
     *  \param[in] value         Source value. */
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
