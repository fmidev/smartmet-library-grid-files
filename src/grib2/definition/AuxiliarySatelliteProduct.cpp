// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AuxiliarySatelliteProductImpl.*' files.
// ***********************************************************************

#include "AuxiliarySatelliteProduct.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AuxiliarySatelliteProduct::AuxiliarySatelliteProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

AuxiliarySatelliteProduct::~AuxiliarySatelliteProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void AuxiliarySatelliteProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterCategory = memoryReader.read_UInt8_opt();
    mParameterNumber = memoryReader.read_UInt8_opt();
    mTypeOfGeneratingProcess = memoryReader.read_UInt8_opt();
    mObservationGeneratingProcessIdentifier = memoryReader.read_UInt8_opt();
    mNB = memoryReader.read_UInt8_opt();
    mTypeOfAuxiliaryInformation = memoryReader.read_UInt8_opt();
    mSatelliteSeries = memoryReader.read_UInt16_opt();
    mSatelliteNumber = memoryReader.read_UInt16_opt();
    mInstrumentType = memoryReader.read_UInt16_opt();
    mScaleFactorOfCentralWaveNumber = memoryReader.read_UInt8_opt();
    mScaledValueOfCentralWaveNumber = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void AuxiliarySatelliteProduct::write(DataWriter &dataWriter) {
  try {
    dataWriter << mParameterCategory;
    dataWriter << mParameterNumber;
    dataWriter << mTypeOfGeneratingProcess;
    dataWriter << mObservationGeneratingProcessIdentifier;
    dataWriter << mNB;
    dataWriter << mTypeOfAuxiliaryInformation;
    dataWriter << mSatelliteSeries;
    dataWriter << mSatelliteNumber;
    dataWriter << mInstrumentType;
    dataWriter << mScaleFactorOfCentralWaveNumber;
    dataWriter << mScaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void AuxiliarySatelliteProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAuxiliarySatelliteProduct.ParameterCategory", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterCategory));
    sprintf(name, "%sAuxiliarySatelliteProduct.ParameterNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterNumber));
    sprintf(name, "%sAuxiliarySatelliteProduct.TypeOfGeneratingProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfGeneratingProcess));
    sprintf(name, "%sAuxiliarySatelliteProduct.ObservationGeneratingProcessIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mObservationGeneratingProcessIdentifier));
    sprintf(name, "%sAuxiliarySatelliteProduct.NB", prefix.c_str());
    attributeList.addAttribute(name, toString(mNB));
    sprintf(name, "%sAuxiliarySatelliteProduct.TypeOfAuxiliaryInformation", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfAuxiliaryInformation));
    sprintf(name, "%sAuxiliarySatelliteProduct.SatelliteSeries", prefix.c_str());
    attributeList.addAttribute(name, toString(mSatelliteSeries));
    sprintf(name, "%sAuxiliarySatelliteProduct.SatelliteNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mSatelliteNumber));
    sprintf(name, "%sAuxiliarySatelliteProduct.InstrumentType", prefix.c_str());
    attributeList.addAttribute(name, toString(mInstrumentType));
    sprintf(name, "%sAuxiliarySatelliteProduct.ScaleFactorOfCentralWaveNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfCentralWaveNumber));
    sprintf(name, "%sAuxiliarySatelliteProduct.ScaledValueOfCentralWaveNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfCentralWaveNumber));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void AuxiliarySatelliteProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "AuxiliarySatelliteProduct\n";
    stream << space(level) << "- ParameterCategory = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- ParameterNumber = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- TypeOfGeneratingProcess = " << toString(mTypeOfGeneratingProcess) << "\n";
    stream << space(level) << "- ObservationGeneratingProcessIdentifier = " << toString(mObservationGeneratingProcessIdentifier) << "\n";
    stream << space(level) << "- NB = " << toString(mNB) << "\n";
    stream << space(level) << "- TypeOfAuxiliaryInformation = " << toString(mTypeOfAuxiliaryInformation) << "\n";
    stream << space(level) << "- SatelliteSeries = " << toString(mSatelliteSeries) << "\n";
    stream << space(level) << "- SatelliteNumber = " << toString(mSatelliteNumber) << "\n";
    stream << space(level) << "- InstrumentType = " << toString(mInstrumentType) << "\n";
    stream << space(level) << "- ScaleFactorOfCentralWaveNumber = " << toString(mScaleFactorOfCentralWaveNumber) << "\n";
    stream << space(level) << "- ScaledValueOfCentralWaveNumber = " << toString(mScaledValueOfCentralWaveNumber) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash AuxiliarySatelliteProduct::countHash() {
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
    if (mTypeOfAuxiliaryInformation)
      boost::hash_combine(seed, *mTypeOfAuxiliaryInformation);
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint AuxiliarySatelliteProduct::getTemplateNumber() const {
  return 311;
}

ProductDefinition *AuxiliarySatelliteProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new AuxiliarySatelliteProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterCategory} attribute. */

const T::UInt8_opt &AuxiliarySatelliteProduct::getParameterCategory() const {
  try {
    return mParameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterNumber} attribute. */

const T::UInt8_opt &AuxiliarySatelliteProduct::getParameterNumber() const {
  try {
    return mParameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfGeneratingProcess} attribute. */

const T::UInt8_opt &AuxiliarySatelliteProduct::getTypeOfGeneratingProcess() const {
  try {
    return mTypeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mObservationGeneratingProcessIdentifier} attribute. */

const T::UInt8_opt &AuxiliarySatelliteProduct::getObservationGeneratingProcessIdentifier() const {
  try {
    return mObservationGeneratingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNB} attribute. */

const T::UInt8_opt &AuxiliarySatelliteProduct::getNB() const {
  try {
    return mNB;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfAuxiliaryInformation} attribute. */

const T::UInt8_opt &AuxiliarySatelliteProduct::getTypeOfAuxiliaryInformation() const {
  try {
    return mTypeOfAuxiliaryInformation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteSeries} attribute. */

const T::UInt16_opt &AuxiliarySatelliteProduct::getSatelliteSeries() const {
  try {
    return mSatelliteSeries;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteNumber} attribute. */

const T::UInt16_opt &AuxiliarySatelliteProduct::getSatelliteNumber() const {
  try {
    return mSatelliteNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mInstrumentType} attribute. */

const T::UInt16_opt &AuxiliarySatelliteProduct::getInstrumentType() const {
  try {
    return mInstrumentType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfCentralWaveNumber} attribute. */

const T::UInt8_opt &AuxiliarySatelliteProduct::getScaleFactorOfCentralWaveNumber() const {
  try {
    return mScaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfCentralWaveNumber} attribute. */

const T::UInt32_opt &AuxiliarySatelliteProduct::getScaledValueOfCentralWaveNumber() const {
  try {
    return mScaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setParameterCategory(T::UInt8_opt parameterCategory) {
  try {
    mParameterCategory = parameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setParameterNumber(T::UInt8_opt parameterNumber) {
  try {
    mParameterNumber = parameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess) {
  try {
    mTypeOfGeneratingProcess = typeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setObservationGeneratingProcessIdentifier(T::UInt8_opt observationGeneratingProcessIdentifier) {
  try {
    mObservationGeneratingProcessIdentifier = observationGeneratingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setNB(T::UInt8_opt nB) {
  try {
    mNB = nB;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setTypeOfAuxiliaryInformation(T::UInt8_opt typeOfAuxiliaryInformation) {
  try {
    mTypeOfAuxiliaryInformation = typeOfAuxiliaryInformation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setSatelliteSeries(T::UInt16_opt satelliteSeries) {
  try {
    mSatelliteSeries = satelliteSeries;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setSatelliteNumber(T::UInt16_opt satelliteNumber) {
  try {
    mSatelliteNumber = satelliteNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setInstrumentType(T::UInt16_opt instrumentType) {
  try {
    mInstrumentType = instrumentType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setScaleFactorOfCentralWaveNumber(T::UInt8_opt scaleFactorOfCentralWaveNumber) {
  try {
    mScaleFactorOfCentralWaveNumber = scaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AuxiliarySatelliteProduct::setScaledValueOfCentralWaveNumber(T::UInt32_opt scaledValueOfCentralWaveNumber) {
  try {
    mScaledValueOfCentralWaveNumber = scaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
