// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotationSettingsImpl.*' files.
// ***********************************************************************

#include "RotationSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

RotationSettings::RotationSettings() {
  try {
    mLatitudeOfSouthernPole = 0;
    mLongitudeOfSouthernPole = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

RotationSettings::~RotationSettings() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void RotationSettings::read(MemoryReader &memoryReader) {
  try {
    mLatitudeOfSouthernPole = memoryReader.read_int24();
    mLongitudeOfSouthernPole = memoryReader.read_int24();
    mGeography_angleOfRotationInDegrees = memoryReader.read_ibmFloat();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void RotationSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter.write_int24(mLatitudeOfSouthernPole);
    dataWriter.write_int24(mLongitudeOfSouthernPole);
    dataWriter << mGeography_angleOfRotationInDegrees;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void RotationSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sRotationSettings.LatitudeOfSouthernPole", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfSouthernPole));
    sprintf(name, "%sRotationSettings.LongitudeOfSouthernPole", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfSouthernPole));
    sprintf(name, "%sRotationSettings.Geography_angleOfRotationInDegrees", prefix.c_str());
    attributeList.addAttribute(name, toString(mGeography_angleOfRotationInDegrees));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void RotationSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "RotationSettings\n";
    stream << space(level) << "- LatitudeOfSouthernPole = " << toString(mLatitudeOfSouthernPole) << "\n";
    stream << space(level) << "- LongitudeOfSouthernPole = " << toString(mLongitudeOfSouthernPole) << "\n";
    stream << space(level) << "- Geography_angleOfRotationInDegrees = " << toString(mGeography_angleOfRotationInDegrees) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash RotationSettings::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mLatitudeOfSouthernPole);
    boost::hash_combine(seed, mLongitudeOfSouthernPole);
    boost::hash_combine(seed, mGeography_angleOfRotationInDegrees);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfSouthernPole} attribute. */

std::int24_t RotationSettings::getLatitudeOfSouthernPole() const {
  try {
    return mLatitudeOfSouthernPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfSouthernPole} attribute. */

std::int24_t RotationSettings::getLongitudeOfSouthernPole() const {
  try {
    return mLongitudeOfSouthernPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mGeography_angleOfRotationInDegrees} attribute. */

ibmfloat RotationSettings::getGeography_angleOfRotationInDegrees() const {
  try {
    return mGeography_angleOfRotationInDegrees;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotationSettings::setLatitudeOfSouthernPole(std::int24_t latitudeOfSouthernPole) {
  try {
    mLatitudeOfSouthernPole = latitudeOfSouthernPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotationSettings::setLongitudeOfSouthernPole(std::int24_t longitudeOfSouthernPole) {
  try {
    mLongitudeOfSouthernPole = longitudeOfSouthernPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotationSettings::setGeography_angleOfRotationInDegrees(ibmfloat geography_angleOfRotationInDegrees) {
  try {
    mGeography_angleOfRotationInDegrees = geography_angleOfRotationInDegrees;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
