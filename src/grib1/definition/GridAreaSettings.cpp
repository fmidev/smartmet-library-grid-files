// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GridAreaSettingsImpl.*' files.
// ***********************************************************************

#include "GridAreaSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

GridAreaSettings::GridAreaSettings() {
  try {
    mLatitudeOfFirstGridPoint = 0;
    mLongitudeOfFirstGridPoint = 0;
    mLatitudeOfLastGridPoint = 0;
    mLongitudeOfLastGridPoint = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

GridAreaSettings::~GridAreaSettings() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridAreaSettings::read(MemoryReader &memoryReader) {
  try {
    mLatitudeOfFirstGridPoint = memoryReader.read_int24();
    mLongitudeOfFirstGridPoint = memoryReader.read_int24();
    mResolutionFlags.read(memoryReader);
    mLatitudeOfLastGridPoint = memoryReader.read_int24();
    mLongitudeOfLastGridPoint = memoryReader.read_int24();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void GridAreaSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter.write_int24(mLatitudeOfFirstGridPoint);
    dataWriter.write_int24(mLongitudeOfFirstGridPoint);
    mResolutionFlags.write(dataWriter);
    dataWriter.write_int24(mLatitudeOfLastGridPoint);
    dataWriter.write_int24(mLongitudeOfLastGridPoint);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void GridAreaSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sGridAreaSettings.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sGridAreaSettings.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sGridAreaSettings.", prefix.c_str());
    mResolutionFlags.getAttributeList(name, attributeList);
    sprintf(name, "%sGridAreaSettings.LatitudeOfLastGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfLastGridPoint));
    sprintf(name, "%sGridAreaSettings.LongitudeOfLastGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfLastGridPoint));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void GridAreaSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "GridAreaSettings\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    mResolutionFlags.print(stream, level + 1, optionFlags);
    stream << space(level) << "- LatitudeOfLastGridPoint = " << toString(mLatitudeOfLastGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfLastGridPoint = " << toString(mLongitudeOfLastGridPoint) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash GridAreaSettings::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mLatitudeOfFirstGridPoint);
    boost::hash_combine(seed, mLongitudeOfFirstGridPoint);
    // boost::hash_combine(seed,mLatitudeOfLastGridPoint);
    // boost::hash_combine(seed,mLongitudeOfLastGridPoint);
    // boost::hash_combine(seed,mResolutionFlags.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

std::int24_t GridAreaSettings::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

std::int24_t GridAreaSettings::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mResolutionFlags} attribute. */

ResolutionFlagsSettings *GridAreaSettings::getResolutionFlags() const {
  try {
    return static_cast<ResolutionFlagsSettings *>(&mResolutionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfLastGridPoint} attribute. */

std::int24_t GridAreaSettings::getLatitudeOfLastGridPoint() const {
  try {
    return mLatitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfLastGridPoint} attribute. */

std::int24_t GridAreaSettings::getLongitudeOfLastGridPoint() const {
  try {
    return mLongitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridAreaSettings::setLatitudeOfFirstGridPoint(std::int24_t latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridAreaSettings::setLongitudeOfFirstGridPoint(std::int24_t longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridAreaSettings::setResolutionFlags(ResolutionFlagsSettings &resolutionFlags) {
  try {
    mResolutionFlags = resolutionFlags;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridAreaSettings::setLatitudeOfLastGridPoint(std::int24_t latitudeOfLastGridPoint) {
  try {
    mLatitudeOfLastGridPoint = latitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridAreaSettings::setLongitudeOfLastGridPoint(std::int24_t longitudeOfLastGridPoint) {
  try {
    mLongitudeOfLastGridPoint = longitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
