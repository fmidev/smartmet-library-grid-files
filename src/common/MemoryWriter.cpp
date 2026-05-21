#include "MemoryWriter.h"


namespace SmartMet
{


/*! \brief Constructs a MemoryWriter over the given buffer of the given size. */

MemoryWriter::MemoryWriter(uchar *_data,UInt64 _dataSize,bool _dataRelease)
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




/*! \brief Destructor that releases the buffer if owned. */

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





/*! \brief Returns the current write offset in the buffer. */

UInt64 MemoryWriter::getWritePosition()
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




/*! \brief Returns the maximum buffer offset reached so far. */

UInt64 MemoryWriter::getMaxWritePosition()
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




/*! \brief Sets the current write offset in the buffer. */

void MemoryWriter::setWritePosition(UInt64 _pos)
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





/*! \brief Returns a pointer to the underlying buffer. */

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





/*! \brief Writes a block of bytes into the buffer at the current write position. */

void MemoryWriter::write_data(void *_data,UInt64 _size)
{
  try
  {
    uchar *d = (uchar*)_data;
    if ((mWritePosition + _size) >= mDataSize)
      throw Fmi::Exception(BCP,"Trying to write data to outsize of the buffer!");

    for (UInt64 t=0; t< _size; t++)
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
