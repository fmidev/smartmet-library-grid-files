// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StatisticalSettingsImpl.*' files.
// ***********************************************************************

#include "grib2/definition/StatisticalSettings.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

StatisticalSettings::StatisticalSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

StatisticalSettings::~StatisticalSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void StatisticalSettings::read(MemoryReader &memoryReader) {
  try {
    mYearOfEndOfOverallTimeInterval = memoryReader.read_UInt16_opt();
    mMonthOfEndOfOverallTimeInterval = memoryReader.read_UInt8_opt();
    mDayOfEndOfOverallTimeInterval = memoryReader.read_UInt8_opt();
    mHourOfEndOfOverallTimeInterval = memoryReader.read_UInt8_opt();
    mMinuteOfEndOfOverallTimeInterval = memoryReader.read_UInt8_opt();
    mSecondOfEndOfOverallTimeInterval = memoryReader.read_UInt8_opt();
    mNumberOfTimeRange = memoryReader.read_UInt8_opt();
    mNumberOfMissingInStatisticalProcess = memoryReader.read_UInt32_opt();
    mTypeOfStatisticalProcessing = memoryReader.read_UInt8_opt();
    mTypeOfTimeIncrement = memoryReader.read_UInt8_opt();
    mIndicatorOfUnitForTimeRange = memoryReader.read_UInt8_opt();
    mLengthOfTimeRange = memoryReader.read_UInt32_opt();
    mIndicatorOfUnitForTimeIncrement = memoryReader.read_UInt8_opt();
    mTimeIncrement = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void StatisticalSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sStatisticalSettings.YearOfEndOfOverallTimeInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mYearOfEndOfOverallTimeInterval));
    sprintf(name, "%sStatisticalSettings.MonthOfEndOfOverallTimeInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mMonthOfEndOfOverallTimeInterval));
    sprintf(name, "%sStatisticalSettings.DayOfEndOfOverallTimeInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mDayOfEndOfOverallTimeInterval));
    sprintf(name, "%sStatisticalSettings.HourOfEndOfOverallTimeInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mHourOfEndOfOverallTimeInterval));
    sprintf(name, "%sStatisticalSettings.MinuteOfEndOfOverallTimeInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mMinuteOfEndOfOverallTimeInterval));
    sprintf(name, "%sStatisticalSettings.SecondOfEndOfOverallTimeInterval", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecondOfEndOfOverallTimeInterval));
    sprintf(name, "%sStatisticalSettings.NumberOfTimeRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfTimeRange));
    sprintf(name, "%sStatisticalSettings.NumberOfMissingInStatisticalProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfMissingInStatisticalProcess));
    sprintf(name, "%sStatisticalSettings.TypeOfStatisticalProcessing", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfStatisticalProcessing));
    sprintf(name, "%sStatisticalSettings.TypeOfTimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfTimeIncrement));
    sprintf(name, "%sStatisticalSettings.IndicatorOfUnitForTimeRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mIndicatorOfUnitForTimeRange));
    sprintf(name, "%sStatisticalSettings.LengthOfTimeRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mLengthOfTimeRange));
    sprintf(name, "%sStatisticalSettings.IndicatorOfUnitForTimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mIndicatorOfUnitForTimeIncrement));
    sprintf(name, "%sStatisticalSettings.TimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mTimeIncrement));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void StatisticalSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "StatisticalSettings\n";
    stream << space(level) << "- YearOfEndOfOverallTimeInterval = " << toString(mYearOfEndOfOverallTimeInterval) << "\n";
    stream << space(level) << "- MonthOfEndOfOverallTimeInterval = " << toString(mMonthOfEndOfOverallTimeInterval) << "\n";
    stream << space(level) << "- DayOfEndOfOverallTimeInterval = " << toString(mDayOfEndOfOverallTimeInterval) << "\n";
    stream << space(level) << "- HourOfEndOfOverallTimeInterval = " << toString(mHourOfEndOfOverallTimeInterval) << "\n";
    stream << space(level) << "- MinuteOfEndOfOverallTimeInterval = " << toString(mMinuteOfEndOfOverallTimeInterval) << "\n";
    stream << space(level) << "- SecondOfEndOfOverallTimeInterval = " << toString(mSecondOfEndOfOverallTimeInterval) << "\n";
    stream << space(level) << "- NumberOfTimeRange = " << toString(mNumberOfTimeRange) << "\n";
    stream << space(level) << "- NumberOfMissingInStatisticalProcess = " << toString(mNumberOfMissingInStatisticalProcess) << "\n";
    stream << space(level) << "- TypeOfStatisticalProcessing = " << toString(mTypeOfStatisticalProcessing) << "\n";
    stream << space(level) << "- TypeOfTimeIncrement = " << toString(mTypeOfTimeIncrement) << "\n";
    stream << space(level) << "- IndicatorOfUnitForTimeRange = " << toString(mIndicatorOfUnitForTimeRange) << "\n";
    stream << space(level) << "- LengthOfTimeRange = " << toString(mLengthOfTimeRange) << "\n";
    stream << space(level) << "- IndicatorOfUnitForTimeIncrement = " << toString(mIndicatorOfUnitForTimeIncrement) << "\n";
    stream << space(level) << "- TimeIncrement = " << toString(mTimeIncrement) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash StatisticalSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mYearOfEndOfOverallTimeInterval)
      boost::hash_combine(seed, *mYearOfEndOfOverallTimeInterval);
    if (mMonthOfEndOfOverallTimeInterval)
      boost::hash_combine(seed, *mMonthOfEndOfOverallTimeInterval);
    if (mDayOfEndOfOverallTimeInterval)
      boost::hash_combine(seed, *mDayOfEndOfOverallTimeInterval);
    if (mHourOfEndOfOverallTimeInterval)
      boost::hash_combine(seed, *mHourOfEndOfOverallTimeInterval);
    if (mMinuteOfEndOfOverallTimeInterval)
      boost::hash_combine(seed, *mMinuteOfEndOfOverallTimeInterval);
    if (mSecondOfEndOfOverallTimeInterval)
      boost::hash_combine(seed, *mSecondOfEndOfOverallTimeInterval);
    if (mNumberOfTimeRange)
      boost::hash_combine(seed, *mNumberOfTimeRange);
    if (mNumberOfMissingInStatisticalProcess)
      boost::hash_combine(seed, *mNumberOfMissingInStatisticalProcess);
    if (mTypeOfStatisticalProcessing)
      boost::hash_combine(seed, *mTypeOfStatisticalProcessing);
    if (mTypeOfTimeIncrement)
      boost::hash_combine(seed, *mTypeOfTimeIncrement);
    if (mIndicatorOfUnitForTimeRange)
      boost::hash_combine(seed, *mIndicatorOfUnitForTimeRange);
    if (mLengthOfTimeRange)
      boost::hash_combine(seed, *mLengthOfTimeRange);
    if (mIndicatorOfUnitForTimeIncrement)
      boost::hash_combine(seed, *mIndicatorOfUnitForTimeIncrement);
    if (mTimeIncrement)
      boost::hash_combine(seed, *mTimeIncrement);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mYearOfEndOfOverallTimeInterval} attribute. */

const T::UInt16_opt &StatisticalSettings::getYearOfEndOfOverallTimeInterval() const {
  try {
    return mYearOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mMonthOfEndOfOverallTimeInterval} attribute. */

const T::UInt8_opt &StatisticalSettings::getMonthOfEndOfOverallTimeInterval() const {
  try {
    return mMonthOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mDayOfEndOfOverallTimeInterval} attribute. */

const T::UInt8_opt &StatisticalSettings::getDayOfEndOfOverallTimeInterval() const {
  try {
    return mDayOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mHourOfEndOfOverallTimeInterval} attribute. */

const T::UInt8_opt &StatisticalSettings::getHourOfEndOfOverallTimeInterval() const {
  try {
    return mHourOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mMinuteOfEndOfOverallTimeInterval} attribute. */

const T::UInt8_opt &StatisticalSettings::getMinuteOfEndOfOverallTimeInterval() const {
  try {
    return mMinuteOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mSecondOfEndOfOverallTimeInterval} attribute. */

const T::UInt8_opt &StatisticalSettings::getSecondOfEndOfOverallTimeInterval() const {
  try {
    return mSecondOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfTimeRange} attribute. */

const T::UInt8_opt &StatisticalSettings::getNumberOfTimeRange() const {
  try {
    return mNumberOfTimeRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfMissingInStatisticalProcess} attribute. */

const T::UInt32_opt &StatisticalSettings::getNumberOfMissingInStatisticalProcess() const {
  try {
    return mNumberOfMissingInStatisticalProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfStatisticalProcessing} attribute. */

const T::UInt8_opt &StatisticalSettings::getTypeOfStatisticalProcessing() const {
  try {
    return mTypeOfStatisticalProcessing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfTimeIncrement} attribute. */

const T::UInt8_opt &StatisticalSettings::getTypeOfTimeIncrement() const {
  try {
    return mTypeOfTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mIndicatorOfUnitForTimeRange} attribute. */

const T::UInt8_opt &StatisticalSettings::getIndicatorOfUnitForTimeRange() const {
  try {
    return mIndicatorOfUnitForTimeRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLengthOfTimeRange} attribute. */

const T::UInt32_opt &StatisticalSettings::getLengthOfTimeRange() const {
  try {
    return mLengthOfTimeRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mIndicatorOfUnitForTimeIncrement} attribute. */

const T::UInt8_opt &StatisticalSettings::getIndicatorOfUnitForTimeIncrement() const {
  try {
    return mIndicatorOfUnitForTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTimeIncrement} attribute. */

const T::UInt32_opt &StatisticalSettings::getTimeIncrement() const {
  try {
    return mTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setYearOfEndOfOverallTimeInterval(T::UInt16_opt yearOfEndOfOverallTimeInterval) {
  try {
    mYearOfEndOfOverallTimeInterval = yearOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setMonthOfEndOfOverallTimeInterval(T::UInt8_opt monthOfEndOfOverallTimeInterval) {
  try {
    mMonthOfEndOfOverallTimeInterval = monthOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setDayOfEndOfOverallTimeInterval(T::UInt8_opt dayOfEndOfOverallTimeInterval) {
  try {
    mDayOfEndOfOverallTimeInterval = dayOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setHourOfEndOfOverallTimeInterval(T::UInt8_opt hourOfEndOfOverallTimeInterval) {
  try {
    mHourOfEndOfOverallTimeInterval = hourOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setMinuteOfEndOfOverallTimeInterval(T::UInt8_opt minuteOfEndOfOverallTimeInterval) {
  try {
    mMinuteOfEndOfOverallTimeInterval = minuteOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setSecondOfEndOfOverallTimeInterval(T::UInt8_opt secondOfEndOfOverallTimeInterval) {
  try {
    mSecondOfEndOfOverallTimeInterval = secondOfEndOfOverallTimeInterval;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setNumberOfTimeRange(T::UInt8_opt numberOfTimeRange) {
  try {
    mNumberOfTimeRange = numberOfTimeRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setNumberOfMissingInStatisticalProcess(T::UInt32_opt numberOfMissingInStatisticalProcess) {
  try {
    mNumberOfMissingInStatisticalProcess = numberOfMissingInStatisticalProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setTypeOfStatisticalProcessing(T::UInt8_opt typeOfStatisticalProcessing) {
  try {
    mTypeOfStatisticalProcessing = typeOfStatisticalProcessing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setTypeOfTimeIncrement(T::UInt8_opt typeOfTimeIncrement) {
  try {
    mTypeOfTimeIncrement = typeOfTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setIndicatorOfUnitForTimeRange(T::UInt8_opt indicatorOfUnitForTimeRange) {
  try {
    mIndicatorOfUnitForTimeRange = indicatorOfUnitForTimeRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setLengthOfTimeRange(T::UInt32_opt lengthOfTimeRange) {
  try {
    mLengthOfTimeRange = lengthOfTimeRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setIndicatorOfUnitForTimeIncrement(T::UInt8_opt indicatorOfUnitForTimeIncrement) {
  try {
    mIndicatorOfUnitForTimeIncrement = indicatorOfUnitForTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StatisticalSettings::setTimeIncrement(T::UInt32_opt timeIncrement) {
  try {
    mTimeIncrement = timeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
