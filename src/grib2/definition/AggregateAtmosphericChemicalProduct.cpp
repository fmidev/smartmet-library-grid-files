// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AggregateAtmosphericChemicalProductImpl.*' files.
// ***********************************************************************

#include "AggregateAtmosphericChemicalProduct.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AggregateAtmosphericChemicalProduct::AggregateAtmosphericChemicalProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

AggregateAtmosphericChemicalProduct::~AggregateAtmosphericChemicalProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void AggregateAtmosphericChemicalProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterChemical.read(memoryReader);
    mHorizontal.read(memoryReader);
    mStatistical.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void AggregateAtmosphericChemicalProduct::write(DataWriter &dataWriter) {
  try {
    mParameterChemical.write(dataWriter);
    mHorizontal.write(dataWriter);
    mStatistical.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void AggregateAtmosphericChemicalProduct::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAggregateAtmosphericChemicalProduct.", prefix.c_str());
    mParameterChemical.getAttributeList(name, attributeList);
    sprintf(name, "%sAggregateAtmosphericChemicalProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sAggregateAtmosphericChemicalProduct.", prefix.c_str());
    mStatistical.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void AggregateAtmosphericChemicalProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "AggregateAtmosphericChemicalProduct\n";
    mParameterChemical.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash AggregateAtmosphericChemicalProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameterChemical.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mStatistical.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint AggregateAtmosphericChemicalProduct::getTemplateNumber() const {
  return 42;
}

ProductDefinition *AggregateAtmosphericChemicalProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new AggregateAtmosphericChemicalProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameterChemical} attribute. */

ParameterChemicalSettings *AggregateAtmosphericChemicalProduct::getParameterChemical() const {
  try {
    return static_cast<ParameterChemicalSettings *>(&mParameterChemical);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *AggregateAtmosphericChemicalProduct::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

StatisticalSettings *AggregateAtmosphericChemicalProduct::getStatistical() const {
  try {
    return static_cast<StatisticalSettings *>(&mStatistical);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AggregateAtmosphericChemicalProduct::setParameterChemical(ParameterChemicalSettings &parameterChemical) {
  try {
    mParameterChemical = parameterChemical;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AggregateAtmosphericChemicalProduct::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AggregateAtmosphericChemicalProduct::setStatistical(StatisticalSettings &statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
