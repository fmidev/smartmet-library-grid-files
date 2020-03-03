#if 0

#include "GribFile.h"
#include "../common/Exception.h"
#include "../common/FileWriter.h"
#include "../common/GeneralFunctions.h"
#include "../grid/PrintOptions.h"
#include "../common/ShowFunction.h"


#define FUNCTION_TRACE FUNCTION_TRACE_OFF

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

GribFile::GribFile()
{
  FUNCTION_TRACE
  try
  {
    mPointCacheEnabled = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





GribFile::GribFile(const GribFile& other)
:GRID::PhysicalGridFile(other)
{
  FUNCTION_TRACE
  try
  {
    mPointCacheEnabled = false;
    for (auto msg = other.mMessages.begin(); msg != other.mMessages.end(); ++msg)
    {
      Message *message = new Message(*(msg->second));
      message->setGribFilePtr(this);
      mMessages.insert(std::pair<uint,Message*>(msg->first,message));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Copy constructor failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

GribFile::~GribFile()
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
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief The method memory maps the given file and reads its content
    into the current object.

       \param filename  The grib filename with a possible directory path.
*/

//uint mapCnt2 = 0;


void GribFile::read(std::string filename)
{
  FUNCTION_TRACE
  try
  {
    mFileSize = getFileSize(filename.c_str());
    if (mFileSize < 0)
      throw SmartMet::Spine::Exception(BCP,"The file '" + filename + "' does not exist!");

    setFileName(filename);

    // Map the entire file
    MappedFileParams params(filename);
    params.flags = boost::iostreams::mapped_file::readonly;
    params.length = mFileSize;
    mMappedFile.reset(new MappedFile(params));
    mIsMemoryMapped = true;

    mMemoryPtr = const_cast<char*>(mMappedFile->const_data());
    auto endAddr = mMemoryPtr + mFileSize;

    // Making sure that the file is read into the memory.
    /*
    for (long t= 0; t<fsize; t = t + 16)
    {
      mapCnt2 += startAddr[t];
    }
    */
    MemoryReader memoryReader(reinterpret_cast<unsigned char*>(mMemoryPtr),reinterpret_cast<unsigned char*>(endAddr));
    read(memoryReader);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,nullptr);
    exception.addParameter("File name ",filename);
    throw exception;
  }
}





/*! \brief The method searches message positions from the grib file and after that
    it creates and initializes message objects according to the found message information.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GribFile::read(MemoryReader& memoryReader)
{
  FUNCTION_TRACE
  try
  {
    mIsMemoryMapped = true;

    memoryReader.setReadPosition(0);
    auto gribs = searchMessageLocations(memoryReader);

    auto startAddr = memoryReader.getStartPtr();
    auto endAddr = memoryReader.getEndPtr();

    // Scan the messages
    uint sz = gribs.size();
    for (uint i = 0; i < sz; i++)
    {
      auto ptr = gribs[i];
      if ((i+1) < gribs.size())
        endAddr = reinterpret_cast<unsigned char*>(gribs[i+1]);
      else
        endAddr = memoryReader.getEndPtr();

      MemoryReader memoryReader2(ptr,endAddr);
      memoryReader2.setParentPtr(startAddr);

      readMessage(memoryReader2,i);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GribFile::write(std::string filename)
{
  FUNCTION_TRACE
  try
  {
    FileWriter dataWriter;
    dataWriter.createFile(filename.c_str());
    write(dataWriter);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void GribFile::write(DataWriter& dataWriter)
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GRID::GridFile* GribFile::createGridFile()
{
  FUNCTION_TRACE
  try
  {
    return (GRID::GridFile*)new GribFile(*this);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GribFile::deleteUsers()
{
  FUNCTION_TRACE
  try
  {
    mUserList.clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GribFile::clearCachedValues(uint hitsRequired,uint timePeriod) const
{
  FUNCTION_TRACE
  try
  {
    for (auto msg = mMessages.begin();  msg != mMessages.end(); ++msg)
    {
      if (msg->second->isRead())
        msg->second->clearCachedValues(hitsRequired,timePeriod);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GRID::Message* GribFile::newMessage()
{
  FUNCTION_TRACE
  try
  {
    GRIB2::Message *msg = new GRIB2::Message();

    msg->setBitmapSection(new BitmapSection());
    msg->setIdentificationSection(new IdentificationSection());
    msg->setGridSection(new GridSection());
    msg->setRepresentationSection(new RepresentationSection());
    msg->setIndicatorSection(new IndicatorSection());
    msg->setLocalSection(new LocalSection());
    msg->setProductSection(new ProductSection());
    msg->setDataSection(new DataSection());

    addMessage(msg);
    return msg;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GRID::Message* GribFile::newMessage(uint messageIndex,GRID::MessageInfo& messageInfo)
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

    GRIB2::Message *msg = new GRIB2::Message(this,messageIndex,messageInfo);
    mMessages.insert(std::pair<uint,Message*>(messageIndex,msg));
    return msg;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GribFile::addMessage(GRID::Message *message)
{
  FUNCTION_TRACE
  try
  {
    if (message == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'message' parameter points to nullptr!");


    GRIB2::Message *msg = (GRIB2::Message*)message;
    addMessage(msg);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void GribFile::addMessage(GRIB2::Message *message)
{
  FUNCTION_TRACE
  try
  {
    if (message == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'message' parameter points to nullptr!");

    message->setGribFilePtr(this);
    message->setMessageIndex(mMessages.size());

    mMessages.insert(std::pair<uint,Message*>(mMessages.size(),message));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method can be used for finding out the type of the file.

        \return   The type of the file (expressed as an enum value).
*/

T::FileType GribFile::getFileType() const
{
  FUNCTION_TRACE
  try
  {
    return T::FileTypeValue::Grib2;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the type of the file expressed as a string.

        \return   The type of the file (expressed as a string).
*/

std::string GribFile::getFileTypeString() const
{
  FUNCTION_TRACE
  try
  {
    return std::string("GRIB2");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief This method can be used in order to find out the number
    of the message in the current file.

       \return  The number of the messages in the current file.
*/

std::size_t GribFile::getNumberOfMessages()
{
  FUNCTION_TRACE
  try
  {
    if (!isMemoryMapped())
      mapToMemory();

    if (mMessages.size() == 0)
      return 0;

    auto last = mMessages.rbegin();
    return last->first + 1;
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

GRID::Message* GribFile::getMessageByIndex(std::size_t index)
{
  FUNCTION_TRACE
  try
  {
    if (!isMemoryMapped())
      mapToMemory();

    auto msg = mMessages.find(index);
    if (msg != mMessages.end())
    {
      if (msg->second != nullptr &&  !msg->second->isRead())
      {
        msg->second->read();
      }

      return msg->second;
    }

    return nullptr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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

T::Data_ptr_vec GribFile::searchMessageLocations(MemoryReader& memoryReader)
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

      int spos = memoryReader.search_string("GRIB");

      if (spos < 0)
        return gribs;

      memoryReader.setReadPosition(memoryReader.getReadPosition()+spos);

      bool valid = true;

      // Skip identifier, reserved and discipline and then read the edition number

      auto startPtr = memoryReader.getReadPtr();
      memoryReader.read_null(7);

      std::uint8_t edition = 0;
      memoryReader >> edition;

      // TODO: Keeping this genering for now
      if (missing(edition))
      {
        valid = false;
      }

      if (edition != 2)
      {
        valid = false;
      }

      std::uint64_t totalLength = 0;
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
        gribs.push_back(startPtr);
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

void GribFile::readMessage(MemoryReader& memoryReader, uint messageIndex)
{
  FUNCTION_TRACE
  try
  {
    // Scan messages one by one until the end section is encountered

    std::shared_ptr<BitmapSection> last_real_bitmap;

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

      Message *message = new Message();
      message->setGribFilePtr(this);
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
            if (msg->second != nullptr)
              message->copyMissingSections(*msg->second);
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





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void GribFile::print(std::ostream& stream,uint level,uint optionFlags) const
{
  FUNCTION_TRACE
  try
  {
    std::size_t messageCount = mMessages.size();

    stream << space(level) << "GribFile (version 2)\n";
    stream << space(level) << "- fileName         = " << getFileName() << "\n";
    stream << space(level) << "- fileId           = " << mFileId << "\n";
    stream << space(level) << "- deletionTime     = " << mFileDeletionTime << "\n";
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet


#endif
