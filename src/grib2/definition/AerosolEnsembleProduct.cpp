// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AerosolEnsembleProductImpl.*' files.
// ***********************************************************************

#include "AerosolEnsembleProduct.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AerosolEnsembleProduct::AerosolEnsembleProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

AerosolEnsembleProduct::~AerosolEnsembleProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void AerosolEnsembleProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterAerosol.read(memoryReader);
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

void AerosolEnsembleProduct::write(DataWriter &dataWriter) {
  try {
    mParameterAerosol.write(dataWriter);
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

void AerosolEnsembleProduct::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAerosolEnsembleProduct.", prefix.c_str());
    mParameterAerosol.getAttributeList(name, attributeList);
    sprintf(name, "%sAerosolEnsembleProduct.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sAerosolEnsembleProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sAerosolEnsembleProduct.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool AerosolEnsembleProduct::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mParameterAerosol.getAttributeValue(attributeName, attributeValue))
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

bool AerosolEnsembleProduct::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mParameterAerosol.hasAttributeValue(attributeName, attributeValue))
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

void AerosolEnsembleProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "AerosolEnsembleProduct\n";
    mParameterAerosol.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash AerosolEnsembleProduct::countHash() {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint AerosolEnsembleProduct::getTemplateNumber() const {
  return 45;
}

ProductDefinition *AerosolEnsembleProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new AerosolEnsembleProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameterAerosol} attribute. */

ParameterAerosolSettings *AerosolEnsembleProduct::getParameterAerosol() const {
  try {
    return static_cast<ParameterAerosolSettings *>(&mParameterAerosol);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *AerosolEnsembleProduct::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *AerosolEnsembleProduct::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

EpsSettings *AerosolEnsembleProduct::getEps() const {
  try {
    return static_cast<EpsSettings *>(&mEps);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AerosolEnsembleProduct::setParameterAerosol(ParameterAerosolSettings &parameterAerosol) {
  try {
    mParameterAerosol = parameterAerosol;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AerosolEnsembleProduct::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AerosolEnsembleProduct::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AerosolEnsembleProduct::setEps(EpsSettings &eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
