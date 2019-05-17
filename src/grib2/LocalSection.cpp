#include "LocalSection.h"
#include "Message.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"

#include <iostream>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class.*/

LocalSection::LocalSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
    mDataPtr = nullptr;
    mDataSize = 0;
    mReleaseData = false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

LocalSection::LocalSection(const LocalSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mNumberOfSection = other.mNumberOfSection;
    mDataSize = other.mDataSize;
    mReleaseData = other.mReleaseData;
    mDataPtr = nullptr;

    if (mDataSize > 0  &&  other.mDataPtr != nullptr)
    {
      mDataPtr = new uchar[mDataSize];
      memcpy(mDataPtr,other.mDataPtr,mDataSize);
      mReleaseData = true;
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}




/*! \brief The destructor of the class. */

LocalSection::~LocalSection()
{
  try
  {
    if (mReleaseData &&  mDataPtr != nullptr)
      delete[] mDataPtr;

    mDataPtr = nullptr;
    mDataSize = 0;
    mReleaseData = false;
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method sets the pointer to the Message -object in which the current section
    object belongs to. This helps the object to reference information in other sections.

        \param message    The Message -object pointer.
*/

void LocalSection::setMessagePtr(Message *message)
{
  try
  {
    mMessage = message;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void LocalSection::setData(T::Data_ptr data,std::size_t size)
{
  try
  {
    if (mReleaseData &&  mDataPtr != nullptr)
    {
      delete[] mDataPtr;
      mDataPtr = nullptr;
      mDataSize = 0;
    }

    mDataPtr = data;
    mDataSize = size;
    mReleaseData = true;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method is used for fetching a (long long ) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool LocalSection::getProperty(uint propertyId,long long& value)
{
  try
  {
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool LocalSection::setProperty(uint propertyId,long long value)
{
  try
  {
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void LocalSection::read(MemoryReader& memoryReader)
{
  try
  {
    const std::size_t section_fixed_size = 5;  // section length + number

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
      mDataPtr = memoryReader.getReadPtr();
      mDataSize = *mSectionLength - section_fixed_size;
      memoryReader.read_null(mDataSize);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void LocalSection::write(DataWriter& dataWriter)
{
  try
  {
    const std::size_t section_fixed_size = 5;  // section length + number

    mFilePosition = dataWriter.getWritePosition();

    mSectionLength = section_fixed_size + mDataSize;
    mNumberOfSection = (std::uint8_t)Message::SectionNumber::local_section;

    dataWriter << mSectionLength;
    dataWriter << mNumberOfSection;

    if (mDataPtr != nullptr  &&  mDataSize > 0)
    {
      dataWriter.write_data(mDataPtr,mDataSize);
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t LocalSection::getSectionLength() const
{
  try
  {
    if (mSectionLength)
      return *mSectionLength;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t LocalSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number anyway
    if (mNumberOfSection)
      return *mNumberOfSection;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Data_ptr LocalSection::getDataPtr() const
{
  try
  {
    return mDataPtr;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




std::size_t LocalSection::getDataSize() const
{
  try
  {
    return mDataSize;
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
