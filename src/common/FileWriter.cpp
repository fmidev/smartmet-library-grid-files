#include "FileWriter.h"


namespace SmartMet
{


FileWriter::FileWriter()
{
  try
  {
    mFileHandle = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





FileWriter::~FileWriter()
{
  try
  {
    if (mFileHandle != nullptr)
      fclose(mFileHandle);

    mFileHandle = nullptr;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void FileWriter::createFile(const char *_filename)
{
  try
  {
    mFilename = _filename;
    mFileHandle = fopen(_filename,"w");
    if (mFileHandle)
    {
      SmartMet::Spine::Exception exception(BCP,"Cannot create a file!");
      exception.addParameter("Filename",mFilename);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void FileWriter::closeFile()
{
  try
  {
    if (mFileHandle != nullptr)
      fclose(mFileHandle);

    mFileHandle = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ulonglong FileWriter::getWritePosition()
{
  try
  {
    if (mFileHandle == nullptr)
      throw SmartMet::Spine::Exception(BCP,"No file defined!");

    return ftell(mFileHandle);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void FileWriter::setWritePosition(ulonglong _pos)
{
  try
  {
    if (mFileHandle == nullptr)
      throw SmartMet::Spine::Exception(BCP,"No file defined!");

    fseek(mFileHandle,_pos,SEEK_SET);

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void FileWriter::write_data(void *_data,ulonglong _size)
{
  try
  {
    if (mFileHandle == nullptr)
      throw SmartMet::Spine::Exception(BCP,"No file defined!");

    fwrite(_data,_size,1,mFileHandle);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace SmartMet
