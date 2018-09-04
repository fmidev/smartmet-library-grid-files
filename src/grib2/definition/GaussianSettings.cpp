// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GaussianSettingsImpl.*' files.
// ***********************************************************************

#include "GaussianSettings.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

GaussianSettings::GaussianSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The copy constructor of the class. */

GaussianSettings::GaussianSettings(const GaussianSettings &other) {
  try {
    mGrid = other.mGrid;
    mIDirectionIncrement = other.mIDirectionIncrement;
    mN = other.mN;
    mScanningMode = other.mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

GaussianSettings::~GaussianSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GaussianSettings::read(MemoryReader &memoryReader) {
  try {
    mGrid.read(memoryReader);
    mIDirectionIncrement = memoryReader.read_UInt32_opt();
    mN = memoryReader.read_UInt32_opt();
    mScanningMode.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void GaussianSettings::write(DataWriter &dataWriter) {
  try {
    mGrid.write(dataWriter);
    dataWriter << mIDirectionIncrement;
    dataWriter << mN;
    mScanningMode.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void GaussianSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void GaussianSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "GaussianSettings\n";
    mGrid.print(stream, level + 1, optionFlags);
    stream << space(level) << "- IDirectionIncrement = " << toString(mIDirectionIncrement) << "\n";
    stream << space(level) << "- N = " << toString(mN) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
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
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mGrid} attribute. */

GridSettings *GaussianSettings::getGrid() const {
  try {
    return static_cast<GridSettings *>(&mGrid);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mIDirectionIncrement} attribute. */

const T::UInt32_opt &GaussianSettings::getIDirectionIncrement() const {
  try {
    return mIDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mN} attribute. */

const T::UInt32_opt &GaussianSettings::getN() const {
  try {
    return mN;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *GaussianSettings::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void GaussianSettings::setGrid(GridSettings &grid) {
  try {
    mGrid = grid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void GaussianSettings::setIDirectionIncrement(T::UInt32_opt iDirectionIncrement) {
  try {
    mIDirectionIncrement = iDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void GaussianSettings::setN(T::UInt32_opt n) {
  try {
    mN = n;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void GaussianSettings::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
