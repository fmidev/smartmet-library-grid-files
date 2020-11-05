#include "ProductSection.h"
#include "Message.h"
#include "../identification/GridDef.h"
#include <macgyver/Exception.h>
#include "../common/GeneralFunctions.h"

#include "implementation/NormalProductImpl.h"                                   // 4.0
#include "implementation/EnsembleForecastImpl.h"                                // 4.1
#include "implementation/EnsembleDerivedForecastImpl.h"                         // 4.2
#include "implementation/EnsembleClusterDerivedForecastImpl.h"                  // 4.3
#include "implementation/ProbabilityForecastImpl.h"                             // 4.5
#include "implementation/PercentileForecastImpl.h"                              // 4.6
#include "implementation/ForecastErrorImpl.h"                                   // 4.7
#include "implementation/AggregateForecastImpl.h"                               // 4.8
#include "implementation/TimeIntervalProbabilityForecastImpl.h"                 // 4.9
#include "implementation/TimeIntervalPercentileForecastImpl.h"                  // 4.10
#include "implementation/TimeIntervalEnsembleForecastImpl.h"                    // 4.11
#include "implementation/TimeIntervalEnsembleDerivedForecastImpl.h"             // 4.12
#include "implementation/TimeIntervalEnsembleClusterDerivedForecastImpl.h"      // 4.13
#include "implementation/TimeIntervalAggregateForecastImpl.h"                   // 4.15
#include "implementation/DeprecatedSatelliteProductImpl.h"                      // 4.30
#include "implementation/SatelliteProductImpl.h"                                // 4.31
#include "implementation/SimulatedSatelliteProductImpl.h"                       // 4.32
#include "implementation/SimulatedSatelliteEnsembleProductImpl.h"               // 4.33
#include "implementation/TimeIntervalSimulatedSatelliteEnsembleProductImpl.h"   // 4.34
#include "implementation/AtmosphericChemicalProductImpl.h"                      // 4.40
#include "implementation/AtmosphericChemicalEnsembleProductImpl.h"              // 4.41
#include "implementation/AggregateAtmosphericChemicalProductImpl.h"             // 4.42
#include "implementation/TimeIntervalAtmosphericChemicalEnsembleProductImpl.h"  // 4.43
#include "implementation/AerosolEnsembleProductImpl.h"                          // 4.45
#include "implementation/AggregateAerosolProductImpl.h"                         // 4.46
#include "implementation/TimeIntervalAerosolEnsembleProductImpl.h"              // 4.47
#include "implementation/AerosolOpticalPropertiesProductImpl.h"                 // 4.48
#include "implementation/CategoricalForecastImpl.h"                             // 4.51
#include "implementation/PartitionedProductImpl.h"                              // 4.53
#include "implementation/PartitionedEnsembleProductImpl.h"                      // 4.54
#include "implementation/EnsembleReforecastImpl.h"                              // 4.60
#include "implementation/TimeIntervalEnsembleReforecastImpl.h"                  // 4.61
#include "implementation/TimeIntervalCategoricalForecastImpl.h"                 // 4.91
#include "implementation/CharacterStringProductImpl.h"                          // 4.254
#include "implementation/AuxiliarySatelliteProductImpl.h"                       // 4.311
#include "implementation/CrossSectionProductImpl.h"                             // 4.1000
#include "implementation/ProcessedCrossSectionProductImpl.h"                    // 4.1001
#include "implementation/AreaProcessedCrossSectionProductImpl.h"                // 4.1002
#include "implementation/HovmollerProductImpl.h"                                // 4.1100
#include "implementation/ProcessedHovmollerProductImpl.h"                       // 4.1101
#include "implementation/Product_49Impl.h"
#include "implementation/Product_55Impl.h"
#include "implementation/Product_56Impl.h"
#include "implementation/Product_57Impl.h"
#include "implementation/Product_58Impl.h"
#include "implementation/Product_59Impl.h"
#include "implementation/Product_67Impl.h"
#include "implementation/Product_68Impl.h"
#include "implementation/Product_70Impl.h"
#include "implementation/Product_71Impl.h"
#include "implementation/Product_72Impl.h"
#include "implementation/Product_73Impl.h"

