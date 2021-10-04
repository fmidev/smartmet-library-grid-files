#pragma once

#include "RepresentationDefinition.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../grid/MessageSection.h"

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

                    RepresentationSection();
                    RepresentationSection(const RepresentationSection& other);
    virtual         ~RepresentationSection();

    // ### Common methods for all message sections

    void            getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const;
    T::FilePosition getFilePosition() const;
    std::uint32_t   getSectionLength() const;
    std::string     getSectionName() const;
    std::uint8_t    getSectionNumber() const;

    // ### Section specific methods

    void            decodeValues(T::ParamValue_vec& decodedValues) const;
    void            encodeValues(Message *message,T::ParamValue_vec& values);
    std::uint8_t    getNumberOfSection() const;
    std::uint32_t   getNumberOfValues() const;
    std::uint16_t   getDataRepresentationTemplateNumber() const;
    std::string     getDataRepresentationString() const;
    bool            getValueByIndex(uint index,T::ParamValue& value) const;

    void            setNumberOfValues(std::uint32_t numOfValues);
    void            setMessagePtr(Message *message);
    void            setRepresentationDefinition(std::uint16_t templateNumber);
    void            setRepresentationDefinition(RepresentationDefinition *representationDefinition);

    bool            getProperty(uint propertyId,long long& value);
    bool            setProperty(uint propertyId,long long value);

    void            read(MemoryReader& memoryReader);
    void            write(DataWriter& dataWriter);
    void            print(std::ostream& stream,uint level,uint optionFlags) const;


    RepresentationDefinition_sptr getRepresentationDefinition();

  private:

    RepresentationDefinition*     createRepresentationDefinition(std::uint16_t templateNumber);

    /*! \brief The pointer to the message object. */
    Message*        mMessage;

    /*! \brief The pointer to the RepresentationDefinition object. */
    RepresentationDefinition_sptr mRepresentationDefinition;

    /*! \brief The section start position in the file. */
    T::FilePosition mFilePosition;

    /*! \brief The length of the section. */
    T::UInt32_opt   mSectionLength;

    /*! \brief The Number of data points. */
    T::UInt32_opt   mNumberOfValues;

    /*! \brief Data Representation Template Number (see Code Table 5.0). */
    T::UInt16_opt   mDataRepresentationTemplateNumber;

    /*! \brief The section number. */
    T::UInt8_opt    mNumberOfSection;

  public:
    class Template
    {
      public:

        const static std::uint16_t GridDataRepresentation = 0;
        const static std::uint16_t MatrixDataRepresentation = 1;
        const static std::uint16_t ComplexGridDataRepresentation = 2;
        const static std::uint16_t ComplexDifferenceGridDataRepresentation = 3;
        const static std::uint16_t FloatingPointGridDataRepresentation = 4;
        const static std::uint16_t PreprocessedGridDataRepresentation = 6;
        const static std::uint16_t JpegGridDataRepresentation = 40;
        const static std::uint16_t PngGridDataRepresentation = 41;
        const static std::uint16_t SpectralGridDataRepresentation = 42;
        const static std::uint16_t SpectralDataRepresentation = 50;
        const static std::uint16_t SphericalHarmonicsDataRepresentation = 51;
        const static std::uint16_t LogarithmicGridDataRepresentation = 61;
        const static std::uint16_t ComplexSphericalHarmonicsDataRepresentation = 50000;
    };

};


using RepresentSect_sptr = std::shared_ptr<RepresentationSection>;


}  // namespace GRIB2
}  // namespace SmartMet
