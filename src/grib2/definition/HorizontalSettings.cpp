// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'HorizontalSettingsImpl.*' files.
// ***********************************************************************

#include "HorizontalSettings.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

HorizontalSettings::HorizontalSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

HorizontalSettings::~HorizontalSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void HorizontalSettings::read(MemoryReader &memoryReader) {
  try {
    mTypeOfFirstFixedSurface = memoryReader.read_UInt8_opt();
    mScaleFactorOfFirstFixedSurface = memoryReader.read_Int8_opt();
    mScaledValueOfFirstFixedSurface = memoryReader.read_UInt32_opt();
    mTypeOfSecondFixedSurface = memoryReader.read_UInt8_opt();
    mScaleFactorOfSecondFixedSurface = memoryReader.read_Int8_opt();
    mScaledValueOfSecondFixedSurface = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void HorizontalSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sHorizontalSettings.TypeOfFirstFixedSurface", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfFirstFixedSurface));
    sprintf(name, "%sHorizontalSettings.ScaleFactorOfFirstFixedSurface", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfFirstFixedSurface));
    sprintf(name, "%sHorizontalSettings.ScaledValueOfFirstFixedSurface", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfFirstFixedSurface));
    sprintf(name, "%sHorizontalSettings.TypeOfSecondFixedSurface", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfSecondFixedSurface));
    sprintf(name, "%sHorizontalSettings.ScaleFactorOfSecondFixedSurface", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfSecondFixedSurface));
    sprintf(name, "%sHorizontalSettings.ScaledValueOfSecondFixedSurface", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfSecondFixedSurface));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void HorizontalSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "HorizontalSettings\n";
    stream << space(level) << "- TypeOfFirstFixedSurface = " << toString(mTypeOfFirstFixedSurface) << "\n";
    stream << space(level) << "- ScaleFactorOfFirstFixedSurface = " << toString(mScaleFactorOfFirstFixedSurface) << "\n";
    stream << space(level) << "- ScaledValueOfFirstFixedSurface = " << toString(mScaledValueOfFirstFixedSurface) << "\n";
    stream << space(level) << "- TypeOfSecondFixedSurface = " << toString(mTypeOfSecondFixedSurface) << "\n";
    stream << space(level) << "- ScaleFactorOfSecondFixedSurface = " << toString(mScaleFactorOfSecondFixedSurface) << "\n";
    stream << space(level) << "- ScaledValueOfSecondFixedSurface = " << toString(mScaledValueOfSecondFixedSurface) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash HorizontalSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mTypeOfFirstFixedSurface)
      boost::hash_combine(seed, *mTypeOfFirstFixedSurface);
    if (mScaleFactorOfFirstFixedSurface)
      boost::hash_combine(seed, *mScaleFactorOfFirstFixedSurface);
    if (mScaledValueOfFirstFixedSurface)
      boost::hash_combine(seed, *mScaledValueOfFirstFixedSurface);
    if (mTypeOfSecondFixedSurface)
      boost::hash_combine(seed, *mTypeOfSecondFixedSurface);
    if (mScaleFactorOfSecondFixedSurface)
      boost::hash_combine(seed, *mScaleFactorOfSecondFixedSurface);
    if (mScaledValueOfSecondFixedSurface)
      boost::hash_combine(seed, *mScaledValueOfSecondFixedSurface);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfFirstFixedSurface} attribute. */

const T::UInt8_opt &HorizontalSettings::getTypeOfFirstFixedSurface() const {
  try {
    return mTypeOfFirstFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfFirstFixedSurface} attribute. */

const T::Int8_opt &HorizontalSettings::getScaleFactorOfFirstFixedSurface() const {
  try {
    return mScaleFactorOfFirstFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfFirstFixedSurface} attribute. */

const T::UInt32_opt &HorizontalSettings::getScaledValueOfFirstFixedSurface() const {
  try {
    return mScaledValueOfFirstFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfSecondFixedSurface} attribute. */

const T::UInt8_opt &HorizontalSettings::getTypeOfSecondFixedSurface() const {
  try {
    return mTypeOfSecondFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfSecondFixedSurface} attribute. */

const T::Int8_opt &HorizontalSettings::getScaleFactorOfSecondFixedSurface() const {
  try {
    return mScaleFactorOfSecondFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfSecondFixedSurface} attribute. */

const T::UInt32_opt &HorizontalSettings::getScaledValueOfSecondFixedSurface() const {
  try {
    return mScaledValueOfSecondFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void HorizontalSettings::setTypeOfFirstFixedSurface(T::UInt8_opt typeOfFirstFixedSurface) {
  try {
    mTypeOfFirstFixedSurface = typeOfFirstFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void HorizontalSettings::setScaleFactorOfFirstFixedSurface(T::Int8_opt scaleFactorOfFirstFixedSurface) {
  try {
    mScaleFactorOfFirstFixedSurface = scaleFactorOfFirstFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void HorizontalSettings::setScaledValueOfFirstFixedSurface(T::UInt32_opt scaledValueOfFirstFixedSurface) {
  try {
    mScaledValueOfFirstFixedSurface = scaledValueOfFirstFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void HorizontalSettings::setTypeOfSecondFixedSurface(T::UInt8_opt typeOfSecondFixedSurface) {
  try {
    mTypeOfSecondFixedSurface = typeOfSecondFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void HorizontalSettings::setScaleFactorOfSecondFixedSurface(T::Int8_opt scaleFactorOfSecondFixedSurface) {
  try {
    mScaleFactorOfSecondFixedSurface = scaleFactorOfSecondFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void HorizontalSettings::setScaledValueOfSecondFixedSurface(T::UInt32_opt scaledValueOfSecondFixedSurface) {
  try {
    mScaledValueOfSecondFixedSurface = scaledValueOfSecondFixedSurface;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
