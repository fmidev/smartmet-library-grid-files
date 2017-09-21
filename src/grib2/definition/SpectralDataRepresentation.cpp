// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SpectralDataRepresentationImpl.*' files.
// ***********************************************************************

#include "grib2/definition/SpectralDataRepresentation.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SpectralDataRepresentation::SpectralDataRepresentation() {
  try {
    mRealPartOf00 = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

SpectralDataRepresentation::~SpectralDataRepresentation() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SpectralDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mRealPartOf00 = memoryReader.read_float();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SpectralDataRepresentation::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSpectralDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sSpectralDataRepresentation.RealPartOf00", prefix.c_str());
    attributeList.addAttribute(name, toString(mRealPartOf00));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SpectralDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SpectralDataRepresentation\n";
    mPacking.print(stream, level + 1, optionFlags);
    stream << space(level) << "- RealPartOf00 = " << toString(mRealPartOf00) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SpectralDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mRealPartOf00);
    boost::hash_combine(seed, mPacking.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

const PackingSettings *SpectralDataRepresentation::getPacking() const {
  try {
    return &mPacking;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mRealPartOf00} attribute. */

float SpectralDataRepresentation::getRealPartOf00() const {
  try {
    return mRealPartOf00;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpectralDataRepresentation::setPacking(PackingSettings packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpectralDataRepresentation::setRealPartOf00(float realPartOf00) {
  try {
    mRealPartOf00 = realPartOf00;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
