// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedLatLonImpl.*' files.
// ***********************************************************************

#include "StretchedLatLon.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

StretchedLatLon::StretchedLatLon() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

StretchedLatLon::StretchedLatLon(const StretchedLatLon &other) : GridDefinition(other) {
  try {
    mEarthShape = other.mEarthShape;
    mLatLon = other.mLatLon;
    mStretching = other.mStretching;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

StretchedLatLon::~StretchedLatLon() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void StretchedLatLon::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mLatLon.read(memoryReader);
    mStretching.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void StretchedLatLon::write(DataWriter &dataWriter) {
  try {
    mEarthShape.write(dataWriter);
    mLatLon.write(dataWriter);
    mStretching.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void StretchedLatLon::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sStretchedLatLon.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedLatLon.", prefix.c_str());
    mLatLon.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedLatLon.", prefix.c_str());
    mStretching.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void StretchedLatLon::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "StretchedLatLon\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    mLatLon.print(stream, level + 1, optionFlags);
    mStretching.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash StretchedLatLon::countHash() {
  try {
    std::size_t seed = 0;
    // boost::hash_combine(seed,mEarthShape.countHash());
    boost::hash_combine(seed, mLatLon.countHash());
    boost::hash_combine(seed, mStretching.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint StretchedLatLon::getTemplateNumber() const {
  return 2;
}

GridDefinition *StretchedLatLon::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new StretchedLatLon(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

EarthShapeSettings *StretchedLatLon::getEarthShape() const {
  try {
    return static_cast<EarthShapeSettings *>(&mEarthShape);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mLatLon} attribute. */

LatLonSettings *StretchedLatLon::getLatLon() const {
  try {
    return static_cast<LatLonSettings *>(&mLatLon);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStretching} attribute. */

StretchingSettings *StretchedLatLon::getStretching() const {
  try {
    return static_cast<StretchingSettings *>(&mStretching);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void StretchedLatLon::setEarthShape(EarthShapeSettings &earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void StretchedLatLon::setLatLon(LatLonSettings &latLon) {
  try {
    mLatLon = latLon;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void StretchedLatLon::setStretching(StretchingSettings &stretching) {
  try {
    mStretching = stretching;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
