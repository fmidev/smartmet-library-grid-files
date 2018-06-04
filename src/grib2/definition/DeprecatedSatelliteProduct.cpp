// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'DeprecatedSatelliteProductImpl.*' files.
// ***********************************************************************

#include "DeprecatedSatelliteProduct.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

DeprecatedSatelliteProduct::DeprecatedSatelliteProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

DeprecatedSatelliteProduct::~DeprecatedSatelliteProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void DeprecatedSatelliteProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterCategory = memoryReader.read_UInt8_opt();
    mParameterNumber = memoryReader.read_UInt8_opt();
    mTypeOfGeneratingProcess = memoryReader.read_UInt8_opt();
    mObservationGeneratingProcessIdentifier = memoryReader.read_UInt8_opt();
    mNB = memoryReader.read_UInt8_opt();
    mSatelliteSeries = memoryReader.read_UInt16_opt();
    mSatelliteNumber = memoryReader.read_UInt16_opt();
    mInstrumentType = memoryReader.read_UInt8_opt();
    mScaleFactorOfCentralWaveNumber = memoryReader.read_UInt8_opt();
    mScaledValueOfCentralWaveNumber = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void DeprecatedSatelliteProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sDeprecatedSatelliteProduct.ParameterCategory", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterCategory));
    sprintf(name, "%sDeprecatedSatelliteProduct.ParameterNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterNumber));
    sprintf(name, "%sDeprecatedSatelliteProduct.TypeOfGeneratingProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfGeneratingProcess));
    sprintf(name, "%sDeprecatedSatelliteProduct.ObservationGeneratingProcessIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mObservationGeneratingProcessIdentifier));
    sprintf(name, "%sDeprecatedSatelliteProduct.NB", prefix.c_str());
    attributeList.addAttribute(name, toString(mNB));
    sprintf(name, "%sDeprecatedSatelliteProduct.SatelliteSeries", prefix.c_str());
    attributeList.addAttribute(name, toString(mSatelliteSeries));
    sprintf(name, "%sDeprecatedSatelliteProduct.SatelliteNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mSatelliteNumber));
    sprintf(name, "%sDeprecatedSatelliteProduct.InstrumentType", prefix.c_str());
    attributeList.addAttribute(name, toString(mInstrumentType));
    sprintf(name, "%sDeprecatedSatelliteProduct.ScaleFactorOfCentralWaveNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfCentralWaveNumber));
    sprintf(name, "%sDeprecatedSatelliteProduct.ScaledValueOfCentralWaveNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfCentralWaveNumber));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void DeprecatedSatelliteProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "DeprecatedSatelliteProduct\n";
    stream << space(level) << "- ParameterCategory = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- ParameterNumber = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- TypeOfGeneratingProcess = " << toString(mTypeOfGeneratingProcess) << "\n";
    stream << space(level) << "- ObservationGeneratingProcessIdentifier = " << toString(mObservationGeneratingProcessIdentifier) << "\n";
    stream << space(level) << "- NB = " << toString(mNB) << "\n";
    stream << space(level) << "- SatelliteSeries = " << toString(mSatelliteSeries) << "\n";
    stream << space(level) << "- SatelliteNumber = " << toString(mSatelliteNumber) << "\n";
    stream << space(level) << "- InstrumentType = " << toString(mInstrumentType) << "\n";
    stream << space(level) << "- ScaleFactorOfCentralWaveNumber = " << toString(mScaleFactorOfCentralWaveNumber) << "\n";
    stream << space(level) << "- ScaledValueOfCentralWaveNumber = " << toString(mScaledValueOfCentralWaveNumber) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash DeprecatedSatelliteProduct::countHash() {
  try {
    std::size_t seed = 0;
    if (mParameterCategory)
      boost::hash_combine(seed, *mParameterCategory);
    if (mParameterNumber)
      boost::hash_combine(seed, *mParameterNumber);
    if (mTypeOfGeneratingProcess)
      boost::hash_combine(seed, *mTypeOfGeneratingProcess);
    if (mObservationGeneratingProcessIdentifier)
      boost::hash_combine(seed, *mObservationGeneratingProcessIdentifier);
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
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mParameterCategory} attribute. */

const T::UInt8_opt &DeprecatedSatelliteProduct::getParameterCategory() const {
  try {
    return mParameterCategory;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mParameterNumber} attribute. */

const T::UInt8_opt &DeprecatedSatelliteProduct::getParameterNumber() const {
  try {
    return mParameterNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfGeneratingProcess} attribute. */

const T::UInt8_opt &DeprecatedSatelliteProduct::getTypeOfGeneratingProcess() const {
  try {
    return mTypeOfGeneratingProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mObservationGeneratingProcessIdentifier} attribute. */

const T::UInt8_opt &DeprecatedSatelliteProduct::getObservationGeneratingProcessIdentifier() const {
  try {
    return mObservationGeneratingProcessIdentifier;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNB} attribute. */

const T::UInt8_opt &DeprecatedSatelliteProduct::getNB() const {
  try {
    return mNB;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteSeries} attribute. */

const T::UInt16_opt &DeprecatedSatelliteProduct::getSatelliteSeries() const {
  try {
    return mSatelliteSeries;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteNumber} attribute. */

const T::UInt16_opt &DeprecatedSatelliteProduct::getSatelliteNumber() const {
  try {
    return mSatelliteNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mInstrumentType} attribute. */

const T::UInt8_opt &DeprecatedSatelliteProduct::getInstrumentType() const {
  try {
    return mInstrumentType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfCentralWaveNumber} attribute. */

const T::UInt8_opt &DeprecatedSatelliteProduct::getScaleFactorOfCentralWaveNumber() const {
  try {
    return mScaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfCentralWaveNumber} attribute. */

const T::UInt32_opt &DeprecatedSatelliteProduct::getScaledValueOfCentralWaveNumber() const {
  try {
    return mScaledValueOfCentralWaveNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setParameterCategory(T::UInt8_opt parameterCategory) {
  try {
    mParameterCategory = parameterCategory;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setParameterNumber(T::UInt8_opt parameterNumber) {
  try {
    mParameterNumber = parameterNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess) {
  try {
    mTypeOfGeneratingProcess = typeOfGeneratingProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setObservationGeneratingProcessIdentifier(T::UInt8_opt observationGeneratingProcessIdentifier) {
  try {
    mObservationGeneratingProcessIdentifier = observationGeneratingProcessIdentifier;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setNB(T::UInt8_opt nB) {
  try {
    mNB = nB;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setSatelliteSeries(T::UInt16_opt satelliteSeries) {
  try {
    mSatelliteSeries = satelliteSeries;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setSatelliteNumber(T::UInt16_opt satelliteNumber) {
  try {
    mSatelliteNumber = satelliteNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setInstrumentType(T::UInt8_opt instrumentType) {
  try {
    mInstrumentType = instrumentType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setScaleFactorOfCentralWaveNumber(T::UInt8_opt scaleFactorOfCentralWaveNumber) {
  try {
    mScaleFactorOfCentralWaveNumber = scaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void DeprecatedSatelliteProduct::setScaledValueOfCentralWaveNumber(T::UInt32_opt scaledValueOfCentralWaveNumber) {
  try {
    mScaledValueOfCentralWaveNumber = scaledValueOfCentralWaveNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
