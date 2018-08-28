#include "IdentificationSection.h"
#include "Message.h"
#include "../identification/GridDef.h"
#include "../common/Exception.h"
#include "../common/GeneralFunctions.h"

#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>


namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

IdentificationSection::IdentificationSection()
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

IdentificationSection::IdentificationSection(const IdentificationSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mNumberOfSection = other.mNumberOfSection;
    mCentre = other.mCentre;
    mSubCentre = other.mSubCentre;
    mTablesVersion = other.mTablesVersion;
    mLocalTablesVersion = other.mLocalTablesVersion;
    mSignificanceOfReferenceTime = other.mSignificanceOfReferenceTime;
    mYear = other.mYear;
    mMonth = other.mMonth;
    mDay = other.mDay;
    mHour = other.mHour;
    mMinute = other.mMinute;
    mSecond = other.mSecond;
    mProductionStatusOfProcessedData = other.mProductionStatusOfProcessedData;
    mTypeOfProcessedData = other.mTypeOfProcessedData;
    mDataPtr = nullptr;
    mDataSize = other.mDataSize;
    mReleaseData = false;

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

IdentificationSection::~IdentificationSection()
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setMessagePtr(Message *message)
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





bool IdentificationSection::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::IdentificationSection::Centre:
        setCentre(value);
        return true;

      case Property::IdentificationSection::SubCentre:
        setSubCentre(value);
        return true;

      case Property::IdentificationSection::TablesVersion:
        setTablesVersion(value);
        return true;

      case Property::IdentificationSection::LocalTablesVersion:
        setLocalTablesVersion(value);
        return true;

      case Property::IdentificationSection::SignificanceOfReferenceTime:
        setSignificanceOfReferenceTime(value);
        return true;

      case Property::IdentificationSection::Year:
        setYear(value);
        return true;

      case Property::IdentificationSection::Month:
        setMonth(value);
        return true;

      case Property::IdentificationSection::Day:
        setDay(value);
        return true;

      case Property::IdentificationSection::Hour:
        setHour(value);
        return true;

      case Property::IdentificationSection::Minute:
        setMinute(value);
        return true;

      case Property::IdentificationSection::Second:
        setSecond(value);
        return true;

      case Property::IdentificationSection::ProductionStatusOfProcessedData:
        setProductionStatusOfProcessedData(value);
        return true;

      case Property::IdentificationSection::TypeOfProcessedData:
        setTypeOfProcessedData(value);
        return true;
    }
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

