// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'JpegGridDataRepresentationImpl.*' files.
// ***********************************************************************

#include "grib2/definition/JpegGridDataRepresentation.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

JpegGridDataRepresentation::JpegGridDataRepresentation() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

JpegGridDataRepresentation::~JpegGridDataRepresentation() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void JpegGridDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mOriginalValues.read(memoryReader);
    mTypeOfCompressionUsed = memoryReader.read_UInt8_opt();
    mTargetCompressionRatio = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void JpegGridDataRepresentation::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sJpegGridDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sJpegGridDataRepresentation.", prefix.c_str());
    mOriginalValues.getAttributeList(name, attributeList);
    sprintf(name, "%sJpegGridDataRepresentation.TypeOfCompressionUsed", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfCompressionUsed));
    sprintf(name, "%sJpegGridDataRepresentation.TargetCompressionRatio", prefix.c_str());
    attributeList.addAttribute(name, toString(mTargetCompressionRatio));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void JpegGridDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "JpegGridDataRepresentation\n";
    mPacking.print(stream, level + 1, optionFlags);
    mOriginalValues.print(stream, level + 1, optionFlags);
    stream << space(level) << "- TypeOfCompressionUsed = " << toString(mTypeOfCompressionUsed) << "\n";
    stream << space(level) << "- TargetCompressionRatio = " << toString(mTargetCompressionRatio) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash JpegGridDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    if (mTypeOfCompressionUsed)
      boost::hash_combine(seed, *mTypeOfCompressionUsed);
    if (mTargetCompressionRatio)
      boost::hash_combine(seed, *mTargetCompressionRatio);
    boost::hash_combine(seed, mPacking.countHash());
    boost::hash_combine(seed, mOriginalValues.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

const PackingSettings *JpegGridDataRepresentation::getPacking() const {
  try {
    return &mPacking;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mOriginalValues} attribute. */

const OriginalValuesSettings *JpegGridDataRepresentation::getOriginalValues() const {
  try {
    return &mOriginalValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfCompressionUsed} attribute. */

const T::UInt8_opt &JpegGridDataRepresentation::getTypeOfCompressionUsed() const {
  try {
    return mTypeOfCompressionUsed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTargetCompressionRatio} attribute. */

const T::UInt8_opt &JpegGridDataRepresentation::getTargetCompressionRatio() const {
  try {
    return mTargetCompressionRatio;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void JpegGridDataRepresentation::setPacking(PackingSettings packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void JpegGridDataRepresentation::setOriginalValues(OriginalValuesSettings originalValues) {
  try {
    mOriginalValues = originalValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void JpegGridDataRepresentation::setTypeOfCompressionUsed(T::UInt8_opt typeOfCompressionUsed) {
  try {
    mTypeOfCompressionUsed = typeOfCompressionUsed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void JpegGridDataRepresentation::setTargetCompressionRatio(T::UInt8_opt targetCompressionRatio) {
  try {
    mTargetCompressionRatio = targetCompressionRatio;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
