#include "IndicatorSection.h"
#include "Message.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"

#include <iostream>

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

IndicatorSection::IndicatorSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
    mIdentifier[0] = 'G';
    mIdentifier[1] = 'R';
    mIdentifier[2] = 'I';
    mIdentifier[3] = 'B';
    mTotalLength = 0;
    mEditionNumber = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

IndicatorSection::IndicatorSection(const IndicatorSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    memcpy(mIdentifier,other.mIdentifier,4);
    mTotalLength = other.mTotalLength;
    mEditionNumber = other.mEditionNumber;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

IndicatorSection::~IndicatorSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void IndicatorSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sindicator.editionNumber",prefix.c_str());
    attributeList.addAttribute(name,toString(getEditionNumber()));

    sprintf(name,"%sindicator.totalLength",prefix.c_str());
    attributeList.addAttribute(name,toString(getTotalLength()));
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

bool IndicatorSection::getProperty(uint propertyId,long long& value)
{
  try
  {
    switch (propertyId)
    {
      case Property::IndicatorSection::EditionNumber:
        value = mEditionNumber;
        return true;
    }
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

bool IndicatorSection::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::IndicatorSection::EditionNumber:
        mEditionNumber = value;
        return true;
    }
    return false;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method is used for setting a (double) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool IndicatorSection::setProperty(uint propertyId,double value)
{
  try
  {
    return setProperty(propertyId,C_INT64(value));
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

void IndicatorSection::setMessagePtr(Message *message)
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





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void IndicatorSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    uchar id[4];
    memoryReader.read_data(id,4);
    if (memcmp(mIdentifier,id,4) != 0)
    {
      SmartMet::Spine::Exception exception(BCP,"Not a grib file!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    mTotalLength = memoryReader.read_uint24();

    memoryReader >> mEditionNumber;
    if (mEditionNumber != 1)
    {
      SmartMet::Spine::Exception exception(BCP,"Wrong edition number!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
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

void IndicatorSection::write(DataWriter& dataWriter)
{
  try
  {
    mFilePosition = dataWriter.getWritePosition();
    mEditionNumber = 1;

    dataWriter.write_data(mIdentifier,4);
    dataWriter.write_uint24(mTotalLength);
    dataWriter << mEditionNumber;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition IndicatorSection::getFilePosition() const
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

std::uint32_t IndicatorSection::getSectionLength() const
{
  try
  {
    return 8;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the name of the section. */

std::string IndicatorSection::getSectionName() const
{
  try
  {
    return std::string("Indicator");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the section number. */

std::uint8_t IndicatorSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::indicator_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::uint8_t IndicatorSection::getEditionNumber() const
{
  try
  {
    return mEditionNumber;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





std::uint32_t IndicatorSection::getTotalLength() const
{
  try
  {
    return mTotalLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IndicatorSection::setTotalLength(std::uint32_t length)
{
  try
  {
    mTotalLength = length;
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

void IndicatorSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition  = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- totalLength   = " << toString(getTotalLength()) << "\n";
    stream << space(level) << "- editionNumber = " << toString(getEditionNumber()) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
