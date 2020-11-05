#include "ProductSection.h"
#include "Message.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"
#include "../identification/GridDef.h"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <macgyver/StringConversion.h>


namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class. */

ProductSection::ProductSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
    mSectionLength = 0;
    mTableVersion = 0;
    mCentre = 0;
    mGeneratingProcessIdentifier = 0;
    mGridDefinitionNumber = 0;
    mSectionFlags = 0;
    mIndicatorOfParameter = 0;
    mIndicatorOfTypeOfLevel = 0;
    mLevel = 0;
    mYearOfCentury = 0;
    mMonth = 0;
    mDay = 0;
    mHour = 0;
    mMinute = 0;
    mUnitOfTimeRange = 0;
    mP1 = 0;
    mP2 = 0;
    mTimeRangeIndicator = 0;
    mNumberIncludedInAverage = 0;
    mNumberMissingFromAveragesOrAccumulations = 0;
    mCenturyOfReferenceTimeOfData = 0;
    mSubCentre = 0;
    mDecimalScaleFactor = 0;
    mForecastType = 1;
    mForecastNumber = -1;
    mDataPtr = nullptr;
    mDataSize = 0;
    mReleaseData = false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

ProductSection::ProductSection(const ProductSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mTableVersion = other.mTableVersion;
    mCentre = other.mCentre;
    mGeneratingProcessIdentifier = other.mGeneratingProcessIdentifier;
    mGridDefinitionNumber = other.mGridDefinitionNumber;
    mSectionFlags = other.mSectionFlags;
    mIndicatorOfParameter = other.mIndicatorOfParameter;
    mIndicatorOfTypeOfLevel = other.mIndicatorOfTypeOfLevel;
    mLevel = other.mLevel;
    mYearOfCentury = other.mYearOfCentury;
    mMonth = other.mMonth;
    mDay = other.mDay;
    mHour = other.mHour;
    mMinute = other.mMinute;
    mUnitOfTimeRange = other.mUnitOfTimeRange;
    mP1 = other.mP1;
    mP2 = other.mP2;
    mTimeRangeIndicator = other.mTimeRangeIndicator;
    mNumberIncludedInAverage = other.mNumberIncludedInAverage;
    mNumberMissingFromAveragesOrAccumulations = other.mNumberMissingFromAveragesOrAccumulations;
    mCenturyOfReferenceTimeOfData = other.mCenturyOfReferenceTimeOfData;
    mSubCentre = other.mSubCentre;
    mDecimalScaleFactor = other.mDecimalScaleFactor;
    mForecastType = other.mForecastType;
    mForecastNumber = other.mForecastNumber;
    mDataSize = other.mDataSize;
    mReleaseData = false;
    mDataPtr = nullptr;

    if (mDataSize >  0  &&  other.mDataPtr != nullptr)
    {
      mDataPtr = new uchar[mDataSize];
      memcpy(mDataPtr,other.mDataPtr,mDataSize);
      mReleaseData = true;
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

ProductSection::~ProductSection()
{
  try
  {
    if (mReleaseData &&  mDataPtr != nullptr)
    {
      delete[] mDataPtr;
      mDataPtr = nullptr;
    }
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

void ProductSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sproduct.tableVersion",prefix.c_str());
    attributeList.addAttribute(name,toString(mTableVersion));

    sprintf(name,"%sproduct.centre.id",prefix.c_str());
    attributeList.addAttribute(name,toString(mCentre));

    sprintf(name,"%sproduct.centre.name",prefix.c_str());
    attributeList.addAttribute(name,Identification::gridDef.getGribTableValue(1,0,"0",mCentre));

    sprintf(name,"%sproduct.generatingProcessIdentifier",prefix.c_str());
    attributeList.addAttribute(name,toString(mGeneratingProcessIdentifier));

    sprintf(name,"%sproduct.gridDefinitionNumber",prefix.c_str());
    attributeList.addAttribute(name,toString(mGridDefinitionNumber));

    sprintf(name,"%sproduct.sectionFlags",prefix.c_str());
    attributeList.addAttribute(name,toString(mSectionFlags));

    sprintf(name,"%sproduct.indicatorOfParameter",prefix.c_str());
    attributeList.addAttribute(name,toString(mIndicatorOfParameter));

    sprintf(name,"%sproduct.indicatorOfParameterString",prefix.c_str());
    attributeList.addAttribute(name,Identification::gridDef.getGribTableValue(1,0,"2.128",mIndicatorOfParameter));

    sprintf(name,"%sproduct.indicatorOfTypeOfLevel",prefix.c_str());
    attributeList.addAttribute(name,toString(mIndicatorOfTypeOfLevel));

    sprintf(name,"%sproduct.indicatorOfTypeOfLevelString",prefix.c_str());
    attributeList.addAttribute(name,Identification::gridDef.getGribTableValue(1,0,"3",mIndicatorOfTypeOfLevel));

    sprintf(name,"%sproduct.level",prefix.c_str());
    attributeList.addAttribute(name,toString(mLevel));

    sprintf(name,"%sproduct.yearOfCentury",prefix.c_str());
    attributeList.addAttribute(name,toString(mYearOfCentury));

    sprintf(name,"%sproduct.month",prefix.c_str());
    attributeList.addAttribute(name,toString(mMonth));

    sprintf(name,"%sproduct.day",prefix.c_str());
    attributeList.addAttribute(name,toString(mDay));

    sprintf(name,"%sproduct.hour",prefix.c_str());
    attributeList.addAttribute(name,toString(mHour));

    sprintf(name,"%sproduct.minute",prefix.c_str());
    attributeList.addAttribute(name,toString(mMinute));

    sprintf(name,"%sproduct.unitOfTimeRange",prefix.c_str());
    attributeList.addAttribute(name,toString(mUnitOfTimeRange));

    sprintf(name,"%sproduct.P1",prefix.c_str());
    attributeList.addAttribute(name,toString(mP1));

    sprintf(name,"%sproduct.P2",prefix.c_str());
    attributeList.addAttribute(name,toString(mP2));

    sprintf(name,"%sproduct.timeRangeIndicator",prefix.c_str());
    attributeList.addAttribute(name,toString(mTimeRangeIndicator));

    sprintf(name,"%sproduct.numberIncludedInAverage",prefix.c_str());
    attributeList.addAttribute(name,toString(mNumberIncludedInAverage));

    sprintf(name,"%sproduct.numberMissingFromAveragesOrAccumulations",prefix.c_str());
    attributeList.addAttribute(name,toString(mNumberMissingFromAveragesOrAccumulations));

    sprintf(name,"%sproduct.centuryOfReferenceTimeOfData",prefix.c_str());
    attributeList.addAttribute(name,toString(mCenturyOfReferenceTimeOfData));

    sprintf(name,"%sproduct.subCentre",prefix.c_str());
    attributeList.addAttribute(name,toString(mSubCentre));

    sprintf(name,"%sproduct.decimalScaleFactor",prefix.c_str());
    attributeList.addAttribute(name,toString(mDecimalScaleFactor));
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

void ProductSection::setMessagePtr(Message *message)
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

bool ProductSection::getProperty(uint propertyId,long long& value)
{
  try
  {
    switch (propertyId)
    {
      case Property::ProductSection::TableVersion:
        value = mTableVersion;
        return true;

      case Property::ProductSection::Centre:
        value = mCentre;
        return true;

      case Property::ProductSection::GeneratingProcessIdentifier:
        value = mGeneratingProcessIdentifier;
        return true;

      case Property::ProductSection::GridDefinitionNumber:
        value = mGridDefinitionNumber;
        return true;

      case Property::ProductSection::SectionFlags:
        value = mSectionFlags;
        return true;

      case Property::ProductSection::IndicatorOfParameter:
        value = mIndicatorOfParameter;
        return true;

      case Property::ProductSection::IndicatorOfTypeOfLevel:
        value = mIndicatorOfTypeOfLevel;
        return true;

      case Property::ProductSection::Level:
        value = mLevel;
        return true;

      case Property::ProductSection::YearOfCentury:
        value = mYearOfCentury;
        return true;

      case Property::ProductSection::Month:
        value = mMonth;
        return true;

      case Property::ProductSection::Day:
        value = mDay;
        return true;

      case Property::ProductSection::Hour:
        value = mHour;
        return true;

      case Property::ProductSection::Minute:
        value = mMinute;
        return true;

      case Property::ProductSection::UnitOfTimeRange:
        value = mUnitOfTimeRange;
        return true;

      case Property::ProductSection::P1:
        value = mP1;
        return true;

      case Property::ProductSection::P2:
        value = mP2;
        return true;

      case Property::ProductSection::TimeRangeIndicator:
        value = mTimeRangeIndicator;
        return true;

      case Property::ProductSection::NumberIncludedInAverage:
        value = mNumberIncludedInAverage;
        return true;

      case Property::ProductSection::NumberMissingFromAveragesOrAccumulations:
        value = mNumberMissingFromAveragesOrAccumulations;
        return true;

      case Property::ProductSection::CenturyOfReferenceTimeOfData:
        value = mCenturyOfReferenceTimeOfData;
        return true;

      case Property::ProductSection::SubCentre:
        value = mSubCentre;
        return true;

      case Property::ProductSection::DecimalScaleFactor:
        value = mDecimalScaleFactor;
        return true;

      case Property::ProductSection::ForecastType:
        value = mForecastType;
        return true;

      case Property::ProductSection::ForecastNumber:
        value = mForecastNumber;
        return true;
    }
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

bool ProductSection::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::ProductSection::TableVersion:
        setTableVersion(value);
        return true;

      case Property::ProductSection::Centre:
        setCentre(value);
        return true;

      case Property::ProductSection::GeneratingProcessIdentifier:
        setGeneratingProcessIdentifier(value);
        return true;

      case Property::ProductSection::GridDefinitionNumber:
        setGridDefinitionNumber(value);
        return true;

      case Property::ProductSection::SectionFlags:
        setSectionFlags(value);
        return true;

      case Property::ProductSection::IndicatorOfParameter:
        setIndicatorOfParameter(value);
        return true;

      case Property::ProductSection::IndicatorOfTypeOfLevel:
        setIndicatorOfTypeOfLevel(value);
        return true;

      case Property::ProductSection::Level:
        setLevel(value);
        return true;

      case Property::ProductSection::YearOfCentury:
        setYearOfCentury(value);
        return true;

      case Property::ProductSection::Month:
        setMonth(value);
        return true;

      case Property::ProductSection::Day:
        setDay(value);
        return true;

      case Property::ProductSection::Hour:
        setHour(value);
        return true;

      case Property::ProductSection::Minute:
        setMinute(value);
        return true;

      case Property::ProductSection::UnitOfTimeRange:
        setUnitOfTimeRange(value);
        return true;

      case Property::ProductSection::P1:
        setP1(value);
        return true;

      case Property::ProductSection::P2:
        setP2(value);
        return true;

      case Property::ProductSection::TimeRangeIndicator:
        setTimeRangeIndicator(value);
        return true;

      case Property::ProductSection::NumberIncludedInAverage:
        setNumberIncludedInAverage(value);
        return true;

      case Property::ProductSection::NumberMissingFromAveragesOrAccumulations:
        setNumberMissingFromAveragesOrAccumulations(value);
        return true;

      case Property::ProductSection::CenturyOfReferenceTimeOfData:
        setCenturyOfReferenceTimeOfData(value);
        return true;

      case Property::ProductSection::SubCentre:
        setSubCentre(value);
        return true;

      case Property::ProductSection::DecimalScaleFactor:
        setDecimalScaleFactor(value);
        return true;

      case Property::ProductSection::ForecastType:
        setForecastType(value);
        return true;

      case Property::ProductSection::ForecastNumber:
        setForecastNumber(value);
        return true;
    }
    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (double) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool ProductSection::setProperty(uint propertyId,double value)
{
  try
  {
    return setProperty(propertyId,C_INT64(value));
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ProductSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    auto rPos = memoryReader.getReadPosition();

    mSectionLength =  memoryReader.read_uint24();
    memoryReader >> mTableVersion;
    memoryReader >> mCentre;
    memoryReader >> mGeneratingProcessIdentifier;
    memoryReader >> mGridDefinitionNumber;
    memoryReader >> mSectionFlags;
    memoryReader >> mIndicatorOfParameter;
    memoryReader >> mIndicatorOfTypeOfLevel;
    memoryReader >> mLevel;
    memoryReader >> mYearOfCentury;
    memoryReader >> mMonth;
    memoryReader >> mDay;
    memoryReader >> mHour;
    memoryReader >> mMinute;
    memoryReader >> mUnitOfTimeRange;
    memoryReader >> mP1;
    memoryReader >> mP2;
    memoryReader >> mTimeRangeIndicator;
    memoryReader >> mNumberIncludedInAverage;
    memoryReader >> mNumberMissingFromAveragesOrAccumulations;
    memoryReader >> mCenturyOfReferenceTimeOfData;
    memoryReader >> mSubCentre;
    memoryReader >> mDecimalScaleFactor;

    if (mSectionLength > 50)
    {
      memoryReader.setReadPosition(rPos + 40);
      mDataPtr = memoryReader.getReadPtr();
      mDataSize = mSectionLength - 40;

      auto t = memoryReader.read_uint8();

      switch (t)
      {
        case 0xC:
        case 0xF:
        case 0x10:
        case 0x17:
          memoryReader.setReadPosition(rPos + 49);
          mForecastNumber = memoryReader.read_uint16();
          break;

        case 0x1:
        case 0xD:
        case 0xE:
        case 0x12:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x24:
        case 0x25:
        case 0x31:
        case 0x32:
          memoryReader.setReadPosition(rPos + 49);
          mForecastNumber = memoryReader.read_uint8();
          break;
      }

      if (mForecastNumber > 0)
        mForecastType = 3;
    }

    memoryReader.setReadPosition(rPos + mSectionLength);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed failed!",nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void ProductSection::write(DataWriter& dataWriter)
{
  try
  {
    mFilePosition = dataWriter.getWritePosition();

    if (mDataPtr == nullptr  ||  mDataSize == 0)
      mSectionLength = 28;
    else
      mSectionLength = 40 + mDataSize;

    dataWriter.write_uint24(mSectionLength);
    dataWriter << mTableVersion;
    dataWriter << mCentre;
    dataWriter << mGeneratingProcessIdentifier;
    dataWriter << mGridDefinitionNumber;
    dataWriter << mSectionFlags;
    dataWriter << mIndicatorOfParameter;
    dataWriter << mIndicatorOfTypeOfLevel;
    dataWriter << mLevel;
    dataWriter << mYearOfCentury;
    dataWriter << mMonth;
    dataWriter << mDay;
    dataWriter << mHour;
    dataWriter << mMinute;
    dataWriter << mUnitOfTimeRange;
    dataWriter << mP1;
    dataWriter << mP2;
    dataWriter << mTimeRangeIndicator;
    dataWriter << mNumberIncludedInAverage;
    dataWriter << mNumberMissingFromAveragesOrAccumulations;
    dataWriter << mCenturyOfReferenceTimeOfData;
    dataWriter << mSubCentre;
    dataWriter << mDecimalScaleFactor;

    if (mDataPtr != nullptr  &&  mDataSize > 0)
    {
      ulonglong fPos = dataWriter.getWritePosition();
      dataWriter.write_nTimes(0xFF,40-(fPos-mFilePosition));
      dataWriter.write_data(mDataPtr,mDataSize);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition ProductSection::getFilePosition() const
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

std::uint32_t ProductSection::getSectionLength() const
{
  try
  {
    return mSectionLength;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the name of the section. */

std::string ProductSection::getSectionName() const
{
  try
  {
    return std::string("Product");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the section number. */

std::uint8_t ProductSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::product_section;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the table version. */

std::uint8_t ProductSection::getTableVersion() const
{
  try
  {
    return mTableVersion;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the identifier of the generating center. */

std::uint8_t ProductSection::getCentre() const
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





/*! \brief The method returns the identifier of the generating process. */

std::uint8_t ProductSection::getGeneratingProcessIdentifier() const
{
  try
  {
    return mGeneratingProcessIdentifier;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the grid definition number used by the generating center. */

std::uint8_t ProductSection::getGridDefinitionNumber() const
{
  try
  {
    return mGridDefinitionNumber;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the section flags. */

std::uint8_t ProductSection::getSectionFlags() const
{
  try
  {
    return mSectionFlags;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the indicator of the parameter. */

std::uint8_t ProductSection::getIndicatorOfParameter() const
{
  try
  {
    return mIndicatorOfParameter;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the indicator of the level type. */

std::uint8_t ProductSection::getIndicatorOfTypeOfLevel() const
{
  try
  {
    return mIndicatorOfTypeOfLevel;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the value of the level. */

std::uint16_t ProductSection::getLevel() const
{
  try
  {
    return mLevel;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the reference year. */

std::uint8_t ProductSection::getYearOfCentury() const
{
  try
  {
    return mYearOfCentury;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the reference month. */

std::uint8_t ProductSection::getMonth() const
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





/*! \brief The method returns the reference day. */

std::uint8_t ProductSection::getDay() const
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





/*! \brief The method returns the reference hour. */

std::uint8_t ProductSection::getHour() const
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





/*! \brief The method returns the reference minute. */

std::uint8_t ProductSection::getMinute() const
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





/*! \brief The method returns the unit of the time range. */

std::uint8_t ProductSection::getUnitOfTimeRange() const
{
  try
  {
    return mUnitOfTimeRange;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the period of time (= number of time units). */

std::uint8_t ProductSection::getP1() const
{
  try
  {
    return mP1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the period of time (=number of time units) or time interval between successive
    analyses, initialized analyses or forecasts, undergoing averaging or accumulation.
*/

std::uint8_t ProductSection::getP2() const
{
  try
  {
    return mP2;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the time range indicator. */

std::uint8_t ProductSection::getTimeRangeIndicator() const
{
  try
  {
    return mTimeRangeIndicator;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the number included in average, when {@link mTimeRangeIndicator}
    indicates an average or accumulation. Otherwise the returned value is zero.
*/

std::uint16_t ProductSection::getNumberIncludedInAverage() const
{
  try
  {
    return mNumberMissingFromAveragesOrAccumulations;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the number missing from averages or accumulations. */

std::uint8_t ProductSection::getNumberMissingFromAveragesOrAccumulations() const
{
  try
  {
    return mNumberMissingFromAveragesOrAccumulations;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}




/*! \brief The method returns the century of the reference time of data. */

std::uint8_t ProductSection::getCenturyOfReferenceTimeOfData() const
{
  try
  {
    return mCenturyOfReferenceTimeOfData;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the sub-center identification. */

std::uint8_t ProductSection::getSubCentre() const
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





/*! \brief The method returns the decimal scale factor. */

std::uint16_t ProductSection::getDecimalScaleFactor() const
{
  try
  {
    return mDecimalScaleFactor;
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

T::TimeString ProductSection::getReferenceTime() const
{
  try
  {
    char ts[100];
    if (mYearOfCentury != 0xFF  &&  mMonth != 0xFF  &&  mDay != 0xFF)
    {
      if (mCenturyOfReferenceTimeOfData != 0xFF)
        sprintf(ts,"%04u%02u%02uT%02u%02u00",C_UINT((mCenturyOfReferenceTimeOfData-1)*100+mYearOfCentury),mMonth,mDay,mHour,mMinute);
      else
        sprintf(ts,"%04u%02u%02uT%02u%02u00",C_UINT(1900+mYearOfCentury),mMonth,mDay,mHour,mMinute);
      return std::string(ts);
    }
    return std::string("19000101T000000");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the forecast type of the current grid.

        \return   The forecast type.
*/

short ProductSection::getForecastType() const
{
  try
  {
    return mForecastType;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the forecast number of the current grid.

        \return   The forecast number.
*/

short ProductSection::getForecastNumber() const
{
  try
  {
    return mForecastNumber;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the forecast time of the current grid.

        \return   The forecast time.
*/

T::TimeString ProductSection::getForecastTime() const
{
  try
  {
    T::TimeStamp refTime = toTimeStamp(getReferenceTime());

    boost::posix_time::time_duration dd;

    switch (mUnitOfTimeRange)
    {
      case 0: // m Minute
        dd = boost::posix_time::minutes(1);
        break;

      case 1: // h Hour
        dd = boost::posix_time::hours(1);
        break;

      case 2: // D Day
        dd = boost::posix_time::hours(24);
        break;

      case 10: // 3h 3 hours
        dd = boost::posix_time::hours(3);
        break;

      case 11: // 6h 6 hours
        dd = boost::posix_time::hours(6);
        break;

      case 12: // 12h 12 hours
        dd = boost::posix_time::hours(12);
        break;

      case 13: // 15m 15 minutes
        dd = boost::posix_time::minutes(15);
        break;

      case 14: // 30m 30 minutes
        dd = boost::posix_time::minutes(30);
        break;

      case 254: // s Second
        dd = boost::posix_time::seconds(1);
        break;

      case 3: // M Month
      case 4: // Y Year
      case 5: // 10Y Decade
      case 6: // 30Y Normal (30 years)
      case 7: // C Century
        break;
    }

    T::TimeStamp tt = refTime;

    uint p12 = ((C_UINT(mP1)) << 8) + mP2;

    switch (mTimeRangeIndicator)
    {
      case 0: // Forecast product valid at reference time + P1 (P1>0)
        tt = refTime + dd*mP1;
        break;

      case 1: // Initialized analysis product for reference time (P1=0).
        tt = refTime;
        break;

      case 2: // Product with a valid time ranging between reference time + P1 and reference time + P2
        tt = refTime + dd*mP1 /* + dd*mP2*/;
        break;

      case 3: // Average (reference time + P1 to reference time + P2)
        tt = refTime + dd*mP1 /*+ dd*mP2*/;
        break;

      case 4: // Accumulation (reference time + P1 to reference time + P2) product considered valid at reference time + P2
        tt = refTime + dd*mP2 /*+ dd*mP2*/;
        break;

      case 5: // Difference (reference time + P2 minus reference time + P1) product considered valid at reference time + P2
        tt = refTime + dd*mP2;
        break;

      case 10: // P1 occupies octets 19 and 20; product valid at reference time + P1
        tt = refTime + dd*p12;
        break;

      case 51: // Climatological Mean Value:
        tt = refTime;
        break;

      case 113: // Average of N forecasts (or initialized analyses); each product has forecast period of P1 (P1=0 for initialized analyses); products have reference times at intervals of P2, beginning at the given reference time.
        tt = refTime + dd*mP2;;
        break;

      case 114: // Accumulation of N forecasts (or initialized analyses); each product has forecast period of P1 (P1=0 for initialized analyses); products have reference times at intervals of P2, beginning at the given reference time.
        tt = refTime + dd*mP2;
        break;

      case 115: // Average of N forecasts, all with the same reference time; the first has a forecast period of P1, the remaining forecasts follow at intervals of P2.
        tt = refTime + dd*mP1 + dd*mP2;
        break;

      case 116: // Accumulation of N forecasts, all with the same reference time; the first has a forecast period of P1, the remaining follow at intervals of P2.
        tt = refTime + dd*mP1 + dd*mP2;
        break;

      case 117: // Average of N forecasts, the first has a period of P1, the subsequent ones have forecast periods reduced from the previous one by an interval of P2; the reference time for the first is given in octets 13- 17, the subsequent ones have reference times increased from the previous one by an interval of P2. Thus all the forecasts have the same valid time, given by the initial reference time + P1.
        tt = refTime + dd*mP1;
        break;

      case 118: // Temporal variance, or covariance, of N initialized analyses; each product has forecast period P1=0; products have reference times at intervals of P2, beginning at the given reference time.
        tt = refTime + dd*mP2;
        break;

      case 123: // Average of N uninitialized analyses, starting at the reference time, at intervals of P2.
        tt = refTime + dd*mP2;
        break;

      case 124: // Accumulation of N uninitialized analyses, starting at the reference time, at intervals of P2.
        tt = refTime + dd*mP2;
        break;
    }

    return toString(tt);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setTableVersion(std::uint8_t tableVersion)
{
  try
  {
    mTableVersion = tableVersion;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setCentre(std::uint8_t centre)
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





void ProductSection::setGeneratingProcessIdentifier(std::uint8_t generatingProcessIdentifier)
{
  try
  {
    mGeneratingProcessIdentifier = generatingProcessIdentifier;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setGridDefinitionNumber(std::uint8_t gridDefinitionNumber)
{
  try
  {
    mGridDefinitionNumber = gridDefinitionNumber;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setSectionFlags(std::uint8_t sectionFlags)
{
  try
  {
    mSectionFlags = sectionFlags;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setIndicatorOfParameter(std::uint8_t indicatorOfParameter)
{
  try
  {
    mIndicatorOfParameter = indicatorOfParameter;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setIndicatorOfTypeOfLevel(std::uint8_t indicatorOfTypeOfLevel)
{
  try
  {
    mIndicatorOfTypeOfLevel = indicatorOfTypeOfLevel;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setLevel(std::uint16_t level)
{
  try
  {
    mLevel = level;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setYearOfCentury(std::uint8_t yearOfCentury)
{
  try
  {
    mYearOfCentury = yearOfCentury;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setMonth(std::uint8_t month)
{
  try
  {
    if (month < 1 ||  month > 12)
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",Fmi::to_string(month));
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





void ProductSection::setDay(std::uint8_t day)
{
  try
  {
    if (day < 1 ||  day > 31)
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",Fmi::to_string(day));
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





void ProductSection::setHour(std::uint8_t hour)
{
  try
  {
    if (hour > 23)
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",Fmi::to_string(hour));
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





void ProductSection::setMinute(std::uint8_t minute)
{
  try
  {
    if (minute > 59)
    {
      Fmi::Exception exception(BCP,"The given value is not in the acceptable value range!");
      exception.addParameter("Value",Fmi::to_string(minute));
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





void ProductSection::setUnitOfTimeRange(std::uint8_t unitOfTimeRange)
{
  try
  {
    mUnitOfTimeRange = unitOfTimeRange;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setP1(std::uint8_t p1)
{
  try
  {
    mP1 = p1;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setP2(std::uint8_t p2)
{
  try
  {
    mP2 = p2;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setTimeRangeIndicator(std::uint8_t timeRangeIndicator)
{
  try
  {
    mTimeRangeIndicator = timeRangeIndicator;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setNumberIncludedInAverage(std::uint16_t numberIncludeInAverage)
{
  try
  {
    mNumberIncludedInAverage = numberIncludeInAverage;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setNumberMissingFromAveragesOrAccumulations(std::uint8_t numberMissingFromAveragesOrAccumulations)
{
  try
  {
    mNumberMissingFromAveragesOrAccumulations = numberMissingFromAveragesOrAccumulations;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setCenturyOfReferenceTimeOfData(std::uint8_t centuryOfReferenceTimeOfData)
{
  try
  {
    mCenturyOfReferenceTimeOfData = centuryOfReferenceTimeOfData;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setSubCentre(std::uint8_t subCentre)
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





void ProductSection::setDecimalScaleFactor(std::uint16_t decimalScaleFactor)
{
  try
  {
    mDecimalScaleFactor = decimalScaleFactor;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setForecastType(short forecastType)
{
  try
  {
    mForecastType = forecastType;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





void ProductSection::setForecastNumber(short forecastNuber)
{
  try
  {
    mForecastNumber = forecastNuber;
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

void ProductSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition                             = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength                            = " <<  toString(mSectionLength) << "\n";
    stream << space(level) << "- tableVersion                             = " <<  toString(mTableVersion) << "\n";
    stream << space(level) << "- centre                                   = " <<  toString(mCentre) << " (" << Identification::gridDef.getGribTableValue(1,0,"0",mCentre) << ")\n";
    stream << space(level) << "- generatingProcessIdentifier              = " <<  toString(mGeneratingProcessIdentifier) << "\n";
    stream << space(level) << "- gridDefinitionNumber                     = " <<  toString(mGridDefinitionNumber) << "\n";
    stream << space(level) << "- sectionFlags                             = " <<  toString(mSectionFlags) << "\n";
    stream << space(level) << "- indicatorOfParameter                     = " <<  toString(mIndicatorOfParameter)  << " (" << Identification::gridDef.getGribTableValue(1,0,"2.128",mIndicatorOfParameter) << ")\n";
    stream << space(level) << "- indicatorOfTypeOfLevel                   = " <<  toString(mIndicatorOfTypeOfLevel) << " (" << Identification::gridDef.getGribTableValue(1,0,"3",mIndicatorOfTypeOfLevel) << ")\n";
    stream << space(level) << "- level                                    = " <<  toString(mLevel) << "\n";
    stream << space(level) << "- yearOfCentury                            = " <<  toString(mYearOfCentury) << "\n";
    stream << space(level) << "- month                                    = " <<  toString(mMonth) << "\n";
    stream << space(level) << "- day                                      = " <<  toString(mDay) << "\n";
    stream << space(level) << "- hour                                     = " <<  toString(mHour) << "\n";
    stream << space(level) << "- minute                                   = " <<  toString(mMinute) << "\n";
    stream << space(level) << "- unitOfTimeRange                          = " <<  toString(mUnitOfTimeRange) << "\n";
    stream << space(level) << "- P1                                       = " <<  toString(mP1) << "\n";
    stream << space(level) << "- P2                                       = " <<  toString(mP2) << "\n";
    stream << space(level) << "- timeRangeIndicator                       = " <<  toString(mTimeRangeIndicator) << "\n";
    stream << space(level) << "- numberIncludedInAverage                  = " <<  toString(mNumberIncludedInAverage) << "\n";
    stream << space(level) << "- numberMissingFromAveragesOrAccumulations = " <<  toString(mNumberMissingFromAveragesOrAccumulations) << "\n";
    stream << space(level) << "- centuryOfReferenceTimeOfData             = " <<  toString(mCenturyOfReferenceTimeOfData) << "\n";
    stream << space(level) << "- subCentre                                = " <<  toString(mSubCentre) << "\n";
    stream << space(level) << "- decimalScaleFactor                       = " <<  toString(mDecimalScaleFactor) << "\n";
    stream << space(level) << "- mForecastType                            = " <<  toString(mForecastType) << "\n";
    stream << space(level) << "- mForecastNumber                          = " <<  toString(mForecastNumber) << "\n";
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}  // namespace GRID
}  // namespace SmartMet
