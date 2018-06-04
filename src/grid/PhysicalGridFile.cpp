#include "PhysicalGridFile.h"
#include "../common/Exception.h"
#include "../common/GeneralDefinitions.h"
#include "../common/GeneralFunctions.h"
#include "../identification/GridDef.h"
#include "../grib1/GribFile.h"
#include "../grib2/GribFile.h"

namespace SmartMet
{
namespace GRID
{


/*! \brief The constructor of the class. */

PhysicalGridFile::PhysicalGridFile()
{
  try
  {
    mIsMemoryMapped = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

PhysicalGridFile::~PhysicalGridFile()
{
  try
  {
    if (mMappedFile  &&  mIsMemoryMapped)
      mMappedFile->close();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool PhysicalGridFile::isMemoryMapped() const
{
  try
  {
    if (mGridFile)
      return mGridFile->isMemoryMapped();

    return mIsMemoryMapped;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void PhysicalGridFile::mapToMemory()
{
  try
  {
    if (mGridFile)
      mGridFile->mapToMemory();
    else
    {
      if (!mIsMemoryMapped)
        read(mFileName);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool PhysicalGridFile::isPhysical() const
{
  try
  {
    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





bool PhysicalGridFile::isVirtual() const
{
  try
  {
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
  try
  {
    // Safety checks

    auto fsize = getFileSize(filename.c_str());
    if (fsize < 0)
      throw SmartMet::Spine::Exception(BCP,"The file '" + filename + "' does not exist!");

    setFileName(filename);

    // Map the entire file

    MappedFileParams params(filename);
    params.flags = boost::iostreams::mapped_file::readonly;
    params.length = fsize;
    mMappedFile.reset(new MappedFile(params));
    mIsMemoryMapped = true;
    mFileModificationTime = getFileModificationTime(mFileName.c_str());

    //mMapping.reset(new bi::file_mapping(path.c_str(), bi::read_only));
    // mRegion.reset(new bi::mapped_region(*mMapping, bi::read_only, 0, fsize));

    auto startAddr = const_cast<char*>(mMappedFile->const_data());
    auto endAddr = startAddr + fsize;

    MemoryReader memoryReader((unsigned char*)startAddr,(unsigned char*)endAddr);

    T::FileType fileType = getFileType(memoryReader);

    switch (fileType)
    {
      case T::FileType::Grib1:
      {
        auto file = new GRIB1::GribFile();
        file->setFileName(filename);
        file->setFileId(mFileId);
        file->setGroupFlags(mGroupFlags);
        file->setProducerId(mProducerId);
        file->setGenerationId(mGenerationId);
        file->setCheckTime(mCheckTime);
        mGridFile.reset(file);
        file->read(memoryReader);
      }
      break;

      case T::FileType::Grib2:
      {
        auto file = new GRIB2::GribFile();
        file->setFileName(filename);
        file->setFileId(mFileId);
        file->setGroupFlags(mGroupFlags);
        file->setProducerId(mProducerId);
        file->setGenerationId(mGenerationId);
        file->setCheckTime(mCheckTime);
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
    SmartMet::Spine::Exception exception(BCP,"Read failed!",NULL);
    exception.addParameter("File name ",filename);
    throw exception;
  }
}





/*! \brief This method is used in order to detect the type of the current file. Technically
    the method reads few bytes from the beginning of the file and tries to recognize
    the used file type

        \param memoryReader  This object controls the access to the memory mapped file.
*/

T::FileType PhysicalGridFile::getFileType(MemoryReader& memoryReader)
{
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
        return T::FileType::Grib1;

      if (d[7] == 2)
        return T::FileType::Grib2;

    }
    return T::FileType::Unknown;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





ulonglong PhysicalGridFile::searchFileStartPosition(MemoryReader& memoryReader)
{
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
    throw SmartMet::Spine::Exception(BCP,"Message search failed!",NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void PhysicalGridFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << "PhysicalGridFile\n";
    GridFile::print(stream,level+1,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




}  // namespace GRID
}  // namespace SmartMet
