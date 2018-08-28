// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SphericalHarmonicImpl.*' files.
// ***********************************************************************

#include "SphericalHarmonic.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SphericalHarmonic::SphericalHarmonic() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

SphericalHarmonic::SphericalHarmonic(const SphericalHarmonic &other) : GridDefinition(other) {
  try {
    mSphericalHarmonic = other.mSphericalHarmonic;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

SphericalHarmonic::~SphericalHarmonic() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SphericalHarmonic::read(MemoryReader &memoryReader) {
  try {
    mSphericalHarmonic.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void SphericalHarmonic::write(DataWriter &dataWriter) {
  try {
    mSphericalHarmonic.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SphericalHarmonic::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSphericalHarmonic.", prefix.c_str());
    mSphericalHarmonic.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SphericalHarmonic::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SphericalHarmonic\n";
    mSphericalHarmonic.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SphericalHarmonic::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mSphericalHarmonic.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint SphericalHarmonic::getTemplateNumber() const {
  return 50;
}

GridDefinition *SphericalHarmonic::createGridDefinition() const {
  try {
    return (GridDefinition *)new SphericalHarmonic(*this);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mSphericalHarmonic} attribute. */

SphericalHarmonicSettings *SphericalHarmonic::getSphericalHarmonic() const {
  try {
    return (SphericalHarmonicSettings *)&mSphericalHarmonic;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SphericalHarmonic::setSphericalHarmonic(SphericalHarmonicSettings &sphericalHarmonic) {
  try {
    mSphericalHarmonic = sphericalHarmonic;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
