#pragma once

#include "common/MemoryReader.h"
#include "grid/MessageSection.h"

namespace SmartMet
{
namespace GRIB1
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
  Section 0 - Indicator section
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-4     GRIB (coded according to the CCITT International Alphabet No. 5)
  5-7     Total length of GRIB message (including Section 0)
  8       GRIB edition number (currently 1)
  --------------------------------------------------------------------------------------
*/


class IndicatorSection : public GRID::MessageSection
{
  public:

                  IndicatorSection(Message *message);
    virtual       ~IndicatorSection();

    // ### Common methods for all message sections

    void            getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition getFilePosition() const;
    std::uint32_t   getSectionLength() const;
    std::string     getSectionName() const;
    std::uint8_t    getSectionNumber() const;
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Section specific methods

    std::uint32_t   getIdentifier() const;
    std::uint8_t    getEditionNumber() const;
    std::uint32_t   getTotalLength() const;

    void            read(MemoryReader& memoryReader);

  private:

    /*! \brief The pointer to the message object. */
    Message*        mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition mFilePosition;

    std::uint32_t   mIdentifier;
    std::uint32_t   mTotalLength;
    std::uint8_t    mEditionNumber;
};


typedef std::shared_ptr<IndicatorSection> IndicatorSection_sptr;

}  // namespace GRIB1
}  // namespace SmartMet
