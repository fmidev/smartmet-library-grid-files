#include "MemoryWriter.h"


namespace SmartMet
{


MemoryWriter::MemoryWriter(uchar *_data,ulonglong _dataSize,bool _dataRelease)
{
  try
  {
    if (_data == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The '_data' parameter points to nullptr!");

    if (_dataSize == 0)
      throw SmartMet::Spine::Exception(BCP,"The value of the '_dataSize' parameter is 0!");

    data = _data;
    dataSize = _dataSize;
    dataRelease = _dataRelease;
    writePosition = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




MemoryWriter::~MemoryWriter()
{
  try
  {
    if (dataRelease  &&  data != nullptr)
      delete [] data;

    data = nullptr;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





ulonglong MemoryWriter::getWritePosition()
{
  try
  {
    return writePosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




void MemoryWriter::setWritePosition(ulonglong _pos)
{
  try
  {
    if (_pos >= dataSize)
      throw SmartMet::Spine::Exception(BCP,"The '_pos' parameter point to out of the data area!");

    writePosition = _pos;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uchar* MemoryWriter::getDataPtr()
{
  try
  {
    return data;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void MemoryWriter::write_data(void *_data,ulonglong _size)
{
  try
  {
    uchar *d = (uchar*)_data;
    if ((writePosition + _size) >= dataSize)
      throw SmartMet::Spine::Exception(BCP,"Trying to write data to outsize of the buffer!");

    for (ulonglong t=0; t< _size; t++)
      data[writePosition + t] = d[t];

    writePosition += _size;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace SmartMet
