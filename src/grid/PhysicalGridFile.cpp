#include "PhysicalGridFile.h"
#include "../common/Exception.h"
#include "../common/GeneralDefinitions.h"
#include "../common/GeneralFunctions.h"
#include "../common/ShowFunction.h"
#include "../identification/GridDef.h"
#include "../grib1/Message.h"
#include "../grib2/Message.h"
#include "../fmig1/Message.h"


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
/*
    if (mMessagePositions.size() > 0)
    {
      // We know the message positions, so we can create the actual message objects.

      for (auto it = mMessagePositions.begin(); it != mMessagePositions.end(); ++it)
      {
        createMessage(it->first,it->second);
      }
      mMessagePositions.clear();
    }
*/
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GRID::Message* PhysicalGridFile::createMessage(uint messageIndex,GRID::MessageInfo& messageInfo)
{
  FUNCTION_TRACE
  try
  {
    if (mMessages.find(messageIndex) != mMessages.end())
    {
      SmartMet::Spine::Exception exception(BCP,"Message index already exists!");
      exception.addParameter("MessageIndex",std::to_string(messageIndex));
      throw exception;
    }

    auto startAddr = mMemoryPtr + messageInfo.mFilePosition;
    auto endAddr = startAddr + messageInfo.mMessageSize;

    MemoryReader memoryReader(reinterpret_cast<unsigned char*>(startAddr),reinterpret_cast<unsigned char*>(endAddr));

    uchar fileType = readMessageType(memoryReader);

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

      case T::FileTypeValue::Fmig1:
      {
        FMIG1::Message *msg = new FMIG1::Message(this,messageIndex,messageInfo);
        mMessages.insert(std::pair<uint,Message*>(messageIndex,msg));
        return msg;
      }
    }
    return nullptr;
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






#if 0

/*! \brief The method memory maps the given file.
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

    // We do not need to read messages beforehand anymore, because we know their file positions
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Read failed!",nullptr);
    exception.addParameter("File name ",mFileName);
    throw exception;
  }
}

#endif



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
    read(memoryReader);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Read failed!",nullptr);
    exception.addParameter("File name ",filename);
    throw exception;
  }
}




/*! \brief The method searches message positions from the grib file and after that
    it creates and initializes message objects according to the found message information.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PhysicalGridFile::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    mIsMemoryMapped = true;

    memoryReader.setReadPosition(0);
    auto gribs = searchMessageLocations(memoryReader);

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

        case T::FileTypeValue::Fmig1:
          readFmig1Message(memoryReader,i);
          break;
      }
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method is used in order to read a single message from the grib file. The new
    message object will be greated and added to the message list. Notice that this method
    is a private and it is called internally during the file reading.

        \param memoryReader  This object controls the access to the memory mapped file.
        \param messageIndex  Index of the message
*/

void PhysicalGridFile::readGrib1Message(MemoryReader& memoryReader, uint messageIndex)
{
  FUNCTION_TRACE
  try
  {
    GRIB1::Message *message = new GRIB1::Message();
    message->setGridFilePtr(this);
    message->setMessageIndex(messageIndex);
    message->setPointCacheEnabled(mPointCacheEnabled);
    mMessages.insert(std::pair<uint,Message*>(messageIndex,message));
    message->read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Message addition failed!",nullptr);
  }
}





/*! \brief This method is used in order to read a single message from the grib file. The new
    message object will be greated and added to the message list. Notice that this method
    is a private and it is called internally during the file reading.

        \param memoryReader  This object controls the access to the memory mapped file.
        \param messageIndex  Index of the message
*/

void PhysicalGridFile::readFmig1Message(MemoryReader& memoryReader, uint messageIndex)
{
  FUNCTION_TRACE
  try
  {
    FMIG1::Message *message = new FMIG1::Message();
    message->setGridFilePtr(this);
    message->setMessageIndex(messageIndex);
    message->setPointCacheEnabled(mPointCacheEnabled);
    mMessages.insert(std::pair<uint,Message*>(messageIndex,message));
    message->read(memoryReader);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Message addition failed!",nullptr);
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

void PhysicalGridFile::readGrib2Message(MemoryReader& memoryReader, uint messageIndex)
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
        std::cout << CODE_LOCATION << ": Memory area end reached!\n";
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
      message->setPointCacheEnabled(mPointCacheEnabled);
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
        SmartMet::Spine::Exception exception(BCP,"Incomplete message in the GRIB2 file!");
        exception.addParameter("Message index",std::to_string(messageIndex));
        throw exception;
      }

      message->initParameterInfo();
      mMessages.insert(std::pair<uint,Message*>(messageIndex,message));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Message addition failed!",nullptr);
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

MessagePos_vec PhysicalGridFile::searchMessageLocations(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    MessagePos_vec gribs;

    // A complete indicator section takes 16 bytes, hence we can stop the loop earlier
    // thus making sure all reads inside the loop succeed.

    auto fileStartPtr = memoryReader.getReadPtr();


    if (memoryReader.peek_string("FMIG"))
    {
      FMIG1::Message msg;
      msg.read(memoryReader);

      uint len = msg.getTimeStepCount();
      for (uint t=0; t<len; t++)
        gribs.push_back(std::pair<uchar,ulonglong>(T::FileTypeValue::Fmig1,0));

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
        //SmartMet::Spine::Exception exception(BCP,"The GRIB size ('totalLength') is out of the limits!");
        //exception.addParameter("Read position",uint64_toHex(memoryReader.getReadPosition()));
        //exception.addParameter("totalLength",std::to_string(totalLength));
        //throw exception;
      }

      if (valid)
      {
        memoryReader.read_null(totalLength-16);
        gribs.push_back(std::pair<uchar,ulonglong>(edition,(ulonglong)(startPtr-fileStartPtr)));
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
    throw SmartMet::Spine::Exception(BCP,"Message search failed!",nullptr);
  }
}





/*! \brief This method can be used in order to get pointer to the message object
    according to its index. The current message pointer can be used for accessing
    data inside the current message.

        \param index  The message index (0..N).
*/

GRID::Message* PhysicalGridFile::getMessageByIndex(std::size_t index)
{
  FUNCTION_TRACE
  try
  {
    if (!isMemoryMapped())
      mapToMemory();

    AutoThreadLock lock(&mMemoryMappingLock);

    if (mMessagePositions.size() > 0)
    {
      auto pos = mMessagePositions.find(index);
      if (pos != mMessagePositions.end())
      {
        createMessage(pos->first,pos->second);
        mMessagePositions.erase(pos);
      }
    }

    auto msg = mMessages.find(index);
    if (msg != mMessages.end())
    {
      if (msg->second != nullptr &&  !msg->second->isRead())
      {
        msg->second->read();
      }

      return msg->second;
    }
    else
    {
      printf("*** Message not found %lu / %lu\n",index,mMessages.size());
    }

    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::size_t PhysicalGridFile::getNumberOfMessages()
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void PhysicalGridFile::write(std::string filename)
{
  FUNCTION_TRACE
  try
  {
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
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Write failed!",nullptr);
    throw exception;
  }
}




/*! \brief This method is used in order to detect the type of the current message. Technically
    the method reads few bytes from the beginning of the message and tries to recognize
    the used message type

        \param memoryReader  This object controls the access to the memory mapped file.
*/

uchar PhysicalGridFile::readMessageType(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    memoryReader.setReadPosition(0);

    //unsigned long long pos = searchFileStartPosition(memoryReader);
    //memoryReader.setReadPosition(pos);

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
    if (d[0] == 'F'  &&  d[1] == 'M'  &&  d[2] == 'I'  &&  d[3] == 'G')
    {
      // This is a grib file.

      if (d[4] == 1)
        return T::FileTypeValue::Fmig1;

    }

    return T::FileTypeValue::Unknown;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*
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
*/




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
