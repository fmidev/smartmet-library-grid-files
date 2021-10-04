// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SatelliteProductImpl.*' files.
// ***********************************************************************

#include "SatelliteProduct.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SatelliteProduct::SatelliteProduct() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

SatelliteProduct::~SatelliteProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SatelliteProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterCategory = memoryReader.read_UInt8_opt();
    mParameterNumber = memoryReader.read_UInt8_opt();
    mTypeOfGeneratingProcess = memoryReader.read_UInt8_opt();
    mObservationGeneratingProcessIdentifier = memoryReader.read_UInt8_opt();
    mNB = memoryReader.read_UInt8_opt();
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

void SatelliteProduct::write(DataWriter &dataWriter) {
  try {
    dataWriter << mParameterCategory;
    dataWriter << mParameterNumber;
    dataWriter << mTypeOfGeneratingProcess;
    dataWriter << mObservationGeneratingProcessIdentifier;
    dataWriter << mNB;
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

void SatelliteProduct::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSatelliteProduct.ParameterCategory", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterCategory));
    sprintf(name, "%sSatelliteProduct.ParameterNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterNumber));
    sprintf(name, "%sSatelliteProduct.TypeOfGeneratingProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfGeneratingProcess));
    sprintf(name, "%sSatelliteProduct.ObservationGeneratingProcessIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mObservationGeneratingProcessIdentifier));
    sprintf(name, "%sSatelliteProduct.NB", prefix.c_str());
    attributeList.addAttribute(name, toString(mNB));
    sprintf(name, "%sSatelliteProduct.SatelliteSeries", prefix.c_str());
    attributeList.addAttribute(name, toString(mSatelliteSeries));
    sprintf(name, "%sSatelliteProduct.SatelliteNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mSatelliteNumber));
    sprintf(name, "%sSatelliteProduct.InstrumentType", prefix.c_str());
    attributeList.addAttribute(name, toString(mInstrumentType));
    sprintf(name, "%sSatelliteProduct.ScaleFactorOfCentralWaveNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfCentralWaveNumber));
    sprintf(name, "%sSatelliteProduct.ScaledValueOfCentralWaveNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfCentralWaveNumber));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool SatelliteProduct::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (strcasecmp(attributeName, "ParameterCategory") == 0) {
      attributeValue = toString(mParameterCategory);
      return true;
    }
    if (strcasecmp(attributeName, "ParameterNumber") == 0) {
      attributeValue = toString(mParameterNumber);
      return true;
    }
    if (strcasecmp(attributeName, "TypeOfGeneratingProcess") == 0) {
      attributeValue = toString(mTypeOfGeneratingProcess);
      return true;
    }
    if (strcasecmp(attributeName, "ObservationGeneratingProcessIdentifier") == 0) {
      attributeValue = toString(mObservationGeneratingProcessIdentifier);
      return true;
    }
    if (strcasecmp(attributeName, "NB") == 0) {
      attributeValue = toString(mNB);
      return true;
    }
    if (strcasecmp(attributeName, "SatelliteSeries") == 0) {
      attributeValue = toString(mSatelliteSeries);
      return true;
    }
    if (strcasecmp(attributeName, "SatelliteNumber") == 0) {
      attributeValue = toString(mSatelliteNumber);
      return true;
    }
    if (strcasecmp(attributeName, "InstrumentType") == 0) {
      attributeValue = toString(mInstrumentType);
      return true;
    }
    if (strcasecmp(attributeName, "ScaleFactorOfCentralWaveNumber") == 0) {
      attributeValue = toString(mScaleFactorOfCentralWaveNumber);
      return true;
    }
    if (strcasecmp(attributeName, "ScaledValueOfCentralWaveNumber") == 0) {
      attributeValue = toString(mScaledValueOfCentralWaveNumber);
      return true;
    }
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool SatelliteProduct::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "ParameterCategory") == 0 && strcasecmp(attributeValue, toString(mParameterCategory).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ParameterNumber") == 0 && strcasecmp(attributeValue, toString(mParameterNumber).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "TypeOfGeneratingProcess") == 0 && strcasecmp(attributeValue, toString(mTypeOfGeneratingProcess).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ObservationGeneratingProcessIdentifier") == 0 && strcasecmp(attributeValue, toString(mObservationGeneratingProcessIdentifier).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "NB") == 0 && strcasecmp(attributeValue, toString(mNB).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "SatelliteSeries") == 0 && strcasecmp(attributeValue, toString(mSatelliteSeries).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "SatelliteNumber") == 0 && strcasecmp(attributeValue, toString(mSatelliteNumber).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "InstrumentType") == 0 && strcasecmp(attributeValue, toString(mInstrumentType).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaleFactorOfCentralWaveNumber") == 0 && strcasecmp(attributeValue, toString(mScaleFactorOfCentralWaveNumber).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaledValueOfCentralWaveNumber") == 0 && strcasecmp(attributeValue, toString(mScaledValueOfCentralWaveNumber).c_str()) == 0)
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SatelliteProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SatelliteProduct\n";
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SatelliteProduct::countHash() {
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint SatelliteProduct::getTemplateNumber() const {
  return 31;
}

ProductDefinition *SatelliteProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new SatelliteProduct(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterCategory} attribute. */

const T::UInt8_opt &SatelliteProduct::getParameterCategory() const {
  try {
    return mParameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterNumber} attribute. */

const T::UInt8_opt &SatelliteProduct::getParameterNumber() const {
  try {
    return mParameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfGeneratingProcess} attribute. */

const T::UInt8_opt &SatelliteProduct::getTypeOfGeneratingProcess() const {
  try {
    return mTypeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mObservationGeneratingProcessIdentifier} attribute. */

const T::UInt8_opt &SatelliteProduct::getObservationGeneratingProcessIdentifier() const {
  try {
    return mObservationGeneratingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNB} attribute. */

const T::UInt8_opt &SatelliteProduct::getNB() const {
  try {
    return mNB;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteSeries} attribute. */

const T::UInt16_opt &SatelliteProduct::getSatelliteSeries() const {
  try {
    return mSatelliteSeries;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSatelliteNumber} attribute. */

const T::UInt16_opt &SatelliteProduct::getSatelliteNumber() const {
  try {
    return mSatelliteNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mInstrumentType} attribute. */

const T::UInt16_opt &SatelliteProduct::getInstrumentType() const {
  try {
    return mInstrumentType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfCentralWaveNumber} attribute. */

const T::UInt8_opt &SatelliteProduct::getScaleFactorOfCentralWaveNumber() const {
  try {
    return mScaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfCentralWaveNumber} attribute. */

const T::UInt32_opt &SatelliteProduct::getScaledValueOfCentralWaveNumber() const {
  try {
    return mScaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setParameterCategory(T::UInt8_opt parameterCategory) {
  try {
    mParameterCategory = parameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setParameterNumber(T::UInt8_opt parameterNumber) {
  try {
    mParameterNumber = parameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess) {
  try {
    mTypeOfGeneratingProcess = typeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setObservationGeneratingProcessIdentifier(T::UInt8_opt observationGeneratingProcessIdentifier) {
  try {
    mObservationGeneratingProcessIdentifier = observationGeneratingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setNB(T::UInt8_opt nB) {
  try {
    mNB = nB;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setSatelliteSeries(T::UInt16_opt satelliteSeries) {
  try {
    mSatelliteSeries = satelliteSeries;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setSatelliteNumber(T::UInt16_opt satelliteNumber) {
  try {
    mSatelliteNumber = satelliteNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setInstrumentType(T::UInt16_opt instrumentType) {
  try {
    mInstrumentType = instrumentType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setScaleFactorOfCentralWaveNumber(T::UInt8_opt scaleFactorOfCentralWaveNumber) {
  try {
    mScaleFactorOfCentralWaveNumber = scaleFactorOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SatelliteProduct::setScaledValueOfCentralWaveNumber(T::UInt32_opt scaledValueOfCentralWaveNumber) {
  try {
    mScaledValueOfCentralWaveNumber = scaledValueOfCentralWaveNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
