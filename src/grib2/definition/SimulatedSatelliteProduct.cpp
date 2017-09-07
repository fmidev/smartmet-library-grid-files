// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SimulatedSatelliteProductImpl.*' files.
// ***********************************************************************

#include "grib2/definition/SimulatedSatelliteProduct.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SimulatedSatelliteProduct::SimulatedSatelliteProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

SimulatedSatelliteProduct::~SimulatedSatelliteProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
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
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
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
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
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
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
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
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

const ParameterSettings *SimulatedSatelliteProduct::getParameter() const {
  try {
    return &mParameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

const PointInTimeSettings *SimulatedSatelliteProduct::getPointInTime() const {
  try {
    return &mPointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNB} attribute. */

const T::UInt8_opt &SimulatedSatelliteProduct::getNB() const {
  try {
    return mNB;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteSeries} attribute. */

const T::UInt16_opt &SimulatedSatelliteProduct::getSatelliteSeries() const {
  try {
    return mSatelliteSeries;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteNumber} attribute. */

const T::UInt16_opt &SimulatedSatelliteProduct::getSatelliteNumber() const {
  try {
    return mSatelliteNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mInstrumentType} attribute. */

const T::UInt16_opt &SimulatedSatelliteProduct::getInstrumentType() const {
  try {
    return mInstrumentType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfCentralWaveNumber} attribute. */

const T::UInt8_opt &SimulatedSatelliteProduct::getScaleFactorOfCentralWaveNumber() const {
  try {
    return mScaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfCentralWaveNumber} attribute. */

const T::UInt32_opt &SimulatedSatelliteProduct::getScaledValueOfCentralWaveNumber() const {
  try {
    return mScaledValueOfCentralWaveNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SimulatedSatelliteProduct::setParameter(ParameterSettings parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SimulatedSatelliteProduct::setPointInTime(PointInTimeSettings pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SimulatedSatelliteProduct::setNB(T::UInt8_opt nB) {
  try {
    mNB = nB;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SimulatedSatelliteProduct::setSatelliteSeries(T::UInt16_opt satelliteSeries) {
  try {
    mSatelliteSeries = satelliteSeries;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SimulatedSatelliteProduct::setSatelliteNumber(T::UInt16_opt satelliteNumber) {
  try {
    mSatelliteNumber = satelliteNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SimulatedSatelliteProduct::setInstrumentType(T::UInt16_opt instrumentType) {
  try {
    mInstrumentType = instrumentType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SimulatedSatelliteProduct::setScaleFactorOfCentralWaveNumber(T::UInt8_opt scaleFactorOfCentralWaveNumber) {
  try {
    mScaleFactorOfCentralWaveNumber = scaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SimulatedSatelliteProduct::setScaledValueOfCentralWaveNumber(T::UInt32_opt scaledValueOfCentralWaveNumber) {
  try {
    mScaledValueOfCentralWaveNumber = scaledValueOfCentralWaveNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
