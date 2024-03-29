// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PackingSettingsImpl.*' files.
// ***********************************************************************

#include "PackingSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PackingSettings::PackingSettings() {
  try {
    mReferenceValue = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

PackingSettings::~PackingSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PackingSettings::read(MemoryReader &memoryReader) {
  try {
    mReferenceValue = memoryReader.read_float();
    mBinaryScaleFactor = memoryReader.read_Int16_opt();
    mDecimalScaleFactor = memoryReader.read_Int16_opt();
    mBitsPerValue = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void PackingSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mReferenceValue;
    dataWriter << mBinaryScaleFactor;
    dataWriter << mDecimalScaleFactor;
    dataWriter << mBitsPerValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void PackingSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sPackingSettings.ReferenceValue", prefix.c_str());
    attributeList.addAttribute(name, toString(mReferenceValue));
    sprintf(name, "%sPackingSettings.BinaryScaleFactor", prefix.c_str());
    attributeList.addAttribute(name, toString(mBinaryScaleFactor));
    sprintf(name, "%sPackingSettings.DecimalScaleFactor", prefix.c_str());
    attributeList.addAttribute(name, toString(mDecimalScaleFactor));
    sprintf(name, "%sPackingSettings.BitsPerValue", prefix.c_str());
    attributeList.addAttribute(name, toString(mBitsPerValue));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool PackingSettings::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (strcasecmp(attributeName, "ReferenceValue") == 0) {
      attributeValue = toString(mReferenceValue);
      return true;
    }
    if (strcasecmp(attributeName, "BinaryScaleFactor") == 0) {
      attributeValue = toString(mBinaryScaleFactor);
      return true;
    }
    if (strcasecmp(attributeName, "DecimalScaleFactor") == 0) {
      attributeValue = toString(mDecimalScaleFactor);
      return true;
    }
    if (strcasecmp(attributeName, "BitsPerValue") == 0) {
      attributeValue = toString(mBitsPerValue);
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

bool PackingSettings::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "ReferenceValue") == 0 && strcasecmp(attributeValue, toString(mReferenceValue).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "BinaryScaleFactor") == 0 && strcasecmp(attributeValue, toString(mBinaryScaleFactor).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "DecimalScaleFactor") == 0 && strcasecmp(attributeValue, toString(mDecimalScaleFactor).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "BitsPerValue") == 0 && strcasecmp(attributeValue, toString(mBitsPerValue).c_str()) == 0)
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

void PackingSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "PackingSettings\n";
    stream << space(level) << "- ReferenceValue = " << toString(mReferenceValue) << "\n";
    stream << space(level) << "- BinaryScaleFactor = " << toString(mBinaryScaleFactor) << "\n";
    stream << space(level) << "- DecimalScaleFactor = " << toString(mDecimalScaleFactor) << "\n";
    stream << space(level) << "- BitsPerValue = " << toString(mBitsPerValue) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash PackingSettings::countHash() const {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mReferenceValue);
    if (mBinaryScaleFactor)
      boost::hash_combine(seed, *mBinaryScaleFactor);
    if (mDecimalScaleFactor)
      boost::hash_combine(seed, *mDecimalScaleFactor);
    if (mBitsPerValue)
      boost::hash_combine(seed, *mBitsPerValue);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mReferenceValue} attribute. */

float PackingSettings::getReferenceValue() const {
  try {
    return mReferenceValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mBinaryScaleFactor} attribute. */

const T::Int16_opt &PackingSettings::getBinaryScaleFactor() const {
  try {
    return mBinaryScaleFactor;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDecimalScaleFactor} attribute. */

const T::Int16_opt &PackingSettings::getDecimalScaleFactor() const {
  try {
    return mDecimalScaleFactor;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mBitsPerValue} attribute. */

const T::UInt8_opt &PackingSettings::getBitsPerValue() const {
  try {
    return mBitsPerValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PackingSettings::setReferenceValue(float referenceValue) {
  try {
    mReferenceValue = referenceValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PackingSettings::setBinaryScaleFactor(T::Int16_opt binaryScaleFactor) {
  try {
    mBinaryScaleFactor = binaryScaleFactor;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PackingSettings::setDecimalScaleFactor(T::Int16_opt decimalScaleFactor) {
  try {
    mDecimalScaleFactor = decimalScaleFactor;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PackingSettings::setBitsPerValue(T::UInt8_opt bitsPerValue) {
  try {
    mBitsPerValue = bitsPerValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
