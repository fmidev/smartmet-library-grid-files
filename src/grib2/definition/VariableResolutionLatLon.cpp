// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'VariableResolutionLatLonImpl.*' files.
// ***********************************************************************

#include "VariableResolutionLatLon.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

VariableResolutionLatLon::VariableResolutionLatLon() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

VariableResolutionLatLon::~VariableResolutionLatLon() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void VariableResolutionLatLon::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mVariableLatLon.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void VariableResolutionLatLon::write(DataWriter &dataWriter) {
  try {
    mEarthShape.write(dataWriter);
    mVariableLatLon.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void VariableResolutionLatLon::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sVariableResolutionLatLon.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sVariableResolutionLatLon.", prefix.c_str());
    mVariableLatLon.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void VariableResolutionLatLon::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "VariableResolutionLatLon\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    mVariableLatLon.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash VariableResolutionLatLon::countHash() {
  try {
    std::size_t seed = 0;
    // boost::hash_combine(seed,mEarthShape.countHash());
    boost::hash_combine(seed, mVariableLatLon.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint VariableResolutionLatLon::getTemplateNumber() const {
  return 4;
}

GridDefinition *VariableResolutionLatLon::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new VariableResolutionLatLon(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

EarthShapeSettings *VariableResolutionLatLon::getEarthShape() const {
  try {
    return static_cast<EarthShapeSettings *>(&mEarthShape);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mVariableLatLon} attribute. */

VariableLatLonSettings *VariableResolutionLatLon::getVariableLatLon() const {
  try {
    return static_cast<VariableLatLonSettings *>(&mVariableLatLon);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void VariableResolutionLatLon::setEarthShape(EarthShapeSettings &earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void VariableResolutionLatLon::setVariableLatLon(VariableLatLonSettings &variableLatLon) {
  try {
    mVariableLatLon = variableLatLon;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
