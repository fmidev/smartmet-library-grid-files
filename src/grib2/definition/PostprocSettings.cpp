// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PostprocSettingsImpl.*' files.
// ***********************************************************************

#include "PostprocSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PostprocSettings::PostprocSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

PostprocSettings::~PostprocSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PostprocSettings::read(MemoryReader &memoryReader) {
  try {
    mParameterCategory = memoryReader.read_UInt8_opt();
    mParameterNumber = memoryReader.read_UInt8_opt();
    mInputProcessIdentifier = memoryReader.read_UInt16_opt();
    mInputOriginatingCentre = memoryReader.read_UInt16_opt();
    mTypeOfPostProcessing = memoryReader.read_UInt8_opt();
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

void PostprocSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mParameterCategory;
    dataWriter << mParameterNumber;
    dataWriter << mInputProcessIdentifier;
    dataWriter << mInputOriginatingCentre;
    dataWriter << mTypeOfPostProcessing;
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

void PostprocSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sPostprocSettings.ParameterCategory", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterCategory));
    sprintf(name, "%sPostprocSettings.ParameterNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterNumber));
    sprintf(name, "%sPostprocSettings.InputProcessIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mInputProcessIdentifier));
    sprintf(name, "%sPostprocSettings.InputOriginatingCentre", prefix.c_str());
    attributeList.addAttribute(name, toString(mInputOriginatingCentre));
    sprintf(name, "%sPostprocSettings.TypeOfPostProcessing", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfPostProcessing));
    sprintf(name, "%sPostprocSettings.TypeOfGeneratingProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfGeneratingProcess));
    sprintf(name, "%sPostprocSettings.BackgroundProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mBackgroundProcess));
    sprintf(name, "%sPostprocSettings.GeneratingProcessIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mGeneratingProcessIdentifier));
    sprintf(name, "%sPostprocSettings.HoursAfterDataCutoff", prefix.c_str());
    attributeList.addAttribute(name, toString(mHoursAfterDataCutoff));
    sprintf(name, "%sPostprocSettings.MinutesAfterDataCutoff", prefix.c_str());
    attributeList.addAttribute(name, toString(mMinutesAfterDataCutoff));
    sprintf(name, "%sPostprocSettings.IndicatorOfUnitOfTimeRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mIndicatorOfUnitOfTimeRange));
    sprintf(name, "%sPostprocSettings.ForecastTime", prefix.c_str());
    attributeList.addAttribute(name, toString(mForecastTime));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool PostprocSettings::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
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
    if (strcasecmp(attributeName, "InputProcessIdentifier") == 0) {
      attributeValue = toString(mInputProcessIdentifier);
      return true;
    }
    if (strcasecmp(attributeName, "InputOriginatingCentre") == 0) {
      attributeValue = toString(mInputOriginatingCentre);
      return true;
    }
    if (strcasecmp(attributeName, "TypeOfPostProcessing") == 0) {
      attributeValue = toString(mTypeOfPostProcessing);
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

bool PostprocSettings::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "ParameterCategory") == 0 && strcasecmp(attributeValue, toString(mParameterCategory).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ParameterNumber") == 0 && strcasecmp(attributeValue, toString(mParameterNumber).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "InputProcessIdentifier") == 0 && strcasecmp(attributeValue, toString(mInputProcessIdentifier).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "InputOriginatingCentre") == 0 && strcasecmp(attributeValue, toString(mInputOriginatingCentre).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "TypeOfPostProcessing") == 0 && strcasecmp(attributeValue, toString(mTypeOfPostProcessing).c_str()) == 0)
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

void PostprocSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "PostprocSettings\n";
    stream << space(level) << "- ParameterCategory = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- ParameterNumber = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- InputProcessIdentifier = " << toString(mInputProcessIdentifier) << "\n";
    stream << space(level) << "- InputOriginatingCentre = " << toString(mInputOriginatingCentre) << "\n";
    stream << space(level) << "- TypeOfPostProcessing = " << toString(mTypeOfPostProcessing) << "\n";
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

T::Hash PostprocSettings::countHash() const {
  try {
    std::size_t seed = 0;
    if (mParameterCategory)
      boost::hash_combine(seed, *mParameterCategory);
    if (mParameterNumber)
      boost::hash_combine(seed, *mParameterNumber);
    if (mInputProcessIdentifier)
      boost::hash_combine(seed, *mInputProcessIdentifier);
    if (mInputOriginatingCentre)
      boost::hash_combine(seed, *mInputOriginatingCentre);
    if (mTypeOfPostProcessing)
      boost::hash_combine(seed, *mTypeOfPostProcessing);
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

const T::UInt8_opt &PostprocSettings::getParameterCategory() const {
  try {
    return mParameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterNumber} attribute. */

const T::UInt8_opt &PostprocSettings::getParameterNumber() const {
  try {
    return mParameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mInputProcessIdentifier} attribute. */

const T::UInt16_opt &PostprocSettings::getInputProcessIdentifier() const {
  try {
    return mInputProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mInputOriginatingCentre} attribute. */

const T::UInt16_opt &PostprocSettings::getInputOriginatingCentre() const {
  try {
    return mInputOriginatingCentre;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfPostProcessing} attribute. */

const T::UInt8_opt &PostprocSettings::getTypeOfPostProcessing() const {
  try {
    return mTypeOfPostProcessing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfGeneratingProcess} attribute. */

const T::UInt8_opt &PostprocSettings::getTypeOfGeneratingProcess() const {
  try {
    return mTypeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mBackgroundProcess} attribute. */

const T::UInt8_opt &PostprocSettings::getBackgroundProcess() const {
  try {
    return mBackgroundProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mGeneratingProcessIdentifier} attribute. */

const T::UInt8_opt &PostprocSettings::getGeneratingProcessIdentifier() const {
  try {
    return mGeneratingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mHoursAfterDataCutoff} attribute. */

const T::UInt16_opt &PostprocSettings::getHoursAfterDataCutoff() const {
  try {
    return mHoursAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mMinutesAfterDataCutoff} attribute. */

const T::UInt8_opt &PostprocSettings::getMinutesAfterDataCutoff() const {
  try {
    return mMinutesAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mIndicatorOfUnitOfTimeRange} attribute. */

const T::UInt8_opt &PostprocSettings::getIndicatorOfUnitOfTimeRange() const {
  try {
    return mIndicatorOfUnitOfTimeRange;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mForecastTime} attribute. */

const T::Int32_opt &PostprocSettings::getForecastTime() const {
  try {
    return mForecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setParameterCategory(T::UInt8_opt parameterCategory) {
  try {
    mParameterCategory = parameterCategory;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setParameterNumber(T::UInt8_opt parameterNumber) {
  try {
    mParameterNumber = parameterNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setInputProcessIdentifier(T::UInt16_opt inputProcessIdentifier) {
  try {
    mInputProcessIdentifier = inputProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setInputOriginatingCentre(T::UInt16_opt inputOriginatingCentre) {
  try {
    mInputOriginatingCentre = inputOriginatingCentre;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setTypeOfPostProcessing(T::UInt8_opt typeOfPostProcessing) {
  try {
    mTypeOfPostProcessing = typeOfPostProcessing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess) {
  try {
    mTypeOfGeneratingProcess = typeOfGeneratingProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setBackgroundProcess(T::UInt8_opt backgroundProcess) {
  try {
    mBackgroundProcess = backgroundProcess;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setGeneratingProcessIdentifier(T::UInt8_opt generatingProcessIdentifier) {
  try {
    mGeneratingProcessIdentifier = generatingProcessIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setHoursAfterDataCutoff(T::UInt16_opt hoursAfterDataCutoff) {
  try {
    mHoursAfterDataCutoff = hoursAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setMinutesAfterDataCutoff(T::UInt8_opt minutesAfterDataCutoff) {
  try {
    mMinutesAfterDataCutoff = minutesAfterDataCutoff;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setIndicatorOfUnitOfTimeRange(T::UInt8_opt indicatorOfUnitOfTimeRange) {
  try {
    mIndicatorOfUnitOfTimeRange = indicatorOfUnitOfTimeRange;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PostprocSettings::setForecastTime(T::Int32_opt forecastTime) {
  try {
    mForecastTime = forecastTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
