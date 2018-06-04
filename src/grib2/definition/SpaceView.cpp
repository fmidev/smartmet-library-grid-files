// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SpaceViewImpl.*' files.
// ***********************************************************************

#include "SpaceView.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SpaceView::SpaceView() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

SpaceView::~SpaceView() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SpaceView::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mNx = memoryReader.read_UInt32_opt();
    mNy = memoryReader.read_UInt32_opt();
    mLatitudeOfSubSatellitePoint = memoryReader.read_Int32_opt();
    mLongitudeOfSubSatellitePoint = memoryReader.read_Int32_opt();
    mResolution.read(memoryReader);
    mDx = memoryReader.read_UInt32_opt();
    mDy = memoryReader.read_UInt32_opt();
    mXp = memoryReader.read_UInt32_opt();
    mYp = memoryReader.read_UInt32_opt();
    mScanningMode.read(memoryReader);
    mOrientationOfTheGrid = memoryReader.read_Int32_opt();
    mNr = memoryReader.read_UInt32_opt();
    mXo = memoryReader.read_UInt32_opt();
    mYo = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SpaceView::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSpaceView.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sSpaceView.Nx", prefix.c_str());
    attributeList.addAttribute(name, toString(mNx));
    sprintf(name, "%sSpaceView.Ny", prefix.c_str());
    attributeList.addAttribute(name, toString(mNy));
    sprintf(name, "%sSpaceView.LatitudeOfSubSatellitePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfSubSatellitePoint));
    sprintf(name, "%sSpaceView.LongitudeOfSubSatellitePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfSubSatellitePoint));
    sprintf(name, "%sSpaceView.", prefix.c_str());
    mResolution.getAttributeList(name, attributeList);
    sprintf(name, "%sSpaceView.Dx", prefix.c_str());
    attributeList.addAttribute(name, toString(mDx));
    sprintf(name, "%sSpaceView.Dy", prefix.c_str());
    attributeList.addAttribute(name, toString(mDy));
    sprintf(name, "%sSpaceView.Xp", prefix.c_str());
    attributeList.addAttribute(name, toString(mXp));
    sprintf(name, "%sSpaceView.Yp", prefix.c_str());
    attributeList.addAttribute(name, toString(mYp));
    sprintf(name, "%sSpaceView.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sSpaceView.OrientationOfTheGrid", prefix.c_str());
    attributeList.addAttribute(name, toString(mOrientationOfTheGrid));
    sprintf(name, "%sSpaceView.Nr", prefix.c_str());
    attributeList.addAttribute(name, toString(mNr));
    sprintf(name, "%sSpaceView.Xo", prefix.c_str());
    attributeList.addAttribute(name, toString(mXo));
    sprintf(name, "%sSpaceView.Yo", prefix.c_str());
    attributeList.addAttribute(name, toString(mYo));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SpaceView::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SpaceView\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Nx = " << toString(mNx) << "\n";
    stream << space(level) << "- Ny = " << toString(mNy) << "\n";
    stream << space(level) << "- LatitudeOfSubSatellitePoint = " << toString(mLatitudeOfSubSatellitePoint) << "\n";
    stream << space(level) << "- LongitudeOfSubSatellitePoint = " << toString(mLongitudeOfSubSatellitePoint) << "\n";
    mResolution.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Dx = " << toString(mDx) << "\n";
    stream << space(level) << "- Dy = " << toString(mDy) << "\n";
    stream << space(level) << "- Xp = " << toString(mXp) << "\n";
    stream << space(level) << "- Yp = " << toString(mYp) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- OrientationOfTheGrid = " << toString(mOrientationOfTheGrid) << "\n";
    stream << space(level) << "- Nr = " << toString(mNr) << "\n";
    stream << space(level) << "- Xo = " << toString(mXo) << "\n";
    stream << space(level) << "- Yo = " << toString(mYo) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SpaceView::countHash() {
  try {
    std::size_t seed = 0;
    if (mNx)
      boost::hash_combine(seed, *mNx);
    if (mNy)
      boost::hash_combine(seed, *mNy);
    if (mLatitudeOfSubSatellitePoint)
      boost::hash_combine(seed, *mLatitudeOfSubSatellitePoint);
    if (mLongitudeOfSubSatellitePoint)
      boost::hash_combine(seed, *mLongitudeOfSubSatellitePoint);
    if (mDx)
      boost::hash_combine(seed, *mDx);
    if (mDy)
      boost::hash_combine(seed, *mDy);
    if (mXp)
      boost::hash_combine(seed, *mXp);
    if (mYp)
      boost::hash_combine(seed, *mYp);
    if (mOrientationOfTheGrid)
      boost::hash_combine(seed, *mOrientationOfTheGrid);
    if (mNr)
      boost::hash_combine(seed, *mNr);
    if (mXo)
      boost::hash_combine(seed, *mXo);
    if (mYo)
      boost::hash_combine(seed, *mYo);
    // boost::hash_combine(seed,mEarthShape.countHash());
    // boost::hash_combine(seed,mResolution.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

const EarthShapeSettings *SpaceView::getEarthShape() const {
  try {
    return &mEarthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNx} attribute. */

const T::UInt32_opt &SpaceView::getNx() const {
  try {
    return mNx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNy} attribute. */

const T::UInt32_opt &SpaceView::getNy() const {
  try {
    return mNy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfSubSatellitePoint} attribute. */

const T::Int32_opt &SpaceView::getLatitudeOfSubSatellitePoint() const {
  try {
    return mLatitudeOfSubSatellitePoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfSubSatellitePoint} attribute. */

const T::Int32_opt &SpaceView::getLongitudeOfSubSatellitePoint() const {
  try {
    return mLongitudeOfSubSatellitePoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mResolution} attribute. */

const ResolutionSettings *SpaceView::getResolution() const {
  try {
    return &mResolution;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mDx} attribute. */

const T::UInt32_opt &SpaceView::getDx() const {
  try {
    return mDx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mDy} attribute. */

const T::UInt32_opt &SpaceView::getDy() const {
  try {
    return mDy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mXp} attribute. */

const T::UInt32_opt &SpaceView::getXp() const {
  try {
    return mXp;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mYp} attribute. */

const T::UInt32_opt &SpaceView::getYp() const {
  try {
    return mYp;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

const ScanningModeSettings *SpaceView::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mOrientationOfTheGrid} attribute. */

const T::Int32_opt &SpaceView::getOrientationOfTheGrid() const {
  try {
    return mOrientationOfTheGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNr} attribute. */

const T::UInt32_opt &SpaceView::getNr() const {
  try {
    return mNr;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mXo} attribute. */

const T::UInt32_opt &SpaceView::getXo() const {
  try {
    return mXo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mYo} attribute. */

const T::UInt32_opt &SpaceView::getYo() const {
  try {
    return mYo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setEarthShape(EarthShapeSettings earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setNx(T::UInt32_opt nx) {
  try {
    mNx = nx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setNy(T::UInt32_opt ny) {
  try {
    mNy = ny;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setLatitudeOfSubSatellitePoint(T::Int32_opt latitudeOfSubSatellitePoint) {
  try {
    mLatitudeOfSubSatellitePoint = latitudeOfSubSatellitePoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setLongitudeOfSubSatellitePoint(T::Int32_opt longitudeOfSubSatellitePoint) {
  try {
    mLongitudeOfSubSatellitePoint = longitudeOfSubSatellitePoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setResolution(ResolutionSettings resolution) {
  try {
    mResolution = resolution;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setDx(T::UInt32_opt dx) {
  try {
    mDx = dx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setDy(T::UInt32_opt dy) {
  try {
    mDy = dy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setXp(T::UInt32_opt xp) {
  try {
    mXp = xp;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setYp(T::UInt32_opt yp) {
  try {
    mYp = yp;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setScanningMode(ScanningModeSettings scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setOrientationOfTheGrid(T::Int32_opt orientationOfTheGrid) {
  try {
    mOrientationOfTheGrid = orientationOfTheGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setNr(T::UInt32_opt nr) {
  try {
    mNr = nr;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setXo(T::UInt32_opt xo) {
  try {
    mXo = xo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void SpaceView::setYo(T::UInt32_opt yo) {
  try {
    mYo = yo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
