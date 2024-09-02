#include "GridFile.h"
#include "PrintOptions.h"
#include <macgyver/Exception.h>
#include <macgyver/StringConversion.h>
#include "../common/GeneralDefinitions.h"
#include "../common/GeneralFunctions.h"
#include "../common/ShowFunction.h"
#include "../identification/GridDef.h"
#include "../common/FileWriter.h"
#include "../grib1/Message.h"
#include "../grib2/Message.h"
#include "../netcdf/Message.h"
#include "../netcdf/NetCdfFile.h"
#include "../querydata/Message.h"
#include <linux/userfaultfd.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <signal.h>
#include <poll.h>


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
    mMemoryMapInfo.reset(new MapInfo());
    mMemoryMapInfo->serverType = 1;
    mMemoryMapInfo->protocol = 0;
    mGroupFlags = 0;
    mProducerId = 0;
    mGenerationId = 0;
    mAccessTime = 0;
    mCheckTime = 0;
    mSourceId = 0;
    mDeletionTime = 0;

    mIsRead = false;
    mMessagePositionError = false;
    mNetCdfFile = nullptr;
    mQueryDataFile = nullptr;
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
    //mMemoryMapInfo = other.mMemoryMapInfo;
    mFileId = other.mFileId;
    mFileModificationTime = other.mFileModificationTime;
    mDeletionTime = other.mDeletionTime;
    mGroupFlags = other.mGroupFlags;
    mProducerId = other.mProducerId;
    mGenerationId = other.mGenerationId;
    mSourceId = other.mSourceId;
    mAccessTime = other.mAccessTime;
    mCheckTime = other.mCheckTime;

    mIsRead = false;
    mMessagePositionError = false;
    mNetCdfFile = nullptr;
    mQueryDataFile = nullptr;
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
    mMemoryMapInfo.reset(new MapInfo());
    mMemoryMapInfo->serverType = 1;
    mMemoryMapInfo->protocol = 0;
    mFileId = 0;
    mGroupFlags = 0;
    mProducerId = 0;
    mGenerationId = 0;
    mAccessTime = 0;
    mCheckTime = 0;
    mSourceId = 0;
    mIsRead = false;
    mMessagePositionError = false;
    mNetCdfFile = nullptr;
    mQueryDataFile = nullptr;
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

    if (mNetCdfFile)
      delete mNetCdfFile;

    if (mQueryDataFile)
      delete mQueryDataFile;

    if (isMemoryMapped())
    {
      memoryMapper.unmap(mMemoryMapInfo);
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
    return mMemoryMapInfo->protocol;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the server type (filesys,S3,etc.) that is used for accessing the current current grid file.

      \return  The service type.
*/

uchar GridFile::getServerType() const
{
  FUNCTION_TRACE
  try
  {
    return mMemoryMapInfo->serverType;
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
    return mMemoryMapInfo->server;
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





long long GridFile::countSize()
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
      if (it->second->getFileMemoryPtr() == nullptr)
      {
        long long fsize = it->second->getFilePosition() + it->second->getMessageSize();
        if (fileSize < fsize)
          fileSize = fsize;
      }
    }

    return fileSize;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





long long GridFile::getRequestCounters(RequestCounters& requestCounters)
{
  FUNCTION_TRACE
  try
  {
    long long max = 0;
    for (auto it = mMessages.begin(); it != mMessages.end(); ++it)
    {
      unsigned long long key = ((unsigned long long)mFileId << 32) + it->first;
      long long cnt = it->second->getRequestCounter();
      if (cnt > max)
        max = cnt;

      if (cnt > 0)
        requestCounters.insert(std::pair<unsigned long long,long long>(key,cnt));
    }
    return max;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void GridFile::resetRequestCounters()
{
  FUNCTION_TRACE
  try
  {
    for (auto it = mMessages.begin(); it != mMessages.end(); ++it)
      it->second->setRequestCounter((uint)((double)it->second->getRequestCounter()/100.0));
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





bool GridFile::hasMessagePositionError() const
{
  FUNCTION_TRACE
  try
  {
    return mMessagePositionError;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





bool GridFile::hasMemoryMapperError() const
{
  FUNCTION_TRACE
  try
  {
    if (memoryMapper.isEnabled()  &&  mMemoryMapInfo->mappingError)
      return true;

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
    if (mMemoryMapInfo->memoryPtr)
      return true;

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
    if (mDeletionTime != 0  &&  (time(nullptr) + 180) > mDeletionTime)
      throw Fmi::Exception(BCP,"File is going to be deleted!");

    AutoThreadLock lock(&mMemoryMappingLock);
    if (isMemoryMapped())
      return;

    long long fs = memoryMapper.getFileSize(mMemoryMapInfo->serverType,mMemoryMapInfo->protocol,mMemoryMapInfo->server.c_str(),mMemoryMapInfo->filename.c_str());

    if (fs < 0)
      throw Fmi::Exception(BCP,"Cannot get correct file size. Maybe the file does not exist!");

    if (fs == 0)
      throw Fmi::Exception(BCP,"File size is 0!");

    mMemoryMapInfo->fileSize = fs;

    memoryMapper.map(mMemoryMapInfo);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Filename",getFileName());
    throw exception;
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
    mMemoryMapInfo->filename = fileName;
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
    mMemoryMapInfo->protocol = protocol;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




void GridFile::setServerType(uchar serverType)
{
  FUNCTION_TRACE
  try
  {
    mMemoryMapInfo->serverType = serverType;
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
    mMemoryMapInfo->server = toLowerString(server);
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
    {
      mMessagePositions.insert(std::pair<uint,MessageInfo>(messageIndex,messageInfo));
    }

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





void GridFile::write(const std::string& filename)
{
  FUNCTION_TRACE
  try
  {
    FileWriter fileWriter;
    fileWriter.createFile(filename.c_str());
    write(fileWriter);
    fileWriter.closeFile();
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
    for (auto msg = mMessages.begin();  msg != mMessages.end(); ++msg)
    {
      msg->second->write(dataWriter);
    }
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
    return mMemoryMapInfo->filename;
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





GRID::Message* GridFile::createMessage(uint messageIndex,GRID::MessageInfo& messageInfo)
{
  FUNCTION_TRACE
  try
  {
    if (mMessages.find(messageIndex) != mMessages.end())
    {
      Fmi::Exception exception(BCP,"Message index already exists!");
      exception.addParameter("Message index",Fmi::to_string(messageIndex));
      throw exception;
    }

    long long fsize = getSize();

    if (messageInfo.mFilePosition == messageInfo.mOriginalFilePosition && C_INT64(messageInfo.mFilePosition + messageInfo.mMessageSize) > fsize)
    {
      mMessagePositionError = true;

      Fmi::Exception exception(BCP,"Message position + size is bigger than the size of the file!");
      exception.addParameter("Message index",Fmi::to_string(messageIndex));
      exception.addParameter("Message file position",std::to_string(messageInfo.mFilePosition));
      exception.addParameter("Message size",Fmi::to_string(messageInfo.mMessageSize));
      exception.addParameter("File size",std::to_string(fsize));
      throw exception;
    }


    auto startAddr = mMemoryMapInfo->memoryPtr + messageInfo.mFilePosition;
    auto endAddr = startAddr + messageInfo.mMessageSize;

    if (messageInfo.mFileMemoryPtr  &&  !mMemoryMapInfo->mappedFile)
    {
      startAddr = messageInfo.mFileMemoryPtr + messageInfo.mFilePosition;
      endAddr = startAddr + messageInfo.mMessageSize;
    }


    if (messageInfo.mMessageType == T::FileTypeValue::NetCdf3 || messageInfo.mMessageType == T::FileTypeValue::NetCdf4)
    {
      auto startAddr = mMemoryMapInfo->memoryPtr;
      auto endAddr = startAddr + fsize;


      MemoryReader memoryReader(reinterpret_cast<unsigned char*>(startAddr),reinterpret_cast<unsigned char*>(endAddr));

      if (mMessages.size() == 0)
      {
        memoryReader.setReadPosition(0);
        mNetCdfFile = new NetCDF::NetCdfFile();
        NetCDF::MessageInfoVec messageInfoList;
        mNetCdfFile->read(memoryReader,messageInfoList);

        uint idx = 0;
        for (auto it = messageInfoList.begin();it != messageInfoList.end(); ++it)
        {
          NetCDF::Message *message = new NetCDF::Message(this,mNetCdfFile,idx,*it);
          mMessages.insert(std::pair<uint,Message*>(idx,message));
          idx++;
        }
      }
      auto msg = mMessages.find(messageIndex);
      if (msg != mMessages.end())
        return msg->second;

      return nullptr;
    }

    if (messageInfo.mMessageType == T::FileTypeValue::QueryData)
    {
      auto startAddr = mMemoryMapInfo->memoryPtr;
      auto endAddr = startAddr + fsize;

      MemoryReader memoryReader(reinterpret_cast<unsigned char*>(startAddr),reinterpret_cast<unsigned char*>(endAddr));

      if (mMessages.size() == 0)
      {
        memoryReader.setReadPosition(0);
        mQueryDataFile = new QueryData::QueryDataFile(mMemoryMapInfo->filename.c_str());
        QueryData::MessageInfoVec messageInfoList;
        mQueryDataFile->read(messageInfoList);

        uint idx = 0;
        for (auto it = messageInfoList.begin();it != messageInfoList.end(); ++it)
        {
          QueryData::Message *message = new QueryData::Message(this,mQueryDataFile,idx,*it);
          mMessages.insert(std::pair<uint,Message*>(idx,message));
          idx++;
        }

        // QueryData file has its own mapping functionality. We do not need double mapping.
        /*
        if (mMappedFile  &&  mIsMemoryMapped)
        {
          mMappedFile->close();
        }
        */
      }
      auto msg = mMessages.find(messageIndex);
      if (msg != mMessages.end())
        return msg->second;

      return nullptr;
    }

    MemoryReader memoryReader(reinterpret_cast<unsigned char*>(startAddr),reinterpret_cast<unsigned char*>(endAddr));
    uchar fileType = readMessageType(memoryReader);
    if (fileType == 0)
    {
      MemoryReader memoryReader2(reinterpret_cast<unsigned char*>(mMemoryMapInfo->memoryPtr),reinterpret_cast<unsigned char*>(endAddr));
      fileType = readMessageType(memoryReader2);
    }


    switch (fileType)
    {
      case T::FileTypeValue::Grib1:
      {
        GRIB1::Message *msg = new GRIB1::Message(this,messageIndex,messageInfo);
        mMessages.insert(std::pair<uint,Message*>(messageIndex,msg));
        return msg;
      }

      case T::FileTypeValue::Grib2:
      {
        GRIB2::Message *msg = new GRIB2::Message(this,messageIndex,messageInfo);
        mMessages.insert(std::pair<uint,Message*>(messageIndex,msg));
        return msg;
      }
    }
    return nullptr;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Filename",getFileName());
    throw exception;
  }
}





bool GridFile::isNetworkFile() const
{
  try
  {
    if (!memoryMapper.isEnabled())
      return false;

    if (mMemoryMapInfo->protocol == 0)
      return false;

    return true;
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
    if (!isMemoryMapped())
      return countSize();

    return mMemoryMapInfo->fileSize;
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
    mMemoryMapInfo->fileSize = size;
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
    if (!isMemoryMapped())
      mapToMemory();

    return mMemoryMapInfo->memoryPtr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method memory maps the given file and after that it tries to
    recognize the type of the file. It creates and initializes GRIB1::GridFile
    or GRIB2::GridFile object according to the file type. This object represents
    the actual content of the current file.

       \param filename  The grib filename with a possible directory path.
*/

void GridFile::read(const std::string& filename)
{
  FUNCTION_TRACE
  try
  {
    uint maxMessages = 100000000;
    read(filename,maxMessages);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Read failed!",nullptr);
    exception.addParameter("Filename ",filename);
    throw exception;
  }
}





void GridFile::read(const std::string& filename,uint maxMessages)
{
  FUNCTION_TRACE
  try
  {
    if (mIsRead)
      return;  // Already read

    setFileName(filename);

    if (!isMemoryMapped())
    {
      mapToMemory();
    }

    auto endAddr = mMemoryMapInfo->memoryPtr + mMemoryMapInfo->fileSize;

    MemoryReader memoryReader(reinterpret_cast<unsigned char*>(mMemoryMapInfo->memoryPtr),reinterpret_cast<unsigned char*>(endAddr));
    read(memoryReader,maxMessages);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Read failed!",nullptr);
    exception.addParameter("Filename ",filename);
    throw exception;
  }
}




/*! \brief The method searches message positions from the grib file and after that
    it creates and initializes message objects according to the found message information.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridFile::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    uint maxMessages = 1000000000;
    read(memoryReader,maxMessages);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Filename",getFileName());
    throw exception;
  }
}





void GridFile::read(MemoryReader& memoryReader,uint maxMessages)
{
  FUNCTION_TRACE
  try
  {
    memoryReader.setReadPosition(0);
    auto gribs = searchMessageLocations(memoryReader,maxMessages);

    auto startAddr = memoryReader.getStartPtr();
    auto endAddr = memoryReader.getEndPtr();

    uint sz = gribs.size();
    for (uint i = 0; i < sz; i++)
    {
      auto ptr = reinterpret_cast<unsigned char*>(startAddr + gribs[i].second);
      if ((i+1) < gribs.size())
        endAddr = reinterpret_cast<unsigned char*>(startAddr + gribs[i+1].second);
      else
        endAddr = memoryReader.getEndPtr();

      MemoryReader memoryReader2(ptr,endAddr);
      memoryReader2.setParentPtr(startAddr);

      switch (gribs[i].first)
      {
        case T::FileTypeValue::Grib1:
          readGrib1Message(memoryReader2,i);
          break;

        case T::FileTypeValue::Grib2:
          readGrib2Message(memoryReader2,i);
          break;

        case T::FileTypeValue::NetCdf3:
        case T::FileTypeValue::NetCdf4:
        {
          if (mMessages.size() == 0)
          {
            memoryReader.setReadPosition(0);
            mNetCdfFile = new NetCDF::NetCdfFile();
            NetCDF::MessageInfoVec messageInfoList;
            mNetCdfFile->read(memoryReader,messageInfoList);

            uint idx = 0;
            for (auto it = messageInfoList.begin();it != messageInfoList.end(); ++it)
            {
              NetCDF::Message *message = new NetCDF::Message(this,mNetCdfFile,idx,*it);
              mMessages.insert(std::pair<uint,Message*>(idx,message));
              idx++;
              if (mMessages.size() >= maxMessages)
                return;
            }
          }
        }
        break;

        case T::FileTypeValue::QueryData:
        {
          if (mMessages.size() == 0)
          {
            memoryReader.setReadPosition(0);
            mQueryDataFile = new QueryData::QueryDataFile(mMemoryMapInfo->filename.c_str());
            QueryData::MessageInfoVec messageInfoList;
            mQueryDataFile->read(messageInfoList);
            uint idx = 0;
            for (auto it = messageInfoList.begin();it != messageInfoList.end(); ++it)
            {
              QueryData::Message *message = new QueryData::Message(this,mQueryDataFile,idx,*it);
              mMessages.insert(std::pair<uint,Message*>(idx,message));
              idx++;
              if (mMessages.size() >= maxMessages)
                return;
            }

            // QueryData file has its own mapping functionality. We do not need double mapping.
            /*
            if (mMappedFile  &&  mIsMemoryMapped)
            {
              mMappedFile->close();
            }
            */
          }
        }
        break;
      }
    }
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Filename",getFileName());
    throw exception;
  }
}





/*! \brief This method is used in order to read a single message from the grib file. The new
    message object will be greated and added to the message list. Notice that this method
    is a private and it is called internally during the file reading.

        \param memoryReader  This object controls the access to the memory mapped file.
        \param messageIndex  Index of the message
*/

void GridFile::readGrib1Message(MemoryReader& memoryReader, uint messageIndex)
{
  FUNCTION_TRACE
  try
  {
    GRIB1::Message *message = new GRIB1::Message();
    message->setGridFilePtr(this);
    message->setMessageIndex(messageIndex);
    mMessages.insert(std::pair<uint,Message*>(messageIndex,message));
    message->read(memoryReader);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Message addition failed!",nullptr);
  }
}




/*! \brief This method is used in order to read a single message from the NetCDF file. The new
    message object will be greated and added to the message list. Notice that this method
    is a private and it is called internally during the file reading.

        \param memoryReader  This object controls the access to the memory mapped file.
        \param messageIndex  Index of the message
*/

void GridFile::readNetCDFMessage(MemoryReader& memoryReader, uint messageIndex)
{
  FUNCTION_TRACE
  try
  {

    NetCDF::NetCdfFile *netCdf = new NetCDF::NetCdfFile();
    NetCDF::MessageInfoVec messageInfoList;
    netCdf->read(memoryReader,messageInfoList);
    /*

    NetCDF::Message *message = new NetCDF::Message();
    message->setGridFilePtr(this);
    message->setMessageIndex(messageIndex);
    mMessages.insert(std::pair<uint,Message*>(messageIndex,message));
    message->read(memoryReader);
    */
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Message addition failed!",nullptr);
  }
}




// ----------------------------------------------------------------------
/*!
 * \brief Scan an entire GRIB definition for individual GRIB messages.
 *
 * The RGIB2 requlations state that (A) Sequences of GRIB2 sections 2-7,
 * 3-7 or 4-7 may be repeated within a single GRIB2 message, (B) All
 * sections within such repeated sequences must be present and shall appear in
 * the numerical order, and (C) Unrepeated sections remain in effect until redefined.
 *
 * Schematically the structure is thus like the following index - you can always
 * return back to the previous level and start again:
 *
 *      Section 0: Indicator Section
 *      Section 1: Identification Section
 *      Section 2: Local Use Section (optional)
 *        Section 3: Grid Definition Section
 *          Section 4: Product Definition Section
 *          Section 5: Data Representation Section
 *          Section 6: Bit-Map Section
 *          Section 7: Data Section
 *      Section 8: End Section
 *
 */
// ----------------------------------------------------------------------

void GridFile::readGrib2Message(MemoryReader& memoryReader, uint messageIndex)
{
  FUNCTION_TRACE
  try
  {
    // Scan messages one by one until the end section is encountered

    std::shared_ptr<GRIB2::BitmapSection> last_real_bitmap;

    while (true)
    {
      if ((memoryReader.getReadPtr() +4) > memoryReader.getEndPtr())
      {
        // std::cout << CODE_LOCATION << ": Memory area end reached!\n";
        break;
      }

      if (memoryReader.peek_string("7777"))
      {
        memoryReader.read_null(4);
        break;
      }

      GRIB2::Message *message = new GRIB2::Message();
      message->setGridFilePtr(this);
      message->setMessageIndex(messageIndex);
      message->read(memoryReader);

      // Complete the sections from the previous message
      if (!mMessages.empty())
      {
        if (messageIndex > 0)
        {
          auto msg = mMessages.find(messageIndex-1);
          if (msg != mMessages.end())
          {
            /*
            if (msg->second != nullptr)
              message->copyMissingSections(*msg->second);
              */
          }
        }
      }

      // Some bitmap sections refer to earlier ones
      if (message->getBitmapSection() != nullptr &&  message->getBitmapSection()->getBitmapDataPtr() != nullptr)
        last_real_bitmap = message->getBitmapSection();
      else
        message->setPreviousBitmapSection(last_real_bitmap);

      if (!message->hasRequiredSections())
      {
        delete message;
        Fmi::Exception exception(BCP,"Incomplete message in the GRIB2 file!");
        exception.addParameter("Message index",Fmi::to_string(messageIndex));
        throw exception;
      }

      message->initParameterInfo();
      mMessages.insert(std::pair<uint,Message*>(messageIndex,message));
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Message addition failed!",nullptr);
  }
}





/*! \brief This method tries to locate the message start positions in the grib file.
    The method is needed because a grib file itself does not necessary have a well-defined
    structure. In other words, a grib file contains one or several messages, but in some
    grib files there might be some "garbage bytes" before and after these messages. This
    is probably against "the standard", but still we need to support this. The structure
    of the messages is well-defined, so we just need to locate them first.
    The method return a vector of data pointers pointing to the found messages.

        \param memoryReader  This object controls the access to the memory mapped file.
        \return              A vector of data pointers pointing to the found messages.
*/

MessagePos_vec GridFile::searchMessageLocations(MemoryReader& memoryReader,uint maxMessages)
{
  FUNCTION_TRACE
  try
  {
    MessagePos_vec gribs;

    // A complete indicator section takes 16 bytes, hence we can stop the loop earlier
    // thus making sure all reads inside the loop succeed.

    auto fileStartPtr = memoryReader.getReadPtr();

    if (memoryReader.peek_string("CDF"))
    {
      gribs.emplace_back(T::FileTypeValue::NetCdf4,0);
      return gribs;
    }

    const uchar qd[] = {0x40,0x24,0xB0,0xA3,0x51,0};
    if (memoryReader.peek_string((const char*)qd))
    {
      gribs.emplace_back(T::FileTypeValue::QueryData,0);
      return gribs;
    }


    while (memoryReader.getReadPtr() < memoryReader.getEndPtr())
    {
      // Usually GRIB2 messages do not have any extra garbage between them, several GRIB1 messages do
      // seem to have it. Most likely it's not worth optimizing this search, we'll just skip one byte
      // at a time.

      int spos = memoryReader.search_string("GRIB");

      if (spos < 0)
        return gribs;

      memoryReader.setReadPosition(memoryReader.getReadPosition()+spos);

      bool valid = true;

      // Skip identifier, reserved and discipline and then read the edition number

      auto startPtr = memoryReader.getReadPtr();
      memoryReader.read_null(4);

      std::uint8_t s[3];
      memoryReader >> s[0];
      memoryReader >> s[1];
      memoryReader >> s[2];


      std::uint8_t edition = 0;
      memoryReader >> edition;

      // TODO: Keeping this genering for now
      if (missing(edition))
      {
        valid = false;
      }

      if (edition != 1 &&  edition != 2)
      {
        valid = false;
      }

      std::uint64_t totalLength = 0;

      if (edition == 1)
        totalLength = (s[0] << 16) + (s[1] << 8) + s[2];

      if (edition == 2)
        memoryReader >> totalLength;

      // The value of the total length contains also 16 bytes in the beginning of the section 0.
      if ((memoryReader.getReadPosition() + totalLength-16) > memoryReader.getDataSize())
      {
        valid = false;
        //Fmi::Exception exception(BCP,"The GRIB size ('totalLength') is out of the limits!");
        //exception.addParameter("Read position",uint64_toHex(memoryReader.getReadPosition()));
        //exception.addParameter("totalLength",Fmi::to_string(totalLength));
        //throw exception;
      }

      if (valid)
      {
        memoryReader.read_null(totalLength-16);
        gribs.emplace_back(edition,(ulonglong)(startPtr-fileStartPtr));
        if (gribs.size() >= maxMessages)
          return gribs;
      }
      else
      {
        memoryReader.setReadPtr(startPtr);
        memoryReader.read_null(1);
      }
    }

    return gribs;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Message search failed!",nullptr);
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
    if (memoryMapper.isEnabled()  &&  mMemoryMapInfo->mappingError)
    {
      AutoThreadLock lock(&mMemoryMappingLock);

      // It seems that there have been problems with the current memory map.
      // We should wait some time before retrying the mapping.

      if ((mMemoryMapInfo->mappingTime + 10) > time(0))
        return nullptr;

      // We should try to map the file again.

      memoryMapper.unmap(mMemoryMapInfo);

      for (auto msg = mMessages.begin();  msg != mMessages.end(); ++msg)
      {
        delete (msg->second);
      }
      mMessages.clear();
      mMemoryMapInfo->memoryPtr = 0;
      mMemoryMapInfo->mappingError = false;
    }

    if (!isMemoryMapped())
    {
      mapToMemory();
    }

    AutoThreadLock lock(&mMemoryMappingLock);

    auto msg = mMessages.find(index);
    if (msg != mMessages.end())
    {
      if (msg->second != nullptr &&  !msg->second->isRead())
      {
        //std::cout << "READ " << mFileName << ":" << index << "\n";
        msg->second->read();
      }
      msg->second->incRequestCounter();
      return msg->second;
    }

    if (mMessagePositions.size() > 0)
    {
      auto pos = mMessagePositions.find(index);
      if (pos != mMessagePositions.end())
      {
        auto msg = mMessages.find(index);
        if (msg == mMessages.end())
        {
          //std::cout << "CREATE " << getFileName() << ":" << index << "\n";
          createMessage(pos->first,pos->second);
        }
        else
        {
          //std::cout << "ALREADY CREATED " << mFileName << ":" << index << "\n";
        }
      }
    }

    msg = mMessages.find(index);
    if (msg != mMessages.end())
    {
      if (msg->second != nullptr &&  !msg->second->isRead())
      {
        //std::cout << "READ2 " << mFileName << ":" << index << "\n";
        msg->second->read();
      }
      msg->second->incRequestCounter();
      return msg->second;
    }
    else
    {
      printf("*** GridFile.cpp: Message not found (%s) %lu / %lu /%lu\n",mMemoryMapInfo->filename.c_str(),index,mMessages.size(),mMessagePositions.size());
      if (mMessages.size() != mMessagePositions.size())
      {
        mMessages.clear();
        mMemoryMapInfo->memoryPtr = 0;
        //for (auto it = mMessagePositions.begin(); it != mMessagePositions.end(); ++it)
        //  printf("** %d\n",it->first);
      }
    }

    return nullptr;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("Filename",getFileName());
    exception.addParameter("File size",std::to_string(getSize()));
    throw exception;
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
    std::size_t cnt = 0;

    if (mMessagePositions.size() > 0)
    {
      auto pos = mMessagePositions.rbegin();
      cnt = pos->first + 1;
    }

    if (mMessages.size() > 0)
    {
      auto pos = mMessages.rbegin();
      if (pos->first >= cnt)
        cnt = pos->first + 1;
    }
    return cnt;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief This method is used in order to detect the type of the current message. Technically
    the method reads few bytes from the beginning of the message and tries to recognize
    the used message type

        \param memoryReader  This object controls the access to the memory mapped file.
*/

uchar GridFile::readMessageType(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    memoryReader.setReadPosition(0);

    unsigned char *f = memoryReader.getReadPtr();
    if (f[0] == 0)
    {
      Fmi::Exception exception(BCP,"First byte cannot be zero!",nullptr);
      throw exception;
    }

    if (hasMemoryMapperError())
    {
      Fmi::Exception exception(BCP,"Memory mapper has set fail flag for the current file!",nullptr);
      exception.addParameter("Filename",getFileName());
      throw exception;
    }

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

    if (d[0] == 'C'  &&  d[1] == 'D'  &&  d[2] == 'F')
    {
      // This is a NetCDF file.

      if (d[3] == 1 || d[3] == 2)
        return T::FileTypeValue::NetCdf4;
    }

    if (d[0] == 0x40 &&  d[1] == 0x24  &&  d[2] == 0xB0  &&  d[3] == 0xA3  &&  d[4] == 0x51)
    {
      // This is a querydata file.

      return T::FileTypeValue::QueryData;
    }

    return T::FileTypeValue::Unknown;
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
      if (msg->second)
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
