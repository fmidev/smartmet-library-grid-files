// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SphericalHarmonicSettingsImpl.*' files.
// ***********************************************************************

#include "grib2/definition/SphericalHarmonicSettings.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SphericalHarmonicSettings::SphericalHarmonicSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

SphericalHarmonicSettings::~SphericalHarmonicSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SphericalHarmonicSettings::read(MemoryReader &memoryReader) {
  try {
    mJ = memoryReader.read_UInt32_opt();
    mK = memoryReader.read_UInt32_opt();
    mM = memoryReader.read_UInt32_opt();
    mSpectralType = memoryReader.read_UInt8_opt();
    mSpectralMode = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SphericalHarmonicSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSphericalHarmonicSettings.J", prefix.c_str());
    attributeList.addAttribute(name, toString(mJ));
    sprintf(name, "%sSphericalHarmonicSettings.K", prefix.c_str());
    attributeList.addAttribute(name, toString(mK));
    sprintf(name, "%sSphericalHarmonicSettings.M", prefix.c_str());
    attributeList.addAttribute(name, toString(mM));
    sprintf(name, "%sSphericalHarmonicSettings.SpectralType", prefix.c_str());
    attributeList.addAttribute(name, toString(mSpectralType));
    sprintf(name, "%sSphericalHarmonicSettings.SpectralMode", prefix.c_str());
    attributeList.addAttribute(name, toString(mSpectralMode));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SphericalHarmonicSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SphericalHarmonicSettings\n";
    stream << space(level) << "- J = " << toString(mJ) << "\n";
    stream << space(level) << "- K = " << toString(mK) << "\n";
    stream << space(level) << "- M = " << toString(mM) << "\n";
    stream << space(level) << "- SpectralType = " << toString(mSpectralType) << "\n";
    stream << space(level) << "- SpectralMode = " << toString(mSpectralMode) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SphericalHarmonicSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mJ)
      boost::hash_combine(seed, *mJ);
    if (mK)
      boost::hash_combine(seed, *mK);
    if (mM)
      boost::hash_combine(seed, *mM);
    if (mSpectralType)
      boost::hash_combine(seed, *mSpectralType);
    if (mSpectralMode)
      boost::hash_combine(seed, *mSpectralMode);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mJ} attribute. */

const T::UInt32_opt &SphericalHarmonicSettings::getJ() const {
  try {
    return mJ;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mK} attribute. */

const T::UInt32_opt &SphericalHarmonicSettings::getK() const {
  try {
    return mK;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mM} attribute. */

const T::UInt32_opt &SphericalHarmonicSettings::getM() const {
  try {
    return mM;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSpectralType} attribute. */

const T::UInt8_opt &SphericalHarmonicSettings::getSpectralType() const {
  try {
    return mSpectralType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSpectralMode} attribute. */

const T::UInt8_opt &SphericalHarmonicSettings::getSpectralMode() const {
  try {
    return mSpectralMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SphericalHarmonicSettings::setJ(T::UInt32_opt j) {
  try {
    mJ = j;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SphericalHarmonicSettings::setK(T::UInt32_opt k) {
  try {
    mK = k;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SphericalHarmonicSettings::setM(T::UInt32_opt m) {
  try {
    mM = m;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SphericalHarmonicSettings::setSpectralType(T::UInt8_opt spectralType) {
  try {
    mSpectralType = spectralType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void SphericalHarmonicSettings::setSpectralMode(T::UInt8_opt spectralMode) {
  try {
    mSpectralMode = spectralMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
