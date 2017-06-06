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
  the Data section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates a new DataSection
  object and calls its read() method in order to read the section information into
  the object. After that the section information can be easily accessed through
  the current object.
*/
// ====================================================================================


/*
  --------------------------------------------------------------------------------------
  SECTION 7 -  DATA SECTION
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-4     Length of section in octets (nn)
  5       Number of section (7)
  6-nn    Data in a format  described by Data Template 7.x, where x is the Data
          Representation Template number given in octets 10-11 of Section 5.
  --------------------------------------------------------------------------------------
*/


class DataSection : public GRID::MessageSection
{
  public:

                    DataSection(Message *message);
    virtual         ~DataSection();

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

    /*! \brief The pointer to the grid data */
    T::Data_ptr     mDataPtr;

    /*! \brief The size of the grid data. */
    std::size_t     mDataSize;
};


typedef std::unique_ptr<DataSection> DataSection_uptr;
typedef const DataSection* DataSection_cptr;


}  // namespace GRIB2
}  // namespace SmartMet