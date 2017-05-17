// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeSectionImpl.*' files.
// ***********************************************************************

#include "grib2/definition/TimeSection.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeSection::TimeSection() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

TimeSection::~TimeSection() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current
   object.

        \param memoryReader  This object controls the access to the memory
   mapped file.
*/

void TimeSection::read(MemoryReader &memoryReader) {
  try {
    mNumberOfTimeSteps = memoryReader.read_UInt32_opt();
    mUnitOfOffsetFromReferenceTime = memoryReader.read_UInt8_opt();
    mOffsetFromReferenceOfFirstTime = memoryReader.read_UInt32_opt();
    mTypeOfTimeIncrement = memoryReader.read_UInt8_opt();
    mUnitOfTimeIncrement = memoryReader.read_UInt8_opt();
    mTimeIncrement = memoryReader.read_UInt32_opt();
    mYear = memoryReader.read_UInt16_opt();
    mMonth = memoryReader.read_UInt8_opt();
    mDay = memoryReader.read_UInt8_opt();
    mHour = memoryReader.read_UInt8_opt();
    mMinute = memoryReader.read_UInt8_opt();
    mSecond = memoryReader.read_UInt8_opt();
    mNumberOfVerticalPoints = memoryReader.read_UInt16_opt();
    mPhysicalMeaningOfVerticalCoordinate = memoryReader.read_UInt8_opt();
    mVerticalCoordinate = memoryReader.read_UInt8_opt();
    mNC = memoryReader.read_UInt16_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeSection::getAttributeList(std::string prefix,
                                   T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTimeSection.NumberOfTimeSteps", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfTimeSteps));
    sprintf(name, "%sTimeSection.UnitOfOffsetFromReferenceTime",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mUnitOfOffsetFromReferenceTime));
    sprintf(name, "%sTimeSection.OffsetFromReferenceOfFirstTime",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mOffsetFromReferenceOfFirstTime));
    sprintf(name, "%sTimeSection.TypeOfTimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfTimeIncrement));
    sprintf(name, "%sTimeSection.UnitOfTimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mUnitOfTimeIncrement));
    sprintf(name, "%sTimeSection.TimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mTimeIncrement));
    sprintf(name, "%sTimeSection.Year", prefix.c_str());
    attributeList.addAttribute(name, toString(mYear));
    sprintf(name, "%sTimeSection.Month", prefix.c_str());
    attributeList.addAttribute(name, toString(mMonth));
    sprintf(name, "%sTimeSection.Day", prefix.c_str());
    attributeList.addAttribute(name, toString(mDay));
    sprintf(name, "%sTimeSection.Hour", prefix.c_str());
    attributeList.addAttribute(name, toString(mHour));
    sprintf(name, "%sTimeSection.Minute", prefix.c_str());
    attributeList.addAttribute(name, toString(mMinute));
    sprintf(name, "%sTimeSection.Second", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecond));
    sprintf(name, "%sTimeSection.NumberOfVerticalPoints", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfVerticalPoints));
    sprintf(name, "%sTimeSection.PhysicalMeaningOfVerticalCoordinate",
            prefix.c_str());
    attributeList.addAttribute(name,
                               toString(mPhysicalMeaningOfVerticalCoordinate));
    sprintf(name, "%sTimeSection.VerticalCoordinate", prefix.c_str());
    attributeList.addAttribute(name, toString(mVerticalCoordinate));
    sprintf(name, "%sTimeSection.NC", prefix.c_str());
    attributeList.addAttribute(name, toString(mNC));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given
   stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level
   structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void TimeSection::print(std::ostream &stream, uint level,
                        uint optionFlags) const {
  try {
    stream << space(level) << "TimeSection\n";
    stream << space(level)
           << "- NumberOfTimeSteps = " << toString(mNumberOfTimeSteps) << "\n";
    stream << space(level) << "- UnitOfOffsetFromReferenceTime = "
           << toString(mUnitOfOffsetFromReferenceTime) << "\n";
    stream << space(level) << "- OffsetFromReferenceOfFirstTime = "
           << toString(mOffsetFromReferenceOfFirstTime) << "\n";
    stream << space(level)
           << "- TypeOfTimeIncrement = " << toString(mTypeOfTimeIncrement)
           << "\n";
    stream << space(level)
           << "- UnitOfTimeIncrement = " << toString(mUnitOfTimeIncrement)
           << "\n";
    stream << space(level) << "- TimeIncrement = " << toString(mTimeIncrement)
           << "\n";
    stream << space(level) << "- Year = " << toString(mYear) << "\n";
    stream << space(level) << "- Month = " << toString(mMonth) << "\n";
    stream << space(level) << "- Day = " << toString(mDay) << "\n";
    stream << space(level) << "- Hour = " << toString(mHour) << "\n";
    stream << space(level) << "- Minute = " << toString(mMinute) << "\n";
    stream << space(level) << "- Second = " << toString(mSecond) << "\n";
    stream << space(level)
           << "- NumberOfVerticalPoints = " << toString(mNumberOfVerticalPoints)
           << "\n";
    stream << space(level) << "- PhysicalMeaningOfVerticalCoordinate = "
           << toString(mPhysicalMeaningOfVerticalCoordinate) << "\n";
    stream << space(level)
           << "- VerticalCoordinate = " << toString(mVerticalCoordinate)
           << "\n";
    stream << space(level) << "- NC = " << toString(mNC) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeSection::countHash() {
  try {
    std::size_t seed = 0;
    if (mNumberOfTimeSteps)
      boost::hash_combine(seed, *mNumberOfTimeSteps);
    if (mUnitOfOffsetFromReferenceTime)
      boost::hash_combine(seed, *mUnitOfOffsetFromReferenceTime);
    if (mOffsetFromReferenceOfFirstTime)
      boost::hash_combine(seed, *mOffsetFromReferenceOfFirstTime);
    if (mTypeOfTimeIncrement)
      boost::hash_combine(seed, *mTypeOfTimeIncrement);
    if (mUnitOfTimeIncrement)
      boost::hash_combine(seed, *mUnitOfTimeIncrement);
    if (mTimeIncrement)
      boost::hash_combine(seed, *mTimeIncrement);
    if (mYear)
      boost::hash_combine(seed, *mYear);
    if (mMonth)
      boost::hash_combine(seed, *mMonth);
    if (mDay)
      boost::hash_combine(seed, *mDay);
    if (mHour)
      boost::hash_combine(seed, *mHour);
    if (mMinute)
      boost::hash_combine(seed, *mMinute);
    if (mSecond)
      boost::hash_combine(seed, *mSecond);
    if (mNumberOfVerticalPoints)
      boost::hash_combine(seed, *mNumberOfVerticalPoints);
    if (mPhysicalMeaningOfVerticalCoordinate)
      boost::hash_combine(seed, *mPhysicalMeaningOfVerticalCoordinate);
    if (mVerticalCoordinate)
      boost::hash_combine(seed, *mVerticalCoordinate);
    if (mNC)
      boost::hash_combine(seed, *mNC);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfTimeSteps}
 * attribute. */

const T::UInt32_opt &TimeSection::getNumberOfTimeSteps() const {
  try {
    return mNumberOfTimeSteps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mUnitOfOffsetFromReferenceTime} attribute. */

const T::UInt8_opt &TimeSection::getUnitOfOffsetFromReferenceTime() const {
  try {
    return mUnitOfOffsetFromReferenceTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mOffsetFromReferenceOfFirstTime} attribute. */

const T::UInt32_opt &TimeSection::getOffsetFromReferenceOfFirstTime() const {
  try {
    return mOffsetFromReferenceOfFirstTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfTimeIncrement}
 * attribute. */

const T::UInt8_opt &TimeSection::getTypeOfTimeIncrement() const {
  try {
    return mTypeOfTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mUnitOfTimeIncrement}
 * attribute. */

const T::UInt8_opt &TimeSection::getUnitOfTimeIncrement() const {
  try {
    return mUnitOfTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mTimeIncrement} attribute.
 */

const T::UInt32_opt &TimeSection::getTimeIncrement() const {
  try {
    return mTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mYear} attribute. */

const T::UInt16_opt &TimeSection::getYear() const {
  try {
    return mYear;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mMonth} attribute. */

const T::UInt8_opt &TimeSection::getMonth() const {
  try {
    return mMonth;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mDay} attribute. */

const T::UInt8_opt &TimeSection::getDay() const {
  try {
    return mDay;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mHour} attribute. */

const T::UInt8_opt &TimeSection::getHour() const {
  try {
    return mHour;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mMinute} attribute. */

const T::UInt8_opt &TimeSection::getMinute() const {
  try {
    return mMinute;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSecond} attribute. */

const T::UInt8_opt &TimeSection::getSecond() const {
  try {
    return mSecond;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfVerticalPoints}
 * attribute. */

const T::UInt16_opt &TimeSection::getNumberOfVerticalPoints() const {
  try {
    return mNumberOfVerticalPoints;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mPhysicalMeaningOfVerticalCoordinate} attribute. */

const T::UInt8_opt &
TimeSection::getPhysicalMeaningOfVerticalCoordinate() const {
  try {
    return mPhysicalMeaningOfVerticalCoordinate;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mVerticalCoordinate}
 * attribute. */

const T::UInt8_opt &TimeSection::getVerticalCoordinate() const {
  try {
    return mVerticalCoordinate;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNC} attribute. */

const T::UInt16_opt &TimeSection::getNC() const {
  try {
    return mNC;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
