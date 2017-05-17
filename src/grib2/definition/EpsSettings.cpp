// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'EpsSettingsImpl.*' files.
// ***********************************************************************

#include "grib2/definition/EpsSettings.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

EpsSettings::EpsSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

EpsSettings::~EpsSettings() {
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

void EpsSettings::read(MemoryReader &memoryReader) {
  try {
    mTypeOfEnsembleForecast = memoryReader.read_UInt8_opt();
    mPerturbationNumber = memoryReader.read_UInt8_opt();
    mNumberOfForecastsInEnsemble = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void EpsSettings::getAttributeList(std::string prefix,
                                   T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sEpsSettings.TypeOfEnsembleForecast", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfEnsembleForecast));
    sprintf(name, "%sEpsSettings.PerturbationNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mPerturbationNumber));
    sprintf(name, "%sEpsSettings.NumberOfForecastsInEnsemble", prefix.c_str());
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

void EpsSettings::print(std::ostream &stream, uint level,
                        uint optionFlags) const {
  try {
    stream << space(level) << "EpsSettings\n";
    stream << space(level)
           << "- TypeOfEnsembleForecast = " << toString(mTypeOfEnsembleForecast)
           << "\n";
    stream << space(level)
           << "- PerturbationNumber = " << toString(mPerturbationNumber)
           << "\n";
    stream << space(level) << "- NumberOfForecastsInEnsemble = "
           << toString(mNumberOfForecastsInEnsemble) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash EpsSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mTypeOfEnsembleForecast)
      boost::hash_combine(seed, *mTypeOfEnsembleForecast);
    if (mPerturbationNumber)
      boost::hash_combine(seed, *mPerturbationNumber);
    if (mNumberOfForecastsInEnsemble)
      boost::hash_combine(seed, *mNumberOfForecastsInEnsemble);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfEnsembleForecast}
 * attribute. */

const T::UInt8_opt &EpsSettings::getTypeOfEnsembleForecast() const {
  try {
    return mTypeOfEnsembleForecast;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mPerturbationNumber}
 * attribute. */

const T::UInt8_opt &EpsSettings::getPerturbationNumber() const {
  try {
    return mPerturbationNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mNumberOfForecastsInEnsemble} attribute. */

const T::UInt8_opt &EpsSettings::getNumberOfForecastsInEnsemble() const {
  try {
    return mNumberOfForecastsInEnsemble;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