#include <iostream>
#include <macgyver/StringConversion.h>

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class. */

ProductSection::ProductSection()
{
  try
  {
    mMessage = nullptr;
    mFilePosition = 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed failed!",nullptr);
  }
}





/*! \brief The copy constructor of the class. */

ProductSection::ProductSection(const ProductSection& other)
:GRID::MessageSection(other)
{
  try
  {
    mMessage = nullptr;
    mFilePosition = other.mFilePosition;
    mSectionLength = other.mSectionLength;
    mNumberOfSection = other.mNumberOfSection;
    mNV = other.mNV;
    mProductDefinitionTemplateNumber = other.mProductDefinitionTemplateNumber;
    mCoordinates = other.mCoordinates;

    if (other.mProductDefinition)
    {
      // Duplicating the product definition.
      ProductDefinition *def = other.mProductDefinition->createProductDefinition();
      mProductDefinition.reset(def);
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Constructor failed failed!",nullptr);
  }
}





/*! \brief The destructor of the class. */

ProductSection::~ProductSection()
{
}





/*! \brief The method can be used for collecting all attributeList details related
    to the current section.
*/

void ProductSection::getAttributeList(std::string prefix,T::AttributeList& attributeList) const
{
  try
  {
    char name[300];

    sprintf(name,"%sproduct.productDefinitionTemplateNumber",prefix.c_str());
    attributeList.addAttribute(name,toString(getProductDefinitionTemplateNumber()));

    sprintf(name,"%sproduct.productDefinitionString",prefix.c_str());
    attributeList.addAttribute(name,getProductDefinitionString());

    sprintf(name,"%sproduct.def.",prefix.c_str());
    if (mProductDefinition)
      mProductDefinition->getAttributeList(name,attributeList);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method sets the pointer to the Message -object in which the current section
    object belongs to. This helps the object to reference information in other sections.

        \param message    The Message -object pointer.
*/

void ProductSection::setMessagePtr(Message *message)
{
  try
  {
    mMessage = message;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for fetching a (long long ) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the requested property is returned in this parameter.
        \return            The method returns true if the value of the requested property was found.
*/

bool ProductSection::getProperty(uint propertyId,long long& value)
{
  try
  {
    switch (propertyId)
    {
      case Property::ProductSection::ProductDefinitionTemplateNumber:
        value = *mProductDefinitionTemplateNumber;
        return true;

      case Property::ProductSection::NV:
        value = *mNV;
        return true;
    }

    if (mProductDefinition)
      return mProductDefinition->getProperty(propertyId,value);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method is used for setting a (long long) value for the property according to the property id.

        \param propertyId  The (numeric) identifier of the requested property.
        \param value       The value of the property to be set.
        \return            The method returns true if the value of the requested property was set.
*/

bool ProductSection::setProperty(uint propertyId,long long value)
{
  try
  {
    switch (propertyId)
    {
      case Property::ProductSection::ProductDefinitionTemplateNumber:
        setProductDefinition(value);
        return true;

      case Property::ProductSection::NV:
        setNV(value);
        return true;
    }

    if (mProductDefinition)
      return mProductDefinition->setProperty(propertyId,value);

    return false;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ProductSection::read(MemoryReader& memoryReader)
{
  try
  {
    mFilePosition = memoryReader.getGlobalReadPosition();

    memoryReader >> mSectionLength;
    if (missing(mSectionLength))
    {
      Fmi::Exception exception(BCP,"Section 4 length cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfSection;

    memoryReader >> mNV;
    memoryReader >> mProductDefinitionTemplateNumber;
    if (missing(mProductDefinitionTemplateNumber))
    {
      Fmi::Exception exception(BCP,"Product definition template number cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-2));
      throw exception;
    }

    if (mProductDefinitionTemplateNumber)
    {
      auto productDefinition = createProductDefinition((*mProductDefinitionTemplateNumber));
      if (productDefinition == nullptr)
      {
        Fmi::Exception exception(BCP,"Product definition template not supported!");
        exception.addParameter("Template number",Fmi::to_string(*mProductDefinitionTemplateNumber));
        throw exception;
      }
      mProductDefinition.reset(productDefinition);
      productDefinition->read(memoryReader);
    }

    if (!missing(mNV) && *mNV != 0)
    {
      for (std::uint16_t t=0; t<*mNV; t++)
      {
        auto coordinate = memoryReader.read_float();
        mCoordinates.push_back(coordinate);
      }
    }
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed failed!",nullptr);
  }
}





/*! \brief The method writes all data related to the current object into the data stream.

        \param dataWriter  The data stream object.
*/

void ProductSection::write(DataWriter& dataWriter)
{
  try
  {

    if (!mProductDefinition)
      throw Fmi::Exception(BCP,"Missing product definition");

    if (!missing(mNV) && *mNV != 0)
    {
      throw Fmi::Exception(BCP,"ProductSection does not support optional coordinates yet");
    }

    mFilePosition = dataWriter.getWritePosition();
    mSectionLength = 0;
    mNumberOfSection = (std::uint8_t)Message::SectionNumber::product_section;

    dataWriter << mSectionLength;
    dataWriter << mNumberOfSection;
    dataWriter << mNV;

    mProductDefinitionTemplateNumber = mProductDefinition->getTemplateNumber();
    dataWriter << mProductDefinitionTemplateNumber;

    mProductDefinition->write(dataWriter);

    // Updating the section length.

    ulonglong fPos = dataWriter.getWritePosition();
    mSectionLength = fPos - mFilePosition;
    dataWriter.setWritePosition(mFilePosition);
    dataWriter << mSectionLength;
    dataWriter.setWritePosition(fPos);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the section start position in the grib file.

        \return  The section's start position in the grib file.
*/

T::FilePosition ProductSection::getFilePosition() const
{
  try
  {
    return mFilePosition;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t ProductSection::getSectionLength() const
{
  try
  {
    if (mSectionLength)
      return *mSectionLength;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the name of the section. */

std::string ProductSection::getSectionName() const
{
  try
  {
    return std::string("Product");
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the default section number. */

std::uint8_t ProductSection::getSectionNumber() const
{
  try
  {
    return (std::uint8_t)Message::SectionNumber::product_section;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t ProductSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number
    // anyway
    if (mNumberOfSection)
      return *mNumberOfSection;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





T::UInt16_opt ProductSection::getNV() const
{
  try
  {
    return mNV;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::string ProductSection::getProductDefinitionString() const
{
  try
  {
    std::uint8_t tablesVersion = mMessage->getTablesVersion();
    return Identification::gridDef.getGribTableValue(2,tablesVersion,"4.0", getProductDefinitionTemplateNumber());
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





std::uint16_t ProductSection::getProductDefinitionTemplateNumber() const
{
  try
  {
    if (mProductDefinitionTemplateNumber)
      return *mProductDefinitionTemplateNumber;

    return 0;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}





/*! \brief The method returns the time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString ProductSection::getForecastTime(T::TimeString referenceTime) const
{
  try
  {
    if (mProductDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductDefinition' attribute points to nullptr!");

    return mProductDefinition->getForecastTime(referenceTime);
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}





const T::UInt8_opt ProductSection::getGribParameterCategory() const
{
  try
  {
    if (mProductDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductDefinition' attribute points to nullptr!");

    return mProductDefinition->getGribParameterCategory();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}




const T::UInt8_opt ProductSection::getGribParameterNumber() const
{
  try
  {
    if (mProductDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductDefinition' attribute points to nullptr!");

    return mProductDefinition->getGribParameterNumber();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}





/*! \brief The method returns the type of the parameter level.

         \return   The parameter level type (= enum value).
*/

std::uint8_t ProductSection::getGribParameterLevelId() const
{
  try
  {
    if (mProductDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductDefinition' attribute points to nullptr!");

    return mProductDefinition->getGribParameterLevelId();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}





/*! \brief The method returns the parameter level.

         \return   The parameter level.
*/

T::ParamLevel ProductSection::getGribParameterLevel() const
{
  try
  {
    if (mProductDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductDefinition' attribute points to nullptr!");

    return mProductDefinition->getGribParameterLevel();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}





/*! \brief The method returns the forecast type of the current grid.

        \return   The forecast type.
*/

short ProductSection::getForecastType() const
{
  try
  {
    if (mProductDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductDefinition' attribute points to nullptr!");

    const EpsSettings *eps = mProductDefinition->getEps();
    if (eps != nullptr)
    {
      T::UInt8_opt val = eps->getTypeOfEnsembleForecast();
      if (val)
        return *val;
    }

    return 0;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}





/*! \brief The method returns the forecast number of the current grid.

        \return   The forecast number.
*/

short ProductSection::getForecastNumber() const
{
  try
  {
    if (mProductDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductDefinition' attribute points to nullptr!");

    const EpsSettings *eps = mProductDefinition->getEps();
    if (eps != nullptr)
    {
      T::UInt8_opt val = eps->getPerturbationNumber();
      if (val)
        return *val;
    }

    return -1;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}





void ProductSection::setNV(T::UInt16_opt nv)
{
  try
  {
    mNV = nv;
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}





void ProductSection::setProductDefinition(std::uint16_t productTemplateId)
{
  try
  {
    ProductDefinition *productDefintion = createProductDefinition(productTemplateId);

    if (productDefintion == nullptr)
    {
      Fmi::Exception exception(BCP,"Cannot create product definition!");
      exception.addParameter("Product",Fmi::to_string(productTemplateId));
      throw exception;
    }

    mProductDefinitionTemplateNumber = productDefintion->getTemplateNumber();
    mProductDefinition.reset(productDefintion);
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Creation of a product definition failed!",nullptr);
  }
}





ProductDefinition* ProductSection::createProductDefinition(std::uint16_t productTemplateId)
{
  try
  {
    switch (productTemplateId)
    {
      case Template::NormalProduct:
        return new NormalProductImpl();

      case Template::EnsembleForecast:
        return new EnsembleForecastImpl();

      case Template::EnsembleDerivedForecast:
        return new EnsembleDerivedForecastImpl();

      case Template::EnsembleClusterDerivedForecast:
        return new EnsembleClusterDerivedForecastImpl();

      case Template::ProbabilityForecast:
        return new ProbabilityForecastImpl();

      case Template::PercentileForecast:
        return new PercentileForecastImpl();

      case Template::ForecastError:
        return new ForecastErrorImpl();

      case Template::AggregateForecast:
        return new AggregateForecastImpl();

      case Template::TimeIntervalProbabilityForecast:
        return new TimeIntervalProbabilityForecastImpl();

      case Template::TimeIntervalPercentileForecast:
        return new TimeIntervalPercentileForecastImpl();

      case Template::TimeIntervalEnsembleForecast:
        return new TimeIntervalEnsembleForecastImpl();

      case Template::TimeIntervalEnsembleDerivedForecast:
        return new TimeIntervalEnsembleDerivedForecastImpl();

      case Template::TimeIntervalEnsembleClusterDerivedForecast:
        return new TimeIntervalEnsembleClusterDerivedForecastImpl();

      case Template::TimeIntervalAggregateForecast:
        return new TimeIntervalAggregateForecastImpl();

      case Template::DeprecatedSatelliteProduct:
        return new DeprecatedSatelliteProductImpl();

      case Template::SatelliteProduct:
        return new SatelliteProductImpl();

      case Template::SimulatedSatelliteProduct:
        return new SimulatedSatelliteProductImpl();

      case Template::SimulatedSatelliteEnsembleProduct:
        return new SimulatedSatelliteEnsembleProductImpl();

      case Template::TimeIntervalSimulatedSatelliteEnsembleProduct:
        return new TimeIntervalSimulatedSatelliteEnsembleProductImpl();

      case Template::AtmosphericChemicalProduct:
        return new AtmosphericChemicalProductImpl();

      case Template::AtmosphericChemicalEnsembleProduct:
        return new AtmosphericChemicalEnsembleProductImpl();

      case Template::AggregateAtmosphericChemicalProduct:
        return new AggregateAtmosphericChemicalProductImpl();

      case Template::TimeIntervalAtmosphericChemicalEnsembleProduct:
        return new TimeIntervalAtmosphericChemicalEnsembleProductImpl();

      case Template::AerosolEnsembleProduct:
        return new AerosolEnsembleProductImpl();

      case Template::AggregateAerosolProduct:
        return new AggregateAerosolProductImpl();

      case Template::TimeIntervalAerosolEnsembleProduct:
        return new TimeIntervalAerosolEnsembleProductImpl();

      case Template::AerosolOpticalPropertiesProduct:
        return new AerosolOpticalPropertiesProductImpl();

      case Template::CategoricalForecast:
        return new CategoricalForecastImpl();

      case Template::PartitionedProduct:
        return new PartitionedProductImpl();

      case Template::PartitionedEnsembleProduct:
        return new PartitionedEnsembleProductImpl();

      case Template::EnsembleReforecast:
        return new EnsembleReforecastImpl();

      case Template::TimeIntervalEnsembleReforecast:
        return new TimeIntervalEnsembleReforecastImpl();

      case Template::TimeIntervalCategoricalForecast:
        return new TimeIntervalCategoricalForecastImpl();

      case Template::CharacterStringProduct:
        return new CharacterStringProductImpl();

      case Template::AuxiliarySatelliteProduct:
        return new AuxiliarySatelliteProductImpl();

      case Template::CrossSectionProduct:
        return new CrossSectionProductImpl();

      case Template::ProcessedCrossSectionProduct:
        return new ProcessedCrossSectionProductImpl();

      case Template::AreaProcessedCrossSectionProduct:
        return new AreaProcessedCrossSectionProductImpl();

      case Template::HovmollerProduct:
        return new HovmollerProductImpl();

      case Template::ProcessedHovmollerProduct:
        return new ProcessedHovmollerProductImpl();

      case Template::Product_49:
        return new Product_49Impl();

      case Template::Product_55:
        return new Product_55Impl();

      case Template::Product_56:
        return new Product_56Impl();

      case Template::Product_57:
        return new Product_57Impl();

      case Template::Product_58:
        return new Product_58Impl();

      case Template::Product_59:
        return new Product_59Impl();

      case Template::Product_67:
        return new Product_67Impl();

      case Template::Product_68:
        return new Product_68Impl();

      case Template::Product_70:
        return new Product_70Impl();

      case Template::Product_71:
        return new Product_71Impl();

      case Template::Product_72:
        return new Product_72Impl();

      case Template::Product_73:
        return new Product_73Impl();
    }

    return nullptr;
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Creation of a product definition failed!",nullptr);
  }
}





ProductDefinition* ProductSection::getProductDefinition() const
{
  try
  {
    return mProductDefinition.get();
  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Creation of a product definition failed!",nullptr);
  }
}




T::UInt8_opt ProductSection::getGeneratingProcessIdentifier() const
{
  try
  {
    if (mProductDefinition == nullptr)
      throw Fmi::Exception(BCP,"The 'mProductDefinition' attribute points to nullptr!");

    return mProductDefinition->getGeneratingProcessIdentifier();
  }
  catch (...)
  {
    Fmi::Exception exception(BCP,"Operation failed!",nullptr);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}




/*! \brief The method prints the content of the current object into the given stream.

        \param ostream      The output stream.
        \param level        The print level (used when printing multi-level structures).
        \param optionFlags  The printing options expressed in flag-bits.
*/

void ProductSection::print(std::ostream& stream,uint level,uint optionFlags) const
{
  try
  {
    stream << space(level) << "SECTION ["<< toString(getSectionNumber()) << "] " << getSectionName() << "\n";
    stream << space(level) << "- filePosition                    = " << toString(mFilePosition) << " (" << uint64_toHex(mFilePosition) << ")\n";
    stream << space(level) << "- sectionLength                   = " <<  toString(mSectionLength) << "\n";
    stream << space(level) << "- numberOfSection                 = " << toString(mNumberOfSection) << "\n";
    stream << space(level) << "- NV                              = " << toString(getNV()) << "\n";
    stream << space(level) << "- productDefinitionTemplateNumber = " << toString(getProductDefinitionTemplateNumber()) << "\n";
    stream << space(level) << "- productDefinitionString         = " <<  getProductDefinitionString() << "\n";

    // Dump the product details: code table 4.0

    if (mProductDefinition)
      mProductDefinition->print(stream,level+1,optionFlags);

  }
  catch (...)
  {
    throw Fmi::Exception(BCP,"Operation failed!",nullptr);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