void IdentificationSection::read(MemoryReader& memoryReader)
{
  try
  {
    const std::size_t section_fixed_size = 21;

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
      mDataPtr = memoryReader.getReadPtr();
      mDataSize = *mSectionLength - section_fixed_size;
      memoryReader.read_null(mDataSize);
    }

    // Note: Table 0 ends like this:
    //   # 255 Missing value
    //   255 consensus Consensus
    // However, the centre takes two bytes, and hence the missing value should be 0xffff

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::write(DataWriter& dataWriter)
{
  try
  {
    const std::size_t section_fixed_size = 21;

    if (missing(mCentre))
      throw SmartMet::Spine::Exception(BCP,"GRIB centre cannot be missing!");

    if (missing(mYear))
      throw SmartMet::Spine::Exception(BCP,"GRIB data year cannot be missing!");

    if (missing(mMonth))
      throw SmartMet::Spine::Exception(BCP,"GRIB data month cannot be missing!");

    if (missing(mDay))
      throw SmartMet::Spine::Exception(BCP,"GRIB data day cannot be missing!");

    if (missing(mHour))
      throw SmartMet::Spine::Exception(BCP,"GRIB data hour cannot be missing!");

    if (missing(mMinute))
      throw SmartMet::Spine::Exception(BCP,"GRIB data minute cannot be missing!");

    if (missing(mSecond))
      throw SmartMet::Spine::Exception(BCP,"GRIB data second cannot be missing!");

    mFilePosition = dataWriter.getWritePosition();
    mSectionLength = section_fixed_size + mDataSize;
    mNumberOfSection = GRIB2::Message::SectionNumber::identification_section;

    dataWriter << mSectionLength;
    dataWriter << mNumberOfSection;
    dataWriter << mCentre;
    dataWriter << mSubCentre;
    dataWriter << mTablesVersion;
    dataWriter << mLocalTablesVersion;
    dataWriter << mSignificanceOfReferenceTime;
    dataWriter << mYear;
    dataWriter << mMonth;
    dataWriter << mDay;
    dataWriter << mHour;
    dataWriter << mMinute;
    dataWriter << mSecond;
    dataWriter << mProductionStatusOfProcessedData;
    dataWriter << mTypeOfProcessedData;

    if (mDataPtr != nullptr  &&  mDataSize > 0)
      dataWriter.write_data(mDataPtr,mDataSize);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t IdentificationSection::getSectionLength() const
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

std::string IdentificationSection::getSectionName() const
{
  try
  {
    return std::string("Identification");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

T::UInt8_opt IdentificationSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number anyway
    return mNumberOfSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}




T::UInt16_opt IdentificationSection::getCentre() const
{
  try
  {
    return mCentre;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt16_opt IdentificationSection::getYear() const
{
  try
  {
    return mYear;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt8_opt IdentificationSection::getMonth() const
{
  try
  {
    return mMonth;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt8_opt IdentificationSection::getDay() const
{
  try
  {
    return mDay;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt8_opt IdentificationSection::getHour() const
{
  try
  {
    return mHour;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt8_opt IdentificationSection::getMinute() const
{
  try
  {
    return mMinute;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::UInt8_opt IdentificationSection::getSecond() const
{
  try
  {
    return mSecond;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





T::Data_ptr IdentificationSection::getReservedDataPtr() const
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





void IdentificationSection::setCentre(T::UInt16_opt centre)
{
  try
  {
    mCentre = centre;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setSubCentre(T::UInt16_opt subCentre)
{
  try
  {
    mSubCentre = subCentre;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setTablesVersion(T::UInt8_opt tablesVersion)
{
  try
  {
    mTablesVersion = tablesVersion;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setLocalTablesVersion(T::UInt8_opt localTablesVersion)
{
  try
  {
    mLocalTablesVersion = localTablesVersion;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setSignificanceOfReferenceTime(T::UInt8_opt significanceOfRererenceTime)
{
  try
  {
    mSignificanceOfReferenceTime = significanceOfRererenceTime;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setYear(T::UInt16_opt year)
{
  try
  {
    mYear = year;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setMonth(T::UInt8_opt month)
{
  try
  {
    if (month  &&  ((*month) < 1 || (*month) > 12))
    {
      SmartMet::Spine::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(month));
      exception.addParameter("Value Range","1..12");
      throw exception;
    }

    mMonth = month;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setDay(T::UInt8_opt day)
{
  try
  {
    if (day  &&  ((*day) < 1 ||  (*day) > 31))
    {
      SmartMet::Spine::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(day));
      exception.addParameter("Value Range","1..31");
      throw exception;
    }

    mDay = day;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setHour(T::UInt8_opt hour)
{
  try
  {
    if (hour  && (*hour) > 23)
    {
      SmartMet::Spine::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(hour));
      exception.addParameter("Value Range","0..23");
      throw exception;
    }

    mHour = hour;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setMinute(T::UInt8_opt minute)
{
  try
  {
    if (minute && (*minute) > 59)
    {
      SmartMet::Spine::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(minute));
      exception.addParameter("Value Range","0..59");
      throw exception;
    }

    mMinute = minute;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setSecond(T::UInt8_opt second)
{
  try
  {
    if (second  && (*second) > 59)
    {
      SmartMet::Spine::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(second));
      exception.addParameter("Value Range","0..59");
      throw exception;
    }

    mSecond = second;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setProductionStatusOfProcessedData(T::UInt8_opt productionStatusOfProcessedData)
{
  try
  {
    mProductionStatusOfProcessedData = productionStatusOfProcessedData;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}





void IdentificationSection::setTypeOfProcessedData(T::UInt8_opt typeOfProcessedData)
{
  try
  {
    mTypeOfProcessedData = typeOfProcessedData;
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
    stream << space(level) << "- reserved                        = " << mDataSize << " bytes\n";
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,nullptr);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
