#include "grib2/ProductSection.h"
#include "identification/GribDef.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "Message.h"

#include "grib2/implementation/NormalProductImpl.h"                                   // 4.0
#include "grib2/implementation/EnsembleForecastImpl.h"                                // 4.1
#include "grib2/implementation/EnsembleDerivedForecastImpl.h"                         // 4.2
#include "grib2/implementation/EnsembleClusterDerivedForecastImpl.h"                  // 4.3
#include "grib2/implementation/ProbabilityForecastImpl.h"                             // 4.5
#include "grib2/implementation/PercentileForecastImpl.h"                              // 4.6
#include "grib2/implementation/ForecastErrorImpl.h"                                   // 4.7
#include "grib2/implementation/AggregateForecastImpl.h"                               // 4.8
#include "grib2/implementation/TimeIntervalProbabilityForecastImpl.h"                 // 4.9
#include "grib2/implementation/TimeIntervalPercentileForecastImpl.h"                  // 4.10
#include "grib2/implementation/TimeIntervalEnsembleForecastImpl.h"                    // 4.11
#include "grib2/implementation/TimeIntervalEnsembleDerivedForecastImpl.h"             // 4.12
#include "grib2/implementation/TimeIntervalEnsembleClusterDerivedForecastImpl.h"      // 4.13
#include "grib2/implementation/TimeIntervalAggregateForecastImpl.h"                   // 4.15
#include "grib2/implementation/DeprecatedSatelliteProductImpl.h"                      // 4.30
#include "grib2/implementation/SatelliteProductImpl.h"                                // 4.31
#include "grib2/implementation/SimulatedSatelliteProductImpl.h"                       // 4.32
#include "grib2/implementation/SimulatedSatelliteEnsembleProductImpl.h"               // 4.33
#include "grib2/implementation/TimeIntervalSimulatedSatelliteEnsembleProductImpl.h"   // 4.34
#include "grib2/implementation/AtmosphericChemicalProductImpl.h"                      // 4.40
#include "grib2/implementation/AtmosphericChemicalEnsembleProductImpl.h"              // 4.41
#include "grib2/implementation/AggregateAtmosphericChemicalProductImpl.h"             // 4.42
#include "grib2/implementation/TimeIntervalAtmosphericChemicalEnsembleProductImpl.h"  // 4.43
#include "grib2/implementation/AerosolEnsembleProductImpl.h"                          // 4.45
#include "grib2/implementation/AggregateAerosolProductImpl.h"                         // 4.46
#include "grib2/implementation/TimeIntervalAerosolEnsembleProductImpl.h"              // 4.47
#include "grib2/implementation/AerosolOpticalPropertiesProductImpl.h"                 // 4.48
#include "grib2/implementation/CategoricalForecastImpl.h"                             // 4.51
#include "grib2/implementation/PartitionedProductImpl.h"                              // 4.53
#include "grib2/implementation/PartitionedEnsembleProductImpl.h"                      // 4.54
#include "grib2/implementation/EnsembleReforecastImpl.h"                              // 4.60
#include "grib2/implementation/TimeIntervalEnsembleReforecastImpl.h"                  // 4.61
#include "grib2/implementation/TimeIntervalCategoricalForecastImpl.h"                 // 4.91
#include "grib2/implementation/CharacterStringProductImpl.h"                          // 4.254
#include "grib2/implementation/AuxiliarySatelliteProductImpl.h"                       // 4.311
#include "grib2/implementation/CrossSectionProductImpl.h"                             // 4.1000
#include "grib2/implementation/ProcessedCrossSectionProductImpl.h"                    // 4.1001
#include "grib2/implementation/AreaProcessedCrossSectionProductImpl.h"                // 4.1002
#include "grib2/implementation/HovmollerProductImpl.h"                                // 4.1100
#include "grib2/implementation/ProcessedHovmollerProductImpl.h"                       // 4.1101

#include <iostream>

namespace SmartMet
{
namespace GRIB2
{


/*! \brief The constructor of the class.

        \param message  A pointer to the message object.
*/

ProductSection::ProductSection(Message *message)
{
  try
  {
    mMessage = message;
    mFilePosition = 0;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Constructor failed failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
      SmartMet::Spine::Exception exception(BCP,"Section 4 length cannot be missing!");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-4));
      throw exception;
    }

    memoryReader >> mNumberOfSection;

