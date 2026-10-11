#include "FileWriter.h"


namespace SmartMet
{


/*! \brief Default constructor for FileWriter. */

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





/*! \brief Destructor that closes the file if still open. */

FileWriter::~FileWriter()
{
  try
  {
    if (mFileHandle != nullptr)
      (void)fclose(mFileHandle);

    mFileHandle = nullptr;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief Creates and opens a new file for writing. */

void FileWriter::createFile(const char *_filename)
{
  try
  {
    mFilename = _filename;
    mFileHandle = fopen(_filename,"we");
    if (!mFileHandle)
    {
      Fmi::Exception exception(BCP,"Cannot create a file!");
      exception.addParameter("Filename",mFilename);
      throw exception;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Closes the currently open file. */

void FileWriter::closeFile()
{
  try
  {
    if (mFileHandle != nullptr)
    {
      // Forget the handle first: it must not be closed again if this throws
      FILE *file = mFileHandle;
      mFileHandle = nullptr;
      if (fclose(file) != 0)
        throw Fmi::Exception(BCP,"Failed to close the output file");
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Returns the current write offset in the open file. */

UInt64 FileWriter::getWritePosition()
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





/*! \brief Returns the maximum file offset reached so far. */

UInt64 FileWriter::getMaxWritePosition()
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





/*! \brief Seeks to the given byte offset in the open file. */

void FileWriter::setWritePosition(UInt64 _pos)
{
  try
  {
    if (mFileHandle == nullptr)
      throw Fmi::Exception(BCP,"No file defined!");

    if (fseek(mFileHandle,_pos,SEEK_SET) != 0)
      throw Fmi::Exception(BCP,"Failed to seek in the file");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief Writes a block of raw bytes to the open file. */

void FileWriter::write_data(void *_data,UInt64 _size)
{
  try
  {
    if (mFileHandle == nullptr)
      throw Fmi::Exception(BCP,"No file defined!");

    if (fwrite(_data,_size,1,mFileHandle) != 1)
      throw Fmi::Exception(BCP,"Failed to write the file");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace SmartMet
