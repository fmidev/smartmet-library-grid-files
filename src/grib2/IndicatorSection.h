#pragma once

#include "grid/MessageSection.h"
#include "common/MemoryReader.h"

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

                      IndicatorSection(Message *message);
    virtual           ~IndicatorSection();

    // ### Common methods for all message sections

    void              getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition   getFilePosition() const;
    std::uint32_t     getSectionLength() const;
    std::string       getSectionName() const;
    std::uint8_t      getSectionNumber() const;
    void              print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Section specific methods

    T::UInt32_opt     getIdentifier() const;
    T::UInt16_opt     getReserved() const;
    std::uint8_t      getDiscipline() const;
    std::string       getDisciplineString() const;
    std::uint8_t      getEditionNumber() const;
    std::uint64_t     getTotalLength() const;
    void              read(MemoryReader& memoryReader);

  private:

    /*! \brief The pointer to the message object. */
    Message*          mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition   mFilePosition;

    /*! \brief The GRIB file identifier ('GRIB'). */
    T::UInt32_opt     mIdentifier;

    /*! \brief Reserved bytes. */
    T::UInt16_opt     mReserved;

    /*! \brief The discipline of the message. The GRIB Master Table Number (see Code Table 0.0). */
    T::UInt8_opt      mDiscipline;

    /*! \brief The GRIB edition number. */
    T::UInt8_opt      mEditionNumber;

    /*! \brief The total length of the GRIB message in octets (including Section 0). */
    std::uint64_t     mTotalLength;
};

typedef std::shared_ptr<IndicatorSection> IndicatorSection_sptr;


}  // namespace GRIB2
}  // namespace SmartMet
