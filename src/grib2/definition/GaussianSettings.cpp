// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GaussianSettingsImpl.*' files.
// ***********************************************************************

#include "grib2/definition/GaussianSettings.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

GaussianSettings::GaussianSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

GaussianSettings::~GaussianSettings() {
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

void GaussianSettings::read(MemoryReader &memoryReader) {
  try {
    mGrid.read(memoryReader);
    mIDirectionIncrement = memoryReader.read_UInt32_opt();
    mN = memoryReader.read_UInt32_opt();
    mScanningMode.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void GaussianSettings::getAttributeList(std::string prefix,
                                        T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sGaussianSettings.", prefix.c_str());
    mGrid.getAttributeList(name, attributeList);
    sprintf(name, "%sGaussianSettings.IDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mIDirectionIncrement));
    sprintf(name, "%sGaussianSettings.N", prefix.c_str());
    attributeList.addAttribute(name, toString(mN));
    sprintf(name, "%sGaussianSettings.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
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

void GaussianSettings::print(std::ostream &stream, uint level,
                             uint optionFlags) const {
  try {
    stream << space(level) << "GaussianSettings\n";
    mGrid.print(stream, level + 1, optionFlags);
    stream << space(level)
           << "- IDirectionIncrement = " << toString(mIDirectionIncrement)
           << "\n";
    stream << space(level) << "- N = " << toString(mN) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash GaussianSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mIDirectionIncrement)
      boost::hash_combine(seed, *mIDirectionIncrement);
    if (mN)
      boost::hash_combine(seed, *mN);
    boost::hash_combine(seed, mGrid.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mGrid} attribute. */

const GridSettings *GaussianSettings::getGrid() const {
  try {
    return &mGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mIDirectionIncrement}
 * attribute. */

const T::UInt32_opt &GaussianSettings::getIDirectionIncrement() const {
  try {
    return mIDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mN} attribute. */

const T::UInt32_opt &GaussianSettings::getN() const {
  try {
    return mN;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode}
 * attribute. */

const ScanningModeSettings *GaussianSettings::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
