// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalEnsembleDerivedForecastImpl.*' files.
// ***********************************************************************

#include "TimeIntervalEnsembleDerivedForecast.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeIntervalEnsembleDerivedForecast::TimeIntervalEnsembleDerivedForecast() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

TimeIntervalEnsembleDerivedForecast::~TimeIntervalEnsembleDerivedForecast() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void TimeIntervalEnsembleDerivedForecast::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mHorizontal.read(memoryReader);
    mDerived.read(memoryReader);
    mStatistical.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void TimeIntervalEnsembleDerivedForecast::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mHorizontal.write(dataWriter);
    mDerived.write(dataWriter);
    mStatistical.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeIntervalEnsembleDerivedForecast::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTimeIntervalEnsembleDerivedForecast.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleDerivedForecast.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleDerivedForecast.", prefix.c_str());
    mDerived.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleDerivedForecast.", prefix.c_str());
    mStatistical.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool TimeIntervalEnsembleDerivedForecast::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mParameter.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mHorizontal.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mDerived.getAttributeValue(attributeName, attributeValue))
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

bool TimeIntervalEnsembleDerivedForecast::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mParameter.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mHorizontal.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mDerived.hasAttributeValue(attributeName, attributeValue))
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

void TimeIntervalEnsembleDerivedForecast::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TimeIntervalEnsembleDerivedForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mDerived.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeIntervalEnsembleDerivedForecast::countHash() const {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint TimeIntervalEnsembleDerivedForecast::getTemplateNumber() const {
  return 12;
}

ProductDefinition *TimeIntervalEnsembleDerivedForecast::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new TimeIntervalEnsembleDerivedForecast(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *TimeIntervalEnsembleDerivedForecast::getParameter() const {
  try {
    return static_cast<ParameterSettings *>(&mParameter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *TimeIntervalEnsembleDerivedForecast::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mDerived} attribute. */

DerivedSettings *TimeIntervalEnsembleDerivedForecast::getDerived() const {
  try {
    return static_cast<DerivedSettings *>(&mDerived);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

StatisticalSettings *TimeIntervalEnsembleDerivedForecast::getStatistical() const {
  try {
    return static_cast<StatisticalSettings *>(&mStatistical);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalEnsembleDerivedForecast::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalEnsembleDerivedForecast::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalEnsembleDerivedForecast::setDerived(DerivedSettings &derived) {
  try {
    mDerived = derived;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TimeIntervalEnsembleDerivedForecast::setStatistical(StatisticalSettings &statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
