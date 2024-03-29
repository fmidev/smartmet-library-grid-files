// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchingSettingsImpl.*' files.
// ***********************************************************************

#include "StretchingSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

StretchingSettings::StretchingSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

StretchingSettings::~StretchingSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void StretchingSettings::read(MemoryReader &memoryReader) {
  try {
    mLatitudeOfThePoleOfStretching = memoryReader.read_Int32_opt();
    mLongitudeOfThePoleOfStretching = memoryReader.read_Int32_opt();
    mStretchingFactorScaled = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void StretchingSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mLatitudeOfThePoleOfStretching;
    dataWriter << mLongitudeOfThePoleOfStretching;
    dataWriter << mStretchingFactorScaled;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void StretchingSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sStretchingSettings.LatitudeOfThePoleOfStretching", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfThePoleOfStretching));
    sprintf(name, "%sStretchingSettings.LongitudeOfThePoleOfStretching", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfThePoleOfStretching));
    sprintf(name, "%sStretchingSettings.StretchingFactorScaled", prefix.c_str());
    attributeList.addAttribute(name, toString(mStretchingFactorScaled));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool StretchingSettings::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (strcasecmp(attributeName, "LatitudeOfThePoleOfStretching") == 0) {
      attributeValue = toString(mLatitudeOfThePoleOfStretching);
      return true;
    }
    if (strcasecmp(attributeName, "LongitudeOfThePoleOfStretching") == 0) {
      attributeValue = toString(mLongitudeOfThePoleOfStretching);
      return true;
    }
    if (strcasecmp(attributeName, "StretchingFactorScaled") == 0) {
      attributeValue = toString(mStretchingFactorScaled);
      return true;
    }
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool StretchingSettings::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "LatitudeOfThePoleOfStretching") == 0 && strcasecmp(attributeValue, toString(mLatitudeOfThePoleOfStretching).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "LongitudeOfThePoleOfStretching") == 0 && strcasecmp(attributeValue, toString(mLongitudeOfThePoleOfStretching).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "StretchingFactorScaled") == 0 && strcasecmp(attributeValue, toString(mStretchingFactorScaled).c_str()) == 0)
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

void StretchingSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "StretchingSettings\n";
    stream << space(level) << "- LatitudeOfThePoleOfStretching = " << toString(mLatitudeOfThePoleOfStretching) << "\n";
    stream << space(level) << "- LongitudeOfThePoleOfStretching = " << toString(mLongitudeOfThePoleOfStretching) << "\n";
    stream << space(level) << "- StretchingFactorScaled = " << toString(mStretchingFactorScaled) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash StretchingSettings::countHash() const {
  try {
    std::size_t seed = 0;
    if (mLatitudeOfThePoleOfStretching)
      boost::hash_combine(seed, *mLatitudeOfThePoleOfStretching);
    if (mLongitudeOfThePoleOfStretching)
      boost::hash_combine(seed, *mLongitudeOfThePoleOfStretching);
    if (mStretchingFactorScaled)
      boost::hash_combine(seed, *mStretchingFactorScaled);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfThePoleOfStretching} attribute. */

const T::Int32_opt &StretchingSettings::getLatitudeOfThePoleOfStretching() const {
  try {
    return mLatitudeOfThePoleOfStretching;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfThePoleOfStretching} attribute. */

const T::Int32_opt &StretchingSettings::getLongitudeOfThePoleOfStretching() const {
  try {
    return mLongitudeOfThePoleOfStretching;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mStretchingFactorScaled} attribute. */

const T::UInt32_opt &StretchingSettings::getStretchingFactorScaled() const {
  try {
    return mStretchingFactorScaled;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchingSettings::setLatitudeOfThePoleOfStretching(T::Int32_opt latitudeOfThePoleOfStretching) {
  try {
    mLatitudeOfThePoleOfStretching = latitudeOfThePoleOfStretching;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchingSettings::setLongitudeOfThePoleOfStretching(T::Int32_opt longitudeOfThePoleOfStretching) {
  try {
    mLongitudeOfThePoleOfStretching = longitudeOfThePoleOfStretching;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchingSettings::setStretchingFactorScaled(T::UInt32_opt stretchingFactorScaled) {
  try {
    mStretchingFactorScaled = stretchingFactorScaled;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
