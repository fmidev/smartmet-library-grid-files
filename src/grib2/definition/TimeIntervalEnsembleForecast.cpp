// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalEnsembleForecastImpl.*' files.
// ***********************************************************************

#include "TimeIntervalEnsembleForecast.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeIntervalEnsembleForecast::TimeIntervalEnsembleForecast() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

TimeIntervalEnsembleForecast::~TimeIntervalEnsembleForecast() {
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void TimeIntervalEnsembleForecast::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mHorizontal.write(dataWriter);
    mEps.write(dataWriter);
    mStatistical.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeIntervalEnsembleForecast::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool TimeIntervalEnsembleForecast::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mParameter.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mHorizontal.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mEps.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mStatistical.getAttributeValue(attributeName, attributeValue))
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool TimeIntervalEnsembleForecast::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mParameter.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mHorizontal.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mEps.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mStatistical.hasAttributeValue(attributeName, attributeValue))
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

void TimeIntervalEnsembleForecast::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TimeIntervalEnsembleForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeIntervalEnsembleForecast::countHash() const {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint TimeIntervalEnsembleForecast::getTemplateNumber() const {
  return 11;
}

ProductDefinition *TimeIntervalEnsembleForecast::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new TimeIntervalEnsembleForecast(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *TimeIntervalEnsembleForecast::getParameter() const {
  try {
    return static_cast<ParameterSettings *>(&mParameter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *TimeIntervalEnsembleForecast::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

EpsSettings *TimeIntervalEnsembleForecast::getEps() const {
  try {
    return static_cast<EpsSettings *>(&mEps);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

StatisticalSettings *TimeIntervalEnsembleForecast::getStatistical() const {
  try {
    return static_cast<StatisticalSettings *>(&mStatistical);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalEnsembleForecast::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalEnsembleForecast::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalEnsembleForecast::setEps(EpsSettings &eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalEnsembleForecast::setStatistical(StatisticalSettings &statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
