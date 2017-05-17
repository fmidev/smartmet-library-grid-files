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
  the Local section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates a new LocalSection
  object and calls its read() method in order to read the section information into
  the object. After that the section information can be easily accessed through
  the current object.
*/
// ====================================================================================

/*
  --------------------------------------------------------------------------------------
  SECTION 2 - LOCAL SECTION USE
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-4     Length of section in octets (nn)
  5       Number of section (2)
  6-nn    Local use
  --------------------------------------------------------------------------------------
 */


class LocalSection : public GRID::MessageSection
{
  public:

                    LocalSection(Message *message);
    virtual         ~LocalSection();

    // ### Common methods for all message sections

    void            getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition getFilePosition() const;
    std::uint32_t   getSectionLength() const;
    std::string     getSectionName() const;
    std::uint8_t    getSectionNumber() const;
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Section specific methods

    std::uint8_t    getNumberOfSection() const;
    T::Data_ptr     getDataPtr() const;
    std::size_t     getDataSize() const;
    void            read(MemoryReader& memoryReader);

  private:

    /*! \brief The pointer to the message object. */
    Message*        mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition mFilePosition;

    /*! \brief The length of the section. */
    T::UInt32_opt   mSectionLength;

    /*! \brief The section number. */
    T::UInt8_opt    mNumberOfSection;

    /*! \brief The pointer to the local data. */
    T::Data_ptr     mData;

    /*! \brief The length of the local data. */
    std::size_t     mDataLength;
};


typedef std::shared_ptr<LocalSection> LocalSection_sptr;


}  // namespace GRIB2
}  // namespace SmartMet
