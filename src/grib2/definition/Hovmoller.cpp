// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'HovmollerImpl.*' files.
// ***********************************************************************

#include "grib2/definition/Hovmoller.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

Hovmoller::Hovmoller() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

Hovmoller::~Hovmoller() {
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

void Hovmoller::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mBasicAngleOfTheInitialProductionDomain = memoryReader.read_UInt32_opt();
    mSubdivisionsOfBasicAngle = memoryReader.read_UInt32_opt();
    mLatitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfFirstGridPoint = memoryReader.read_UInt32_opt();
    mScanningMode.read(memoryReader);
    mLatitudeOfLastGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfLastGridPoint = memoryReader.read_UInt32_opt();
    mTypeOfHorizontalLine = memoryReader.read_UInt8_opt();
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
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Hovmoller::getAttributeList(std::string prefix,
                                 T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sHovmoller.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sHovmoller.BasicAngleOfTheInitialProductionDomain",
            prefix.c_str());
    attributeList.addAttribute(
        name, toString(mBasicAngleOfTheInitialProductionDomain));
    sprintf(name, "%sHovmoller.SubdivisionsOfBasicAngle", prefix.c_str());
    attributeList.addAttribute(name, toString(mSubdivisionsOfBasicAngle));
    sprintf(name, "%sHovmoller.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sHovmoller.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sHovmoller.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sHovmoller.LatitudeOfLastGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfLastGridPoint));
    sprintf(name, "%sHovmoller.LongitudeOfLastGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfLastGridPoint));
    sprintf(name, "%sHovmoller.TypeOfHorizontalLine", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfHorizontalLine));
    sprintf(name, "%sHovmoller.NumberOfTimeSteps", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfTimeSteps));
    sprintf(name, "%sHovmoller.UnitOfOffsetFromReferenceTime", prefix.c_str());
    attributeList.addAttribute(name, toString(mUnitOfOffsetFromReferenceTime));
    sprintf(name, "%sHovmoller.OffsetFromReferenceOfFirstTime", prefix.c_str());
    attributeList.addAttribute(name, toString(mOffsetFromReferenceOfFirstTime));
    sprintf(name, "%sHovmoller.TypeOfTimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfTimeIncrement));
    sprintf(name, "%sHovmoller.UnitOfTimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mUnitOfTimeIncrement));
    sprintf(name, "%sHovmoller.TimeIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mTimeIncrement));
    sprintf(name, "%sHovmoller.Year", prefix.c_str());
    attributeList.addAttribute(name, toString(mYear));
    sprintf(name, "%sHovmoller.Month", prefix.c_str());
    attributeList.addAttribute(name, toString(mMonth));
    sprintf(name, "%sHovmoller.Day", prefix.c_str());
    attributeList.addAttribute(name, toString(mDay));
    sprintf(name, "%sHovmoller.Hour", prefix.c_str());
    attributeList.addAttribute(name, toString(mHour));
    sprintf(name, "%sHovmoller.Minute", prefix.c_str());
    attributeList.addAttribute(name, toString(mMinute));
    sprintf(name, "%sHovmoller.Second", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecond));
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

void Hovmoller::print(std::ostream &stream, uint level,
                      uint optionFlags) const {
  try {
    stream << space(level) << "Hovmoller\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    stream << space(level) << "- BasicAngleOfTheInitialProductionDomain = "
           << toString(mBasicAngleOfTheInitialProductionDomain) << "\n";
    stream << space(level) << "- SubdivisionsOfBasicAngle = "
           << toString(mSubdivisionsOfBasicAngle) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = "
           << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = "
           << toString(mLongitudeOfFirstGridPoint) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- LatitudeOfLastGridPoint = "
           << toString(mLatitudeOfLastGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfLastGridPoint = "
           << toString(mLongitudeOfLastGridPoint) << "\n";
    stream << space(level)
           << "- TypeOfHorizontalLine = " << toString(mTypeOfHorizontalLine)
           << "\n";
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
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Hovmoller::countHash() {
  try {
    std::size_t seed = 0;
    if (mBasicAngleOfTheInitialProductionDomain)
      boost::hash_combine(seed, *mBasicAngleOfTheInitialProductionDomain);
    if (mSubdivisionsOfBasicAngle)
      boost::hash_combine(seed, *mSubdivisionsOfBasicAngle);
    if (mLatitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLatitudeOfFirstGridPoint);
    if (mLongitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLongitudeOfFirstGridPoint);
    if (mLatitudeOfLastGridPoint)
      boost::hash_combine(seed, *mLatitudeOfLastGridPoint);
    if (mLongitudeOfLastGridPoint)
      boost::hash_combine(seed, *mLongitudeOfLastGridPoint);
    if (mTypeOfHorizontalLine)
      boost::hash_combine(seed, *mTypeOfHorizontalLine);
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
    boost::hash_combine(seed, mEarthShape.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute.
 */

const EarthShapeSettings *Hovmoller::getEarthShape() const {
  try {
    return &mEarthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mBasicAngleOfTheInitialProductionDomain} attribute. */

const T::UInt32_opt &
Hovmoller::getBasicAngleOfTheInitialProductionDomain() const {
  try {
    return mBasicAngleOfTheInitialProductionDomain;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSubdivisionsOfBasicAngle}
 * attribute. */

const T::UInt32_opt &Hovmoller::getSubdivisionsOfBasicAngle() const {
  try {
    return mSubdivisionsOfBasicAngle;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint}
 * attribute. */

const T::Int32_opt &Hovmoller::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mLongitudeOfFirstGridPoint} attribute. */

const T::UInt32_opt &Hovmoller::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode}
 * attribute. */

const ScanningModeSettings *Hovmoller::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfLastGridPoint}
 * attribute. */

const T::Int32_opt &Hovmoller::getLatitudeOfLastGridPoint() const {
  try {
    return mLatitudeOfLastGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfLastGridPoint}
 * attribute. */

const T::UInt32_opt &Hovmoller::getLongitudeOfLastGridPoint() const {
  try {
    return mLongitudeOfLastGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfHorizontalLine}
 * attribute. */

const T::UInt8_opt &Hovmoller::getTypeOfHorizontalLine() const {
  try {
    return mTypeOfHorizontalLine;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfTimeSteps}
 * attribute. */

const T::UInt32_opt &Hovmoller::getNumberOfTimeSteps() const {
  try {
    return mNumberOfTimeSteps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mUnitOfOffsetFromReferenceTime} attribute. */

const T::UInt8_opt &Hovmoller::getUnitOfOffsetFromReferenceTime() const {
  try {
    return mUnitOfOffsetFromReferenceTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mOffsetFromReferenceOfFirstTime} attribute. */

const T::UInt32_opt &Hovmoller::getOffsetFromReferenceOfFirstTime() const {
  try {
    return mOffsetFromReferenceOfFirstTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfTimeIncrement}
 * attribute. */

const T::UInt8_opt &Hovmoller::getTypeOfTimeIncrement() const {
  try {
    return mTypeOfTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mUnitOfTimeIncrement}
 * attribute. */

const T::UInt8_opt &Hovmoller::getUnitOfTimeIncrement() const {
  try {
    return mUnitOfTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mTimeIncrement} attribute.
 */

const T::UInt32_opt &Hovmoller::getTimeIncrement() const {
  try {
    return mTimeIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mYear} attribute. */

const T::UInt16_opt &Hovmoller::getYear() const {
  try {
    return mYear;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mMonth} attribute. */

const T::UInt8_opt &Hovmoller::getMonth() const {
  try {
    return mMonth;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mDay} attribute. */

const T::UInt8_opt &Hovmoller::getDay() const {
  try {
    return mDay;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mHour} attribute. */

const T::UInt8_opt &Hovmoller::getHour() const {
  try {
    return mHour;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mMinute} attribute. */

const T::UInt8_opt &Hovmoller::getMinute() const {
  try {
    return mMinute;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSecond} attribute. */

const T::UInt8_opt &Hovmoller::getSecond() const {
  try {
    return mSecond;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
