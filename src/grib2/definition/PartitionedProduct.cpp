// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PartitionedProductImpl.*' files.
// ***********************************************************************

#include "grib2/definition/PartitionedProduct.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PartitionedProduct::PartitionedProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

PartitionedProduct::~PartitionedProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PartitionedProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterPartition.read(memoryReader);
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void PartitionedProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sPartitionedProduct.", prefix.c_str());
    mParameterPartition.getAttributeList(name, attributeList);
    sprintf(name, "%sPartitionedProduct.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sPartitionedProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void PartitionedProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "PartitionedProduct\n";
    mParameterPartition.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash PartitionedProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameterPartition.countHash());
    boost::hash_combine(seed, mPointInTime.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameterPartition} attribute. */

const ParameterPartitionSettings *PartitionedProduct::getParameterPartition() const {
  try {
    return &mParameterPartition;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

const PointInTimeSettings *PartitionedProduct::getPointInTime() const {
  try {
    return &mPointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

const HorizontalSettings *PartitionedProduct::getHorizontal() const {
  try {
    return &mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void PartitionedProduct::setParameterPartition(ParameterPartitionSettings parameterPartition) {
  try {
    mParameterPartition = parameterPartition;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void PartitionedProduct::setPointInTime(PointInTimeSettings pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void PartitionedProduct::setHorizontal(HorizontalSettings horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
