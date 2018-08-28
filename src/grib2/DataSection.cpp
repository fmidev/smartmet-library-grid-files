#include "DataSection.h"
#include "GridSection.h"
#include "BitmapSection.h"
#include "RepresentationSection.h"
#include "Message.h"
#include "../grid/PrintOptions.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

DataSection::DataSection()
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





DataSection::DataSection(const DataSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mDataSize = other.mDataSize;
    mReleaseData = false;
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

DataSection::~DataSection()
{
  try
  {
    if (mReleaseData &&  mDataPtr != nullptr)
      delete mDataPtr;

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

void DataSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sdata.size",prefix.c_str());
    attributeList.addAttribute(name,toString(getDataSize()));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::setData(T::Data_ptr data,std::size_t size)
{
  try
  {
    if (mReleaseData &&  mDataPtr != nullptr)
    {
      delete mDataPtr;
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





void DataSection::setMessagePtr(Message *message)
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





bool DataSection::setProperty(uint propertyId,long long value)
{
  try
  {
    /*
    switch (propertyId)
    {
    }
    */
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

void DataSection::read(MemoryReader& memoryReader)
{
  try
  {
    const std::size_t section_fixed_size = 5;  // length and number = 4+1 bytes

    mFilePosition = memoryReader.getGlobalReadPosition();
    mDataPtr = nullptr;
    mDataSize = 0;

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
      memoryReader.read_null(static_cast<unsigned int>(mDataSize));
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void DataSection::write(DataWriter& dataWriter)
{
  try
  {
    const std::size_t section_fixed_size = 5;  // length and number = 4+1 bytes

    mFilePosition = dataWriter.getWritePosition();

    mSectionLength = section_fixed_size + mDataSize;
    mNumberOfSection = (std::uint8_t)Message::SectionNumber::data_section;

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

T::FilePosition DataSection::getFilePosition() const
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

std::uint32_t DataSection::getSectionLength() const
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

std::string DataSection::getSectionName() const
{
  try
  {
    return std::string("Data");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t DataSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::data_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t DataSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number
    // anyway
    if (mNumberOfSection)
      return *mNumberOfSection;

    return 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Data_ptr DataSection::getDataPtr() const
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





std::size_t DataSection::getDataSize() const
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

void DataSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition    = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength   = " << toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfSection = " << toString(mNumberOfSection) << "\n";
    stream << space(level) << "- dataLength      = " << toString(getDataSize()) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
