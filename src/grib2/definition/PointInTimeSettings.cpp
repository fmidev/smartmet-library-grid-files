// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PointInTimeSettingsImpl.*' files.
// ***********************************************************************

#include "grib2/definition/PointInTimeSettings.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PointInTimeSettings::PointInTimeSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

PointInTimeSettings::~PointInTimeSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PointInTimeSettings::read(MemoryReader &memoryReader) {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void PointInTimeSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void PointInTimeSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "PointInTimeSettings\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash PointInTimeSettings::countHash() {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
