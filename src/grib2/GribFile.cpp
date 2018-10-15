#include "GribFile.h"
#include "../common/Exception.h"
#include "../common/FileWriter.h"
#include "../common/GeneralFunctions.h"
#include "../grid/PrintOptions.h"

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

GribFile::GribFile()
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





GribFile::GribFile(const GribFile& other)
:GRID::PhysicalGridFile(other)
{
  try
  {
    for (auto msg = other.mMessages.begin(); msg != other.mMessages.end(); ++msg)
    {
      Message *message = new Message(*(*msg));
      message->setGribFilePtr(this);
      mMessages.push_back(message);
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
  try
  {
    for (auto msg = mMessages.begin();  msg != mMessages.end(); ++msg)
    {
      delete (*msg);
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

void GribFile::read(std::string filename)
{
  try
  {
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

//    mMapping.reset(new bi::file_mapping(path.c_str(), bi::read_only));
//    mRegion.reset(new bi::mapped_region(*mMapping, bi::read_only, 0, fsize));

    auto startAddr = const_cast<char*>(mMappedFile->const_data());
    auto endAddr = startAddr + fsize;

    MemoryReader memoryReader(reinterpret_cast<unsigned char*>(startAddr),reinterpret_cast<unsigned char*>(endAddr));
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





void GribFile::write(DataWriter& dataWriter)
{
  try
  {
    for (auto msg = mMessages.begin();  msg != mMessages.end(); ++msg)
    {
      (*msg)->write(dataWriter);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GRID::GridFile* GribFile::createGridFile()
{
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
  try
  {
    mUserList.clear();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





GRID::Message* GribFile::newMessage()
{
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





void GribFile::addMessage(GRID::Message *message)
{
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
  try
  {
    if (message == nullptr)
      throw SmartMet::Spine::Exception(BCP,"The 'message' parameter points to nullptr!");

    message->setGribFilePtr(this);
    message->setMessageIndex(mMessages.size());
    mMessages.push_back(message);
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
  try
  {
    if (!isMemoryMapped())
      mapToMemory();

    return mMessages.size();
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
  try
  {
    if (!isMemoryMapped())
      mapToMemory();

    if (index >= mMessages.size())
      return nullptr;
    /*
    {
      SmartMet::Spine::Exception exception(BCP,"Index out of the range!");
      exception.addParameter("Index",std::to_string(index));
      exception.addParameter("Range","0.." + std::to_string(mMessages.size()));
      throw exception;
    }
    */

    return mMessages[index];
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

      if (!memoryReader.peek_string("GRIB"))
      {
        memoryReader.read_null(1);
      }
      else
      {
        // Found message.

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
          //SmartMet::Spine::Exception exception(BCP,"GRIB edition number missing (255)!");
          //exception.addParameter("Read position",uint64_toHex(memoryReader.getReadPosition()-1));
          //throw exception;
        }

        if (edition != 2)
        {
          valid = false;
          //SmartMet::Spine::Exception exception(BCP,"Wrong GRIB edition number '" +
          //                         std::to_string(static_cast<int>(edition)) + "'!");
          //exception.addParameter("Read position",uint64_toHex(memoryReader.getReadPosition()-1));
          //throw exception;
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
      message->read(memoryReader);

      // Complete the sections from the previous message
      if (!mMessages.empty())
        message->copyMissingSections(*mMessages.back());

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

      mMessages.push_back(message);
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
      (*msg)->print(stream,level+1,optionFlags);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet
