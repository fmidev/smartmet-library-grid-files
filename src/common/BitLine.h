#pragma once

#include <stdlib.h>
#include <stdio.h>

namespace SmartMet
{

typedef unsigned char uchar;
typedef unsigned int uint;


// ====================================================================================
/*! \brief Run-length-encoded bit array optimised for large sparse bitmaps.
 *
 *  Instead of storing every bit, stores only the positions where the bit value
 *  changes (a "change list").  For a 65000×65000 bitmap with 10 million transitions
 *  this takes ~40 MB rather than ~500 MB.  Used for land/sea masks and topography
 *  bitmaps in the grid subsystem. */
// ====================================================================================

class BitLine
{
  public:
    /*! \brief Construct an empty bit line (all zeros, length zero). */
                        BitLine();

    /*! \brief Construct by encoding a raw bitmap.
     *  \param[in] bits       Source byte array (MSB-first bit order).
     *  \param[in] numOfBits  Number of bits to encode. */
                        BitLine(uchar *bits,uint numOfBits);

    /*! \brief Copy constructor. */
                        BitLine(BitLine& bitLine);
    virtual             ~BitLine();

    /*! \brief Copy assignment. */
    virtual void        operator=(BitLine& bitLine);

    /*! \brief Return the total number of change positions in the change list. */
    virtual uint        getChangeCount();

    /*! \brief Return the number of change positions within [startPos, endPos].
     *  \param[in] startPos  Start of the query range (inclusive, zero-based).
     *  \param[in] endPos    End of the query range (inclusive). */
    virtual uint        getChangeCount(uint startPos,uint endPos);

    /*! \brief Return the change position at the given index.
     *  \param[in] index  Zero-based index into the change list.
     *  \return Bit position of the change. */
    virtual uint        getChange(uint index);

    /*! \brief Fill \p changePositions with all changes in [startPos, endPos].
     *  \param[in]  startPos         Start of the range (inclusive).
     *  \param[in]  endPos           End of the range (inclusive).
     *  \param[out] changePositions  Caller-allocated array to receive the positions.
     *  \return Number of changes found. */
    virtual uint        getChanges(uint startPos,uint endPos,uint* changePositions);

    /*! \brief Return the length (total number of bits). */
    virtual uint        getLength();

    /*! \brief Return the maximum change position stored. */
    virtual uint        getMaxChange();

    /*! \brief Return true if all bits are 0. */
    virtual bool        isAllZeros();

    /*! \brief Return true if all bits are 1. */
    virtual bool        isAllOnes();

    /*! \brief Encode a raw bitmap into this BitLine.
     *  \param[in] bits       Source byte array (MSB-first bit order).
     *  \param[in] numOfBits  Number of bits to encode. */
    virtual void        setValue(uchar *bits,uint numOfBits);

    /*! \brief Initialise from a pre-computed change list.
     *  \param[in] numOfBits        Total bit length.
     *  \param[in] changePositions  Array of bit positions where the value changes.
     *  \param[in] numOfChanges     Number of entries in \p changePositions.
     *  \param[in] release          If true, take ownership of \p changePositions. */
    virtual void        setValue(uint numOfBits,uint* changePositions,uint numOfChanges,bool release);

    /*! \brief Deserialise this BitLine from an open binary FILE.
     *  \param[in] file  Open file positioned at the serialised data. */
    virtual void        readFromFile(FILE *file);

    /*! \brief Deserialise this BitLine from a file path.
     *  \param[in] filename  Path to the serialised file. */
    virtual void        readFromFile(const char *filename);

    /*! \brief Serialise this BitLine to an open binary FILE.
     *  \param[in] file  Open file to write into. */
    virtual void        writeToFile(FILE *file);

    /*! \brief Serialise this BitLine to a file path.
     *  \param[in] filename  Output path. */
    virtual void        writeToFile(const char *filename);

  protected:

    uint                *changes;     //!< Sorted array of bit-change positions
    uint                changeCount;  //!< Number of entries in changes[]
    uint                length;       //!< Total bit length of the encoded sequence

  public:

    /*! \brief Return the bit value at position \p index.
     *  \param[in] index  Zero-based bit position.
     *  \return True if the bit is 1; false if 0 or out of range. */
    inline bool getBit(uint index)
    {
      if (index >= length || changeCount == 0)
        return false;

      if (changeCount == 1  &&  changes[0] == 0)
        return true;

      uint idx = getClosestIndex(index);
      uint val = changes[idx];

      if (val > index)
        return false;

      if ((idx % 2) == 0)
        return true;

      return false;
    }
    
    
    inline int compare(uint v1,uint v2)
    {
      if (v1 == v2)
        return 0;

      if (v1 < v2)
        return -1;
      
      return 1;
    }


    /*! \brief Binary-search the change list for the index closest to \p _value.
     *  \param[in] _value  Bit position to search for.
     *  \return Index into changes[] of the closest preceding or equal entry. */
    inline uint getClosestIndex(uint _value)
    {
      if (changes == nullptr  ||  changeCount == 0)
        return 0;

      int low = 0;
      int high = (int)changeCount - 1;
      int mid = 0;

      while (low <= high)
      {
        mid = (low + high) / 2;
        int res = compare(changes[mid],_value);

        if (res == 0)
          return (uint)mid;

        if (res < 0)
          low = mid + 1;
        else
          high = mid - 1;
      }

      if (mid >= 0  &&  mid < (int)changeCount)
      {
        int res = compare(changes[mid],_value);

        if (mid > 0  &&  res > 0)
          return (uint)(mid - 1);
        else
          return (uint)mid;
      }

      return 0;
    }


  protected:
    
    inline bool getBit(uchar *_bits,uint _pos)
    {
      uint bt = _pos / 8;
      uint bit = _pos % 8;
  
      uchar v = 1 << bit;
  
      if (_bits[bt] & v)
        return true;
  
      return false;  
    }

};

}
