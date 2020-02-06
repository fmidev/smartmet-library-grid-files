#include "PhysicalGridFile.h"
#include "../common/Exception.h"
#include "../common/GeneralDefinitions.h"
#include "../common/GeneralFunctions.h"
#include "../common/ShowFunction.h"
#include "../identification/GridDef.h"
#include "../grib1/GribFile.h"
#include "../grib2/GribFile.h"


#define FUNCTION_TRACE FUNCTION_TRACE_OFF


namespace SmartMet
{
namespace GRID
{


/*! \brief The constructor of the class. */

PhysicalGridFile::PhysicalGridFile()
{
  FUNCTION_TRACE
  try
  {
    mIsMemoryMapped = false;
    mIsRead = false;
    mMemoryPtr = nullptr;
    mFileSize = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

PhysicalGridFile::PhysicalGridFile(const PhysicalGridFile& other)
:GridFile(other)
{
  FUNCTION_TRACE
  try
  {
    mIsMemoryMapped = false;
    mIsRead = false;
    mMemoryPtr = nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Copy constructor failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

PhysicalGridFile::~PhysicalGridFile()
{
  FUNCTION_TRACE
  try
  {
    if (mMappedFile  &&  mIsMemoryMapped)
      mMappedFile->close();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





bool PhysicalGridFile::isMemoryMapped() const
{
  FUNCTION_TRACE
  try
  {
    if (mGridFile)
      return mGridFile->isMemoryMapped();

    return mIsMemoryMapped;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void PhysicalGridFile::mapToMemory()
{
  FUNCTION_TRACE
  try
  {
    if (mGridFile)
    {
      mGridFile->mapToMemory();
    }
    else
    {
      if (!mIsMemoryMapped)
      {
        read();

        if (mGridFile  &&  mMessagePositions.size() > 0)
        {
          // Now we know the type of the grid file. So we can add predefined
          // message positions into it.

          for (auto it = mMessagePositions.begin(); it != mMessagePositions.end(); ++it)
          {
            mGridFile->newMessage(it->first,it->second,0);
          }
          mMessagePositions.clear();
        }
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool PhysicalGridFile::isPhysical() const
{
  FUNCTION_TRACE
  try
  {
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool PhysicalGridFile::isVirtual() const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





long long PhysicalGridFile::getSize()
{
  FUNCTION_TRACE
  try
  {
    if (!isMemoryMapped())
      mapToMemory();

    return mFileSize;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





char* PhysicalGridFile::getMemoryPtr()
{
  FUNCTION_TRACE
  try
  {
    if (!isMemoryMapped())
      mapToMemory();

    return mMemoryPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void PhysicalGridFile::setMemoryPtr(char *memoryPtr,long long size)
{
  FUNCTION_TRACE
  try
  {
    mMemoryPtr = memoryPtr;
    mFileSize = size;
    mIsMemoryMapped = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}







/*! \brief The method memory maps the given file and after that it tries to
    recognize the type of the file. It creates and initializes GRIB1::PhysicalGridFile
    or GRIB2::PhysicalGridFile object according to the file type. This object represents
    the actual content of the current file.
*/

void PhysicalGridFile::read()
{
  FUNCTION_TRACE
  try
  {
    if (mIsRead)
      return;  // Already read

    if (!mIsMemoryMapped)
    {
      AutoThreadLock lock(&mMemoryMappingLock);

      if (!mIsMemoryMapped)
      {
        mFileSize = getFileSize(mFileName.c_str());
        if (mFileSize < 0)
          throw SmartMet::Spine::Exception(BCP,"The file '" + mFileName + "' does not exist!");

        MappedFileParams params(mFileName);
        params.flags = boost::iostreams::mapped_file::readonly;
        params.length = mFileSize;
        mMappedFile.reset(new MappedFile(params));
        mIsMemoryMapped = true;
        mFileModificationTime = getFileModificationTime(mFileName.c_str());

        mMemoryPtr = const_cast<char*>(mMappedFile->const_data());
      }
    }

    auto endAddr = mMemoryPtr + mFileSize;


    MemoryReader memoryReader(reinterpret_cast<unsigned char*>(mMemoryPtr),reinterpret_cast<unsigned char*>(endAddr));

    uchar fileType = readFileType(memoryReader);

    switch (fileType)
    {
      case T::FileTypeValue::Grib1:
      {
        auto file = new GRIB1::GribFile();
        file->setFileName(mFileName);
        file->setFileId(mFileId);
        file->setPointCacheEnabled(mPointCacheEnabled);
        file->setGroupFlags(mGroupFlags);
        file->setProducerId(mProducerId);
        file->setGenerationId(mGenerationId);
        file->setCheckTime(mCheckTime);
        file->setMemoryPtr(mMemoryPtr,mFileSize);
        mGridFile.reset(file);
      }
      break;

      case T::FileTypeValue::Grib2:
      {
        auto file = new GRIB2::GribFile();
        file->setFileName(mFileName);
        file->setFileId(mFileId);
        file->setPointCacheEnabled(mPointCacheEnabled);
        file->setGroupFlags(mGroupFlags);
        file->setProducerId(mProducerId);
        file->setGenerationId(mGenerationId);
        file->setCheckTime(mCheckTime);
        file->setMemoryPtr(mMemoryPtr,mFileSize);
        mGridFile.reset(file);
      }
      break;

      default:
        throw SmartMet::Spine::Exception(BCP,"Unknown file type!");
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Read failed!",nullptr);
    exception.addParameter("File name ",mFileName);
    throw exception;
  }
}





/*! \brief The method memory maps the given file and after that it tries to
    recognize the type of the file. It creates and initializes GRIB1::PhysicalGridFile
    or GRIB2::PhysicalGridFile object according to the file type. This object represents
    the actual content of the current file.

       \param filename  The grib filename with a possible directory path.
*/

void PhysicalGridFile::read(std::string filename)
{
  FUNCTION_TRACE
  try
  {
    if (mIsRead)
      return;  // Already read

    setFileName(filename);

    if (!mIsMemoryMapped)
    {
      AutoThreadLock lock(&mMemoryMappingLock);

      if (!mIsMemoryMapped)
      {
        mFileSize = getFileSize(mFileName.c_str());
        if (mFileSize < 0)
          throw SmartMet::Spine::Exception(BCP,"The file '" + mFileName + "' does not exist!");

        MappedFileParams params(mFileName);
        params.flags = boost::iostreams::mapped_file::readonly;
        params.length = mFileSize;
        mMappedFile.reset(new MappedFile(params));
        mIsMemoryMapped = true;
        mFileModificationTime = getFileModificationTime(mFileName.c_str());

        mMemoryPtr = const_cast<char*>(mMappedFile->const_data());
      }
    }

    auto endAddr = mMemoryPtr + mFileSize;


    MemoryReader memoryReader(reinterpret_cast<unsigned char*>(mMemoryPtr),reinterpret_cast<unsigned char*>(endAddr));

    uchar fileType = readFileType(memoryReader);

    switch (fileType)
    {
      case T::FileTypeValue::Grib1:
      {
        auto file = new GRIB1::GribFile();
        file->setFileName(filename);
        file->setFileId(mFileId);
        file->setPointCacheEnabled(mPointCacheEnabled);
        file->setGroupFlags(mGroupFlags);
        file->setProducerId(mProducerId);
        file->setGenerationId(mGenerationId);
        file->setCheckTime(mCheckTime);
        file->setMemoryPtr(mMemoryPtr,mFileSize);
        mGridFile.reset(file);
        file->read(memoryReader);
      }
      break;

      case T::FileTypeValue::Grib2:
      {
        auto file = new GRIB2::GribFile();
        file->setFileName(filename);
        file->setFileId(mFileId);
        file->setPointCacheEnabled(mPointCacheEnabled);
        file->setGroupFlags(mGroupFlags);
        file->setProducerId(mProducerId);
        file->setGenerationId(mGenerationId);
        file->setCheckTime(mCheckTime);
        file->setMemoryPtr(mMemoryPtr,mFileSize);
        mGridFile.reset(file);
        file->read(memoryReader);
      }
      break;

      default:
        throw SmartMet::Spine::Exception(BCP,"Unknown file type!");
    }
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Read failed!",nullptr);
    exception.addParameter("File name ",filename);
    throw exception;
  }
}





void PhysicalGridFile::write(std::string filename)
{
  FUNCTION_TRACE
  try
  {
    if (mGridFile)
      mGridFile->write(filename);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Write failed!",nullptr);
    exception.addParameter("File name ",filename);
    throw exception;
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void PhysicalGridFile::write(DataWriter& dataWriter)
{
  FUNCTION_TRACE
  try
  {
    if (mGridFile)
      mGridFile->write(dataWriter);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Write failed!",nullptr);
    throw exception;
  }
}




/*! \brief This method is used in order to detect the type of the current file. Technically
    the method reads few bytes from the beginning of the file and tries to recognize
    the used file type

        \param memoryReader  This object controls the access to the memory mapped file.
*/

uchar PhysicalGridFile::readFileType(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    memoryReader.setReadPosition(0);

    unsigned long long pos = searchFileStartPosition(memoryReader);
    memoryReader.setReadPosition(pos);

    unsigned char d[8];
    memoryReader.read_data(d,8);
    memoryReader.setReadPosition(0);

    if (d[0] == 'G'  &&  d[1] == 'R'  &&  d[2] == 'I'  &&  d[3] == 'B')
    {
      // This is a grib file.

      if (d[7] == 1)
        return T::FileTypeValue::Grib1;

      if (d[7] == 2)
        return T::FileTypeValue::Grib2;

    }
    return T::FileTypeValue::Unknown;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





ulonglong PhysicalGridFile::searchFileStartPosition(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    std::vector<unsigned char*> gribs;

    // A complete indicator section takes 16 bytes, hence we can stop the loop earlier
    // thus making sure all reads inside the loop succeed.

    while (memoryReader.getReadPtr() < memoryReader.getEndPtr())
    {
      // Usually GRIB2 messages do not have any extra garbage between them, several GRIB1 messages do
      // seem to have it. Most likely it's not worth optimizing this search, we'll just skip one byte
      // at a time.

      long long pos = memoryReader.getReadPosition();

      if (!memoryReader.peek_string("GRIB"))
      {
        memoryReader.read_null(1);
      }
      else
      {
        return pos;
      }
    }
    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Message search failed!",nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void PhysicalGridFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  FUNCTION_TRACE
  try
  {
    stream << "PhysicalGridFile\n";
    GridFile::print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




}  // namespace GRID
}  // namespace SmartMet
