// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedRotatedGaussianImpl.*' files.
// ***********************************************************************

#include "StretchedRotatedGaussian.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

StretchedRotatedGaussian::StretchedRotatedGaussian() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

StretchedRotatedGaussian::~StretchedRotatedGaussian() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void StretchedRotatedGaussian::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mGaussian.read(memoryReader);
    mRotation.read(memoryReader);
    mStretching.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void StretchedRotatedGaussian::write(DataWriter &dataWriter) {
  try {
    mEarthShape.write(dataWriter);
    mGaussian.write(dataWriter);
    mRotation.write(dataWriter);
    mStretching.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void StretchedRotatedGaussian::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sStretchedRotatedGaussian.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedRotatedGaussian.", prefix.c_str());
    mGaussian.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedRotatedGaussian.", prefix.c_str());
    mRotation.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedRotatedGaussian.", prefix.c_str());
    mStretching.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void StretchedRotatedGaussian::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "StretchedRotatedGaussian\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    mGaussian.print(stream, level + 1, optionFlags);
    mRotation.print(stream, level + 1, optionFlags);
    mStretching.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash StretchedRotatedGaussian::countHash() {
  try {
    std::size_t seed = 0;
    // boost::hash_combine(seed,mEarthShape.countHash());
    boost::hash_combine(seed, mGaussian.countHash());
    boost::hash_combine(seed, mRotation.countHash());
    boost::hash_combine(seed, mStretching.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint StretchedRotatedGaussian::getTemplateNumber() const {
  return 43;
}

GridDefinition *StretchedRotatedGaussian::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new StretchedRotatedGaussian(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

EarthShapeSettings *StretchedRotatedGaussian::getEarthShape() const {
  try {
    return static_cast<EarthShapeSettings *>(&mEarthShape);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mGaussian} attribute. */

GaussianSettings *StretchedRotatedGaussian::getGaussian() const {
  try {
    return static_cast<GaussianSettings *>(&mGaussian);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mRotation} attribute. */

RotationSettings *StretchedRotatedGaussian::getRotation() const {
  try {
    return static_cast<RotationSettings *>(&mRotation);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStretching} attribute. */

StretchingSettings *StretchedRotatedGaussian::getStretching() const {
  try {
    return static_cast<StretchingSettings *>(&mStretching);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedRotatedGaussian::setEarthShape(EarthShapeSettings &earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedRotatedGaussian::setGaussian(GaussianSettings &gaussian) {
  try {
    mGaussian = gaussian;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedRotatedGaussian::setRotation(RotationSettings &rotation) {
  try {
    mRotation = rotation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedRotatedGaussian::setStretching(StretchingSettings &stretching) {
  try {
    mStretching = stretching;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
