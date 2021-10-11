// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'LatLonImpl.*' files.
// ***********************************************************************

#include "LatLon.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

LatLon::LatLon() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

LatLon::~LatLon() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void LatLon::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mLatLon.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void LatLon::write(DataWriter &dataWriter) {
  try {
    mEarthShape.write(dataWriter);
    mLatLon.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void LatLon::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sLatLon.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sLatLon.", prefix.c_str());
    mLatLon.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool LatLon::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mEarthShape.getAttributeValue(attributeName, attributeValue))
      return true;
    if (mLatLon.getAttributeValue(attributeName, attributeValue))
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool LatLon::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mEarthShape.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (mLatLon.hasAttributeValue(attributeName, attributeValue))
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void LatLon::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "LatLon\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    mLatLon.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash LatLon::countHash() const {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint LatLon::getTemplateNumber() const {
  return 0;
}

GridDefinition *LatLon::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new LatLon(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

EarthShapeSettings *LatLon::getEarthShape() const {
  try {
    return static_cast<EarthShapeSettings *>(&mEarthShape);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mLatLon} attribute. */

LatLonSettings *LatLon::getLatLon() const {
  try {
    return static_cast<LatLonSettings *>(&mLatLon);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LatLon::setEarthShape(EarthShapeSettings &earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LatLon::setLatLon(LatLonSettings &latLon) {
  try {
    mLatLon = latLon;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
