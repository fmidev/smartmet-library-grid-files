#pragma once

#include "DataWriter.h"


namespace SmartMet
{


class MemoryWriter : public DataWriter
{
  public:
                MemoryWriter(uchar *_data,ulonglong _dataSize,bool _dataRelease);
    virtual     ~MemoryWriter();

    uchar*      getDataPtr();
    ulonglong   getWritePosition();
    ulonglong   getMaxWritePosition();
    void        setWritePosition(ulonglong _pos);
    void        write_data(void *_data,ulonglong _size);

  protected:

    uchar       *mData;
    ulonglong   mDataSize;
    bool        mDataRelease;
    ulonglong   mWritePosition;
    ulonglong   mMaxWritePosition;
};


}  // namespace SmartMet
