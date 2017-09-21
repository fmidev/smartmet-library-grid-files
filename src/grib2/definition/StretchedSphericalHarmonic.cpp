// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedSphericalHarmonicImpl.*' files.
// ***********************************************************************

#include "grib2/definition/StretchedSphericalHarmonic.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

StretchedSphericalHarmonic::StretchedSphericalHarmonic() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

StretchedSphericalHarmonic::~StretchedSphericalHarmonic() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void StretchedSphericalHarmonic::read(MemoryReader &memoryReader) {
  try {
    mSphericalHarmonic.read(memoryReader);
    mStretching.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void StretchedSphericalHarmonic::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sStretchedSphericalHarmonic.", prefix.c_str());
    mSphericalHarmonic.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedSphericalHarmonic.", prefix.c_str());
    mStretching.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void StretchedSphericalHarmonic::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "StretchedSphericalHarmonic\n";
    mSphericalHarmonic.print(stream, level + 1, optionFlags);
    mStretching.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash StretchedSphericalHarmonic::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mSphericalHarmonic.countHash());
    boost::hash_combine(seed, mStretching.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mSphericalHarmonic} attribute. */

const SphericalHarmonicSettings *StretchedSphericalHarmonic::getSphericalHarmonic() const {
  try {
    return &mSphericalHarmonic;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mStretching} attribute. */

const StretchingSettings *StretchedSphericalHarmonic::getStretching() const {
  try {
    return &mStretching;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setSphericalHarmonic(SphericalHarmonicSettings sphericalHarmonic) {
  try {
    mSphericalHarmonic = sphericalHarmonic;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setStretching(StretchingSettings stretching) {
  try {
    mStretching = stretching;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
