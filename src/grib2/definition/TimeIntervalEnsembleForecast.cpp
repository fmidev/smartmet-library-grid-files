// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalEnsembleForecastImpl.*' files.
// ***********************************************************************

#include "grib2/definition/TimeIntervalEnsembleForecast.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeIntervalEnsembleForecast::TimeIntervalEnsembleForecast() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

TimeIntervalEnsembleForecast::~TimeIntervalEnsembleForecast() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void TimeIntervalEnsembleForecast::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mHorizontal.read(memoryReader);
    mEps.read(memoryReader);
    mStatistical.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeIntervalEnsembleForecast::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTimeIntervalEnsembleForecast.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleForecast.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleForecast.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleForecast.", prefix.c_str());
    mStatistical.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void TimeIntervalEnsembleForecast::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TimeIntervalEnsembleForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeIntervalEnsembleForecast::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mEps.countHash());
    boost::hash_combine(seed, mStatistical.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

const ParameterSettings *TimeIntervalEnsembleForecast::getParameter() const {
  try {
    return &mParameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

const HorizontalSettings *TimeIntervalEnsembleForecast::getHorizontal() const {
  try {
    return &mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

const EpsSettings *TimeIntervalEnsembleForecast::getEps() const {
  try {
    return &mEps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

const StatisticalSettings *TimeIntervalEnsembleForecast::getStatistical() const {
  try {
    return &mStatistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleForecast::setParameter(ParameterSettings parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleForecast::setHorizontal(HorizontalSettings horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleForecast::setEps(EpsSettings eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleForecast::setStatistical(StatisticalSettings statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
