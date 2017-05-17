#include "IndicatorSection.h"
#include "Message.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"

#include <iostream>

namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

IndicatorSection::IndicatorSection(Message *message)
{
  try
  {
    mMessage = message;
    mFilePosition = 0;
    mIdentifier = 0;
    mTotalLength = 0;
    mEditionNumber = 0;
}
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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

    memoryReader >> mIdentifier;
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::uint32_t IndicatorSection::getIdentifier() const
{
  try
  {
    return mIdentifier;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    stream << space(level) << "- identifier    = " << toString(getIdentifier()) << "\n";
    stream << space(level) << "- totalLength   = " << toString(getTotalLength()) << "\n";
    stream << space(level) << "- editionNumber = " << toString(getEditionNumber()) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}


}  // namespace GRIB1
}  // namespace SmartMet
