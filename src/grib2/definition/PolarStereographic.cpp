// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PolarStereographicImpl.*' files.
// ***********************************************************************

#include "PolarStereographic.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PolarStereographic::PolarStereographic() {
  try {
    mResolutionAndComponentFlags = 0;
    mProjectionCentreFlag = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

PolarStereographic::~PolarStereographic() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PolarStereographic::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mNx = memoryReader.read_UInt32_opt();
    mNy = memoryReader.read_UInt32_opt();
    mLatitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfFirstGridPoint = memoryReader.read_UInt32_opt();
    mResolutionAndComponentFlags = memoryReader.read_uint8();
    mLaD = memoryReader.read_Int32_opt();
    mOrientationOfTheGrid = memoryReader.read_Int32_opt();
    mDx = memoryReader.read_UInt32_opt();
    mDy = memoryReader.read_UInt32_opt();
    mProjectionCentreFlag = memoryReader.read_uint8();
    mScanningMode.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void PolarStereographic::write(DataWriter &dataWriter) {
  try {
    mEarthShape.write(dataWriter);
    dataWriter << mNx;
    dataWriter << mNy;
    dataWriter << mLatitudeOfFirstGridPoint;
    dataWriter << mLongitudeOfFirstGridPoint;
    dataWriter << mResolutionAndComponentFlags;
    dataWriter << mLaD;
    dataWriter << mOrientationOfTheGrid;
    dataWriter << mDx;
    dataWriter << mDy;
    dataWriter << mProjectionCentreFlag;
    mScanningMode.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void PolarStereographic::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sPolarStereographic.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sPolarStereographic.Nx", prefix.c_str());
    attributeList.addAttribute(name, toString(mNx));
    sprintf(name, "%sPolarStereographic.Ny", prefix.c_str());
    attributeList.addAttribute(name, toString(mNy));
    sprintf(name, "%sPolarStereographic.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sPolarStereographic.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sPolarStereographic.ResolutionAndComponentFlags", prefix.c_str());
    attributeList.addAttribute(name, toString(mResolutionAndComponentFlags));
    sprintf(name, "%sPolarStereographic.LaD", prefix.c_str());
    attributeList.addAttribute(name, toString(mLaD));
    sprintf(name, "%sPolarStereographic.OrientationOfTheGrid", prefix.c_str());
    attributeList.addAttribute(name, toString(mOrientationOfTheGrid));
    sprintf(name, "%sPolarStereographic.Dx", prefix.c_str());
    attributeList.addAttribute(name, toString(mDx));
    sprintf(name, "%sPolarStereographic.Dy", prefix.c_str());
    attributeList.addAttribute(name, toString(mDy));
    sprintf(name, "%sPolarStereographic.ProjectionCentreFlag", prefix.c_str());
    attributeList.addAttribute(name, toString(mProjectionCentreFlag));
    sprintf(name, "%sPolarStereographic.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void PolarStereographic::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "PolarStereographic\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Nx = " << toString(mNx) << "\n";
    stream << space(level) << "- Ny = " << toString(mNy) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- ResolutionAndComponentFlags = " << toString(mResolutionAndComponentFlags) << "\n";
    stream << space(level) << "- LaD = " << toString(mLaD) << "\n";
    stream << space(level) << "- OrientationOfTheGrid = " << toString(mOrientationOfTheGrid) << "\n";
    stream << space(level) << "- Dx = " << toString(mDx) << "\n";
    stream << space(level) << "- Dy = " << toString(mDy) << "\n";
    stream << space(level) << "- ProjectionCentreFlag = " << toString(mProjectionCentreFlag) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash PolarStereographic::countHash() {
  try {
    std::size_t seed = 0;
    if (mNx)
      boost::hash_combine(seed, *mNx);
    if (mNy)
      boost::hash_combine(seed, *mNy);
    if (mLatitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLatitudeOfFirstGridPoint);
    if (mLongitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLongitudeOfFirstGridPoint);
    boost::hash_combine(seed, mResolutionAndComponentFlags);
    if (mLaD)
      boost::hash_combine(seed, *mLaD);
    if (mOrientationOfTheGrid)
      boost::hash_combine(seed, *mOrientationOfTheGrid);
    if (mDx)
      boost::hash_combine(seed, *mDx);
    if (mDy)
      boost::hash_combine(seed, *mDy);
    boost::hash_combine(seed, mProjectionCentreFlag);
    // boost::hash_combine(seed,mEarthShape.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint PolarStereographic::getTemplateNumber() const {
  return 20;
}

GridDefinition *PolarStereographic::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new PolarStereographic(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

EarthShapeSettings *PolarStereographic::getEarthShape() const {
  try {
    return static_cast<EarthShapeSettings *>(&mEarthShape);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNx} attribute. */

const T::UInt32_opt &PolarStereographic::getNx() const {
  try {
    return mNx;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNy} attribute. */

const T::UInt32_opt &PolarStereographic::getNy() const {
  try {
    return mNy;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

const T::Int32_opt &PolarStereographic::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

const T::UInt32_opt &PolarStereographic::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mResolutionAndComponentFlags} attribute. */

std::uint8_t PolarStereographic::getResolutionAndComponentFlags() const {
  try {
    return mResolutionAndComponentFlags;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLaD} attribute. */

const T::Int32_opt &PolarStereographic::getLaD() const {
  try {
    return mLaD;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mOrientationOfTheGrid} attribute. */

const T::Int32_opt &PolarStereographic::getOrientationOfTheGrid() const {
  try {
    return mOrientationOfTheGrid;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDx} attribute. */

const T::UInt32_opt &PolarStereographic::getDx() const {
  try {
    return mDx;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDy} attribute. */

const T::UInt32_opt &PolarStereographic::getDy() const {
  try {
    return mDy;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mProjectionCentreFlag} attribute. */

std::uint8_t PolarStereographic::getProjectionCentreFlag() const {
  try {
    return mProjectionCentreFlag;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *PolarStereographic::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setEarthShape(EarthShapeSettings &earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setNx(T::UInt32_opt nx) {
  try {
    mNx = nx;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setNy(T::UInt32_opt ny) {
  try {
    mNy = ny;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setLongitudeOfFirstGridPoint(T::UInt32_opt longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setResolutionAndComponentFlags(std::uint8_t resolutionAndComponentFlags) {
  try {
    mResolutionAndComponentFlags = resolutionAndComponentFlags;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setLaD(T::Int32_opt laD) {
  try {
    mLaD = laD;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setOrientationOfTheGrid(T::Int32_opt orientationOfTheGrid) {
  try {
    mOrientationOfTheGrid = orientationOfTheGrid;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setDx(T::UInt32_opt dx) {
  try {
    mDx = dx;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setDy(T::UInt32_opt dy) {
  try {
    mDy = dy;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setProjectionCentreFlag(std::uint8_t projectionCentreFlag) {
  try {
    mProjectionCentreFlag = projectionCentreFlag;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PolarStereographic::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
