#pragma once

#include "DataWriter.h"


namespace SmartMet
{


class MemoryWriter : public DataWriter
{
  public:
                MemoryWriter(uchar *_data,UInt64 _dataSize,bool _dataRelease);
    virtual     ~MemoryWriter();

    uchar*      getDataPtr();
    UInt64      getWritePosition();
    UInt64      getMaxWritePosition();
    void        setWritePosition(UInt64 _pos);
    void        write_data(void *_data,UInt64 _size);

  protected:

    uchar       *mData;
    UInt64      mDataSize;
    bool        mDataRelease;
    UInt64      mWritePosition;
    UInt64      mMaxWritePosition;
};


}  // namespace SmartMet
