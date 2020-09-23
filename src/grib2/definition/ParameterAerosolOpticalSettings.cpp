// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ParameterAerosolOpticalSettingsImpl.*' files.
// ***********************************************************************

#include "ParameterAerosolOpticalSettings.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

ParameterAerosolOpticalSettings::ParameterAerosolOpticalSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

ParameterAerosolOpticalSettings::ParameterAerosolOpticalSettings(const ParameterAerosolOpticalSettings &other) {
  try {
    mParameterCategory = other.mParameterCategory;
    mParameterNumber = other.mParameterNumber;
    mAerosolType = other.mAerosolType;
    mTypeOfSizeInterval = other.mTypeOfSizeInterval;
    mScaleFactorOfFirstSize = other.mScaleFactorOfFirstSize;
    mScaledValueOfFirstSize = other.mScaledValueOfFirstSize;
    mScaleFactorOfSecondSize = other.mScaleFactorOfSecondSize;
    mScaledValueOfSecondSize = other.mScaledValueOfSecondSize;
    mTypeOfWavelengthInterval = other.mTypeOfWavelengthInterval;
    mScaleFactorOfFirstWavelength = other.mScaleFactorOfFirstWavelength;
    mScaledValueOfFirstWavelength = other.mScaledValueOfFirstWavelength;
    mScaleFactorOfSecondWavelength = other.mScaleFactorOfSecondWavelength;
    mScaledValueOfSecondWavelength = other.mScaledValueOfSecondWavelength;
    mTypeOfGeneratingProcess = other.mTypeOfGeneratingProcess;
    mBackgroundProcess = other.mBackgroundProcess;
    mGeneratingProcessIdentifier = other.mGeneratingProcessIdentifier;
    mHoursAfterDataCutoff = other.mHoursAfterDataCutoff;
    mMinutesAfterDataCutoff = other.mMinutesAfterDataCutoff;
    mIndicatorOfUnitOfTimeRange = other.mIndicatorOfUnitOfTimeRange;
    mForecastTime = other.mForecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

ParameterAerosolOpticalSettings::~ParameterAerosolOpticalSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ParameterAerosolOpticalSettings::read(MemoryReader &memoryReader) {
  try {
    mParameterCategory = memoryReader.read_UInt8_opt();
    mParameterNumber = memoryReader.read_UInt8_opt();
    mAerosolType = memoryReader.read_UInt16_opt();
    mTypeOfSizeInterval = memoryReader.read_UInt8_opt();
    mScaleFactorOfFirstSize = memoryReader.read_Int8_opt();
    mScaledValueOfFirstSize = memoryReader.read_Int32_opt();
    mScaleFactorOfSecondSize = memoryReader.read_Int8_opt();
    mScaledValueOfSecondSize = memoryReader.read_Int32_opt();
    mTypeOfWavelengthInterval = memoryReader.read_UInt8_opt();
    mScaleFactorOfFirstWavelength = memoryReader.read_Int8_opt();
    mScaledValueOfFirstWavelength = memoryReader.read_Int32_opt();
    mScaleFactorOfSecondWavelength = memoryReader.read_Int8_opt();
    mScaledValueOfSecondWavelength = memoryReader.read_Int32_opt();
    mTypeOfGeneratingProcess = memoryReader.read_UInt8_opt();
    mBackgroundProcess = memoryReader.read_UInt8_opt();
    mGeneratingProcessIdentifier = memoryReader.read_UInt8_opt();
    mHoursAfterDataCutoff = memoryReader.read_UInt16_opt();
    mMinutesAfterDataCutoff = memoryReader.read_UInt8_opt();
    mIndicatorOfUnitOfTimeRange = memoryReader.read_UInt8_opt();
    mForecastTime = memoryReader.read_Int32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void ParameterAerosolOpticalSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mParameterCategory;
    dataWriter << mParameterNumber;
    dataWriter << mAerosolType;
    dataWriter << mTypeOfSizeInterval;
    dataWriter << mScaleFactorOfFirstSize;
    dataWriter << mScaledValueOfFirstSize;
    dataWriter << mScaleFactorOfSecondSize;
    dataWriter << mScaledValueOfSecondSize;
    dataWriter << mTypeOfWavelengthInterval;
    dataWriter << mScaleFactorOfFirstWavelength;
    dataWriter << mScaledValueOfFirstWavelength;
    dataWriter << mScaleFactorOfSecondWavelength;
    dataWriter << mScaledValueOfSecondWavelength;
    dataWriter << mTypeOfGeneratingProcess;
    dataWriter << mBackgroundProcess;
    dataWriter << mGeneratingProcessIdentifier;
    dataWriter << mHoursAfterDataCutoff;
    dataWriter << mMinutesAfterDataCutoff;
    dataWriter << mIndicatorOfUnitOfTimeRange;
    dataWriter << mForecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ParameterAerosolOpticalSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sParameterAerosolOpticalSettings.ParameterCategory", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterCategory));
    sprintf(name, "%sParameterAerosolOpticalSettings.ParameterNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterNumber));
    sprintf(name, "%sParameterAerosolOpticalSettings.AerosolType", prefix.c_str());
    attributeList.addAttribute(name, toString(mAerosolType));
    sprintf(name, "%sParameterAerosolOpticalSettings.TypeOfSizeInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfSizeInterval));
    sprintf(name, "%sParameterAerosolOpticalSettings.ScaleFactorOfFirstSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfFirstSize));
    sprintf(name, "%sParameterAerosolOpticalSettings.ScaledValueOfFirstSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfFirstSize));
    sprintf(name, "%sParameterAerosolOpticalSettings.ScaleFactorOfSecondSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfSecondSize));
    sprintf(name, "%sParameterAerosolOpticalSettings.ScaledValueOfSecondSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfSecondSize));
    sprintf(name, "%sParameterAerosolOpticalSettings.TypeOfWavelengthInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfWavelengthInterval));
    sprintf(name, "%sParameterAerosolOpticalSettings.ScaleFactorOfFirstWavelength", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfFirstWavelength));
    sprintf(name, "%sParameterAerosolOpticalSettings.ScaledValueOfFirstWavelength", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfFirstWavelength));
    sprintf(name, "%sParameterAerosolOpticalSettings.ScaleFactorOfSecondWavelength", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfSecondWavelength));
    sprintf(name, "%sParameterAerosolOpticalSettings.ScaledValueOfSecondWavelength", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfSecondWavelength));
    sprintf(name, "%sParameterAerosolOpticalSettings.TypeOfGeneratingProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfGeneratingProcess));
    sprintf(name, "%sParameterAerosolOpticalSettings.BackgroundProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mBackgroundProcess));
    sprintf(name, "%sParameterAerosolOpticalSettings.GeneratingProcessIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mGeneratingProcessIdentifier));
    sprintf(name, "%sParameterAerosolOpticalSettings.HoursAfterDataCutoff", prefix.c_str());
    attributeList.addAttribute(name, toString(mHoursAfterDataCutoff));
    sprintf(name, "%sParameterAerosolOpticalSettings.MinutesAfterDataCutoff", prefix.c_str());
    attributeList.addAttribute(name, toString(mMinutesAfterDataCutoff));
    sprintf(name, "%sParameterAerosolOpticalSettings.IndicatorOfUnitOfTimeRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mIndicatorOfUnitOfTimeRange));
    sprintf(name, "%sParameterAerosolOpticalSettings.ForecastTime", prefix.c_str());
    attributeList.addAttribute(name, toString(mForecastTime));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ParameterAerosolOpticalSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ParameterAerosolOpticalSettings\n";
    stream << space(level) << "- ParameterCategory = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- ParameterNumber = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- AerosolType = " << toString(mAerosolType) << "\n";
    stream << space(level) << "- TypeOfSizeInterval = " << toString(mTypeOfSizeInterval) << "\n";
    stream << space(level) << "- ScaleFactorOfFirstSize = " << toString(mScaleFactorOfFirstSize) << "\n";
    stream << space(level) << "- ScaledValueOfFirstSize = " << toString(mScaledValueOfFirstSize) << "\n";
    stream << space(level) << "- ScaleFactorOfSecondSize = " << toString(mScaleFactorOfSecondSize) << "\n";
    stream << space(level) << "- ScaledValueOfSecondSize = " << toString(mScaledValueOfSecondSize) << "\n";
    stream << space(level) << "- TypeOfWavelengthInterval = " << toString(mTypeOfWavelengthInterval) << "\n";
    stream << space(level) << "- ScaleFactorOfFirstWavelength = " << toString(mScaleFactorOfFirstWavelength) << "\n";
    stream << space(level) << "- ScaledValueOfFirstWavelength = " << toString(mScaledValueOfFirstWavelength) << "\n";
    stream << space(level) << "- ScaleFactorOfSecondWavelength = " << toString(mScaleFactorOfSecondWavelength) << "\n";
    stream << space(level) << "- ScaledValueOfSecondWavelength = " << toString(mScaledValueOfSecondWavelength) << "\n";
    stream << space(level) << "- TypeOfGeneratingProcess = " << toString(mTypeOfGeneratingProcess) << "\n";
    stream << space(level) << "- BackgroundProcess = " << toString(mBackgroundProcess) << "\n";
    stream << space(level) << "- GeneratingProcessIdentifier = " << toString(mGeneratingProcessIdentifier) << "\n";
    stream << space(level) << "- HoursAfterDataCutoff = " << toString(mHoursAfterDataCutoff) << "\n";
    stream << space(level) << "- MinutesAfterDataCutoff = " << toString(mMinutesAfterDataCutoff) << "\n";
    stream << space(level) << "- IndicatorOfUnitOfTimeRange = " << toString(mIndicatorOfUnitOfTimeRange) << "\n";
    stream << space(level) << "- ForecastTime = " << toString(mForecastTime) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ParameterAerosolOpticalSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mParameterCategory)
      boost::hash_combine(seed, *mParameterCategory);
    if (mParameterNumber)
      boost::hash_combine(seed, *mParameterNumber);
    if (mAerosolType)
      boost::hash_combine(seed, *mAerosolType);
    if (mTypeOfSizeInterval)
      boost::hash_combine(seed, *mTypeOfSizeInterval);
    if (mScaleFactorOfFirstSize)
      boost::hash_combine(seed, *mScaleFactorOfFirstSize);
    if (mScaledValueOfFirstSize)
      boost::hash_combine(seed, *mScaledValueOfFirstSize);
    if (mScaleFactorOfSecondSize)
      boost::hash_combine(seed, *mScaleFactorOfSecondSize);
    if (mScaledValueOfSecondSize)
      boost::hash_combine(seed, *mScaledValueOfSecondSize);
    if (mTypeOfWavelengthInterval)
      boost::hash_combine(seed, *mTypeOfWavelengthInterval);
    if (mScaleFactorOfFirstWavelength)
      boost::hash_combine(seed, *mScaleFactorOfFirstWavelength);
    if (mScaledValueOfFirstWavelength)
      boost::hash_combine(seed, *mScaledValueOfFirstWavelength);
    if (mScaleFactorOfSecondWavelength)
      boost::hash_combine(seed, *mScaleFactorOfSecondWavelength);
    if (mScaledValueOfSecondWavelength)
      boost::hash_combine(seed, *mScaledValueOfSecondWavelength);
    if (mTypeOfGeneratingProcess)
      boost::hash_combine(seed, *mTypeOfGeneratingProcess);
    if (mBackgroundProcess)
      boost::hash_combine(seed, *mBackgroundProcess);
    if (mGeneratingProcessIdentifier)
      boost::hash_combine(seed, *mGeneratingProcessIdentifier);
    if (mHoursAfterDataCutoff)
      boost::hash_combine(seed, *mHoursAfterDataCutoff);
    if (mMinutesAfterDataCutoff)
      boost::hash_combine(seed, *mMinutesAfterDataCutoff);
    if (mIndicatorOfUnitOfTimeRange)
      boost::hash_combine(seed, *mIndicatorOfUnitOfTimeRange);
    if (mForecastTime)
      boost::hash_combine(seed, *mForecastTime);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterCategory} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getParameterCategory() const {
  try {
    return mParameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterNumber} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getParameterNumber() const {
  try {
    return mParameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mAerosolType} attribute. */

const T::UInt16_opt &ParameterAerosolOpticalSettings::getAerosolType() const {
  try {
    return mAerosolType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfSizeInterval} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getTypeOfSizeInterval() const {
  try {
    return mTypeOfSizeInterval;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfFirstSize} attribute. */

const T::Int8_opt &ParameterAerosolOpticalSettings::getScaleFactorOfFirstSize() const {
  try {
    return mScaleFactorOfFirstSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfFirstSize} attribute. */

const T::Int32_opt &ParameterAerosolOpticalSettings::getScaledValueOfFirstSize() const {
  try {
    return mScaledValueOfFirstSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfSecondSize} attribute. */

const T::Int8_opt &ParameterAerosolOpticalSettings::getScaleFactorOfSecondSize() const {
  try {
    return mScaleFactorOfSecondSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfSecondSize} attribute. */

const T::Int32_opt &ParameterAerosolOpticalSettings::getScaledValueOfSecondSize() const {
  try {
    return mScaledValueOfSecondSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfWavelengthInterval} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getTypeOfWavelengthInterval() const {
  try {
    return mTypeOfWavelengthInterval;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfFirstWavelength} attribute. */

const T::Int8_opt &ParameterAerosolOpticalSettings::getScaleFactorOfFirstWavelength() const {
  try {
    return mScaleFactorOfFirstWavelength;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfFirstWavelength} attribute. */

const T::Int32_opt &ParameterAerosolOpticalSettings::getScaledValueOfFirstWavelength() const {
  try {
    return mScaledValueOfFirstWavelength;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfSecondWavelength} attribute. */

const T::Int8_opt &ParameterAerosolOpticalSettings::getScaleFactorOfSecondWavelength() const {
  try {
    return mScaleFactorOfSecondWavelength;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfSecondWavelength} attribute. */

const T::Int32_opt &ParameterAerosolOpticalSettings::getScaledValueOfSecondWavelength() const {
  try {
    return mScaledValueOfSecondWavelength;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfGeneratingProcess} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getTypeOfGeneratingProcess() const {
  try {
    return mTypeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mBackgroundProcess} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getBackgroundProcess() const {
  try {
    return mBackgroundProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mGeneratingProcessIdentifier} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getGeneratingProcessIdentifier() const {
  try {
    return mGeneratingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mHoursAfterDataCutoff} attribute. */

const T::UInt16_opt &ParameterAerosolOpticalSettings::getHoursAfterDataCutoff() const {
  try {
    return mHoursAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mMinutesAfterDataCutoff} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getMinutesAfterDataCutoff() const {
  try {
    return mMinutesAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mIndicatorOfUnitOfTimeRange} attribute. */

const T::UInt8_opt &ParameterAerosolOpticalSettings::getIndicatorOfUnitOfTimeRange() const {
  try {
    return mIndicatorOfUnitOfTimeRange;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mForecastTime} attribute. */

const T::Int32_opt &ParameterAerosolOpticalSettings::getForecastTime() const {
  try {
    return mForecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setParameterCategory(T::UInt8_opt parameterCategory) {
  try {
    mParameterCategory = parameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setParameterNumber(T::UInt8_opt parameterNumber) {
  try {
    mParameterNumber = parameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setAerosolType(T::UInt16_opt aerosolType) {
  try {
    mAerosolType = aerosolType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setTypeOfSizeInterval(T::UInt8_opt typeOfSizeInterval) {
  try {
    mTypeOfSizeInterval = typeOfSizeInterval;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setScaleFactorOfFirstSize(T::Int8_opt scaleFactorOfFirstSize) {
  try {
    mScaleFactorOfFirstSize = scaleFactorOfFirstSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setScaledValueOfFirstSize(T::Int32_opt scaledValueOfFirstSize) {
  try {
    mScaledValueOfFirstSize = scaledValueOfFirstSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setScaleFactorOfSecondSize(T::Int8_opt scaleFactorOfSecondSize) {
  try {
    mScaleFactorOfSecondSize = scaleFactorOfSecondSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setScaledValueOfSecondSize(T::Int32_opt scaledValueOfSecondSize) {
  try {
    mScaledValueOfSecondSize = scaledValueOfSecondSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setTypeOfWavelengthInterval(T::UInt8_opt typeOfWavelengthInterval) {
  try {
    mTypeOfWavelengthInterval = typeOfWavelengthInterval;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setScaleFactorOfFirstWavelength(T::Int8_opt scaleFactorOfFirstWavelength) {
  try {
    mScaleFactorOfFirstWavelength = scaleFactorOfFirstWavelength;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setScaledValueOfFirstWavelength(T::Int32_opt scaledValueOfFirstWavelength) {
  try {
    mScaledValueOfFirstWavelength = scaledValueOfFirstWavelength;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setScaleFactorOfSecondWavelength(T::Int8_opt scaleFactorOfSecondWavelength) {
  try {
    mScaleFactorOfSecondWavelength = scaleFactorOfSecondWavelength;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setScaledValueOfSecondWavelength(T::Int32_opt scaledValueOfSecondWavelength) {
  try {
    mScaledValueOfSecondWavelength = scaledValueOfSecondWavelength;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess) {
  try {
    mTypeOfGeneratingProcess = typeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setBackgroundProcess(T::UInt8_opt backgroundProcess) {
  try {
    mBackgroundProcess = backgroundProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setGeneratingProcessIdentifier(T::UInt8_opt generatingProcessIdentifier) {
  try {
    mGeneratingProcessIdentifier = generatingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setHoursAfterDataCutoff(T::UInt16_opt hoursAfterDataCutoff) {
  try {
    mHoursAfterDataCutoff = hoursAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setMinutesAfterDataCutoff(T::UInt8_opt minutesAfterDataCutoff) {
  try {
    mMinutesAfterDataCutoff = minutesAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setIndicatorOfUnitOfTimeRange(T::UInt8_opt indicatorOfUnitOfTimeRange) {
  try {
    mIndicatorOfUnitOfTimeRange = indicatorOfUnitOfTimeRange;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void ParameterAerosolOpticalSettings::setForecastTime(T::Int32_opt forecastTime) {
  try {
    mForecastTime = forecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
