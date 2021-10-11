// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ParameterAerosolSettingsImpl.*' files.
// ***********************************************************************

#include "ParameterAerosolSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

ParameterAerosolSettings::ParameterAerosolSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

ParameterAerosolSettings::~ParameterAerosolSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ParameterAerosolSettings::read(MemoryReader &memoryReader) {
  try {
    mParameterCategory = memoryReader.read_UInt8_opt();
    mParameterNumber = memoryReader.read_UInt8_opt();
    mAerosolType = memoryReader.read_UInt16_opt();
    mTypeOfSizeInterval = memoryReader.read_UInt8_opt();
    mScaleFactorOfFirstSize = memoryReader.read_Int8_opt();
    mScaledValueOfFirstSize = memoryReader.read_Int32_opt();
    mScaleFactorOfSecondSize = memoryReader.read_Int8_opt();
    mScaledValueOfSecondSize = memoryReader.read_Int32_opt();
    mTypeOfGeneratingProcess = memoryReader.read_UInt8_opt();
    mBackgroundProcess = memoryReader.read_UInt8_opt();
    mGeneratingProcessIdentifier = memoryReader.read_UInt8_opt();
    mHoursAfterDataCutoff = memoryReader.read_UInt16_opt();
    mMinutesAfterDataCutoff = memoryReader.read_UInt8_opt();
    mIndicatorOfUnitOfTimeRange = memoryReader.read_UInt8_opt();
    mForecastTime = memoryReader.read_Int32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void ParameterAerosolSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mParameterCategory;
    dataWriter << mParameterNumber;
    dataWriter << mAerosolType;
    dataWriter << mTypeOfSizeInterval;
    dataWriter << mScaleFactorOfFirstSize;
    dataWriter << mScaledValueOfFirstSize;
    dataWriter << mScaleFactorOfSecondSize;
    dataWriter << mScaledValueOfSecondSize;
    dataWriter << mTypeOfGeneratingProcess;
    dataWriter << mBackgroundProcess;
    dataWriter << mGeneratingProcessIdentifier;
    dataWriter << mHoursAfterDataCutoff;
    dataWriter << mMinutesAfterDataCutoff;
    dataWriter << mIndicatorOfUnitOfTimeRange;
    dataWriter << mForecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ParameterAerosolSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sParameterAerosolSettings.ParameterCategory", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterCategory));
    sprintf(name, "%sParameterAerosolSettings.ParameterNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterNumber));
    sprintf(name, "%sParameterAerosolSettings.AerosolType", prefix.c_str());
    attributeList.addAttribute(name, toString(mAerosolType));
    sprintf(name, "%sParameterAerosolSettings.TypeOfSizeInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfSizeInterval));
    sprintf(name, "%sParameterAerosolSettings.ScaleFactorOfFirstSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfFirstSize));
    sprintf(name, "%sParameterAerosolSettings.ScaledValueOfFirstSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfFirstSize));
    sprintf(name, "%sParameterAerosolSettings.ScaleFactorOfSecondSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfSecondSize));
    sprintf(name, "%sParameterAerosolSettings.ScaledValueOfSecondSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfSecondSize));
    sprintf(name, "%sParameterAerosolSettings.TypeOfGeneratingProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfGeneratingProcess));
    sprintf(name, "%sParameterAerosolSettings.BackgroundProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mBackgroundProcess));
    sprintf(name, "%sParameterAerosolSettings.GeneratingProcessIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mGeneratingProcessIdentifier));
    sprintf(name, "%sParameterAerosolSettings.HoursAfterDataCutoff", prefix.c_str());
    attributeList.addAttribute(name, toString(mHoursAfterDataCutoff));
    sprintf(name, "%sParameterAerosolSettings.MinutesAfterDataCutoff", prefix.c_str());
    attributeList.addAttribute(name, toString(mMinutesAfterDataCutoff));
    sprintf(name, "%sParameterAerosolSettings.IndicatorOfUnitOfTimeRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mIndicatorOfUnitOfTimeRange));
    sprintf(name, "%sParameterAerosolSettings.ForecastTime", prefix.c_str());
    attributeList.addAttribute(name, toString(mForecastTime));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool ParameterAerosolSettings::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
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
    if (strcasecmp(attributeName, "AerosolType") == 0) {
      attributeValue = toString(mAerosolType);
      return true;
    }
    if (strcasecmp(attributeName, "TypeOfSizeInterval") == 0) {
      attributeValue = toString(mTypeOfSizeInterval);
      return true;
    }
    if (strcasecmp(attributeName, "ScaleFactorOfFirstSize") == 0) {
      attributeValue = toString(mScaleFactorOfFirstSize);
      return true;
    }
    if (strcasecmp(attributeName, "ScaledValueOfFirstSize") == 0) {
      attributeValue = toString(mScaledValueOfFirstSize);
      return true;
    }
    if (strcasecmp(attributeName, "ScaleFactorOfSecondSize") == 0) {
      attributeValue = toString(mScaleFactorOfSecondSize);
      return true;
    }
    if (strcasecmp(attributeName, "ScaledValueOfSecondSize") == 0) {
      attributeValue = toString(mScaledValueOfSecondSize);
      return true;
    }
    if (strcasecmp(attributeName, "TypeOfGeneratingProcess") == 0) {
      attributeValue = toString(mTypeOfGeneratingProcess);
      return true;
    }
    if (strcasecmp(attributeName, "BackgroundProcess") == 0) {
      attributeValue = toString(mBackgroundProcess);
      return true;
    }
    if (strcasecmp(attributeName, "GeneratingProcessIdentifier") == 0) {
      attributeValue = toString(mGeneratingProcessIdentifier);
      return true;
    }
    if (strcasecmp(attributeName, "HoursAfterDataCutoff") == 0) {
      attributeValue = toString(mHoursAfterDataCutoff);
      return true;
    }
    if (strcasecmp(attributeName, "MinutesAfterDataCutoff") == 0) {
      attributeValue = toString(mMinutesAfterDataCutoff);
      return true;
    }
    if (strcasecmp(attributeName, "IndicatorOfUnitOfTimeRange") == 0) {
      attributeValue = toString(mIndicatorOfUnitOfTimeRange);
      return true;
    }
    if (strcasecmp(attributeName, "ForecastTime") == 0) {
      attributeValue = toString(mForecastTime);
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

bool ParameterAerosolSettings::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "ParameterCategory") == 0 && strcasecmp(attributeValue, toString(mParameterCategory).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ParameterNumber") == 0 && strcasecmp(attributeValue, toString(mParameterNumber).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "AerosolType") == 0 && strcasecmp(attributeValue, toString(mAerosolType).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "TypeOfSizeInterval") == 0 && strcasecmp(attributeValue, toString(mTypeOfSizeInterval).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaleFactorOfFirstSize") == 0 && strcasecmp(attributeValue, toString(mScaleFactorOfFirstSize).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaledValueOfFirstSize") == 0 && strcasecmp(attributeValue, toString(mScaledValueOfFirstSize).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaleFactorOfSecondSize") == 0 && strcasecmp(attributeValue, toString(mScaleFactorOfSecondSize).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaledValueOfSecondSize") == 0 && strcasecmp(attributeValue, toString(mScaledValueOfSecondSize).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "TypeOfGeneratingProcess") == 0 && strcasecmp(attributeValue, toString(mTypeOfGeneratingProcess).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "BackgroundProcess") == 0 && strcasecmp(attributeValue, toString(mBackgroundProcess).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "GeneratingProcessIdentifier") == 0 && strcasecmp(attributeValue, toString(mGeneratingProcessIdentifier).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "HoursAfterDataCutoff") == 0 && strcasecmp(attributeValue, toString(mHoursAfterDataCutoff).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "MinutesAfterDataCutoff") == 0 && strcasecmp(attributeValue, toString(mMinutesAfterDataCutoff).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "IndicatorOfUnitOfTimeRange") == 0 && strcasecmp(attributeValue, toString(mIndicatorOfUnitOfTimeRange).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ForecastTime") == 0 && strcasecmp(attributeValue, toString(mForecastTime).c_str()) == 0)
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

void ParameterAerosolSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ParameterAerosolSettings\n";
    stream << space(level) << "- ParameterCategory = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- ParameterNumber = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- AerosolType = " << toString(mAerosolType) << "\n";
    stream << space(level) << "- TypeOfSizeInterval = " << toString(mTypeOfSizeInterval) << "\n";
    stream << space(level) << "- ScaleFactorOfFirstSize = " << toString(mScaleFactorOfFirstSize) << "\n";
    stream << space(level) << "- ScaledValueOfFirstSize = " << toString(mScaledValueOfFirstSize) << "\n";
    stream << space(level) << "- ScaleFactorOfSecondSize = " << toString(mScaleFactorOfSecondSize) << "\n";
    stream << space(level) << "- ScaledValueOfSecondSize = " << toString(mScaledValueOfSecondSize) << "\n";
    stream << space(level) << "- TypeOfGeneratingProcess = " << toString(mTypeOfGeneratingProcess) << "\n";
    stream << space(level) << "- BackgroundProcess = " << toString(mBackgroundProcess) << "\n";
    stream << space(level) << "- GeneratingProcessIdentifier = " << toString(mGeneratingProcessIdentifier) << "\n";
    stream << space(level) << "- HoursAfterDataCutoff = " << toString(mHoursAfterDataCutoff) << "\n";
    stream << space(level) << "- MinutesAfterDataCutoff = " << toString(mMinutesAfterDataCutoff) << "\n";
    stream << space(level) << "- IndicatorOfUnitOfTimeRange = " << toString(mIndicatorOfUnitOfTimeRange) << "\n";
    stream << space(level) << "- ForecastTime = " << toString(mForecastTime) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ParameterAerosolSettings::countHash() const {
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterCategory} attribute. */

const T::UInt8_opt &ParameterAerosolSettings::getParameterCategory() const {
  try {
    return mParameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterNumber} attribute. */

const T::UInt8_opt &ParameterAerosolSettings::getParameterNumber() const {
  try {
    return mParameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mAerosolType} attribute. */

const T::UInt16_opt &ParameterAerosolSettings::getAerosolType() const {
  try {
    return mAerosolType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfSizeInterval} attribute. */

const T::UInt8_opt &ParameterAerosolSettings::getTypeOfSizeInterval() const {
  try {
    return mTypeOfSizeInterval;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfFirstSize} attribute. */

const T::Int8_opt &ParameterAerosolSettings::getScaleFactorOfFirstSize() const {
  try {
    return mScaleFactorOfFirstSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfFirstSize} attribute. */

const T::Int32_opt &ParameterAerosolSettings::getScaledValueOfFirstSize() const {
  try {
    return mScaledValueOfFirstSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfSecondSize} attribute. */

const T::Int8_opt &ParameterAerosolSettings::getScaleFactorOfSecondSize() const {
  try {
    return mScaleFactorOfSecondSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfSecondSize} attribute. */

const T::Int32_opt &ParameterAerosolSettings::getScaledValueOfSecondSize() const {
  try {
    return mScaledValueOfSecondSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfGeneratingProcess} attribute. */

const T::UInt8_opt &ParameterAerosolSettings::getTypeOfGeneratingProcess() const {
  try {
    return mTypeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mBackgroundProcess} attribute. */

const T::UInt8_opt &ParameterAerosolSettings::getBackgroundProcess() const {
  try {
    return mBackgroundProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mGeneratingProcessIdentifier} attribute. */

const T::UInt8_opt &ParameterAerosolSettings::getGeneratingProcessIdentifier() const {
  try {
    return mGeneratingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mHoursAfterDataCutoff} attribute. */

const T::UInt16_opt &ParameterAerosolSettings::getHoursAfterDataCutoff() const {
  try {
    return mHoursAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mMinutesAfterDataCutoff} attribute. */

const T::UInt8_opt &ParameterAerosolSettings::getMinutesAfterDataCutoff() const {
  try {
    return mMinutesAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mIndicatorOfUnitOfTimeRange} attribute. */

const T::UInt8_opt &ParameterAerosolSettings::getIndicatorOfUnitOfTimeRange() const {
  try {
    return mIndicatorOfUnitOfTimeRange;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mForecastTime} attribute. */

const T::Int32_opt &ParameterAerosolSettings::getForecastTime() const {
  try {
    return mForecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setParameterCategory(T::UInt8_opt parameterCategory) {
  try {
    mParameterCategory = parameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setParameterNumber(T::UInt8_opt parameterNumber) {
  try {
    mParameterNumber = parameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setAerosolType(T::UInt16_opt aerosolType) {
  try {
    mAerosolType = aerosolType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setTypeOfSizeInterval(T::UInt8_opt typeOfSizeInterval) {
  try {
    mTypeOfSizeInterval = typeOfSizeInterval;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setScaleFactorOfFirstSize(T::Int8_opt scaleFactorOfFirstSize) {
  try {
    mScaleFactorOfFirstSize = scaleFactorOfFirstSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setScaledValueOfFirstSize(T::Int32_opt scaledValueOfFirstSize) {
  try {
    mScaledValueOfFirstSize = scaledValueOfFirstSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setScaleFactorOfSecondSize(T::Int8_opt scaleFactorOfSecondSize) {
  try {
    mScaleFactorOfSecondSize = scaleFactorOfSecondSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setScaledValueOfSecondSize(T::Int32_opt scaledValueOfSecondSize) {
  try {
    mScaledValueOfSecondSize = scaledValueOfSecondSize;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess) {
  try {
    mTypeOfGeneratingProcess = typeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setBackgroundProcess(T::UInt8_opt backgroundProcess) {
  try {
    mBackgroundProcess = backgroundProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setGeneratingProcessIdentifier(T::UInt8_opt generatingProcessIdentifier) {
  try {
    mGeneratingProcessIdentifier = generatingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setHoursAfterDataCutoff(T::UInt16_opt hoursAfterDataCutoff) {
  try {
    mHoursAfterDataCutoff = hoursAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setMinutesAfterDataCutoff(T::UInt8_opt minutesAfterDataCutoff) {
  try {
    mMinutesAfterDataCutoff = minutesAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setIndicatorOfUnitOfTimeRange(T::UInt8_opt indicatorOfUnitOfTimeRange) {
  try {
    mIndicatorOfUnitOfTimeRange = indicatorOfUnitOfTimeRange;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ParameterAerosolSettings::setForecastTime(T::Int32_opt forecastTime) {
  try {
    mForecastTime = forecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
