// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GridDataRepresentationImpl.*' files.
// ***********************************************************************

#include "GridDataRepresentation.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

GridDataRepresentation::GridDataRepresentation() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

GridDataRepresentation::~GridDataRepresentation() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mOriginalValues.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void GridDataRepresentation::write(DataWriter &dataWriter) {
  try {
    mPacking.write(dataWriter);
    mOriginalValues.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void GridDataRepresentation::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sGridDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sGridDataRepresentation.", prefix.c_str());
    mOriginalValues.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint GridDataRepresentation::getTemplateNumber() const {
  return 0;
}

RepresentationDefinition *GridDataRepresentation::createRepresentationDefinition() const {
  try {
    return static_cast<RepresentationDefinition *>(new GridDataRepresentation(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

PackingSettings *GridDataRepresentation::getPacking() const {
  try {
    return static_cast<PackingSettings *>(&mPacking);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mOriginalValues} attribute. */

OriginalValuesSettings *GridDataRepresentation::getOriginalValues() const {
  try {
    return static_cast<OriginalValuesSettings *>(&mOriginalValues);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridDataRepresentation::setPacking(PackingSettings &packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridDataRepresentation::setOriginalValues(OriginalValuesSettings &originalValues) {
  try {
    mOriginalValues = originalValues;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
