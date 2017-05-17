// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'DerivedSettingsImpl.*' files.
// ***********************************************************************

#include "grib2/definition/DerivedSettings.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

DerivedSettings::DerivedSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

DerivedSettings::~DerivedSettings() {
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

void DerivedSettings::read(MemoryReader &memoryReader) {
  try {
    mDerivedForecast = memoryReader.read_UInt8_opt();
    mNumberOfForecastsInEnsemble = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void DerivedSettings::getAttributeList(std::string prefix,
                                       T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sDerivedSettings.DerivedForecast", prefix.c_str());
    attributeList.addAttribute(name, toString(mDerivedForecast));
    sprintf(name, "%sDerivedSettings.NumberOfForecastsInEnsemble",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfForecastsInEnsemble));
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

void DerivedSettings::print(std::ostream &stream, uint level,
                            uint optionFlags) const {
  try {
    stream << space(level) << "DerivedSettings\n";
    stream << space(level)
           << "- DerivedForecast = " << toString(mDerivedForecast) << "\n";
    stream << space(level) << "- NumberOfForecastsInEnsemble = "
           << toString(mNumberOfForecastsInEnsemble) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash DerivedSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mDerivedForecast)
      boost::hash_combine(seed, *mDerivedForecast);
    if (mNumberOfForecastsInEnsemble)
      boost::hash_combine(seed, *mNumberOfForecastsInEnsemble);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mDerivedForecast}
 * attribute. */

const T::UInt8_opt &DerivedSettings::getDerivedForecast() const {
  try {
    return mDerivedForecast;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mNumberOfForecastsInEnsemble} attribute. */

const T::UInt8_opt &DerivedSettings::getNumberOfForecastsInEnsemble() const {
  try {
    return mNumberOfForecastsInEnsemble;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
