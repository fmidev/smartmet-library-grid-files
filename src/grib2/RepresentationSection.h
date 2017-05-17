#pragma once

#include "common/MemoryReader.h"
#include "grid/MessageSection.h"
#include "RepresentationDefinition.h"
#include <memory>
#include <vector>

namespace SmartMet
{
namespace GRIB2
{

class Message;


// ====================================================================================
/*!
  \brief This class is used for accessing information that is found from
  the Representation section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates a new
  RepresentationSection object and calls its read() method in order to read
  the section information into the object. After that the section information can
  be easily accessed through the current object.
*/
// ====================================================================================

/*
  --------------------------------------------------------------------------------------
  SECTION 5 - DATA REPRESENTATION SECTION
  --------------------------------------------------------------------------------------
  Octet   Contents
  --------------------------------------------------------------------------------------
  1-4     Length of section in octets (nn)
  5       Number of section (5)
  6-9     Number of data points where one or more values are specified in Section 7 when
          a bit map is present, total number of data points when a bit map is absent.
  10-11   Data Representation Template Number (see Code Table 5.0)
  12-nn   Data Representation Template (see Template 5.x, where x is the Data
          Representation Template Number given in octets 10-11)
  --------------------------------------------------------------------------------------
*/


class RepresentationSection : public GRID::MessageSection
{
  public:

                    RepresentationSection(Message *message);
    virtual         ~RepresentationSection();

    // ### Common methods for all message sections

    void            getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition getFilePosition() const;
    std::uint32_t   getSectionLength() const;
    std::string     getSectionName() const;
    std::uint8_t    getSectionNumber() const;
    void            print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Section specific methods

    std::uint8_t    getNumberOfSection() const;
    std::uint32_t   getNumberOfValues() const;
    std::uint16_t   getDataRepresentationTemplateNumber() const;
    std::string     getDataRepresentationString() const;
    bool            getValueByIndex(uint index,T::ParamValue& value) const;
    void            decodeValues(T::ParamValue_vec& decodedValues) const;
    void            read(MemoryReader& memoryReader);

  private:

    RepresentationDefinition* createRepresentationDefinition(T::UInt16_opt number);

    /*! \brief The pointer to the message object. */
    Message*        mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition mFilePosition;

    /*! \brief The length of the section. */
    T::UInt32_opt   mSectionLength;

    /*! \brief The section number. */
    T::UInt8_opt    mNumberOfSection;

    /*! \brief The Number of data points. */
    T::UInt32_opt   mNumberOfValues;

    /*! \brief Data Representation Template Number (see Code Table 5.0). */
    T::UInt16_opt   mDataRepresentationTemplateNumber;

    /*! \brief The pointer to the RepresentationDefinition object. */
    RepresentationDefinition_uptr mRepresentationDefinition;
};


typedef std::unique_ptr<RepresentationSection> RepresentSection_uptr;
typedef const RepresentationSection* RepresentSection_cptr;


}  // namespace GRIB2
}  // namespace SmartMet
