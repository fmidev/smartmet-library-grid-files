#include "IndicatorSection.h"
#include "Message.h"
#include "../identification/GridDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"

#include <iostream>

namespace SmartMet
{
namespace GRIB2
{



/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

IndicatorSection::IndicatorSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
    mTotalLength = 0;
    mIdentifier[0] = 'G';
    mIdentifier[1] = 'R';
    mIdentifier[2] = 'I';
    mIdentifier[3] = 'B';
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
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
    mReserved = other.mReserved;
    mDiscipline = other.mDiscipline;
    mEditionNumber = other.mEditionNumber;
    mTotalLength = other.mTotalLength;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
      case Property::IndicatorSection::Discipline:
        setDiscipline(value);
        return true;

      case Property::IndicatorSection::EditionNumber:
        setEditionNumber(value);
        return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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

    memoryReader.read_data(mIdentifier,4);
    memoryReader >> mReserved;

    memoryReader >> mDiscipline;
    if (missing(mDiscipline))
    {
      Fmi::Exception exception(BCP,"Discipline cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mEditionNumber;
    if (missing(mEditionNumber))
    {
      Fmi::Exception exception(BCP,"GRIB edition number cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mTotalLength;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void IndicatorSection::write(DataWriter& dataWriter)
{
  try
  {
    if (missing(mDiscipline))
      throw Fmi::Exception(BCP,"Discipline cannot be missing!");

    mEditionNumber = 2;
    //if (missing(mEditionNumber))
    //  throw Fmi::Exception(BCP,"GRIB edition number cannot be missing!");


    mFilePosition = dataWriter.getWritePosition();

    dataWriter.write_data(mIdentifier,4);
    dataWriter << mReserved;
    dataWriter << mDiscipline;
    dataWriter << mEditionNumber;
    dataWriter << mTotalLength;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::UInt8_opt IndicatorSection::getDiscipline() const
{
  try
  {
    return mDiscipline;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::UInt8_opt IndicatorSection::getEditionNumber() const
{
  try
  {
    return mEditionNumber;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IndicatorSection::setDiscipline(std::uint8_t discipline)
{
  try
  {
    mDiscipline = discipline;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IndicatorSection::setEditionNumber(std::uint8_t editionNumber)
{
  try
  {
    mEditionNumber = editionNumber;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IndicatorSection::setTotalLength(std::uint64_t totalLength)
{
  try
  {
    mTotalLength = totalLength;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    stream << space(level) << "- reserved         = " << toString(getReserved()) << "\n";
    stream << space(level) << "- discipline       = " << toString(getDiscipline()) << "\n";
    stream << space(level) << "- disciplineString = " << getDisciplineString() << "\n";
    stream << space(level) << "- editionNumber    = " << toString(getEditionNumber()) << "\n";
    stream << space(level) << "- totalLength      = " << toString(getTotalLength()) << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}


}  // namespace GRIB2
}  // namespace SmartMet
