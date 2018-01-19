#include "ProductSection.h"
#include "Message.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "identification/GridDef.h"
#include <boost/date_time/posix_time/posix_time.hpp>


namespace SmartMet
{
namespace GRIB1
{


/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

ProductSection::ProductSection(Message *message)
{
  try
  {
    mMessage = message;
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
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed failed!",NULL);
  }
}





/*! \brief The destructor of the class. */

ProductSection::~ProductSection()
{
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
      if (memoryReader.read_uint8() == 0x1E)
      {
        memoryReader.setReadPosition(rPos + 49);
        mForecastNumber = memoryReader.read_uint8();
        if (mForecastNumber > 0)
          mForecastType = 3;
      }
    }

    memoryReader.setReadPosition(rPos + mSectionLength);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




/*! \brief The method returns the reference time. */

T::TimeString ProductSection::getReferenceTime() const
{
  try
  {
    char ts[100];
    if (mYearOfCentury != 0xFF  &&  mMonth != 0xFF  &&  mDay != 0xFF)
    {
      sprintf(ts,"%04u%02u%02uT%02u%02u00",(uint)(2000+mYearOfCentury),(uint)mMonth,(uint)mDay,(uint)mHour,(uint)mMinute);
      return std::string(ts);
    }
    return std::string("19000101T000000");
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





short ProductSection::getForecastType() const
{
  try
  {
    return mForecastType;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





short ProductSection::getForecastNumber() const
{
  try
  {
    return mForecastNumber;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}





/*! \brief The method returns the forecast start time. */

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
        tt = refTime + dd*mP1;
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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}




#if 0
/*! \brief The method returns the forecast end time. */

T::TimeString ProductSection::getForecastEndTime() const
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

    switch (mTimeRangeIndicator)
    {
      case 0: // Forecast product valid at reference time + P1 (P1>0)
        tt = refTime + dd*mP1;
        break;

      case 1: // Initialized analysis product for reference time (P1=0).
        tt = refTime;
        break;

      case 2: // Product with a valid time ranging between reference time + P1 and reference time + P2
        tt = refTime + dd*mP2;
        break;

      case 3: // Average (reference time + P1 to reference time + P2)
        tt = refTime + dd*mP2;
        break;

      case 4: // Accumulation (reference time + P1 to reference time + P2) product considered valid at reference time + P2
        tt = refTime + dd*mP1;
        break;

      case 5: // Difference (reference time + P2 minus reference time + P1) product considered valid at reference time + P2
        tt = refTime + dd*mP1;
        break;

      case 10: // P1 occupies octets 19 and 20; product valid at reference time + P1
        tt = refTime + dd*mP1;
        break;

      case 51: // Climatological Mean Value:
        tt = refTime;
        break;

      case 113: // Average of N forecasts (or initialized analyses); each product has forecast period of P1 (P1=0 for initialized analyses); products have reference times at intervals of P2, beginning at the given reference time.
        tt = refTime + dd*(mP2+1);
        break;

      case 114: // Accumulation of N forecasts (or initialized analyses); each product has forecast period of P1 (P1=0 for initialized analyses); products have reference times at intervals of P2, beginning at the given reference time.
        tt = refTime + dd*(mP2+1);
        break;

      case 115: // Average of N forecasts, all with the same reference time; the first has a forecast period of P1, the remaining forecasts follow at intervals of P2.
        tt = refTime + dd*mP1 + dd*(mP2+1);
        break;

      case 116: // Accumulation of N forecasts, all with the same reference time; the first has a forecast period of P1, the remaining follow at intervals of P2.
        tt = refTime + dd*mP1 + dd*(mP2+1);
        break;

      case 117: // Average of N forecasts, the first has a period of P1, the subsequent ones have forecast periods reduced from the previous one by an interval of P2; the reference time for the first is given in octets 13- 17, the subsequent ones have reference times increased from the previous one by an interval of P2. Thus all the forecasts have the same valid time, given by the initial reference time + P1.
        tt = refTime + dd*mP1 - dd*mP2;
        break;

      case 118: // Temporal variance, or covariance, of N initialized analyses; each product has forecast period P1=0; products have reference times at intervals of P2, beginning at the given reference time.
        tt = refTime + dd*(mP2+1);
        break;

      case 123: // Average of N uninitialized analyses, starting at the reference time, at intervals of P2.
        tt = refTime + dd*(mP2+1);
        break;

      case 124: // Accumulation of N uninitialized analyses, starting at the reference time, at intervals of P2.
        tt = refTime + dd*(mP2+1);
        break;
    }

    return toString(tt);
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}
#endif




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
    throw SmartMet::Spine::Exception(BCP,exception_operation_failed,NULL);
  }
}

}  // namespace GRID
}  // namespace SmartMet
