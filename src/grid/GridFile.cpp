#include "GridFile.h"
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

GridFile::GridFile()
{
  try
  {
    //mIsMemoryMapped = false;
    mCheckTime = 0;
    mFileId = 0;
    mGroupFlags = 0;
    mProducerId = 0;
    mGenerationId = 0;
    mCheckTime = 0;
    mSourceId = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

GridFile::GridFile(const GridFile& other)
{
  try
  {
    mFileName = other.mFileName;
    mFileId = other.mFileId;
    mFileModificationTime = other.mFileModificationTime;
    mFileDeletionTime = other.mFileDeletionTime;
    mGroupFlags = other.mGroupFlags;
    mProducerId = other.mProducerId;
    mGenerationId = other.mGenerationId;
    mSourceId = other.mSourceId;
    mCheckTime = other.mCheckTime;
    mUserList = other.mUserList;

    if (other.mGridFile)
      mGridFile.reset(other.mGridFile->createGridFile());

    //std::shared_ptr<GridFile>   mGridFile;    // The actual implementation of GRIB1/GRIB2/Virtual-file.

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





GridFile::GridFile(GridFile *gridFile)
{
  try
  {
    mCheckTime = 0;
    mFileId = 0;
    mGroupFlags = 0;
    mProducerId = 0;
    mGenerationId = 0;
    mCheckTime = 0;
    mSourceId = 0;

    mGridFile.reset(gridFile);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}




/*! \brief The destructor of the class. */

GridFile::~GridFile()
{
  try
  {
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





GridFile* GridFile::createGridFile()
{
  throw SmartMet::Spine::Exception(BCP,"Not implemented!");
}





uint GridFile::getFileId() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getFileId();

    return mFileId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint GridFile::getGroupFlags() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getGroupFlags();

    return mGroupFlags;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint GridFile::getProducerId() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getProducerId();

    return mProducerId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint GridFile::getGenerationId() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getGenerationId();

    return mGenerationId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::shared_ptr<GridFile> GridFile::getGridFile()
{
  try
  {
    return mGridFile;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





time_t GridFile::getCheckTime() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getCheckTime();

    return mCheckTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





time_t GridFile::getModificationTime() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getModificationTime();

    return mFileModificationTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::string GridFile::getDeletionTime() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getDeletionTime();

    return mFileDeletionTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





uint GridFile::getSourceId() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getSourceId();

    return mSourceId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::addDependence(uint fileId)
{
  try
  {
    if (mGridFile)
      mGridFile->addDependence(fileId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridFile::hasDependence(uint fileId)
{
  try
  {
    if (mGridFile)
      return hasDependence(fileId);

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::addUser(uint fileId)
{
  try
  {
    if (mGridFile)
    {
      mGridFile->addUser(fileId);
      return;
    }

    if (mUserList.find(fileId) == mUserList.end())
      mUserList.insert(fileId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::deleteUsers()
{
  try
  {
    if (mGridFile)
    {
      mGridFile->deleteUsers();
      return;
    }

    mUserList.clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::getUsers(std::set<uint>& userList)
{
  try
  {
    if (mGridFile)
    {
      mGridFile->getUsers(userList);
      return;
    }

    userList = mUserList;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridFile::isMemoryMapped() const
{
  try
  {
    if (mGridFile)
      return mGridFile->isMemoryMapped();

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::mapToMemory()
{
  try
  {
    if (mGridFile)
      mGridFile->mapToMemory();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridFile::isPhysical() const
{
  try
  {
    if (mGridFile)
      return mGridFile->isPhysical();

    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridFile::isVirtual() const
{
  try
  {
    if (mGridFile)
      return mGridFile->isVirtual();

    return true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setGridFile(GridFile *gridFile)
{
  try
  {
    mGridFile.reset(gridFile);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setCheckTime(time_t checkTime)
{
  try
  {
    mCheckTime = checkTime;
    if (mGridFile)
      mGridFile->setCheckTime(checkTime);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setFileId(uint fileId)
{
  try
  {
    mFileId = fileId;
    if (mGridFile)
      mGridFile->setFileId(fileId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setDeletionTime(std::string deletionTime)
{
  try
  {
    mFileDeletionTime = deletionTime;
    if (mGridFile)
      mGridFile->setDeletionTime(deletionTime);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setGroupFlags(uint groupFlags)
{
  try
  {
    mGroupFlags = groupFlags;
    if (mGridFile)
      mGridFile->setGroupFlags(groupFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setProducerId(uint producerId)
{
  try
  {
    mProducerId = producerId;
    if (mGridFile)
      mGridFile->setProducerId(producerId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}






void GridFile::setGenerationId(uint generationId)
{
  try
  {
    mGenerationId = generationId;
    if (mGridFile)
      mGridFile->setGenerationId(generationId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setFileName(std::string fileName)
{
  try
  {
    mFileName = fileName;
    mFileModificationTime = time(nullptr); //getFileModificationTime(fileName.c_str());
    if (mGridFile)
      mGridFile->setFileName(fileName);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setSourceId(uint sourceId)
{
  try
  {
    mSourceId = sourceId;
    if (mGridFile)
      mGridFile->setSourceId(sourceId);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





Message* GridFile::newMessage()
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"No grid file defined!");

    return mGridFile->newMessage();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::addMessage(Message *message)
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"No grid file defined!");

    mGridFile->addMessage(message);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setGridFile(uchar fileType)
{
  try
  {
    switch (fileType)
    {
      case T::FileTypeValue::Unknown:
        break;

      case T::FileTypeValue::Grib1:
        mGridFile.reset(new GRIB1::GribFile());
        break;

      case T::FileTypeValue::Grib2:
        mGridFile.reset(new GRIB2::GribFile());
        break;

      case T::FileTypeValue::Virtual:
        break;
    };
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::read(std::string filename)
{
  try
  {
    if (mGridFile)
      mGridFile->read(filename);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Read failed!",nullptr);
    exception.addParameter("File name ",filename);
    throw exception;
  }
}





void GridFile::write(std::string filename)
{
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





void GridFile::write(DataWriter& dataWriter)
{
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





/*! \brief The method returns the name and the path of the file.

       \return  The method returns the name and the path of the file.
*/

std::string GridFile::getFileName() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getFileName();

    return mFileName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method can be used in order to find out the number
    of the message in the current file.

       \return  The number of the messages in current the file.
*/

std::size_t GridFile::getNumberOfMessages()
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to nullptr!");

    return mGridFile->getNumberOfMessages();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method can be used in order to get pointer to the message object
    according to its index. The current message pointer can be used for accessing
    data inside the current message.

        \param index  The message index (0..N).
*/

GRID::Message* GridFile::getMessageByIndex(std::size_t index)
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to nullptr!");

    return mGridFile->getMessageByIndex(index);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method can be used for finding out the type of the file. The child classes
    should override this method.

        \return   The type of the file (expressed as an enum value).
*/

T::FileType GridFile::getFileType() const
{
  try
  {
    if (!mGridFile)
      return T::FileTypeValue::Unknown;

    return mGridFile->getFileType();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the type of the file expressed as a string. The child
    classes should override this method.

        \return   The type of the file (expressed as a string).
*/

std::string GridFile::getFileTypeString() const
{
  try
  {
    if (mGridFile)
      return mGridFile->getFileTypeString();

    return std::string("Unknown");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridFile::getPointCacheEnabled()
{
  try
  {
    if (mGridFile)
      return mGridFile->getPointCacheEnabled();

    return mPointCacheEnabled;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::setPointCacheEnabled(bool enabled)
{
  try
  {
    if (mGridFile)
      mGridFile->setPointCacheEnabled(enabled);

    mPointCacheEnabled = enabled;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GridFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    if (!mGridFile)
      throw SmartMet::Spine::Exception(BCP,"The 'mGridFile' attribute points to nullptr!");

    mGridFile->print(stream,level,optionFlags);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




}  // namespace GRID
}  // namespace SmartMet
