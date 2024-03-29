// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotatedSphericalHarmonicImpl.*' files.
// ***********************************************************************

#include "RotatedSphericalHarmonic.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

RotatedSphericalHarmonic::RotatedSphericalHarmonic() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

RotatedSphericalHarmonic::~RotatedSphericalHarmonic() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void RotatedSphericalHarmonic::read(MemoryReader &memoryReader) {
  try {
    mSphericalHarmonic.read(memoryReader);
    mRotation.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void RotatedSphericalHarmonic::write(DataWriter &dataWriter) {
  try {
    mSphericalHarmonic.write(dataWriter);
    mRotation.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void RotatedSphericalHarmonic::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sRotatedSphericalHarmonic.", prefix.c_str());
    mSphericalHarmonic.getAttributeList(name, attributeList);
    sprintf(name, "%sRotatedSphericalHarmonic.", prefix.c_str());
    mRotation.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool RotatedSphericalHarmonic::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mSphericalHarmonic.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mRotation.getAttributeValue(attributeName, attributeValue))
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

bool RotatedSphericalHarmonic::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mSphericalHarmonic.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mRotation.hasAttributeValue(attributeName, attributeValue))
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

void RotatedSphericalHarmonic::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "RotatedSphericalHarmonic\n";
    mSphericalHarmonic.print(stream, level + 1, optionFlags);
    mRotation.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash RotatedSphericalHarmonic::countHash() const {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint RotatedSphericalHarmonic::getTemplateNumber() const {
  return 51;
}

GridDefinition *RotatedSphericalHarmonic::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new RotatedSphericalHarmonic(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mSphericalHarmonic} attribute. */

SphericalHarmonicSettings *RotatedSphericalHarmonic::getSphericalHarmonic() const {
  try {
    return static_cast<SphericalHarmonicSettings *>(&mSphericalHarmonic);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mRotation} attribute. */

RotationSettings *RotatedSphericalHarmonic::getRotation() const {
  try {
    return static_cast<RotationSettings *>(&mRotation);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedSphericalHarmonic::setSphericalHarmonic(SphericalHarmonicSettings &sphericalHarmonic) {
  try {
    mSphericalHarmonic = sphericalHarmonic;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedSphericalHarmonic::setRotation(RotationSettings &rotation) {
  try {
    mRotation = rotation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
