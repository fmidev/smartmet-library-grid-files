#include "GridFile.h"
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

GridFile::GridFile()
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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





/*! \brief The method returns the file identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid file identifier.
*/

uint GridFile::getFileId() const
{
  FUNCTION_TRACE
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





/*! \brief The method returns the group flags of the current grid file. Usully these flags are set
    when the grid file is registered for example into the Content Server.

      \return  The grid file group flags.
*/

uint GridFile::getGroupFlags() const
{
  FUNCTION_TRACE
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





/*! \brief The method returns the producer identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid producer identifier.
*/

uint GridFile::getProducerId() const
{
  FUNCTION_TRACE
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





/*! \brief The method returns the generation identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid generation identifier.
*/

uint GridFile::getGenerationId() const
{
  FUNCTION_TRACE
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





/*! \brief The method returns the shared pointer to the actual grid file.

      \return  The shared pointer of the grid file.
*/

std::shared_ptr<GridFile> GridFile::getGridFile()
{
  FUNCTION_TRACE
  try
  {
    return mGridFile;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the time when the grid file was last time checked.

      \return    The last check time of the current grid file.
*/

time_t GridFile::getCheckTime() const
{
  FUNCTION_TRACE
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





/*! \brief The method returns the modification time of the grid file.

      \return  The modification time of the grid file.
*/

time_t GridFile::getModificationTime() const
{
  FUNCTION_TRACE
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





/*! \brief The method returns the expected deletion time of the grid file.

      \return  The expected deletion time of the grid file.
*/

std::string GridFile::getDeletionTime() const
{
  FUNCTION_TRACE
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





/*! \brief The method returns the source identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \return  The grid source identifier.
*/

uint GridFile::getSourceId() const
{
  FUNCTION_TRACE
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





char* GridFile::getMemoryPtr()
{
  FUNCTION_TRACE
  try
  {
    if (mGridFile)
      mGridFile->getMemoryPtr();

    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





long long GridFile::getSize()
{
  FUNCTION_TRACE
  try
  {
    if (mGridFile)
      mGridFile->getSize();

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::addDependence(uint fileId)
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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





/*! \brief The method returns 'true' if the current grid file is memory mapped. */

bool GridFile::isMemoryMapped() const
{
  FUNCTION_TRACE
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





/*! \brief The method maps the current grid file into the memory.  */

void GridFile::mapToMemory()
{
  FUNCTION_TRACE
  try
  {
    if (mGridFile)
    {
      mGridFile->mapToMemory();
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns 'true' if the current grid file is physical (not virtual). */

bool GridFile::isPhysical() const
{
  FUNCTION_TRACE
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





/*! \brief The method returns 'true' if the current grid file is virtual. */

bool GridFile::isVirtual() const
{
  FUNCTION_TRACE
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





/*! \brief The method sets pointer to the actual grid file.

      \param gridFile   The pointer to the actual grid file.
*/

void GridFile::setGridFile(GridFile *gridFile)
{
  FUNCTION_TRACE
  try
  {
    mGridFile.reset(gridFile);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method sets time when the current grid file was last checked.

      \param checkTime   The last check time.
*/

void GridFile::setCheckTime(time_t checkTime)
{
  FUNCTION_TRACE
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





/*! \brief The method sets the file identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \param fileId  The grid file identifier.
*/

void GridFile::setFileId(uint fileId)
{
  FUNCTION_TRACE
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





/*! \brief The method sets time the expected deletion time of the current grid file.

      \param deletionTime   The deletion time of the grid file.
*/

void GridFile::setDeletionTime(std::string deletionTime)
{
  FUNCTION_TRACE
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





/*! \brief The method sets the group flags of the current grid file. Usully these flags are set
    when the grid file is registered for example into the Content Server.

      \param groupFlags  The grid file group flags.
*/

void GridFile::setGroupFlags(uint groupFlags)
{
  FUNCTION_TRACE
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





/*! \brief The method sets the producer identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \param producerID  The grid producer identifier.
*/

void GridFile::setProducerId(uint producerId)
{
  FUNCTION_TRACE
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






/*! \brief The method sets the generation identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \param generationId  The grid generation identifier.
*/

void GridFile::setGenerationId(uint generationId)
{
  FUNCTION_TRACE
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





/*! \brief The method sets the file name of the current grid file. Usully this name is set
    when the grid file is registered for example into the Content Server.

      \param fileName  The grid file name.
*/

void GridFile::setFileName(std::string fileName)
{
  FUNCTION_TRACE
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





/*! \brief The method sets the source identifier of the current grid file. Usully this identifier is set
    when the grid file is registered for example into the Content Server.

      \param sourceId  The grid source identifier.
*/

void GridFile::setSourceId(uint sourceId)
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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





Message* GridFile::newMessage(uint messageIndex,ulonglong position,uint size)
{
  FUNCTION_TRACE
  try
  {
    if (!mGridFile)
    {
      // We do not know yet the type of the file, so we have to store the message position information
      // temporararily into a map.

      mMessagePositions.insert(std::pair<uint,ulonglong>(messageIndex,position));
      return nullptr;
    }

    return mGridFile->newMessage(messageIndex,position,size);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GridFile::addMessage(Message *message)
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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

void GridFile::write(DataWriter& dataWriter)
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





/*! \brief The method returns the name and the path of the file.

       \return  The method returns the name and the path of the file.
*/

std::string GridFile::getFileName() const
{
  try
  {
    FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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





void GridFile::clearCachedValues(uint hitsRequired,uint timePeriod) const
{
  FUNCTION_TRACE
  try
  {
    if (mGridFile)
      mGridFile->clearCachedValues(hitsRequired,timePeriod);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





bool GridFile::getPointCacheEnabled()
{
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
  FUNCTION_TRACE
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
