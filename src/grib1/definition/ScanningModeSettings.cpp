// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ScanningModeSettingsImpl.*' files.
// ***********************************************************************

#include "ScanningModeSettings.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

ScanningModeSettings::ScanningModeSettings() {
  try {
    mScanningMode = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The copy constructor of the class. */

ScanningModeSettings::ScanningModeSettings(const ScanningModeSettings &other) {
  try {
    mScanningMode = other.mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

ScanningModeSettings::~ScanningModeSettings() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ScanningModeSettings::read(MemoryReader &memoryReader) {
  try {
    mScanningMode = memoryReader.read_uint8();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void ScanningModeSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ScanningModeSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sScanningModeSettings.ScanningMode", prefix.c_str());
    attributeList.addAttribute(name, toString(mScanningMode));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ScanningModeSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ScanningModeSettings\n";
    stream << space(level) << "- ScanningMode = " << toString(mScanningMode) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ScanningModeSettings::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mScanningMode);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mScanningMode} attribute. */

std::uint8_t ScanningModeSettings::getScanningMode() const {
  try {
    return mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void ScanningModeSettings::setScanningMode(std::uint8_t scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB1
} // namespace SmartMet
