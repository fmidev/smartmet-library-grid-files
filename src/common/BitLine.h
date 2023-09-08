#pragma once

#include <stdlib.h>
#include <stdio.h>

namespace SmartMet
{

typedef unsigned char uchar;
typedef unsigned int uint;


// This is a data structure that can be used in order to store big bitmaps that contain
// large areas of the same bit values (for example land-sea -mask). The idea is that this
// structure knows location of the bit value changes in the bit sequence, and can count
// bit values for each bitmap position according to this information. For example if the bitmap
// size is 65000 x 65000 (= 4 225 000 000 bits) and it contains 10 000 000 changes, then we
// need only 40 MB in order to store this infomation.


class BitLine 
{
  public:
                        BitLine();
                        BitLine(uchar *bits,uint numOfBits);
                        BitLine(BitLine& bitLine);
    virtual             ~BitLine();

    virtual void        operator=(BitLine& bitLine);

    virtual uint        getChangeCount();
    virtual uint        getChangeCount(uint startPos,uint endPos);
    virtual uint        getChange(uint index);
    virtual uint        getChanges(uint startPos,uint endPos,uint* changePositions);
    virtual uint        getLength();
    virtual uint        getMaxChange();

    virtual bool        isAllZeros();
    virtual bool        isAllOnes();

    virtual void        setValue(uchar *bits,uint numOfBits);
    virtual void        setValue(uint numOfBits,uint* changePositions,uint numOfChanges,bool release);

    virtual void        readFromFile(FILE *file);
    virtual void        readFromFile(const char *filename);

    virtual void        writeToFile(FILE *file);
    virtual void        writeToFile(const char *filename);

  protected:

    uint                *changes;
    uint                changeCount;
    uint                length;

  public:

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
