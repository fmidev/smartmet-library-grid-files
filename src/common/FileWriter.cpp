#include "FileWriter.h"


namespace SmartMet
{


FileWriter::FileWriter()
{
  try
  {
    mFileHandle = nullptr;
    mMaxFilePosition = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





void FileWriter::createFile(const char *_filename)
{
  try
  {
    mFilename = _filename;
    mFileHandle = fopen(_filename,"we");
    if (mFileHandle)
    {
      Fmi::Exception exception(BCP,"Cannot create a file!");
      exception.addParameter("Filename",mFilename);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





ulonglong FileWriter::getWritePosition()
{
  try
  {
    if (mFileHandle == nullptr)
      throw Fmi::Exception(BCP,"No file defined!");

    return ftell(mFileHandle);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





ulonglong FileWriter::getMaxWritePosition()
{
  try
  {
    if (mFileHandle == nullptr)
      throw Fmi::Exception(BCP,"No file defined!");

    return mMaxFilePosition;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void FileWriter::setWritePosition(ulonglong _pos)
{
  try
  {
    if (mFileHandle == nullptr)
      throw Fmi::Exception(BCP,"No file defined!");

    fseek(mFileHandle,_pos,SEEK_SET);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void FileWriter::write_data(void *_data,ulonglong _size)
{
  try
  {
    if (mFileHandle == nullptr)
      throw Fmi::Exception(BCP,"No file defined!");

    fwrite(_data,_size,1,mFileHandle);
/*
    ulonglong fp = ftell(mFileHandle);
    if (fp > mMaxFilePosition)
      mMaxFilePosition = fp;
*/
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace SmartMet
