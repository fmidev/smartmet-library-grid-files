#include "grib2/IdentificationSection.h"
#include "identification/GridDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "Message.h"

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

const std::size_t section_fixed_size = 22;

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

IdentificationSection::IdentificationSection(Message *message)
{
  try
  {
    mMessage = message;
    mFilePosition = 0;
    mData = NULL;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

IdentificationSection::~IdentificationSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void IdentificationSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sidentification.centre.id",prefix.c_str());
    attributeList.addAttribute(name,toString(mCentre));

    sprintf(name,"%sidentification.centre.name",prefix.c_str());
    attributeList.addAttribute(name,Identification::gridDef.getGribTableValue(1,0,"0",mCentre));

    sprintf(name,"%sidentification.subCentre",prefix.c_str());
    attributeList.addAttribute(name,toString(mSubCentre));

    sprintf(name,"%sidentification.tablesVersion",prefix.c_str());
    attributeList.addAttribute(name,toString(mTablesVersion));

    sprintf(name,"%sidentification.localTablesVersion",prefix.c_str());
    attributeList.addAttribute(name,toString(mLocalTablesVersion));

    sprintf(name,"%sidentification.significanceOfReferenceTime",prefix.c_str());
    attributeList.addAttribute(name,toString(mSignificanceOfReferenceTime));

    sprintf(name,"%sidentification.significanceOfReferenceTimeString",prefix.c_str());
    attributeList.addAttribute(name,Identification::gridDef.getGribTableValue(2,*mTablesVersion,"1.2", mSignificanceOfReferenceTime));

    sprintf(name,"%sidentification.referenceTime.year",prefix.c_str());
    attributeList.addAttribute(name,toString(mYear));

    sprintf(name,"%sidentification.referenceTime.month",prefix.c_str());
    attributeList.addAttribute(name,toString(mMonth));

    sprintf(name,"%sidentification.referenceTime.day",prefix.c_str());
    attributeList.addAttribute(name,toString(mDay));

    sprintf(name,"%sidentification.referenceTime.hour",prefix.c_str());
    attributeList.addAttribute(name,toString(mHour));

    sprintf(name,"%sidentification.referenceTime.minute",prefix.c_str());
    attributeList.addAttribute(name,toString(mMinute));

    sprintf(name,"%sidentification.referenceTime.second",prefix.c_str());
    attributeList.addAttribute(name,toString(mSecond));

    sprintf(name,"%sidentification.processedData.productionStatus",prefix.c_str());
    attributeList.addAttribute(name,toString(mProductionStatusOfProcessedData));

    sprintf(name,"%sidentification.processedData.productionStatusString",prefix.c_str());
    attributeList.addAttribute(name,Identification::gridDef.getGribTableValue(2,*mTablesVersion,"1.3", mProductionStatusOfProcessedData));

    sprintf(name,"%sidentification.processedData.type",prefix.c_str());
    attributeList.addAttribute(name,toString(mTypeOfProcessedData));

    sprintf(name,"%sidentification.processedData.typeString",prefix.c_str());
    attributeList.addAttribute(name,Identification::gridDef.getGribTableValue(2,*mTablesVersion,"1.4",mTypeOfProcessedData));
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void IdentificationSection::read(MemoryReader& memoryReader)
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

    memoryReader >> mCentre;
    if (missing(mCentre))
    {
      SmartMet::Spine::Exception exception(BCP,"GRIB centre cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-2));
      throw exception;
    }

    memoryReader >> mSubCentre;
    memoryReader >> mTablesVersion;
    memoryReader >> mLocalTablesVersion;
    memoryReader >> mSignificanceOfReferenceTime;

    memoryReader >> mYear;
    if (missing(mYear))
    {
      SmartMet::Spine::Exception exception(BCP,"GRIB data year cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-2));
      throw exception;
    }

    memoryReader >> mMonth;
    if (missing(mMonth))
    {
      SmartMet::Spine::Exception exception(BCP,"GRIB data month cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mDay;
    if (missing(mDay))
    {
      SmartMet::Spine::Exception exception(BCP,"GRIB data day cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mHour;
    if (missing(mHour))
    {
      SmartMet::Spine::Exception exception(BCP,"GRIB data hour cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mMinute;
    if (missing(mMinute))
    {
      SmartMet::Spine::Exception exception(BCP,"GRIB data minute cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mSecond;
    if (missing(mSecond))
    {
      SmartMet::Spine::Exception exception(BCP,"GRIB data second cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mProductionStatusOfProcessedData;
    memoryReader >> mTypeOfProcessedData;

    if (*mSectionLength > section_fixed_size)
    {
      mData = memoryReader.getReadPtr();
      memoryReader.read_null(*mSectionLength - section_fixed_size);
    }

    // Note: Table 0 ends like this:
    //   # 255 Missing value
    //   255 consensus Consensus
    // However, the centre takes two bytes, and hence the missing value should be 0xffff

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition IdentificationSection::getFilePosition() const
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

std::uint32_t IdentificationSection::getSectionLength() const
{
  try
  {
    return *mSectionLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the name of the section. */

std::string IdentificationSection::getSectionName() const
{
  try
  {
    return std::string("Identification");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t IdentificationSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::identification_section;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t IdentificationSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number anyway
    return *mNumberOfSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::TimeString IdentificationSection::getReferenceTime() const
{
  try
  {
    char st[100];
    sprintf(st,"%04u%02u%02uT%02u%02u%02u",*mYear,*mMonth,*mDay,*mHour,*mMinute,*mSecond);
    return std::string(st);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




std::uint16_t IdentificationSection::getCentre() const
{
  try
  {
    return *mCentre;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::UInt16_opt IdentificationSection::getSubCentre() const
{
  try
  {
    return mSubCentre;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::UInt8_opt IdentificationSection::getTablesVersion() const
{
  try
  {
    // A missing value implies local tables are used
    return mTablesVersion;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::UInt8_opt IdentificationSection::getLocalTablesVersion() const
{
  try
  {
    return mLocalTablesVersion;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::UInt8_opt IdentificationSection::getSignificanceOfReferenceTime() const
{
  try
  {
    return mSignificanceOfReferenceTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint16_t IdentificationSection::getYear() const
{
  try
  {
    return *mYear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint8_t IdentificationSection::getMonth() const
{
  try
  {
    return *mMonth;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint8_t IdentificationSection::getDay() const
{
  try
  {
    return *mDay;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint8_t IdentificationSection::getHour() const
{
  try
  {
    return *mHour;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint8_t IdentificationSection::getMinute() const
{
  try
  {
    return *mMinute;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





std::uint8_t IdentificationSection::getSecond() const
{
  try
  {
    return *mSecond;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::UInt8_opt IdentificationSection::getProductionStatusOfProcessedData() const
{
  try
  {
    return mProductionStatusOfProcessedData;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::UInt8_opt IdentificationSection::getTypeOfProcessedData() const
{
  try
  {
    return mTypeOfProcessedData;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





T::Data_ptr IdentificationSection::getReservedDataPtr() const
{
  try
  {
    return mData;
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

void IdentificationSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition                    = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength                   = " <<  toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfSection                 = " <<  toString(mNumberOfSection) << "\n";
    stream << space(level) << "- centre                          = " <<  toString(mCentre) << " (" << Identification::gridDef.getGribTableValue(1,0,"0",mCentre) << ")\n";
    stream << space(level) << "- subCentre                       = " <<  toString(mSubCentre) << "\n";
    stream << space(level) << "- tablesVersion                   = " << toString(mTablesVersion) << "\n";
    stream << space(level) << "- localTablesVersion              = " << toString(mLocalTablesVersion) << "\n";  // table 1.1 is local, not dumping "1.1"
    stream << space(level) << "- significanceOfReferenceTime     = " << toString(mSignificanceOfReferenceTime) << " (" << Identification::gridDef.getGribTableValue(2,*mTablesVersion,"1.2", mSignificanceOfReferenceTime)<< ")\n";
    stream << space(level) << "- year                            = " << toString(mYear) << "\n";
    stream << space(level) << "- month                           = " << toString(mMonth) << "\n";
    stream << space(level) << "- day                             = " << toString(mDay) << "\n";
    stream << space(level) << "- hour                            = " << toString(mHour) << "\n";
    stream << space(level) << "- minute                          = " << toString(mMinute) << "\n";
    stream << space(level) << "- second                          = " << toString(mSecond) << "\n";
    stream << space(level) << "- productionStatusOfProcessedData = " << toString(mProductionStatusOfProcessedData) << " (" << Identification::gridDef.getGribTableValue(2,*mTablesVersion,"1.3", mProductionStatusOfProcessedData) << ")\n";
    stream << space(level) << "- typeOfProcessedData             = " << toString(mTypeOfProcessedData) << " (" << Identification::gridDef.getGribTableValue(2,*mTablesVersion,"1.4",mTypeOfProcessedData) << ")\n";

    // Bytes 22-nn are reserved for future use
    auto length = getSectionLength();
    if (length > section_fixed_size)
      stream << space(level) << "- reserved = " << (int)(length - section_fixed_size) << " bytes\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
