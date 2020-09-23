// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'FloatingPointGridDataRepresentationImpl.*' files.
// ***********************************************************************

#include "FloatingPointGridDataRepresentation.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

FloatingPointGridDataRepresentation::FloatingPointGridDataRepresentation() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

FloatingPointGridDataRepresentation::FloatingPointGridDataRepresentation(const FloatingPointGridDataRepresentation &other) : RepresentationDefinition(other) {
  try {
    mPrecision = other.mPrecision;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

FloatingPointGridDataRepresentation::~FloatingPointGridDataRepresentation() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void FloatingPointGridDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPrecision = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void FloatingPointGridDataRepresentation::write(DataWriter &dataWriter) {
  try {
    dataWriter << mPrecision;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void FloatingPointGridDataRepresentation::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sFloatingPointGridDataRepresentation.Precision", prefix.c_str());
    attributeList.addAttribute(name, toString(mPrecision));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void FloatingPointGridDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "FloatingPointGridDataRepresentation\n";
    stream << space(level) << "- Precision = " << toString(mPrecision) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash FloatingPointGridDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    if (mPrecision)
      boost::hash_combine(seed, *mPrecision);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint FloatingPointGridDataRepresentation::getTemplateNumber() const {
  return 4;
}

RepresentationDefinition *FloatingPointGridDataRepresentation::createRepresentationDefinition() const {
  try {
    return static_cast<RepresentationDefinition *>(new FloatingPointGridDataRepresentation(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPrecision} attribute. */

const T::UInt8_opt &FloatingPointGridDataRepresentation::getPrecision() const {
  try {
    return mPrecision;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void FloatingPointGridDataRepresentation::setPrecision(T::UInt8_opt precision) {
  try {
    mPrecision = precision;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
