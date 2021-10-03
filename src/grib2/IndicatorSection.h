#pragma once

#include "../grid/MessageSection.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"

namespace SmartMet
{
namespace GRIB2
{

class Message;


// ====================================================================================
/*!
  \brief This class is used for accessing information that is found from
  the Indicator section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates
  a new IndicatorSection object and calls its read() method in order to read
  the section information into the object. After that the section information
  can be easily accessed through the current object.
*/
// ====================================================================================

/*
  --------------------------------------------------------------------------------------
  SECTION 0 - INDICATOR SECTION
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-4     "GRIB" (coded according to the International Alphabet No. 5.)
  5-6     Reserved
  7       Discipline - GRIB Master Table Number (see Code Table 0.0)
  8       GRIB Edition Number (currently 2)
  9-16    Total length of GRIB message in octets (including Section 0)
  --------------------------------------------------------------------------------------
*/


class IndicatorSection : public GRID::MessageSection
{
  public:

                      IndicatorSection();
                      IndicatorSection(const IndicatorSection& other);
    virtual           ~IndicatorSection();

    // ### Common methods for all message sections

    void              getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    T::FilePosition   getFilePosition() const;
    std::uint32_t     getSectionLength() const;
    std::string       getSectionName() const;
    std::uint8_t      getSectionNumber() const;

    // ### Section specific methods

    T::UInt16_opt     getReserved() const;
    T::UInt8_opt      getDiscipline() const;
    std::string       getDisciplineString() const;
    T::UInt8_opt      getEditionNumber() const;
    std::uint64_t     getTotalLength() const;

    void              setDiscipline(std::uint8_t discipline);
    void              setEditionNumber(std::uint8_t editionNumber);
    void              setTotalLength(std::uint64_t totalLength);
    void              setMessagePtr(Message *message);

    bool              getProperty(uint propertyId,long long& value);
    bool              setProperty(uint propertyId,long long value);

    void              read(MemoryReader& memoryReader);
    void              write(DataWriter& dataWriter);
    void              print(std::ostream& stream,uint level,uint optionFlags) const;

  private:

    /*! \brief The pointer to the message object. */
    Message*          mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition   mFilePosition;

    /*! \brief The total length of the GRIB message in octets (including Section 0). */
    std::uint64_t     mTotalLength;

    /*! \brief The GRIB file identifier ('GRIB'). */
    uchar             mIdentifier[4];

    /*! \brief Reserved bytes. */
    T::UInt16_opt     mReserved;

    /*! \brief The discipline of the message. The GRIB Master Table Number (see Code Table 0.0). */
    T::UInt8_opt      mDiscipline;

    /*! \brief The GRIB edition number. */
    T::UInt8_opt      mEditionNumber;

};

using IndicatorSect_sptr = std::shared_ptr<IndicatorSection>;


}  // namespace GRIB2
}  // namespace SmartMet
