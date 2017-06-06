// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CategoricalSettingsImpl.*' files.
// ***********************************************************************

#include "grib2/definition/CategoricalSettings.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

CategoricalSettings::CategoricalSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

CategoricalSettings::~CategoricalSettings() {
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
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void CategoricalSettings::getAttributeList(
    std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sCategoricalSettings.NumberOfCategories", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfCategories));
    sprintf(name, "%sCategoricalSettings.CategoryType", prefix.c_str());
    attributeList.addAttribute(name, toString(mCategoryType));
    sprintf(name, "%sCategoricalSettings.CodeFigure", prefix.c_str());
    attributeList.addAttribute(name, toString(mCodeFigure));
    sprintf(name, "%sCategoricalSettings.ScaleFactorOfLowerLimit",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfLowerLimit));
    sprintf(name, "%sCategoricalSettings.ScaledValueOfLowerLimit",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfLowerLimit));
    sprintf(name, "%sCategoricalSettings.ScaleFactorOfUpperLimit",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfUpperLimit));
    sprintf(name, "%sCategoricalSettings.ScaledValueOfUpperLimit",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfUpperLimit));
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

void CategoricalSettings::print(std::ostream &stream, uint level,
                                uint optionFlags) const {
  try {
    stream << space(level) << "CategoricalSettings\n";
    stream << space(level)
           << "- NumberOfCategories = " << toString(mNumberOfCategories)
           << "\n";
    stream << space(level) << "- CategoryType = " << toString(mCategoryType)
           << "\n";
    stream << space(level) << "- CodeFigure = " << toString(mCodeFigure)
           << "\n";
    stream << space(level) << "- ScaleFactorOfLowerLimit = "
           << toString(mScaleFactorOfLowerLimit) << "\n";
    stream << space(level) << "- ScaledValueOfLowerLimit = "
           << toString(mScaledValueOfLowerLimit) << "\n";
    stream << space(level) << "- ScaleFactorOfUpperLimit = "
           << toString(mScaleFactorOfUpperLimit) << "\n";
    stream << space(level) << "- ScaledValueOfUpperLimit = "
           << toString(mScaledValueOfUpperLimit) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash CategoricalSettings::countHash() {
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
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfCategories}
 * attribute. */

const T::UInt8_opt &CategoricalSettings::getNumberOfCategories() const {
  try {
    return mNumberOfCategories;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mCategoryType} attribute.
 */

const T::UInt8_opt &CategoricalSettings::getCategoryType() const {
  try {
    return mCategoryType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mCodeFigure} attribute. */

const T::UInt8_opt &CategoricalSettings::getCodeFigure() const {
  try {
    return mCodeFigure;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfLowerLimit}
 * attribute. */

const T::UInt8_opt &CategoricalSettings::getScaleFactorOfLowerLimit() const {
  try {
    return mScaleFactorOfLowerLimit;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfLowerLimit}
 * attribute. */

const T::UInt32_opt &CategoricalSettings::getScaledValueOfLowerLimit() const {
  try {
    return mScaledValueOfLowerLimit;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfUpperLimit}
 * attribute. */

const T::UInt8_opt &CategoricalSettings::getScaleFactorOfUpperLimit() const {
  try {
    return mScaleFactorOfUpperLimit;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfUpperLimit}
 * attribute. */

const T::UInt32_opt &CategoricalSettings::getScaledValueOfUpperLimit() const {
  try {
    return mScaledValueOfUpperLimit;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet