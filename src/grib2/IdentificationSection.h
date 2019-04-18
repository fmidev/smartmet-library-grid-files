#pragma once

#include "../grid/MessageSection.h"
#include "../grid/Typedefs.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"

#include <boost/date_time/posix_time/posix_time.hpp>

namespace SmartMet
{
namespace GRIB2
{

class Message;


// ====================================================================================
/*!
  \brief This class is used for accessing information that is found from
  the Identification section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates
  a new IdentificationSection object and calls its read() method in order to read
  the section information into the object. After that the section information can
  be easily accessed through the current object.
*/
// ====================================================================================

/*
  --------------------------------------------------------------------------------------
  SECTION 1 - IDENTIFICATION SECTION
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-4     Length of section in octets (21 or nn)
  5       Number of section (1)
  6-7     Identification of originating/generating centre (see Common Code Table C-1)
  8-9     Identification of originating/generating sub-centre (allocated by
          originating/generating Centre)
  10      GRIB Master Tables Version Number (see Code Table 1.0 and Note 1) (currently 2)
  11      Version number of GRIB Local Tables used to augment Master Tables (see Code
          Table 1.1 and Note 2)
  12      Significance of Reference Time (see Code Table 1.2)
  13-14   Year (4 digits)
  15      Month
  16      Day
  17      Hour
  18      Minute
  19      Second
  20      Production status of processed data in this GRIB message (see Code Table 1.3)
  21      Type of processed data in this GRIB message (see Code Table 1.4)
  22-nn   Reserved: need not be present
  --------------------------------------------------------------------------------------
*/


class IdentificationSection : public GRID::MessageSection
{
  public:

                    IdentificationSection();
                    IdentificationSection(const IdentificationSection& other);
    virtual         ~IdentificationSection();

    // ### Common methods for all message sections

    void            getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition getFilePosition() const;
    std::uint32_t   getSectionLength() const;
    std::string     getSectionName() const;
    std::uint8_t    getSectionNumber() const;
    T::TimeString   getReferenceTime() const;

    // ### Section specific methods

    T::UInt8_opt    getNumberOfSection() const;
    T::UInt16_opt   getCentre() const;
    T::UInt16_opt   getSubCentre() const;
    T::UInt8_opt    getTablesVersion() const;
    T::UInt8_opt    getLocalTablesVersion() const;
    T::UInt8_opt    getSignificanceOfReferenceTime() const;
    T::UInt16_opt   getYear() const;
    T::UInt8_opt    getMonth() const;
    T::UInt8_opt    getDay() const;
    T::UInt8_opt    getHour() const;
    T::UInt8_opt    getMinute() const;
    T::UInt8_opt    getSecond() const;
    T::UInt8_opt    getProductionStatusOfProcessedData() const;
    T::UInt8_opt    getTypeOfProcessedData() const;
    T::Data_ptr     getReservedDataPtr() const;

    void            setCentre(T::UInt16_opt centre);
    void            setSubCentre(T::UInt16_opt subCentre);
    void            setTablesVersion(T::UInt8_opt tablesVersion);
    void            setLocalTablesVersion(T::UInt8_opt localTablesVersion);
    void            setSignificanceOfReferenceTime(T::UInt8_opt significanceOfReferenceTime);
    void            setYear(T::UInt16_opt year);
    void            setMonth(T::UInt8_opt month);
    void            setDay(T::UInt8_opt day);
    void            setHour(T::UInt8_opt hour);
    void            setMinute(T::UInt8_opt minute);
    void            setSecond(T::UInt8_opt second);
    void            setProductionStatusOfProcessedData(T::UInt8_opt productionStatusOfProcessedData);
    void            setTypeOfProcessedData(T::UInt8_opt typeOfProcessedData);
    void            setMessagePtr(Message *message);

    bool            getProperty(uint propertyId,long long& value);
    bool            setProperty(uint propertyId,long long value);

    void            read(MemoryReader& memoryReader);
    void            write(DataWriter& dataWriter);
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    /*! \brief The pointer to the message object. */
    Message*        mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition mFilePosition;

    /*! \brief The length of the section. */
    T::UInt32_opt   mSectionLength;

    /*! \brief The section number. */
    T::UInt8_opt    mNumberOfSection;

    /*! \brief The identification of originating/generating centre (see Common Code Table C-1). */
    T::UInt16_opt   mCentre;

    /*! \brief The identification of originating/generating sub-centre (allocated by originating/generating Centre). */
    T::UInt16_opt   mSubCentre;

    /*! \brief The GRIB Master Tables Version Number (see Code Table 1.0 and Note 1). */
    T::UInt8_opt    mTablesVersion;

    /*! \brief The version number of GRIB Local Tables used to augment Master Tables (see Code Table 1.1 and Note 2). */
    T::UInt8_opt    mLocalTablesVersion;

    /*! \brief The significance of Reference Time (see Code Table 1.2). */
    T::UInt8_opt    mSignificanceOfReferenceTime;

    /*! \brief The year of the reference time. */
    T::UInt16_opt   mYear;

    /*! \brief The month of the reference time. */
    T::UInt8_opt    mMonth;

    /*! \brief The day of the reference time. */
    T::UInt8_opt    mDay;

    /*! \brief The hour of the reference time. */
    T::UInt8_opt    mHour;

    /*! \brief The minute of the reference time. */
    T::UInt8_opt    mMinute;

    /*! \brief The second of the reference time. */
    T::UInt8_opt    mSecond;

    /*! \brief The production status of processed data in this GRIB message (see Code Table 1.3). */
    T::UInt8_opt    mProductionStatusOfProcessedData;

    /*! \brief The type of processed data in this GRIB message (see Code Table 1.4). */
    T::UInt8_opt    mTypeOfProcessedData;

    /*! \brief  Optional extra data. */
    T::Data_ptr     mDataPtr;

    /*! \brief  The size of the optional extra data. */
    uint            mDataSize;

    bool            mReleaseData;
};

typedef std::shared_ptr<IdentificationSection> IdentifSect_sptr;

}  // namespace GRIB2
}  // namespace SmartMet
