#pragma once

#include "grid/MessageSection.h"
#include "common/MemoryReader.h"

namespace SmartMet
{
namespace GRIB1
{

class Message;


// ====================================================================================
/*!
  \brief This class is used for accessing information that is found from
  the Product section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates
  a new ProductSection object and calls its read() method in order to read
  the section information into the object. After that the section information
  can be easily accessed through the current object.
*/
// ====================================================================================


/*
  --------------------------------------------------------------------------------------
  Section 1 - Product definition section
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------

  1-3     Length of section
  4       GRIB tables Version No. (currently 3 for international exchange) -- Version
          numbers 128-254 are reserved for local use
  5       Identification of originating/generating center (see Code table 0)
  6       Generating process identification number (allocated by originating center)
  7       Grid definition (Number of grid used - from catalog defined by originating center)
  8       Flag (see Code table 1)
  9       Indicator of parameter (see Code table 2)
  10      Indicator of type of level (see Code table 3)
  11-12   Height, pressure, etc. of levels (see Code table 3)
  13      Year of century (see Note 6)  Octets 13-17 give the Reference time of data - date
          and time of start of averaging or accumulation period
  14      Month
  15      Day
  16      Hour
  17      Minute
  18      Indicator of unit of time range (see Code table 4)
  19      P1 - Period of time (number of time units) (0 for analyses or initialized analyses).
          Units of time given by octet 18
  20      P2 - Period of time (number of time units); or time interval between successive
          analyses, initialized analyses or forecasts, undergoing averaging or accumulation.
          Units of time given by octet 18
  21      Time range indicator (see Code table 5)
  22-23   Number included in average, when octet 21 (Code table 5) indicates an average or
          accumulation; otherwise set to zero
  24      Number missing from averages or accumulations
  25      Century of reference time of data (see Note 6)
  26      Sub-center identification (see Code Table 0)
  27-28   Units decimal scale factor (D)
  29-40   Reserved: need not be present
  41-nn   Reserved for originating center use
  --------------------------------------------------------------------------------------
*/


class ProductSection : public GRID::MessageSection
{
  public:
                    ProductSection(Message *message);
    virtual         ~ProductSection();

    // ### Common methods for all message sections

    void            getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition getFilePosition() const;
    std::uint32_t   getSectionLength() const;
    std::string     getSectionName() const;
    std::uint8_t    getSectionNumber() const;
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Section specific methods

    std::uint8_t    getTableVersion() const;
    std::uint8_t    getCentre() const;
    std::uint8_t    getGeneratingProcessIdentifier() const;
    std::uint8_t    getGridDefinitionNumber() const;
    std::uint8_t    getSectionFlags() const;
    std::uint8_t    getIndicatorOfParameter() const;
    std::uint8_t    getIndicatorOfTypeOfLevel() const;
    std::uint16_t   getLevel() const;
    std::uint8_t    getYearOfCentury() const;
    std::uint8_t    getMonth() const;
    std::uint8_t    getDay() const;
    std::uint8_t    getHour() const;
    std::uint8_t    getMinute() const;
    std::uint8_t    getUnitOfTimeRange() const;
    std::uint8_t    getP1() const;
    std::uint8_t    getP2() const;
    std::uint8_t    getTimeRangeIndicator() const;
    std::uint16_t   getNumberIncludedInAverage() const;
    std::uint8_t    getNumberMissingFromAveragesOrAccumulations() const;
    std::uint8_t    getCenturyOfReferenceTimeOfData() const;
    std::uint8_t    getSubCentre() const;
    std::uint16_t   getDecimalScaleFactor() const;
    T::TimeString   getReferenceTime() const;
    T::TimeString   getForecastTime() const;
    void            read(MemoryReader& memoryReader);

  private:

    /*! \brief The pointer to the message object. */
    Message*        mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition mFilePosition;

    /*! \brief The length of the section. */
    std::uint32_t   mSectionLength;

    /*! \brief The GRIB tables version. */
    std::uint8_t    mTableVersion;

    /*! \brief The identification of originating/generating center (see Code table 0). */
    std::uint8_t    mCentre;

    /*! \brief The generating process identification number (allocated by originating center). */
    std::uint8_t    mGeneratingProcessIdentifier;

    /*! \brief The grid definition. */
    std::uint8_t    mGridDefinitionNumber;

    /*! \brief The flags (see Code table 1) */
    std::uint8_t    mSectionFlags;

    /*! \brief The indicator of the parameter (see Code table 2) */
    std::uint8_t    mIndicatorOfParameter;

    /*! \brief The indicator of type of level (see Code table 3) */
    std::uint8_t    mIndicatorOfTypeOfLevel;

    /*! \brief The level value. */
    std::uint16_t   mLevel;

    /*! \brief The year of the reference time. */
    std::uint8_t    mYearOfCentury;

    /*! \brief The month of the reference time. */
    std::uint8_t    mMonth;

    /*! \brief The day of the reference time. */
    std::uint8_t    mDay;

    /*! \brief The hour of the reference time. */
    std::uint8_t    mHour;

    /*! \brief The minute of the reference time. */
    std::uint8_t    mMinute;

    /*! \brief The unit of the time range (see Code table 4) */
    std::uint8_t    mUnitOfTimeRange;

    /*! \brief The period of the time (= number of time units) */
    std::uint8_t    mP1;

    /*! \brief The period of time (number of time units); or time interval between successive
        analyses, initialized analyses or forecasts, undergoing averaging or accumulation. */
    std::uint8_t    mP2;

    /*! \brief The time range indicator (see Code table 5). */
    std::uint8_t    mTimeRangeIndicator;

    /*! \brief The number included in average, when octet 21 (Code table 5) indicates an average or
         accumulation; otherwise set to zero. */
    std::uint16_t   mNumberIncludedInAverage;

    /*! \brief The number missing from averages or accumulations. */
    std::uint8_t    mNumberMissingFromAveragesOrAccumulations;

    /*! \brief The century of reference time of data (see Note 6). */
    std::uint8_t    mCenturyOfReferenceTimeOfData;

    /*! \brief The sub-center identification (see Code Table 0). */
    std::uint8_t    mSubCentre;

    /*! \brief The units decimal scale factor. */
    std::int16_t    mDecimalScaleFactor;
};


typedef std::unique_ptr<ProductSection> ProductSection_uptr;

}  // namespace GRIB1
}  // namespace SmartMet
