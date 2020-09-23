// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SimulatedSatelliteProductImpl.*' files.
// ***********************************************************************

#include "SimulatedSatelliteProduct.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SimulatedSatelliteProduct::SimulatedSatelliteProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

SimulatedSatelliteProduct::SimulatedSatelliteProduct(const SimulatedSatelliteProduct &other) : ProductDefinition(other) {
  try {
    mParameter = other.mParameter;
    mPointInTime = other.mPointInTime;
    mNB = other.mNB;
    mSatelliteSeries = other.mSatelliteSeries;
    mSatelliteNumber = other.mSatelliteNumber;
    mInstrumentType = other.mInstrumentType;
    mScaleFactorOfCentralWaveNumber = other.mScaleFactorOfCentralWaveNumber;
    mScaledValueOfCentralWaveNumber = other.mScaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

SimulatedSatelliteProduct::~SimulatedSatelliteProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SimulatedSatelliteProduct::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mPointInTime.read(memoryReader);
    mNB = memoryReader.read_UInt8_opt();
    mSatelliteSeries = memoryReader.read_UInt16_opt();
    mSatelliteNumber = memoryReader.read_UInt16_opt();
    mInstrumentType = memoryReader.read_UInt16_opt();
    mScaleFactorOfCentralWaveNumber = memoryReader.read_UInt8_opt();
    mScaledValueOfCentralWaveNumber = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void SimulatedSatelliteProduct::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mPointInTime.write(dataWriter);
    dataWriter << mNB;
    dataWriter << mSatelliteSeries;
    dataWriter << mSatelliteNumber;
    dataWriter << mInstrumentType;
    dataWriter << mScaleFactorOfCentralWaveNumber;
    dataWriter << mScaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SimulatedSatelliteProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSimulatedSatelliteProduct.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sSimulatedSatelliteProduct.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sSimulatedSatelliteProduct.NB", prefix.c_str());
    attributeList.addAttribute(name, toString(mNB));
    sprintf(name, "%sSimulatedSatelliteProduct.SatelliteSeries", prefix.c_str());
    attributeList.addAttribute(name, toString(mSatelliteSeries));
    sprintf(name, "%sSimulatedSatelliteProduct.SatelliteNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mSatelliteNumber));
    sprintf(name, "%sSimulatedSatelliteProduct.InstrumentType", prefix.c_str());
    attributeList.addAttribute(name, toString(mInstrumentType));
    sprintf(name, "%sSimulatedSatelliteProduct.ScaleFactorOfCentralWaveNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfCentralWaveNumber));
    sprintf(name, "%sSimulatedSatelliteProduct.ScaledValueOfCentralWaveNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfCentralWaveNumber));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SimulatedSatelliteProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SimulatedSatelliteProduct\n";
    mParameter.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    stream << space(level) << "- NB = " << toString(mNB) << "\n";
    stream << space(level) << "- SatelliteSeries = " << toString(mSatelliteSeries) << "\n";
    stream << space(level) << "- SatelliteNumber = " << toString(mSatelliteNumber) << "\n";
    stream << space(level) << "- InstrumentType = " << toString(mInstrumentType) << "\n";
    stream << space(level) << "- ScaleFactorOfCentralWaveNumber = " << toString(mScaleFactorOfCentralWaveNumber) << "\n";
    stream << space(level) << "- ScaledValueOfCentralWaveNumber = " << toString(mScaledValueOfCentralWaveNumber) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SimulatedSatelliteProduct::countHash() {
  try {
    std::size_t seed = 0;
    if (mNB)
      boost::hash_combine(seed, *mNB);
    if (mSatelliteSeries)
      boost::hash_combine(seed, *mSatelliteSeries);
    if (mSatelliteNumber)
      boost::hash_combine(seed, *mSatelliteNumber);
    if (mInstrumentType)
      boost::hash_combine(seed, *mInstrumentType);
    if (mScaleFactorOfCentralWaveNumber)
      boost::hash_combine(seed, *mScaleFactorOfCentralWaveNumber);
    if (mScaledValueOfCentralWaveNumber)
      boost::hash_combine(seed, *mScaledValueOfCentralWaveNumber);
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mPointInTime.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint SimulatedSatelliteProduct::getTemplateNumber() const {
  return 32;
}

ProductDefinition *SimulatedSatelliteProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new SimulatedSatelliteProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *SimulatedSatelliteProduct::getParameter() const {
  try {
    return static_cast<ParameterSettings *>(&mParameter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *SimulatedSatelliteProduct::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNB} attribute. */

const T::UInt8_opt &SimulatedSatelliteProduct::getNB() const {
  try {
    return mNB;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteSeries} attribute. */

const T::UInt16_opt &SimulatedSatelliteProduct::getSatelliteSeries() const {
  try {
    return mSatelliteSeries;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteNumber} attribute. */

const T::UInt16_opt &SimulatedSatelliteProduct::getSatelliteNumber() const {
  try {
    return mSatelliteNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mInstrumentType} attribute. */

const T::UInt16_opt &SimulatedSatelliteProduct::getInstrumentType() const {
  try {
    return mInstrumentType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfCentralWaveNumber} attribute. */

const T::UInt8_opt &SimulatedSatelliteProduct::getScaleFactorOfCentralWaveNumber() const {
  try {
    return mScaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfCentralWaveNumber} attribute. */

const T::UInt32_opt &SimulatedSatelliteProduct::getScaledValueOfCentralWaveNumber() const {
  try {
    return mScaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void SimulatedSatelliteProduct::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void SimulatedSatelliteProduct::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void SimulatedSatelliteProduct::setNB(T::UInt8_opt nB) {
  try {
    mNB = nB;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void SimulatedSatelliteProduct::setSatelliteSeries(T::UInt16_opt satelliteSeries) {
  try {
    mSatelliteSeries = satelliteSeries;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void SimulatedSatelliteProduct::setSatelliteNumber(T::UInt16_opt satelliteNumber) {
  try {
    mSatelliteNumber = satelliteNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void SimulatedSatelliteProduct::setInstrumentType(T::UInt16_opt instrumentType) {
  try {
    mInstrumentType = instrumentType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void SimulatedSatelliteProduct::setScaleFactorOfCentralWaveNumber(T::UInt8_opt scaleFactorOfCentralWaveNumber) {
  try {
    mScaleFactorOfCentralWaveNumber = scaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void SimulatedSatelliteProduct::setScaledValueOfCentralWaveNumber(T::UInt32_opt scaledValueOfCentralWaveNumber) {
  try {
    mScaledValueOfCentralWaveNumber = scaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
