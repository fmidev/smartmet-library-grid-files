// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalSimulatedSatelliteEnsembleProductImpl.*' files.
// ***********************************************************************

#include "TimeIntervalSimulatedSatelliteEnsembleProduct.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeIntervalSimulatedSatelliteEnsembleProduct::TimeIntervalSimulatedSatelliteEnsembleProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

TimeIntervalSimulatedSatelliteEnsembleProduct::~TimeIntervalSimulatedSatelliteEnsembleProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void TimeIntervalSimulatedSatelliteEnsembleProduct::read(MemoryReader &memoryReader) {
  try {
    mSimulatedSatelliteProduct.read(memoryReader);
    mEps.read(memoryReader);
    mStatistical.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void TimeIntervalSimulatedSatelliteEnsembleProduct::write(DataWriter &dataWriter) {
  try {
    mSimulatedSatelliteProduct.write(dataWriter);
    mEps.write(dataWriter);
    mStatistical.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeIntervalSimulatedSatelliteEnsembleProduct::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTimeIntervalSimulatedSatelliteEnsembleProduct.", prefix.c_str());
    mSimulatedSatelliteProduct.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalSimulatedSatelliteEnsembleProduct.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalSimulatedSatelliteEnsembleProduct.", prefix.c_str());
    mStatistical.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void TimeIntervalSimulatedSatelliteEnsembleProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TimeIntervalSimulatedSatelliteEnsembleProduct\n";
    mSimulatedSatelliteProduct.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeIntervalSimulatedSatelliteEnsembleProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mSimulatedSatelliteProduct.countHash());
    boost::hash_combine(seed, mEps.countHash());
    boost::hash_combine(seed, mStatistical.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint TimeIntervalSimulatedSatelliteEnsembleProduct::getTemplateNumber() const {
  return 34;
}

ProductDefinition *TimeIntervalSimulatedSatelliteEnsembleProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new TimeIntervalSimulatedSatelliteEnsembleProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mSimulatedSatelliteProduct} attribute. */

SimulatedSatelliteProduct *TimeIntervalSimulatedSatelliteEnsembleProduct::getSimulatedSatelliteProduct() const {
  try {
    return static_cast<SimulatedSatelliteProduct *>(&mSimulatedSatelliteProduct);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

EpsSettings *TimeIntervalSimulatedSatelliteEnsembleProduct::getEps() const {
  try {
    return static_cast<EpsSettings *>(&mEps);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

StatisticalSettings *TimeIntervalSimulatedSatelliteEnsembleProduct::getStatistical() const {
  try {
    return static_cast<StatisticalSettings *>(&mStatistical);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalSimulatedSatelliteEnsembleProduct::setSimulatedSatelliteProduct(SimulatedSatelliteProduct &simulatedSatelliteProduct) {
  try {
    mSimulatedSatelliteProduct = simulatedSatelliteProduct;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalSimulatedSatelliteEnsembleProduct::setEps(EpsSettings &eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalSimulatedSatelliteEnsembleProduct::setStatistical(StatisticalSettings &statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
