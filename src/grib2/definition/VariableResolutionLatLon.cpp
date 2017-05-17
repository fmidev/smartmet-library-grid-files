// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'VariableResolutionLatLonImpl.*' files.
// ***********************************************************************

#include "grib2/definition/VariableResolutionLatLon.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

VariableResolutionLatLon::VariableResolutionLatLon() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

VariableResolutionLatLon::~VariableResolutionLatLon() {
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

void VariableResolutionLatLon::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mVariableLatLon.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void VariableResolutionLatLon::getAttributeList(
    std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sVariableResolutionLatLon.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sVariableResolutionLatLon.", prefix.c_str());
    mVariableLatLon.getAttributeList(name, attributeList);
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

void VariableResolutionLatLon::print(std::ostream &stream, uint level,
                                     uint optionFlags) const {
  try {
    stream << space(level) << "VariableResolutionLatLon\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    mVariableLatLon.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash VariableResolutionLatLon::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mEarthShape.countHash());
    boost::hash_combine(seed, mVariableLatLon.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute.
 */

const EarthShapeSettings *VariableResolutionLatLon::getEarthShape() const {
  try {
    return &mEarthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mVariableLatLon}
 * attribute. */

const VariableLatLonSettings *
VariableResolutionLatLon::getVariableLatLon() const {
  try {
    return &mVariableLatLon;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
