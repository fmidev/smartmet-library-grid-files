#pragma once

#include "ProductDefinition.h"
#include "grid/MessageSection.h"
#include "common/Coordinate.h"
#include "common/MemoryReader.h"
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
  the Product section in a GRIB file.

  When a message in a GRIB file is read, the Message class creates a new
  ProductSection object and calls its read() method in order to read the section
  information into the object. After that the section information can be easily
  accessed through the current object.
*/
// ====================================================================================

/*
  --------------------------------------------------------------------------------------
  SECTION 4 - PRODUCT DEFINITION SECTION
  --------------------------------------------------------------------------------------
  Octet     Contents
  --------------------------------------------------------------------------------------
  1-4       Length of section in octets (nn)
  5         Number of section (4)
  6-7       Number of coordinates values after Template (see Note 1)
  8-9       Product Definition Template Number (see Code Table 4.0)
  10-xx     Product Definition Template (see Template 4.X, where X is the Product
            Definition Template Number given in octets 8-9)
  [xx+1]-nn Optional list of coordinates values (see Notes 2 and 3)
  --------------------------------------------------------------------------------------
*/


class ProductSection : public GRID::MessageSection
{
  public:

                          ProductSection(Message *message);
    virtual               ~ProductSection();

    // ### Common methods for all message sections

    void                  getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    T::FilePosition       getFilePosition() const;
    T::TimeString         getForecastTime(T::TimeString referenceTime) const;
    std::uint32_t         getSectionLength() const;
    std::string           getSectionName() const;
    std::uint8_t          getSectionNumber() const;
    T::ParamLevel         getGribParameterLevel() const;
    T::ParamLevelId       getGribParameterLevelId() const;
    ProductDefinition*    getProductDefinition() const;
    void                  print(std::ostream& stream,uint level,uint optionFlags) const;

    // ### Section specific methods

    const T::UInt8_opt    getGribParameterCategory() const;
    const T::UInt8_opt    getGribParameterNumber() const;
    T::UInt8_opt          getGeneratingProcessIdentifier() const;
    short                 getForecastType() const;
    short                 getForecastNumber() const;
    std::uint8_t          getNumberOfSection() const;
    T::UInt16_opt         getNV() const;
    std::uint16_t         getProductDefinitionTemplateNumber() const;
    std::string           getProductDefinitionString() const;
    void                  read(MemoryReader& memoryReader);

  private:

    ProductDefinition*    createProductDefinition(T::UInt16_opt number);

    /*! \brief The pointer to the message object. */
    Message*              mMessage;

    /*! \brief The section start position in the file. */
    T::FilePosition       mFilePosition;

    /*! \brief The length of the section. */
    T::UInt32_opt         mSectionLength;

    /*! \brief The section number. */
    T::UInt8_opt          mNumberOfSection;

    /*! \brief The number of coordinates values after the template data. */
    T::UInt16_opt         mNV;

    /*! \brief The product definition template number. */
    T::UInt16_opt         mProductDefinitionTemplateNumber;

    /*! \brief The pointer to the product definition object. */
    ProductDefinition_uptr  mProductDefinition;

    /*! \brief The optional list of the coordinates values. */
    std::vector<float>    mCoordinates;
};


typedef std::unique_ptr<ProductSection> ProductSection_uptr;
typedef const ProductSection* ProductSection_cptr;


}  // namespace GRIB2
}  // namespace SmartMet
