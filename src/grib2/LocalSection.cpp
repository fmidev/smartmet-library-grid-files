#include "grib2/LocalSection.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "Message.h"

#include <iostream>

const std::size_t section_fixed_size = 5;  // section length + number

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

LocalSection::LocalSection(Message *message)
{
  try
  {
    mMessage = message;
    mFilePosition = 0;
    mData = NULL;
    mDataLength = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

LocalSection::~LocalSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void LocalSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void LocalSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    memoryReader >> mSectionLength;
    if (missing(mSectionLength))
    {
      SmartMet::Spine::Exception exception(BCP,"Section length cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfSection;

    if (*mSectionLength > section_fixed_size)
    {
      mData = memoryReader.getReadPtr();
      mDataLength = *mSectionLength - section_fixed_size;
      memoryReader.read_null(mDataLength);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition LocalSection::getFilePosition() const
{
  try
  {
    return mFilePosition;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t LocalSection::getSectionLength() const
{
  try
  {
    return *mSectionLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the name of the section. */

std::string LocalSection::getSectionName() const
{
  try
  {
    return std::string("Local");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t LocalSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::local_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t LocalSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number anyway
    return *mNumberOfSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





T::Data_ptr LocalSection::getDataPtr() const
{
  try
  {
    return mData;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}




std::size_t LocalSection::getDataSize() const
{
  try
  {
    return mDataLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void LocalSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition    = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength   = " <<  toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfSection = " <<  toString(mNumberOfSection) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
