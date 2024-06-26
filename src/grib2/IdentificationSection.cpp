#include "IdentificationSection.h"
#include "Message.h"
#include "../identification/GridDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"

#include <iostream>


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
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Constructor failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

IdentificationSection::~IdentificationSection()
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
    Fmi::Exception exception(BCP,"Destructor failed",nullptr);
    exception.printError();
  }
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void IdentificationSection::getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sidentification.centre.id",prefix.c_str());
    attributeList.addAttribute(name,toString(mCentre));

    sprintf(name,"%sidentification.subCentre",prefix.c_str());
    attributeList.addAttribute(name,toString(mSubCentre));

    sprintf(name,"%sidentification.tablesVersion",prefix.c_str());
    attributeList.addAttribute(name,toString(mTablesVersion));

    sprintf(name,"%sidentification.localTablesVersion",prefix.c_str());
    attributeList.addAttribute(name,toString(mLocalTablesVersion));

    sprintf(name,"%sidentification.significanceOfReferenceTime",prefix.c_str());
    attributeList.addAttribute(name,toString(mSignificanceOfReferenceTime));

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

    sprintf(name,"%sidentification.processedData.type",prefix.c_str());
    attributeList.addAttribute(name,toString(mTypeOfProcessedData));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool IdentificationSection::getAttributeValue(const char *attributeName, std::string& attributeValue) const
{
  try
  {
    if (strcasecmp(attributeName,"centre") == 0)
    {
      attributeValue = toString(mCentre);
      return true;
    }

    if (strcasecmp(attributeName,"subCentre") == 0)
    {
      attributeValue = toString(mSubCentre);
      return true;
    }

    if (strcasecmp(attributeName,"tablesVersion") == 0)
    {
      attributeValue = toString(mTablesVersion);
      return true;
    }

    if (strcasecmp(attributeName,"localTablesVersion") == 0)
    {
      attributeValue = toString(mLocalTablesVersion);
      return true;
    }

    if (strcasecmp(attributeName,"significanceOfReferenceTime") == 0)
    {
      attributeValue = toString(mSignificanceOfReferenceTime);
      return true;
    }

    if (strcasecmp(attributeName,"productionStatusOfProcessedData") == 0)
    {
      attributeValue = toString(mProductionStatusOfProcessedData);
      return true;
    }

    if (strcasecmp(attributeName,"typeOfProcessedData") == 0)
    {
      attributeValue = toString(mTypeOfProcessedData);
      return true;
    }

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




bool IdentificationSection::hasAttributeValue(const char *attributeName, const char *attributeValue) const
{
  try
  {
    if (strcasecmp(attributeName,"centre") == 0  &&  strcasecmp(attributeValue,toString(mCentre).c_str()) == 0)
      return true;

    if (strcasecmp(attributeName,"subCentre") == 0  &&  strcasecmp(attributeValue,toString(mSubCentre).c_str()) == 0)
      return true;

    if (strcasecmp(attributeName,"tablesVersion") == 0  &&  strcasecmp(attributeValue,toString(mTablesVersion).c_str()) == 0)
      return true;

    if (strcasecmp(attributeName,"localTablesVersion") == 0  &&  strcasecmp(attributeValue,toString(mLocalTablesVersion).c_str()) == 0)
      return true;

    if (strcasecmp(attributeName,"significanceOfReferenceTime") == 0  &&  strcasecmp(attributeValue,toString(mSignificanceOfReferenceTime).c_str()) == 0)
      return true;

    if (strcasecmp(attributeName,"productionStatusOfProcessedData") == 0  &&  strcasecmp(attributeValue,toString(mProductionStatusOfProcessedData).c_str()) == 0)
      return true;

    if (strcasecmp(attributeName,"typeOfProcessedData") == 0  &&  strcasecmp(attributeValue,toString(mTypeOfProcessedData).c_str()) == 0)
      return true;

    return false;
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

void IdentificationSection::setMessagePtr(Message *message)
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

bool IdentificationSection::getProperty(uint propertyId,long long& value)
{
  try
  {
    switch (propertyId)
    {
      case Property::IdentificationSection::Centre:
        value = *mCentre;
        return true;

      case Property::IdentificationSection::SubCentre:
        value = *mSubCentre;
        return true;

      case Property::IdentificationSection::TablesVersion:
        value = *mTablesVersion;
        return true;

      case Property::IdentificationSection::LocalTablesVersion:
        value = *mLocalTablesVersion;
        return true;

      case Property::IdentificationSection::SignificanceOfReferenceTime:
        value = *mSignificanceOfReferenceTime;
        return true;

      case Property::IdentificationSection::Year:
        value = *mYear;
        return true;

      case Property::IdentificationSection::Month:
        value = *mMonth;
        return true;

      case Property::IdentificationSection::Day:
        value = *mDay;
        return true;

      case Property::IdentificationSection::Hour:
        value = *mHour;
        return true;

      case Property::IdentificationSection::Minute:
        value = *mMinute;
        return true;

      case Property::IdentificationSection::Second:
        value = *mSecond;
        return true;

      case Property::IdentificationSection::ProductionStatusOfProcessedData:
        value = *mProductionStatusOfProcessedData;
        return true;

      case Property::IdentificationSection::TypeOfProcessedData:
        value = *mTypeOfProcessedData;
        return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IdentificationSection::getProperties(T::PropertySettingVec& properties)
{
  try
  {
    if (mCentre)
      properties.emplace_back((uint)Property::IdentificationSection::Centre,*mCentre);

    if (mSubCentre)
      properties.emplace_back((uint)Property::IdentificationSection::SubCentre,*mSubCentre);

    if (mTablesVersion)
      properties.emplace_back((uint)Property::IdentificationSection::TablesVersion,*mTablesVersion);

    if (mLocalTablesVersion)
      properties.emplace_back((uint)Property::IdentificationSection::LocalTablesVersion,*mLocalTablesVersion);

    if (mSignificanceOfReferenceTime)
      properties.emplace_back((uint)Property::IdentificationSection::SignificanceOfReferenceTime,*mSignificanceOfReferenceTime);

    if (mYear)
      properties.emplace_back((uint)Property::IdentificationSection::Year,*mYear);

    if (mMonth)
      properties.emplace_back((uint)Property::IdentificationSection::Month,*mMonth);

    if (mDay)
      properties.emplace_back((uint)Property::IdentificationSection::Day,*mDay);

    if (mHour)
      properties.emplace_back((uint)Property::IdentificationSection::Hour,*mHour);

    if (mMinute)
      properties.emplace_back((uint)Property::IdentificationSection::Minute,*mMinute);

    if (mSecond)
      properties.emplace_back((uint)Property::IdentificationSection::Second,*mSecond);

    if (mProductionStatusOfProcessedData)
      properties.emplace_back((uint)Property::IdentificationSection::ProductionStatusOfProcessedData,*mProductionStatusOfProcessedData);

    if (mTypeOfProcessedData)
      properties.emplace_back((uint)Property::IdentificationSection::TypeOfProcessedData,*mTypeOfProcessedData);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
      Fmi::Exception exception(BCP,"Section length cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfSection;

    memoryReader >> mCentre;
    if (missing(mCentre))
    {
      Fmi::Exception exception(BCP,"GRIB centre cannot be missing!");
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
      Fmi::Exception exception(BCP,"GRIB data year cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-2));
      throw exception;
    }

    memoryReader >> mMonth;
    if (missing(mMonth))
    {
      Fmi::Exception exception(BCP,"GRIB data month cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mDay;
    if (missing(mDay))
    {
      Fmi::Exception exception(BCP,"GRIB data day cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mHour;
    if (missing(mHour))
    {
      Fmi::Exception exception(BCP,"GRIB data hour cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mMinute;
    if (missing(mMinute))
    {
      Fmi::Exception exception(BCP,"GRIB data minute cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-1));
      throw exception;
    }

    memoryReader >> mSecond;
    if (missing(mSecond))
    {
      Fmi::Exception exception(BCP,"GRIB data second cannot be missing!");
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void IdentificationSection::write(DataWriter& dataWriter)
{
  try
  {
    const std::size_t section_fixed_size = 21;

    if (missing(mCentre))
      throw Fmi::Exception(BCP,"GRIB centre cannot be missing!");

    if (missing(mYear))
      throw Fmi::Exception(BCP,"GRIB data year cannot be missing!");

    if (missing(mMonth))
      throw Fmi::Exception(BCP,"GRIB data month cannot be missing!");

    if (missing(mDay))
      throw Fmi::Exception(BCP,"GRIB data day cannot be missing!");

    if (missing(mHour))
      throw Fmi::Exception(BCP,"GRIB data hour cannot be missing!");

    if (missing(mMinute))
      throw Fmi::Exception(BCP,"GRIB data minute cannot be missing!");

    if (missing(mSecond))
      throw Fmi::Exception(BCP,"GRIB data second cannot be missing!");

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the reference time of the current grid. The forecast
    times are calculated from this.

        \return   The reference time of the current grid.
*/

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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IdentificationSection::setMonth(T::UInt8_opt month)
{
  try
  {
    if (month  &&  ((*month) < 1 || (*month) > 12))
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(month));
      exception.addParameter("Value Range","1..12");
      throw exception;
    }

    mMonth = month;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IdentificationSection::setDay(T::UInt8_opt day)
{
  try
  {
    if (day  &&  ((*day) < 1 ||  (*day) > 31))
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(day));
      exception.addParameter("Value Range","1..31");
      throw exception;
    }

    mDay = day;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IdentificationSection::setHour(T::UInt8_opt hour)
{
  try
  {
    if (hour  && (*hour) > 23)
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(hour));
      exception.addParameter("Value Range","0..23");
      throw exception;
    }

    mHour = hour;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IdentificationSection::setMinute(T::UInt8_opt minute)
{
  try
  {
    if (minute && (*minute) > 59)
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(minute));
      exception.addParameter("Value Range","0..59");
      throw exception;
    }

    mMinute = minute;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void IdentificationSection::setSecond(T::UInt8_opt second)
{
  try
  {
    if (second  && (*second) > 59)
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",toString(second));
      exception.addParameter("Value Range","0..59");
      throw exception;
    }

    mSecond = second;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
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
    stream << space(level) << "- centre                          = " <<  toString(mCentre) << "\n";
    stream << space(level) << "- subCentre                       = " <<  toString(mSubCentre) << "\n";
    stream << space(level) << "- tablesVersion                   = " << toString(mTablesVersion) << "\n";
    stream << space(level) << "- localTablesVersion              = " << toString(mLocalTablesVersion) << "\n";  // table 1.1 is local, not dumping "1.1"
    stream << space(level) << "- significanceOfReferenceTime     = " << toString(mSignificanceOfReferenceTime) <<  "\n";
    stream << space(level) << "- year                            = " << toString(mYear) << "\n";
    stream << space(level) << "- month                           = " << toString(mMonth) << "\n";
    stream << space(level) << "- day                             = " << toString(mDay) << "\n";
    stream << space(level) << "- hour                            = " << toString(mHour) << "\n";
    stream << space(level) << "- minute                          = " << toString(mMinute) << "\n";
    stream << space(level) << "- second                          = " << toString(mSecond) << "\n";
    stream << space(level) << "- productionStatusOfProcessedData = " << toString(mProductionStatusOfProcessedData) << ")\n";
    stream << space(level) << "- typeOfProcessedData             = " << toString(mTypeOfProcessedData) << "\n";
    stream << space(level) << "- reserved                        = " << mDataSize << " bytes\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
