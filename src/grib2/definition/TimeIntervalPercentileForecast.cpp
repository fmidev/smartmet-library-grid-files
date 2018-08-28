// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalPercentileForecastImpl.*' files.
// ***********************************************************************

#include "TimeIntervalPercentileForecast.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeIntervalPercentileForecast::TimeIntervalPercentileForecast() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

TimeIntervalPercentileForecast::TimeIntervalPercentileForecast(const TimeIntervalPercentileForecast &other) : ProductDefinition(other) {
  try {
    mParameter = other.mParameter;
    mHorizontal = other.mHorizontal;
    mPercentile = other.mPercentile;
    mStatistical = other.mStatistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

TimeIntervalPercentileForecast::~TimeIntervalPercentileForecast() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void TimeIntervalPercentileForecast::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mHorizontal.read(memoryReader);
    mPercentile.read(memoryReader);
    mStatistical.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void TimeIntervalPercentileForecast::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mHorizontal.write(dataWriter);
    mPercentile.write(dataWriter);
    mStatistical.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeIntervalPercentileForecast::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTimeIntervalPercentileForecast.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalPercentileForecast.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalPercentileForecast.", prefix.c_str());
    mPercentile.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalPercentileForecast.", prefix.c_str());
    mStatistical.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void TimeIntervalPercentileForecast::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TimeIntervalPercentileForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mPercentile.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeIntervalPercentileForecast::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mPercentile.countHash());
    boost::hash_combine(seed, mStatistical.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint TimeIntervalPercentileForecast::getTemplateNumber() const {
  return 10;
}

ProductDefinition *TimeIntervalPercentileForecast::createProductDefinition() const {
  try {
    return (ProductDefinition *)new TimeIntervalPercentileForecast(*this);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *TimeIntervalPercentileForecast::getParameter() const {
  try {
    return (ParameterSettings *)&mParameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *TimeIntervalPercentileForecast::getHorizontal() const {
  try {
    return (HorizontalSettings *)&mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPercentile} attribute. */

PercentileSettings *TimeIntervalPercentileForecast::getPercentile() const {
  try {
    return (PercentileSettings *)&mPercentile;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

StatisticalSettings *TimeIntervalPercentileForecast::getStatistical() const {
  try {
    return (StatisticalSettings *)&mStatistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void TimeIntervalPercentileForecast::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void TimeIntervalPercentileForecast::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void TimeIntervalPercentileForecast::setPercentile(PercentileSettings &percentile) {
  try {
    mPercentile = percentile;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void TimeIntervalPercentileForecast::setStatistical(StatisticalSettings &statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
