// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AtmosphericChemicalProductImpl.*' files.
// ***********************************************************************

#include "AtmosphericChemicalProduct.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AtmosphericChemicalProduct::AtmosphericChemicalProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

AtmosphericChemicalProduct::AtmosphericChemicalProduct(const AtmosphericChemicalProduct &other) : ProductDefinition(other) {
  try {
    mParameterChemical = other.mParameterChemical;
    mPointInTime = other.mPointInTime;
    mHorizontal = other.mHorizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

AtmosphericChemicalProduct::~AtmosphericChemicalProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void AtmosphericChemicalProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterChemical.read(memoryReader);
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void AtmosphericChemicalProduct::write(DataWriter &dataWriter) {
  try {
    mParameterChemical.write(dataWriter);
    mPointInTime.write(dataWriter);
    mHorizontal.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void AtmosphericChemicalProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAtmosphericChemicalProduct.", prefix.c_str());
    mParameterChemical.getAttributeList(name, attributeList);
    sprintf(name, "%sAtmosphericChemicalProduct.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sAtmosphericChemicalProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void AtmosphericChemicalProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "AtmosphericChemicalProduct\n";
    mParameterChemical.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash AtmosphericChemicalProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameterChemical.countHash());
    boost::hash_combine(seed, mPointInTime.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint AtmosphericChemicalProduct::getTemplateNumber() const {
  return 40;
}

ProductDefinition *AtmosphericChemicalProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new AtmosphericChemicalProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameterChemical} attribute. */

ParameterChemicalSettings *AtmosphericChemicalProduct::getParameterChemical() const {
  try {
    return static_cast<ParameterChemicalSettings *>(&mParameterChemical);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *AtmosphericChemicalProduct::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *AtmosphericChemicalProduct::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void AtmosphericChemicalProduct::setParameterChemical(ParameterChemicalSettings &parameterChemical) {
  try {
    mParameterChemical = parameterChemical;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void AtmosphericChemicalProduct::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void AtmosphericChemicalProduct::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
