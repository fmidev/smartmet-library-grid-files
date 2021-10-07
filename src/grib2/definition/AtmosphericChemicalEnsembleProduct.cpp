// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AtmosphericChemicalEnsembleProductImpl.*' files.
// ***********************************************************************

#include "AtmosphericChemicalEnsembleProduct.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AtmosphericChemicalEnsembleProduct::AtmosphericChemicalEnsembleProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

AtmosphericChemicalEnsembleProduct::~AtmosphericChemicalEnsembleProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void AtmosphericChemicalEnsembleProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterChemical.read(memoryReader);
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
    mEps.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void AtmosphericChemicalEnsembleProduct::write(DataWriter &dataWriter) {
  try {
    mParameterChemical.write(dataWriter);
    mPointInTime.write(dataWriter);
    mHorizontal.write(dataWriter);
    mEps.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void AtmosphericChemicalEnsembleProduct::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAtmosphericChemicalEnsembleProduct.", prefix.c_str());
    mParameterChemical.getAttributeList(name, attributeList);
    sprintf(name, "%sAtmosphericChemicalEnsembleProduct.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sAtmosphericChemicalEnsembleProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sAtmosphericChemicalEnsembleProduct.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool AtmosphericChemicalEnsembleProduct::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mParameterChemical.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mPointInTime.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mHorizontal.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mEps.getAttributeValue(attributeName, attributeValue))
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool AtmosphericChemicalEnsembleProduct::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mParameterChemical.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mPointInTime.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mHorizontal.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mEps.hasAttributeValue(attributeName, attributeValue))
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void AtmosphericChemicalEnsembleProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "AtmosphericChemicalEnsembleProduct\n";
    mParameterChemical.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash AtmosphericChemicalEnsembleProduct::countHash() const {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint AtmosphericChemicalEnsembleProduct::getTemplateNumber() const {
  return 41;
}

ProductDefinition *AtmosphericChemicalEnsembleProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new AtmosphericChemicalEnsembleProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameterChemical} attribute. */

ParameterChemicalSettings *AtmosphericChemicalEnsembleProduct::getParameterChemical() const {
  try {
    return static_cast<ParameterChemicalSettings *>(&mParameterChemical);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *AtmosphericChemicalEnsembleProduct::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *AtmosphericChemicalEnsembleProduct::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

EpsSettings *AtmosphericChemicalEnsembleProduct::getEps() const {
  try {
    return static_cast<EpsSettings *>(&mEps);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AtmosphericChemicalEnsembleProduct::setParameterChemical(ParameterChemicalSettings &parameterChemical) {
  try {
    mParameterChemical = parameterChemical;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AtmosphericChemicalEnsembleProduct::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AtmosphericChemicalEnsembleProduct::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AtmosphericChemicalEnsembleProduct::setEps(EpsSettings &eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
