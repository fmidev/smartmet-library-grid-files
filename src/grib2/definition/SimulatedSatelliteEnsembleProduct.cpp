// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SimulatedSatelliteEnsembleProductImpl.*' files.
// ***********************************************************************

#include "SimulatedSatelliteEnsembleProduct.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SimulatedSatelliteEnsembleProduct::SimulatedSatelliteEnsembleProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

SimulatedSatelliteEnsembleProduct::~SimulatedSatelliteEnsembleProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SimulatedSatelliteEnsembleProduct::read(MemoryReader &memoryReader) {
  try {
    mSimulatedSatelliteProduct.read(memoryReader);
    mEps.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SimulatedSatelliteEnsembleProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSimulatedSatelliteEnsembleProduct.", prefix.c_str());
    mSimulatedSatelliteProduct.getAttributeList(name, attributeList);
    sprintf(name, "%sSimulatedSatelliteEnsembleProduct.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SimulatedSatelliteEnsembleProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SimulatedSatelliteEnsembleProduct\n";
    mSimulatedSatelliteProduct.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SimulatedSatelliteEnsembleProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mSimulatedSatelliteProduct.countHash());
    boost::hash_combine(seed, mEps.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mSimulatedSatelliteProduct} attribute. */

const SimulatedSatelliteProduct *SimulatedSatelliteEnsembleProduct::getSimulatedSatelliteProduct() const {
  try {
    return &mSimulatedSatelliteProduct;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

const EpsSettings *SimulatedSatelliteEnsembleProduct::getEps() const {
  try {
    return &mEps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SimulatedSatelliteEnsembleProduct::setSimulatedSatelliteProduct(SimulatedSatelliteProduct simulatedSatelliteProduct) {
  try {
    mSimulatedSatelliteProduct = simulatedSatelliteProduct;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SimulatedSatelliteEnsembleProduct::setEps(EpsSettings eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
