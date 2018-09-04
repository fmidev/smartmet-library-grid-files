// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ReforecastSettingsImpl.*' files.
// ***********************************************************************

#include "ReforecastSettings.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

ReforecastSettings::ReforecastSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The copy constructor of the class. */

ReforecastSettings::ReforecastSettings(const ReforecastSettings &other) {
  try {
    mYearOfModelVersion = other.mYearOfModelVersion;
    mMonthOfModelVersion = other.mMonthOfModelVersion;
    mDayOfModelVersion = other.mDayOfModelVersion;
    mHourOfModelVersion = other.mHourOfModelVersion;
    mMinuteOfModelVersion = other.mMinuteOfModelVersion;
    mSecondOfModelVersion = other.mSecondOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

ReforecastSettings::~ReforecastSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ReforecastSettings::read(MemoryReader &memoryReader) {
  try {
    mYearOfModelVersion = memoryReader.read_UInt16_opt();
    mMonthOfModelVersion = memoryReader.read_UInt8_opt();
    mDayOfModelVersion = memoryReader.read_UInt8_opt();
    mHourOfModelVersion = memoryReader.read_UInt8_opt();
    mMinuteOfModelVersion = memoryReader.read_UInt8_opt();
    mSecondOfModelVersion = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void ReforecastSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mYearOfModelVersion;
    dataWriter << mMonthOfModelVersion;
    dataWriter << mDayOfModelVersion;
    dataWriter << mHourOfModelVersion;
    dataWriter << mMinuteOfModelVersion;
    dataWriter << mSecondOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ReforecastSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sReforecastSettings.YearOfModelVersion", prefix.c_str());
    attributeList.addAttribute(name, toString(mYearOfModelVersion));
    sprintf(name, "%sReforecastSettings.MonthOfModelVersion", prefix.c_str());
    attributeList.addAttribute(name, toString(mMonthOfModelVersion));
    sprintf(name, "%sReforecastSettings.DayOfModelVersion", prefix.c_str());
    attributeList.addAttribute(name, toString(mDayOfModelVersion));
    sprintf(name, "%sReforecastSettings.HourOfModelVersion", prefix.c_str());
    attributeList.addAttribute(name, toString(mHourOfModelVersion));
    sprintf(name, "%sReforecastSettings.MinuteOfModelVersion", prefix.c_str());
    attributeList.addAttribute(name, toString(mMinuteOfModelVersion));
    sprintf(name, "%sReforecastSettings.SecondOfModelVersion", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecondOfModelVersion));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ReforecastSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ReforecastSettings\n";
    stream << space(level) << "- YearOfModelVersion = " << toString(mYearOfModelVersion) << "\n";
    stream << space(level) << "- MonthOfModelVersion = " << toString(mMonthOfModelVersion) << "\n";
    stream << space(level) << "- DayOfModelVersion = " << toString(mDayOfModelVersion) << "\n";
    stream << space(level) << "- HourOfModelVersion = " << toString(mHourOfModelVersion) << "\n";
    stream << space(level) << "- MinuteOfModelVersion = " << toString(mMinuteOfModelVersion) << "\n";
    stream << space(level) << "- SecondOfModelVersion = " << toString(mSecondOfModelVersion) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ReforecastSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mYearOfModelVersion)
      boost::hash_combine(seed, *mYearOfModelVersion);
    if (mMonthOfModelVersion)
      boost::hash_combine(seed, *mMonthOfModelVersion);
    if (mDayOfModelVersion)
      boost::hash_combine(seed, *mDayOfModelVersion);
    if (mHourOfModelVersion)
      boost::hash_combine(seed, *mHourOfModelVersion);
    if (mMinuteOfModelVersion)
      boost::hash_combine(seed, *mMinuteOfModelVersion);
    if (mSecondOfModelVersion)
      boost::hash_combine(seed, *mSecondOfModelVersion);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mYearOfModelVersion} attribute. */

const T::UInt16_opt &ReforecastSettings::getYearOfModelVersion() const {
  try {
    return mYearOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mMonthOfModelVersion} attribute. */

const T::UInt8_opt &ReforecastSettings::getMonthOfModelVersion() const {
  try {
    return mMonthOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mDayOfModelVersion} attribute. */

const T::UInt8_opt &ReforecastSettings::getDayOfModelVersion() const {
  try {
    return mDayOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mHourOfModelVersion} attribute. */

const T::UInt8_opt &ReforecastSettings::getHourOfModelVersion() const {
  try {
    return mHourOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mMinuteOfModelVersion} attribute. */

const T::UInt8_opt &ReforecastSettings::getMinuteOfModelVersion() const {
  try {
    return mMinuteOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mSecondOfModelVersion} attribute. */

const T::UInt8_opt &ReforecastSettings::getSecondOfModelVersion() const {
  try {
    return mSecondOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void ReforecastSettings::setYearOfModelVersion(T::UInt16_opt yearOfModelVersion) {
  try {
    mYearOfModelVersion = yearOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void ReforecastSettings::setMonthOfModelVersion(T::UInt8_opt monthOfModelVersion) {
  try {
    mMonthOfModelVersion = monthOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void ReforecastSettings::setDayOfModelVersion(T::UInt8_opt dayOfModelVersion) {
  try {
    mDayOfModelVersion = dayOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void ReforecastSettings::setHourOfModelVersion(T::UInt8_opt hourOfModelVersion) {
  try {
    mHourOfModelVersion = hourOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void ReforecastSettings::setMinuteOfModelVersion(T::UInt8_opt minuteOfModelVersion) {
  try {
    mMinuteOfModelVersion = minuteOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void ReforecastSettings::setSecondOfModelVersion(T::UInt8_opt secondOfModelVersion) {
  try {
    mSecondOfModelVersion = secondOfModelVersion;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
