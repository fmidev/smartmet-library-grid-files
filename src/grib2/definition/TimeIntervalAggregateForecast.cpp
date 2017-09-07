// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalAggregateForecastImpl.*' files.
// ***********************************************************************

#include "grib2/definition/TimeIntervalAggregateForecast.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeIntervalAggregateForecast::TimeIntervalAggregateForecast() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

TimeIntervalAggregateForecast::~TimeIntervalAggregateForecast() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void TimeIntervalAggregateForecast::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
    mStatisticalProcess = memoryReader.read_UInt8_opt();
    mSpatialProcessing = memoryReader.read_UInt8_opt();
    mNumberOfPointsUsed = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeIntervalAggregateForecast::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTimeIntervalAggregateForecast.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalAggregateForecast.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalAggregateForecast.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalAggregateForecast.StatisticalProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mStatisticalProcess));
    sprintf(name, "%sTimeIntervalAggregateForecast.SpatialProcessing", prefix.c_str());
    attributeList.addAttribute(name, toString(mSpatialProcessing));
    sprintf(name, "%sTimeIntervalAggregateForecast.NumberOfPointsUsed", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfPointsUsed));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void TimeIntervalAggregateForecast::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TimeIntervalAggregateForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    stream << space(level) << "- StatisticalProcess = " << toString(mStatisticalProcess) << "\n";
    stream << space(level) << "- SpatialProcessing = " << toString(mSpatialProcessing) << "\n";
    stream << space(level) << "- NumberOfPointsUsed = " << toString(mNumberOfPointsUsed) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeIntervalAggregateForecast::countHash() {
  try {
    std::size_t seed = 0;
    if (mStatisticalProcess)
      boost::hash_combine(seed, *mStatisticalProcess);
    if (mSpatialProcessing)
      boost::hash_combine(seed, *mSpatialProcessing);
    if (mNumberOfPointsUsed)
      boost::hash_combine(seed, *mNumberOfPointsUsed);
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mPointInTime.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

const ParameterSettings *TimeIntervalAggregateForecast::getParameter() const {
  try {
    return &mParameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

const PointInTimeSettings *TimeIntervalAggregateForecast::getPointInTime() const {
  try {
    return &mPointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

const HorizontalSettings *TimeIntervalAggregateForecast::getHorizontal() const {
  try {
    return &mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mStatisticalProcess} attribute. */

const T::UInt8_opt &TimeIntervalAggregateForecast::getStatisticalProcess() const {
  try {
    return mStatisticalProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSpatialProcessing} attribute. */

const T::UInt8_opt &TimeIntervalAggregateForecast::getSpatialProcessing() const {
  try {
    return mSpatialProcessing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfPointsUsed} attribute. */

const T::UInt8_opt &TimeIntervalAggregateForecast::getNumberOfPointsUsed() const {
  try {
    return mNumberOfPointsUsed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void TimeIntervalAggregateForecast::setParameter(ParameterSettings parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void TimeIntervalAggregateForecast::setPointInTime(PointInTimeSettings pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void TimeIntervalAggregateForecast::setHorizontal(HorizontalSettings horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void TimeIntervalAggregateForecast::setStatisticalProcess(T::UInt8_opt statisticalProcess) {
  try {
    mStatisticalProcess = statisticalProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void TimeIntervalAggregateForecast::setSpatialProcessing(T::UInt8_opt spatialProcessing) {
  try {
    mSpatialProcessing = spatialProcessing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void TimeIntervalAggregateForecast::setNumberOfPointsUsed(T::UInt8_opt numberOfPointsUsed) {
  try {
    mNumberOfPointsUsed = numberOfPointsUsed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
