// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ResolutionSettingsImpl.*' files.
// ***********************************************************************

#include "grib2/definition/ResolutionSettings.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

ResolutionSettings::ResolutionSettings() {
  try {
    mResolutionAndComponentFlags = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

ResolutionSettings::~ResolutionSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ResolutionSettings::read(MemoryReader &memoryReader) {
  try {
    mResolutionAndComponentFlags = memoryReader.read_uint8();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ResolutionSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sResolutionSettings.ResolutionAndComponentFlags", prefix.c_str());
    attributeList.addAttribute(name, toString(mResolutionAndComponentFlags));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ResolutionSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ResolutionSettings\n";
    stream << space(level) << "- ResolutionAndComponentFlags = " << toString(mResolutionAndComponentFlags) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ResolutionSettings::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mResolutionAndComponentFlags);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mResolutionAndComponentFlags} attribute. */

std::uint8_t ResolutionSettings::getResolutionAndComponentFlags() const {
  try {
    return mResolutionAndComponentFlags;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void ResolutionSettings::setResolutionAndComponentFlags(std::uint8_t resolutionAndComponentFlags) {
  try {
    mResolutionAndComponentFlags = resolutionAndComponentFlags;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
