// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PercentileForecastImpl.*' files.
// ***********************************************************************

#include "PercentileForecast.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PercentileForecast::PercentileForecast() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

PercentileForecast::~PercentileForecast() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PercentileForecast::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
    mPercentile.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void PercentileForecast::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mPointInTime.write(dataWriter);
    mHorizontal.write(dataWriter);
    mPercentile.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void PercentileForecast::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sPercentileForecast.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sPercentileForecast.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sPercentileForecast.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sPercentileForecast.", prefix.c_str());
    mPercentile.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool PercentileForecast::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mParameter.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mPointInTime.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mHorizontal.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mPercentile.getAttributeValue(attributeName, attributeValue))
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

bool PercentileForecast::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mParameter.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mPointInTime.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mHorizontal.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mPercentile.hasAttributeValue(attributeName, attributeValue))
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

void PercentileForecast::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "PercentileForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mPercentile.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash PercentileForecast::countHash() const {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint PercentileForecast::getTemplateNumber() const {
  return 6;
}

ProductDefinition *PercentileForecast::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new PercentileForecast(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *PercentileForecast::getParameter() const {
  try {
    return static_cast<ParameterSettings *>(&mParameter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *PercentileForecast::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *PercentileForecast::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPercentile} attribute. */

PercentileSettings *PercentileForecast::getPercentile() const {
  try {
    return static_cast<PercentileSettings *>(&mPercentile);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PercentileForecast::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PercentileForecast::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PercentileForecast::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PercentileForecast::setPercentile(PercentileSettings &percentile) {
  try {
    mPercentile = percentile;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
