// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GridDataRepresentationImpl.*' files.
// ***********************************************************************

#include "grib2/definition/GridDataRepresentation.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

GridDataRepresentation::GridDataRepresentation() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

GridDataRepresentation::~GridDataRepresentation() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mOriginalValues.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void GridDataRepresentation::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sGridDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sGridDataRepresentation.", prefix.c_str());
    mOriginalValues.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void GridDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "GridDataRepresentation\n";
    mPacking.print(stream, level + 1, optionFlags);
    mOriginalValues.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash GridDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mPacking.countHash());
    boost::hash_combine(seed, mOriginalValues.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

const PackingSettings *GridDataRepresentation::getPacking() const {
  try {
    return &mPacking;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mOriginalValues} attribute. */

const OriginalValuesSettings *GridDataRepresentation::getOriginalValues() const {
  try {
    return &mOriginalValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void GridDataRepresentation::setPacking(PackingSettings packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void GridDataRepresentation::setOriginalValues(OriginalValuesSettings originalValues) {
  try {
    mOriginalValues = originalValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
