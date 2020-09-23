// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PartitionedProductImpl.*' files.
// ***********************************************************************

#include "PartitionedProduct.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PartitionedProduct::PartitionedProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

PartitionedProduct::PartitionedProduct(const PartitionedProduct &other) : ProductDefinition(other) {
  try {
    mParameterPartition = other.mParameterPartition;
    mPointInTime = other.mPointInTime;
    mHorizontal = other.mHorizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

PartitionedProduct::~PartitionedProduct() {
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void PartitionedProduct::write(DataWriter &dataWriter) {
  try {
    mParameterPartition.write(dataWriter);
    mPointInTime.write(dataWriter);
    mHorizontal.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint PartitionedProduct::getTemplateNumber() const {
  return 53;
}

ProductDefinition *PartitionedProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new PartitionedProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameterPartition} attribute. */

ParameterPartitionSettings *PartitionedProduct::getParameterPartition() const {
  try {
    return static_cast<ParameterPartitionSettings *>(&mParameterPartition);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *PartitionedProduct::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *PartitionedProduct::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void PartitionedProduct::setParameterPartition(ParameterPartitionSettings &parameterPartition) {
  try {
    mParameterPartition = parameterPartition;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void PartitionedProduct::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void PartitionedProduct::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
