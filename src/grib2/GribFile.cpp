#include "GribFile.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "grid/PrintOptions.h"

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
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

GribFile::~GribFile()
{
  try
  {
    std::size_t messageCount = mMessages.size();

    for (std::size_t t=0; t<messageCount; t++)
    {
      delete mMessages[t];
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GribFile::getFileId() const
{
  try
  {
    return mFileId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GribFile::getGroupFlags() const
{
  try
  {
    return mGroupFlags;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GribFile::getProducerId() const
{
  try
  {
    return mProducerId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





uint GribFile::getGenerationId() const
{
  try
  {
    return mGenerationId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method returns the name and the path of the file.

       \return  The method returns the name and the path of the file.
*/

std::string GribFile::getFileName() const
{
  try
  {
    return mFileName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





time_t GribFile::getCheckTime() const
{
  try
  {
    return mCheckTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




void GribFile::setCheckTime(time_t checkTime)
{
  try
  {
    mCheckTime = checkTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




void GribFile::setFileId(uint fileId)
{
  try
  {
    mFileId = fileId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GribFile::setGroupFlags(uint groupFlags)
{
  try
  {
    mGroupFlags = groupFlags;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GribFile::setProducerId(uint producerId)
{
  try
  {
    mProducerId = producerId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}






void GribFile::setGenerationId(uint generationId)
{
  try
  {
    mGenerationId = generationId;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





void GribFile::setFileName(std::string fileName)
{
  try
  {
    mFileName = fileName;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method memory maps the given file and reads its content
    into the current object.

       \param path  The grib filename with a possible directory path.
*/

void GribFile::read(const bf::path& path)
{
  try
  {
    // Safety checks
    if (!bf::exists(path))
      throw SmartMet::Spine::Exception(BCP,"The file '" + path.string() + "' does not exist!");

    if (!bf::is_regular(path))
      throw SmartMet::Spine::Exception(BCP,"The file '" + path.string() + "' is not regular!");

    auto fsize = bf::file_size(path);
    mPath = path;
    setFileName(mPath.string());

    // Map the entire file
    MappedFileParams params(path.c_str());
    params.flags = boost::iostreams::mapped_file::readonly;
    params.length = fsize;
    mMappedFile.reset(new MappedFile(params));
    mIsMemoryMapped = true;

//    mMapping.reset(new bi::file_mapping(path.c_str(), bi::read_only));
//    mRegion.reset(new bi::mapped_region(*mMapping, bi::read_only, 0, fsize));

    auto startAddr = const_cast<char*>(mMappedFile->const_data());
    auto endAddr = startAddr + fsize;

    MemoryReader memoryReader((unsigned char*)startAddr,(unsigned char*)endAddr);
    read(memoryReader);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,exception_operation_failed,NULL);
    exception.addParameter("File name ",path.string());
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
    uint sz = (uint)gribs.size();
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used for finding out the type of the file.

        \return   The type of the file (expressed as an enum value).
*/

T::FileType GribFile::getFileType() const
{
  try
  {
    return T::FileType::Grib2;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used in order to find out the number
    of the message in the current file.

       \return  The number of the messages in the current file.
*/

std::size_t GribFile::getNumberOfMessages() const
{
  try
  {
    return mMessages.size();
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief This method can be used in order to get pointer to the message object
    according to its index. The current message pointer can be used for accessing
    data inside the current message.

        \param index  The message index (0..N).
*/

GRID::Message* GribFile::getMessageByIndex(std::size_t index) const
{
  try
  {
    if (index >= mMessages.size())
      return NULL;
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Message search failed!",NULL);
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

    boost::shared_ptr<BitmapSection> last_real_bitmap;

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

      Message *message = new Message(this);
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
      }

      message->initParameterInfo();

      mMessages.push_back(message);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Message addition failed!",NULL);
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
    stream << space(level) << "- groupFlags       = " << mGroupFlags << "\n";
    stream << space(level) << "- producerId       = " << mProducerId << "\n";
    stream << space(level) << "- generationId     = " << mGenerationId << "\n";
    stream << space(level) << "- numberOfMessages = " << messageCount << "\n";

    if (optionFlags & GRID::PrintFlag::no_messages)
      return;

    for (std::size_t t=0; t<messageCount; t++)
    {
      mMessages[t]->print(stream,level+1,optionFlags);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet
