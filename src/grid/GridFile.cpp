#include "GridFile.h"
#include "PrintOptions.h"
#include <macgyver/Exception.h>
#include "../common/GeneralDefinitions.h"
#include "../common/GeneralFunctions.h"
#include "../common/ShowFunction.h"
#include "../identification/GridDef.h"


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
    mCheckTime = 0;
    mFileId = 0;
    mProtocol = 1;
    mGroupFlags = 0;
    mProducerId = 0;
    mGenerationId = 0;
    mAccessTime = 0;
    mCheckTime = 0;
    mSourceId = 0;
    mDeletionTime = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

GridFile::GridFile(const GridFile& other)
{
  FUNCTION_TRACE
  try
  {
    mFileName = other.mFileName;
    mProtocol = other.mProtocol;
    mServer = other.mServer;
    mFileId = other.mFileId;
    mFileModificationTime = other.mFileModificationTime;
    mDeletionTime = other.mDeletionTime;
    mGroupFlags = other.mGroupFlags;
    mProducerId = other.mProducerId;
    mGenerationId = other.mGenerationId;
    mSourceId = other.mSourceId;
    mAccessTime = other.mAccessTime;
    mCheckTime = other.mCheckTime;
    mUserList = other.mUserList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}





GridFile::GridFile(GridFile *gridFile)
{
  FUNCTION_TRACE
  try
  {
    mCheckTime = 0;
    mProtocol = 1;
    mFileId = 0;
    mGroupFlags = 0;
    mProducerId = 0;
    mGenerationId = 0;
    mAccessTime = 0;
    mCheckTime = 0;
    mSourceId = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}




/*! \brief The destructor of the class. */

GridFile::~GridFile()
{
  FUNCTION_TRACE
  try
  {
    for (auto msg = mMessages.begin();  msg != mMessages.end(); ++msg)
    {
      delete (msg->second);
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





GridFile* GridFile::createGridFile()
{
  throw Fmi::Exception(BCP,"Not implemented!");
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
    return mFileId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return mGroupFlags;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the protocol that is used for accessing the current current grid file.

      \return  The protocol.
*/

uchar GridFile::getProtocol() const
{
  FUNCTION_TRACE
  try
  {
    return mProtocol;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the server where the current current grid file is stored.

      \return  The server name.
*/

std::string GridFile::getServer() const
{
  FUNCTION_TRACE
  try
  {
    return mServer;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return mProducerId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return mGenerationId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the time when the grid file was last time accessed.

      \return    The last access time of the current grid file.
*/

time_t GridFile::getAccessTime() const
{
  FUNCTION_TRACE
  try
  {
    return mAccessTime;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return mCheckTime;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return mFileModificationTime;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the expected deletion time of the grid file.

      \return  The expected deletion time of the grid file.
*/

std::string GridFile::getDeletionTimeStr() const
{
  FUNCTION_TRACE
  try
  {
    return utcTimeFromTimeT(mDeletionTime);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





time_t GridFile::getDeletionTime() const
{
  FUNCTION_TRACE
  try
  {
    return mDeletionTime;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return mSourceId;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





char* GridFile::getMemoryPtr()
{
  FUNCTION_TRACE
  try
  {
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





long long GridFile::getSize()
{
  FUNCTION_TRACE
  try
  {
    long long fileSize = 0;
    for (auto it = mMessagePositions.begin(); it != mMessagePositions.end(); ++it)
    {
      long long fsize = it->second.mFilePosition + it->second.mMessageSize;
      if (fileSize < fsize)
        fileSize = fsize;
    }

    for (auto it = mMessages.begin(); it != mMessages.end(); ++it)
    {
      long long fsize = it->second->getFilePosition() + it->second->getMessageSize();
      if (fileSize < fsize)
        fileSize = fsize;
    }

    return fileSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridFile::addDependence(uint fileId)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridFile::hasDependence(uint fileId)
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridFile::addUser(uint fileId)
{
  FUNCTION_TRACE
  try
  {
    //if (mUserList.find(fileId) == mUserList.end())
      mUserList.insert(fileId);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridFile::deleteUsers()
{
  FUNCTION_TRACE
  try
  {
    mUserList.clear();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridFile::getUsers(std::set<uint>& userList)
{
  FUNCTION_TRACE
  try
  {
    userList = mUserList;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridFile::hasMessagePositionError() const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns 'true' if the current grid file is memory mapped. */

bool GridFile::isMemoryMapped() const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method maps the current grid file into the memory.  */

void GridFile::mapToMemory()
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns 'true' if the current grid file is physical (not virtual). */

bool GridFile::isPhysical() const
{
  FUNCTION_TRACE
  try
  {
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns 'true' if the current grid file is virtual. */

bool GridFile::isVirtual() const
{
  FUNCTION_TRACE
  try
  {
    return true;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets time when the current grid file was last accessed.

      \param checkTime   The last check time.
*/

void GridFile::setAccessTime(time_t accessTime)
{
  FUNCTION_TRACE
  try
  {
    mAccessTime = accessTime;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets time the expected deletion time of the current grid file.

      \param deletionTime   The deletion time of the grid file.
*/

void GridFile::setDeletionTime(const std::string& deletionTime)
{
  FUNCTION_TRACE
  try
  {
    if (deletionTime.length() == 15)
      mDeletionTime = utcTimeToTimeT(deletionTime);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}






/*! \brief The method sets time the expected deletion time of the current grid file.

      \param deletionTime   The deletion time of the grid file.
*/

void GridFile::setDeletionTime(time_t deletionTime)
{
  FUNCTION_TRACE
  try
  {
    mDeletionTime = deletionTime;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the file name of the current grid file. Usully this name is set
    when the grid file is registered for example into the Content Server.

      \param fileName  The grid file name.
*/

void GridFile::setFileName(const std::string& fileName)
{
  FUNCTION_TRACE
  try
  {
    mFileName = fileName;
    mFileModificationTime = time(nullptr); //getFileModificationTime(fileName.c_str());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridFile::setProtocol(uchar protocol)
{
  FUNCTION_TRACE
  try
  {
    mProtocol = protocol;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridFile::setServer(const std::string& server)
{
  FUNCTION_TRACE
  try
  {
    mServer = server;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridFile::setSize(long long size)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




Message* GridFile::newMessage(T::FileType fileType)
{
  FUNCTION_TRACE
  try
  {
    switch (fileType)
    {
      case T::FileTypeValue::Grib1:
      {
        GRIB1::Message *msg = new GRIB1::Message();
        addMessage(msg);
        return msg;
      }

      case T::FileTypeValue::Grib2:
      {
        GRIB2::Message *msg = new GRIB2::Message();

        msg->setBitmapSection(new GRIB2::BitmapSection());
        msg->setIdentificationSection(new GRIB2::IdentificationSection());
        msg->setGridSection(new GRIB2::GridSection());
        msg->setRepresentationSection(new GRIB2::RepresentationSection());
        msg->setIndicatorSection(new GRIB2::IndicatorSection());
        msg->setLocalSection(new GRIB2::LocalSection());
        msg->setProductSection(new GRIB2::ProductSection());
        msg->setDataSection(new GRIB2::DataSection());
        addMessage(msg);
        return msg;
      }
    }
    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





Message* GridFile::newMessage(uint messageIndex,MessageInfo& messageInfo)
{
  FUNCTION_TRACE
  try
  {
    if (mMessagePositions.find(messageIndex) == mMessagePositions.end())
      mMessagePositions.insert(std::pair<uint,MessageInfo>(messageIndex,messageInfo));

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridFile::addMessage(Message *message)
{
  FUNCTION_TRACE
  try
  {
    if (message == nullptr)
      throw Fmi::Exception(BCP,"The 'message' parameter points to nullptr!");

    message->setGridFilePtr(this);
    message->setMessageIndex(mMessages.size());

    mMessages.insert(std::pair<uint,Message*>(mMessages.size(),message));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridFile::read(const std::string& filename)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Read failed!",nullptr);
    exception.addParameter("File name ",filename);
    throw exception;
  }
}





void GridFile::write(const std::string& filename)
{
  FUNCTION_TRACE
  try
  {
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Write failed!",nullptr);
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
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Write failed!",nullptr);
    throw exception;
  }
}





/*! \brief The method returns the name and the path of the file.

       \return  The method returns the name and the path of the file.
*/

std::string GridFile::getFileName() const
{
  FUNCTION_TRACE
  try
  {
    return mFileName;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Not implemented!");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return std::string("Unknown");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    std::size_t messageCount = mMessages.size();

    stream << space(level) << "GridFile\n";
    stream << space(level) << "- fileName         = " << getFileName() << "\n";
    stream << space(level) << "- fileId           = " << mFileId << "\n";
    stream << space(level) << "- deletionTime     = " << getDeletionTimeStr() << "\n";
    stream << space(level) << "- groupFlags       = " << mGroupFlags << "\n";
    stream << space(level) << "- producerId       = " << mProducerId << "\n";
    stream << space(level) << "- generationId     = " << mGenerationId << "\n";
    stream << space(level) << "- numberOfMessages = " << messageCount << "\n";

    if (optionFlags & GRID::PrintFlag::no_messages)
      return;

    for (auto msg = mMessages.begin();  msg != mMessages.end(); ++msg)
    {
      msg->second->print(stream,level+1,optionFlags);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




}  // namespace GRID
}  // namespace SmartMet
