#include "grib2/IndicatorSection.h"
#include "identification/GridDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "Message.h"

#include <iostream>

namespace SmartMet
{
namespace GRIB2
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
    mTotalLength = 0;
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

    sprintf(name,"%sindicator.discipline",prefix.c_str());
    attributeList.addAttribute(name,toString(getDiscipline()));

    sprintf(name,"%sindicator.disciplineString",prefix.c_str());
    attributeList.addAttribute(name,getDisciplineString());

    sprintf(name,"%sindicator.editionNumber",prefix.c_str());
    attributeList.addAttribute(name,toString(getEditionNumber()));

    sprintf(name,"%sindicator.totalLength",prefix.c_str());
    attributeList.addAttribute(name,toString(getTotalLength()));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    memoryReader >> mReserved;

    memoryReader >> mDiscipline;
    if (missing(mDiscipline))
    {
      SmartMet::Spine::Exception exception(BCP,"Discipline cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mEditionNumber;
    if (missing(mEditionNumber))
    {
      SmartMet::Spine::Exception exception(BCP,"GRIB edition number cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mTotalLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t IndicatorSection::getSectionLength() const
{
  try
  {
    return 16;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t IndicatorSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::indicator_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::UInt32_opt IndicatorSection::getIdentifier() const
{
  try
  {
    return mIdentifier;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::UInt16_opt IndicatorSection::getReserved() const
{
  try
  {
    return mReserved;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint8_t IndicatorSection::getDiscipline() const
{
  try
  {
    return *mDiscipline;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint8_t IndicatorSection::getEditionNumber() const
{
  try
  {
    return *mEditionNumber;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint64_t IndicatorSection::getTotalLength() const
{
  try
  {
    return mTotalLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::string IndicatorSection::getDisciplineString() const
{
  try
  {
    return Identification::gridDef.getGribTableValue(2,1,"0.0",getDiscipline());
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    stream << space(level) << "- filePosition     = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- identifier       = " << toString(getIdentifier()) << "\n";
    stream << space(level) << "- reserved         = " << toString(getReserved()) << "\n";
    stream << space(level) << "- discipline       = " << toString(getDiscipline()) << "\n";
    stream << space(level) << "- disciplineString = " << getDisciplineString() << "\n";
    stream << space(level) << "- editionNumber    = " << toString(getEditionNumber()) << "\n";
    stream << space(level) << "- totalLength      = " << toString(getTotalLength()) << "\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet
