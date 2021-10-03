#pragma once

#include "DataWriter.h"


namespace SmartMet
{


class MemoryWriter : public DataWriter
{
  public:
                MemoryWriter(uchar *_data,ulonglong _dataSize,bool _dataRelease);
        ~MemoryWriter() override;

    uchar*      getDataPtr();
    ulonglong   getWritePosition() override;
    ulonglong   getMaxWritePosition() override;
    void        setWritePosition(ulonglong _pos) override;
    void        write_data(void *_data,ulonglong _size) override;

  protected:

    uchar       *mData;
    ulonglong   mDataSize;
    bool        mDataRelease;
    ulonglong   mWritePosition;
    ulonglong   mMaxWritePosition;
};


}  // namespace SmartMet
