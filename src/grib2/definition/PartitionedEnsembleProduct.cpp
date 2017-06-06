// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PartitionedEnsembleProductImpl.*' files.
// ***********************************************************************

#include "grib2/definition/PartitionedEnsembleProduct.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PartitionedEnsembleProduct::PartitionedEnsembleProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

PartitionedEnsembleProduct::~PartitionedEnsembleProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current
   object.

        \param memoryReader  This object controls the access to the memory
   mapped file.
*/

void PartitionedEnsembleProduct::read(MemoryReader &memoryReader) {
  try {
    mPartitionedProduct.read(memoryReader);
    mEps.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void PartitionedEnsembleProduct::getAttributeList(
    std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sPartitionedEnsembleProduct.", prefix.c_str());
    mPartitionedProduct.getAttributeList(name, attributeList);
    sprintf(name, "%sPartitionedEnsembleProduct.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given
   stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level
   structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void PartitionedEnsembleProduct::print(std::ostream &stream, uint level,
                                       uint optionFlags) const {
  try {
    stream << space(level) << "PartitionedEnsembleProduct\n";
    mPartitionedProduct.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash PartitionedEnsembleProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mPartitionedProduct.countHash());
    boost::hash_combine(seed, mEps.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPartitionedProduct}
 * attribute. */

const PartitionedProduct *
PartitionedEnsembleProduct::getPartitionedProduct() const {
  try {
    return &mPartitionedProduct;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

const EpsSettings *PartitionedEnsembleProduct::getEps() const {
  try {
    return &mEps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet