// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GridStretchingSettingsImpl.*' files.
// ***********************************************************************

#include "GridStretchingSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

GridStretchingSettings::GridStretchingSettings() {
  try {
    mLatitudeOfStretchingPole = 0;
    mLongitudeOfStretchingPole = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

GridStretchingSettings::~GridStretchingSettings() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridStretchingSettings::read(MemoryReader &memoryReader) {
  try {
    mLatitudeOfStretchingPole = memoryReader.read_int24();
    mLongitudeOfStretchingPole = memoryReader.read_int24();
    mStretchingFactor = memoryReader.read_ibmFloat();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void GridStretchingSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter.write_int24(mLatitudeOfStretchingPole);
    dataWriter.write_int24(mLongitudeOfStretchingPole);
    dataWriter << mStretchingFactor;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void GridStretchingSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sGridStretchingSettings.LatitudeOfStretchingPole", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfStretchingPole));
    sprintf(name, "%sGridStretchingSettings.LongitudeOfStretchingPole", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfStretchingPole));
    sprintf(name, "%sGridStretchingSettings.StretchingFactor", prefix.c_str());
    attributeList.addAttribute(name, toString(mStretchingFactor));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void GridStretchingSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "GridStretchingSettings\n";
    stream << space(level) << "- LatitudeOfStretchingPole = " << toString(mLatitudeOfStretchingPole) << "\n";
    stream << space(level) << "- LongitudeOfStretchingPole = " << toString(mLongitudeOfStretchingPole) << "\n";
    stream << space(level) << "- StretchingFactor = " << toString(mStretchingFactor) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash GridStretchingSettings::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mLatitudeOfStretchingPole);
    boost::hash_combine(seed, mLongitudeOfStretchingPole);
    boost::hash_combine(seed, mStretchingFactor);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfStretchingPole} attribute. */

std::int24_t GridStretchingSettings::getLatitudeOfStretchingPole() const {
  try {
    return mLatitudeOfStretchingPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfStretchingPole} attribute. */

std::int24_t GridStretchingSettings::getLongitudeOfStretchingPole() const {
  try {
    return mLongitudeOfStretchingPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mStretchingFactor} attribute. */

ibmfloat GridStretchingSettings::getStretchingFactor() const {
  try {
    return mStretchingFactor;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridStretchingSettings::setLatitudeOfStretchingPole(std::int24_t latitudeOfStretchingPole) {
  try {
    mLatitudeOfStretchingPole = latitudeOfStretchingPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridStretchingSettings::setLongitudeOfStretchingPole(std::int24_t longitudeOfStretchingPole) {
  try {
    mLongitudeOfStretchingPole = longitudeOfStretchingPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridStretchingSettings::setStretchingFactor(ibmfloat stretchingFactor) {
  try {
    mStretchingFactor = stretchingFactor;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
