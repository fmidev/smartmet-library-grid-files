#include "MemoryWriter.h"


namespace SmartMet
{


MemoryWriter::MemoryWriter(uchar *_data,ulonglong _dataSize,bool _dataRelease)
{
  try
  {
    if (_data == nullptr)
      throw Fmi::Exception(BCP,"The '_data' parameter points to nullptr!");

    if (_dataSize == 0)
      throw Fmi::Exception(BCP,"The value of the '_dataSize' parameter is 0!");

    mData = _data;
    mDataSize = _dataSize;
    mDataRelease = _dataRelease;
    mWritePosition = 0;
    mMaxWritePosition = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




MemoryWriter::~MemoryWriter()
{
  try
  {
    if (mDataRelease  &&  mData != nullptr)
      delete [] mData;

    mData = nullptr;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





ulonglong MemoryWriter::getWritePosition()
{
  try
  {
    return mWritePosition;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




ulonglong MemoryWriter::getMaxWritePosition()
{
  try
  {
    return mMaxWritePosition;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void MemoryWriter::setWritePosition(ulonglong _pos)
{
  try
  {
    if (_pos >= mDataSize)
      throw Fmi::Exception(BCP,"The '_pos' parameter point to out of the data area!");

    mWritePosition = _pos;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





uchar* MemoryWriter::getDataPtr()
{
  try
  {
    return mData;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void MemoryWriter::write_data(void *_data,ulonglong _size)
{
  try
  {
    auto *d = (uchar*)_data;
    if ((mWritePosition + _size) >= mDataSize)
      throw Fmi::Exception(BCP,"Trying to write data to outsize of the buffer!");

    for (ulonglong t=0; t< _size; t++)
      mData[mWritePosition + t] = d[t];

    mWritePosition += _size;

    if (mWritePosition > mMaxWritePosition)
      mMaxWritePosition = mWritePosition;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace SmartMet
