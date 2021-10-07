// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CategoricalSettingsImpl.*' files.
// ***********************************************************************

#include "CategoricalSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

CategoricalSettings::CategoricalSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

CategoricalSettings::~CategoricalSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void CategoricalSettings::read(MemoryReader &memoryReader) {
  try {
    mNumberOfCategories = memoryReader.read_UInt8_opt();
    mCategoryType = memoryReader.read_UInt8_opt();
    mCodeFigure = memoryReader.read_UInt8_opt();
    mScaleFactorOfLowerLimit = memoryReader.read_UInt8_opt();
    mScaledValueOfLowerLimit = memoryReader.read_UInt32_opt();
    mScaleFactorOfUpperLimit = memoryReader.read_UInt8_opt();
    mScaledValueOfUpperLimit = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void CategoricalSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mNumberOfCategories;
    dataWriter << mCategoryType;
    dataWriter << mCodeFigure;
    dataWriter << mScaleFactorOfLowerLimit;
    dataWriter << mScaledValueOfLowerLimit;
    dataWriter << mScaleFactorOfUpperLimit;
    dataWriter << mScaledValueOfUpperLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void CategoricalSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sCategoricalSettings.NumberOfCategories", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfCategories));
    sprintf(name, "%sCategoricalSettings.CategoryType", prefix.c_str());
    attributeList.addAttribute(name, toString(mCategoryType));
    sprintf(name, "%sCategoricalSettings.CodeFigure", prefix.c_str());
    attributeList.addAttribute(name, toString(mCodeFigure));
    sprintf(name, "%sCategoricalSettings.ScaleFactorOfLowerLimit", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfLowerLimit));
    sprintf(name, "%sCategoricalSettings.ScaledValueOfLowerLimit", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfLowerLimit));
    sprintf(name, "%sCategoricalSettings.ScaleFactorOfUpperLimit", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfUpperLimit));
    sprintf(name, "%sCategoricalSettings.ScaledValueOfUpperLimit", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfUpperLimit));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool CategoricalSettings::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (strcasecmp(attributeName, "NumberOfCategories") == 0) {
      attributeValue = toString(mNumberOfCategories);
      return true;
    }
    if (strcasecmp(attributeName, "CategoryType") == 0) {
      attributeValue = toString(mCategoryType);
      return true;
    }
    if (strcasecmp(attributeName, "CodeFigure") == 0) {
      attributeValue = toString(mCodeFigure);
      return true;
    }
    if (strcasecmp(attributeName, "ScaleFactorOfLowerLimit") == 0) {
      attributeValue = toString(mScaleFactorOfLowerLimit);
      return true;
    }
    if (strcasecmp(attributeName, "ScaledValueOfLowerLimit") == 0) {
      attributeValue = toString(mScaledValueOfLowerLimit);
      return true;
    }
    if (strcasecmp(attributeName, "ScaleFactorOfUpperLimit") == 0) {
      attributeValue = toString(mScaleFactorOfUpperLimit);
      return true;
    }
    if (strcasecmp(attributeName, "ScaledValueOfUpperLimit") == 0) {
      attributeValue = toString(mScaledValueOfUpperLimit);
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

bool CategoricalSettings::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "NumberOfCategories") == 0 && strcasecmp(attributeValue, toString(mNumberOfCategories).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "CategoryType") == 0 && strcasecmp(attributeValue, toString(mCategoryType).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "CodeFigure") == 0 && strcasecmp(attributeValue, toString(mCodeFigure).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaleFactorOfLowerLimit") == 0 && strcasecmp(attributeValue, toString(mScaleFactorOfLowerLimit).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaledValueOfLowerLimit") == 0 && strcasecmp(attributeValue, toString(mScaledValueOfLowerLimit).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaleFactorOfUpperLimit") == 0 && strcasecmp(attributeValue, toString(mScaleFactorOfUpperLimit).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ScaledValueOfUpperLimit") == 0 && strcasecmp(attributeValue, toString(mScaledValueOfUpperLimit).c_str()) == 0)
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

void CategoricalSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "CategoricalSettings\n";
    stream << space(level) << "- NumberOfCategories = " << toString(mNumberOfCategories) << "\n";
    stream << space(level) << "- CategoryType = " << toString(mCategoryType) << "\n";
    stream << space(level) << "- CodeFigure = " << toString(mCodeFigure) << "\n";
    stream << space(level) << "- ScaleFactorOfLowerLimit = " << toString(mScaleFactorOfLowerLimit) << "\n";
    stream << space(level) << "- ScaledValueOfLowerLimit = " << toString(mScaledValueOfLowerLimit) << "\n";
    stream << space(level) << "- ScaleFactorOfUpperLimit = " << toString(mScaleFactorOfUpperLimit) << "\n";
    stream << space(level) << "- ScaledValueOfUpperLimit = " << toString(mScaledValueOfUpperLimit) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash CategoricalSettings::countHash() const {
  try {
    std::size_t seed = 0;
    if (mNumberOfCategories)
      boost::hash_combine(seed, *mNumberOfCategories);
    if (mCategoryType)
      boost::hash_combine(seed, *mCategoryType);
    if (mCodeFigure)
      boost::hash_combine(seed, *mCodeFigure);
    if (mScaleFactorOfLowerLimit)
      boost::hash_combine(seed, *mScaleFactorOfLowerLimit);
    if (mScaledValueOfLowerLimit)
      boost::hash_combine(seed, *mScaledValueOfLowerLimit);
    if (mScaleFactorOfUpperLimit)
      boost::hash_combine(seed, *mScaleFactorOfUpperLimit);
    if (mScaledValueOfUpperLimit)
      boost::hash_combine(seed, *mScaledValueOfUpperLimit);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfCategories} attribute. */

const T::UInt8_opt &CategoricalSettings::getNumberOfCategories() const {
  try {
    return mNumberOfCategories;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mCategoryType} attribute. */

const T::UInt8_opt &CategoricalSettings::getCategoryType() const {
  try {
    return mCategoryType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mCodeFigure} attribute. */

const T::UInt8_opt &CategoricalSettings::getCodeFigure() const {
  try {
    return mCodeFigure;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfLowerLimit} attribute. */

const T::UInt8_opt &CategoricalSettings::getScaleFactorOfLowerLimit() const {
  try {
    return mScaleFactorOfLowerLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfLowerLimit} attribute. */

const T::UInt32_opt &CategoricalSettings::getScaledValueOfLowerLimit() const {
  try {
    return mScaledValueOfLowerLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfUpperLimit} attribute. */

const T::UInt8_opt &CategoricalSettings::getScaleFactorOfUpperLimit() const {
  try {
    return mScaleFactorOfUpperLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfUpperLimit} attribute. */

const T::UInt32_opt &CategoricalSettings::getScaledValueOfUpperLimit() const {
  try {
    return mScaledValueOfUpperLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void CategoricalSettings::setNumberOfCategories(T::UInt8_opt numberOfCategories) {
  try {
    mNumberOfCategories = numberOfCategories;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void CategoricalSettings::setCategoryType(T::UInt8_opt categoryType) {
  try {
    mCategoryType = categoryType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void CategoricalSettings::setCodeFigure(T::UInt8_opt codeFigure) {
  try {
    mCodeFigure = codeFigure;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void CategoricalSettings::setScaleFactorOfLowerLimit(T::UInt8_opt scaleFactorOfLowerLimit) {
  try {
    mScaleFactorOfLowerLimit = scaleFactorOfLowerLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void CategoricalSettings::setScaledValueOfLowerLimit(T::UInt32_opt scaledValueOfLowerLimit) {
  try {
    mScaledValueOfLowerLimit = scaledValueOfLowerLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void CategoricalSettings::setScaleFactorOfUpperLimit(T::UInt8_opt scaleFactorOfUpperLimit) {
  try {
    mScaleFactorOfUpperLimit = scaleFactorOfUpperLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void CategoricalSettings::setScaledValueOfUpperLimit(T::UInt32_opt scaledValueOfUpperLimit) {
  try {
    mScaledValueOfUpperLimit = scaledValueOfUpperLimit;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