    memoryReader >> mNV;
/*
    if (!missing(mNV) && *mNV != 0)
    {
      SmartMet::Spine::Exception exception(BCP,"ProductSection does not support optional coordinates yet");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-2));
      throw exception;
    }
*/
    memoryReader >> mProductDefinitionTemplateNumber;
    if (missing(mProductDefinitionTemplateNumber))
    {
      SmartMet::Spine::Exception exception(BCP,"Product definition template number cannot be missing");
      exception.addParameter("Read position",uint64_toHex(memoryReader.getGlobalReadPosition()-2));
      throw exception;
    }

    auto productDefinition = createProductDefinition(mProductDefinitionTemplateNumber);
    mProductDefinition.reset(productDefinition);
    productDefinition->read(memoryReader);

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
    throw SmartMet::Spine::Exception(BCP,"Operation failed failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the length of the section (in the grib file).

         \return  The length of the section expressed in bytes.
*/

std::uint32_t ProductSection::getSectionLength() const
{
  try
  {
    return *mSectionLength;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the section number that was read from the grib file. */

std::uint8_t ProductSection::getNumberOfSection() const
{
  try
  {
    // No missing check necessary here, we cannot know the section type without the number
    // anyway
    return *mNumberOfSection;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::string ProductSection::getProductDefinitionString() const
{
  try
  {
    std::uint8_t tablesVersion = mMessage->getTablesVersion();
    return Identification::gribDef.getTableValue(2,tablesVersion,"4.0", getProductDefinitionTemplateNumber());
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





std::uint16_t ProductSection::getProductDefinitionTemplateNumber() const
{
  try
  {
    return *mProductDefinitionTemplateNumber;
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}





/*! \brief The method returns the time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString ProductSection::getForecastStartTime(T::TimeString referenceTime) const
{
  try
  {
    if (mProductDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductDefinition' attribute points to NULL!");

    return mProductDefinition->getForecastStartTime(referenceTime);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Operation failed!",NULL);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}




/*! \brief The method returns the time of the current forecast data. In some cases
    the reference time is needed for calculating the actual forecast time.

        \param referenceTime  The possible reference time.
        \return               The forecast time.
*/

T::TimeString ProductSection::getForecastEndTime(T::TimeString referenceTime) const
{
  try
  {
    if (mProductDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductDefinition' attribute points to NULL!");

    return mProductDefinition->getForecastEndTime(referenceTime);
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Operation failed!",NULL);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}




const T::UInt8_opt ProductSection::getGribParameterCategory() const
{
  try
  {
    if (mProductDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductDefinition' attribute points to NULL!");

    return mProductDefinition->getGribParameterCategory();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Operation failed!",NULL);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}




const T::UInt8_opt ProductSection::getGribParameterNumber() const
{
  try
  {
    if (mProductDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductDefinition' attribute points to NULL!");

    return mProductDefinition->getGribParameterNumber();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Operation failed!",NULL);
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
    if (mProductDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductDefinition' attribute points to NULL!");

    return mProductDefinition->getGribParameterLevelId();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Operation failed!",NULL);
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
    if (mProductDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductDefinition' attribute points to NULL!");

    return mProductDefinition->getGribParameterLevel();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Operation failed!",NULL);
    exception.addParameter("ProductDefinitionTemplateNumber",toString(getProductDefinitionTemplateNumber()));
    throw exception;
  }
}





ProductDefinition* ProductSection::createProductDefinition(T::UInt16_opt number)
{
  try
  {
    // Unknown product?
    if (missing(number))
      return nullptr;

    switch (*number)
    {
      case 0:
        return new NormalProductImpl();
      case 1:
        return new EnsembleForecastImpl();
      case 2:
        return new EnsembleDerivedForecastImpl();
      case 3:
        return new EnsembleClusterDerivedForecastImpl();
      case 5:
        return new ProbabilityForecastImpl();
      case 6:
        return new PercentileForecastImpl();
      case 7:
        return new ForecastErrorImpl();
      case 8:
        return new AggregateForecastImpl();
      case 9:
        return new TimeIntervalProbabilityForecastImpl();
      case 10:
        return new TimeIntervalPercentileForecastImpl();
      case 11:
        return new TimeIntervalEnsembleForecastImpl();
      case 12:
        return new TimeIntervalEnsembleDerivedForecastImpl();
      case 13:
        return new TimeIntervalEnsembleClusterDerivedForecastImpl();
      case 15:
        return new TimeIntervalAggregateForecastImpl();
      case 30:
        return new DeprecatedSatelliteProductImpl();
      case 31:
        return new SatelliteProductImpl();
      case 32:
        return new SimulatedSatelliteProductImpl();
      case 33:
        return new SimulatedSatelliteEnsembleProductImpl();
      case 34:
        return new TimeIntervalSimulatedSatelliteEnsembleProductImpl();
      case 40:
        return new AtmosphericChemicalProductImpl();
      case 41:
        return new AtmosphericChemicalEnsembleProductImpl();
      case 42:
        return new AggregateAtmosphericChemicalProductImpl();
      case 43:
        return new TimeIntervalAtmosphericChemicalEnsembleProductImpl();
      case 45:
        return new AerosolEnsembleProductImpl();
      case 46:
        return new AggregateAerosolProductImpl();
      case 47:
        return new TimeIntervalAerosolEnsembleProductImpl();
      case 48:
        return new AerosolOpticalPropertiesProductImpl();
      case 51:
        return new CategoricalForecastImpl();
      case 53:
        return new PartitionedProductImpl();
      case 54:
        return new PartitionedEnsembleProductImpl();
      case 60:
        return new EnsembleReforecastImpl();
      case 61:
        return new TimeIntervalEnsembleReforecastImpl();
      case 91:
        return new TimeIntervalCategoricalForecastImpl();
      case 254:
        return new CharacterStringProductImpl();
      case 311:
        return new AuxiliarySatelliteProductImpl();
      case 1000:
        return new CrossSectionProductImpl();
      case 1001:
        return new ProcessedCrossSectionProductImpl();
      case 1002:
        return new AreaProcessedCrossSectionProductImpl();
      case 1100:
        return new HovmollerProductImpl();
      case 1101:
        return new ProcessedHovmollerProductImpl();
      case 4:
        throw SmartMet::Spine::Exception(BCP,
            "Product 4.4 EnsembleClusterDerivedCircleForecast not supported due to a bugged "
            "4.circular_cluster template!");
      case 14:
        throw SmartMet::Spine::Exception(BCP,
            "Product 4.14 TimeIntervalEnsembleClusterDerivedCircleForecast not supported due to a "
            "bugged 4.circular_cluster template!");
      case 44:
        throw SmartMet::Spine::Exception(BCP,
            "Product 4.44 AerosolProduct not supported due to a bugged 4.parameter_aerosol_44 "
            "template!");
      case 2000:
        throw SmartMet::Spine::Exception(BCP,
            "Product 4.2000 not supported TODO due to God knows what - I forgot!");
      case 40033:
        throw SmartMet::Spine::Exception(BCP,"Product 4.40033 not supported, use 4.33 instead!");
      case 40034:
        throw SmartMet::Spine::Exception(BCP,"Product 4.40034 not supported, use 4.34 instead!");
      default:
        throw SmartMet::Spine::Exception(BCP,"Unknown product definition template number '" +
                                 std::to_string(static_cast<int>(*number)) + "'!");
    }
  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Creation of a product definition failed!",NULL);
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
    throw SmartMet::Spine::Exception(BCP,"Creation of a product definition failed!",NULL);
  }
}




T::UInt8_opt ProductSection::getGeneratingProcessIdentifier() const
{
  try
  {
    if (mProductDefinition == NULL)
      throw SmartMet::Spine::Exception(BCP,"The 'mProductDefinition' attribute points to NULL!");

    return mProductDefinition->getGeneratingProcessIdentifier();
  }
  catch (...)
  {
    SmartMet::Spine::Exception exception(BCP,"Operation failed!",NULL);
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
    stream << space(level) << "- NV                              = " << getNV() << "\n";
    stream << space(level) << "- productDefinitionTemplateNumber = " << toString(getProductDefinitionTemplateNumber()) << "\n";
    stream << space(level) << "- productDefinitionString         = " <<  getProductDefinitionString() << "\n";

    // Dump the product details: code table 4.0

    if (mProductDefinition)
      mProductDefinition->print(stream,level+1,optionFlags);

  }
  catch (...)
  {
    throw SmartMet::Spine::Exception(BCP,"Operation failed!",NULL);
  }
}

}  // namespace GRIB2
}  // namespace SmartMet
