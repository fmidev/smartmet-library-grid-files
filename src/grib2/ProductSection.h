#pragma once

#include "ProductDefinition.h"
#include "../grid/MessageSection.h"
#include "../common/Coordinate.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"

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

                          ProductSection();
                          ProductSection(const ProductSection& other);
                  ~ProductSection() override;

    // ### Common methods for all message sections

    void                  getAttributeList(const std::string& prefix,T::AttributeList& attributeList) const override;
    T::FilePosition       getFilePosition() const override;
    std::uint32_t         getSectionLength() const override;
    std::string           getSectionName() const override;
    std::uint8_t          getSectionNumber() const override;

    // ### Section specific methods

    T::TimeString         getForecastTime(T::TimeString referenceTime) const;
    const T::UInt8_opt    getGribParameterCategory() const;
    T::ParamLevel         getGribParameterLevel() const;
    T::ParamLevelId       getGribParameterLevelId() const;
    const T::UInt8_opt    getGribParameterNumber() const;
    T::UInt8_opt          getGeneratingProcessIdentifier() const;
    short                 getForecastType() const;
    short                 getForecastNumber() const;
    std::uint8_t          getNumberOfSection() const;
    T::UInt16_opt         getNV() const;
    ProductDefinition*    getProductDefinition() const;
    std::uint16_t         getProductDefinitionTemplateNumber() const;
    std::string           getProductDefinitionString() const;

    void                  setNV(T::UInt16_opt nv);

    void                  setProductDefinition(std::uint16_t productTemplateId);
    void                  setMessagePtr(Message *message);

    bool                  getProperty(uint propertyId,long long& value);
    bool                  setProperty(uint propertyId,long long value);

    void                  read(MemoryReader& memoryReader);
    void                  write(DataWriter& dataWriter);
    void                  print(std::ostream& stream,uint level,uint optionFlags) const override;

  private:

    ProductDefinition*    createProductDefinition(std::uint16_t productTemplateId);

    /*! \brief The pointer to the message object. */
    Message*              mMessage;

    /*! \brief The pointer to the product definition object. */
    ProductDefinition_sptr  mProductDefinition;

    /*! \brief The optional list of the coordinates values. */
    std::vector<float>    mCoordinates;

    /*! \brief The section start position in the file. */
    T::FilePosition       mFilePosition;

    /*! \brief The length of the section. */
    T::UInt32_opt         mSectionLength;

    /*! \brief The number of coordinates values after the template data. */
    T::UInt16_opt         mNV;

    /*! \brief The product definition template number. */
    T::UInt16_opt         mProductDefinitionTemplateNumber;

    /*! \brief The section number. */
    T::UInt8_opt          mNumberOfSection;

  public:

    class Template
    {
      public:
        const static std::uint16_t NormalProduct = 0;
        const static std::uint16_t EnsembleForecast = 1;
        const static std::uint16_t EnsembleDerivedForecast = 2;
        const static std::uint16_t EnsembleClusterDerivedForecast = 3;
        const static std::uint16_t ProbabilityForecast = 5;
        const static std::uint16_t PercentileForecast = 6;
        const static std::uint16_t ForecastError = 7;
        const static std::uint16_t AggregateForecast = 8;
        const static std::uint16_t TimeIntervalProbabilityForecast = 9;
        const static std::uint16_t TimeIntervalPercentileForecast = 10;
        const static std::uint16_t TimeIntervalEnsembleForecast = 11;
        const static std::uint16_t TimeIntervalEnsembleDerivedForecast = 12;
        const static std::uint16_t TimeIntervalEnsembleClusterDerivedForecast = 13;
        const static std::uint16_t TimeIntervalAggregateForecast = 15;
        const static std::uint16_t DeprecatedSatelliteProduct = 30;
        const static std::uint16_t SatelliteProduct = 31;
        const static std::uint16_t SimulatedSatelliteProduct = 32;
        const static std::uint16_t SimulatedSatelliteEnsembleProduct = 33;
        const static std::uint16_t TimeIntervalSimulatedSatelliteEnsembleProduct = 34;
        const static std::uint16_t AtmosphericChemicalProduct = 40;
        const static std::uint16_t AtmosphericChemicalEnsembleProduct = 41;
        const static std::uint16_t AggregateAtmosphericChemicalProduct = 42;
        const static std::uint16_t TimeIntervalAtmosphericChemicalEnsembleProduct = 43;
        const static std::uint16_t AerosolEnsembleProduct = 45;
        const static std::uint16_t AggregateAerosolProduct = 46;
        const static std::uint16_t TimeIntervalAerosolEnsembleProduct = 47;
        const static std::uint16_t AerosolOpticalPropertiesProduct = 48;
        const static std::uint16_t Product_49 = 49;
        const static std::uint16_t CategoricalForecast = 51;
        const static std::uint16_t PartitionedProduct = 53;
        const static std::uint16_t PartitionedEnsembleProduct = 54;
        const static std::uint16_t Product_55 = 55;
        const static std::uint16_t Product_56 = 56;
        const static std::uint16_t Product_57 = 57;
        const static std::uint16_t Product_58 = 58;
        const static std::uint16_t Product_59 = 59;
        const static std::uint16_t EnsembleReforecast = 60;
        const static std::uint16_t TimeIntervalEnsembleReforecast = 61;
        const static std::uint16_t Product_67 = 67;
        const static std::uint16_t Product_68 = 68;
        const static std::uint16_t Product_70 = 70;
        const static std::uint16_t Product_71 = 71;
        const static std::uint16_t Product_72 = 72;
        const static std::uint16_t Product_73 = 73;
        const static std::uint16_t TimeIntervalCategoricalForecast = 91;
        const static std::uint16_t CharacterStringProduct = 254;
        const static std::uint16_t AuxiliarySatelliteProduct = 311;
        const static std::uint16_t CrossSectionProduct = 1000;
        const static std::uint16_t ProcessedCrossSectionProduct = 1001;
        const static std::uint16_t AreaProcessedCrossSectionProduct = 1002;
        const static std::uint16_t HovmollerProduct = 1100;
        const static std::uint16_t ProcessedHovmollerProduct = 1101;
    };
};


using ProductSect_sptr = std::shared_ptr<ProductSection>;


}  // namespace GRIB2
}  // namespace SmartMet
