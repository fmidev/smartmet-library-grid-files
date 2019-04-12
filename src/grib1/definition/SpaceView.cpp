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
namespace GRIB1 {

/*! \brief The constructor of the class. */

SpaceView::SpaceView() {
  try {
    mNx = 0;
    mNy = 0;
    mLatitudeOfSubSatellitePoint = 0;
    mLongitudeOfSubSatellitePoint = 0;
    mDx = 0;
    mDy = 0;
    mXpInGridLengths = 0;
    mYpInGridLengths = 0;
    mOrientationOfTheGrid = 0;
    mNrInRadiusOfEarth = 0;
    mXo = 0;
    mYo = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

SpaceView::SpaceView(const SpaceView &other) : GridDefinition(other) {
  try {
    mNx = other.mNx;
    mNy = other.mNy;
    mLatitudeOfSubSatellitePoint = other.mLatitudeOfSubSatellitePoint;
    mLongitudeOfSubSatellitePoint = other.mLongitudeOfSubSatellitePoint;
    mResolutionFlags = other.mResolutionFlags;
    mDx = other.mDx;
    mDy = other.mDy;
    mXpInGridLengths = other.mXpInGridLengths;
    mYpInGridLengths = other.mYpInGridLengths;
    mScanningMode = other.mScanningMode;
    mOrientationOfTheGrid = other.mOrientationOfTheGrid;
    mNrInRadiusOfEarth = other.mNrInRadiusOfEarth;
    mXo = other.mXo;
    mYo = other.mYo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

SpaceView::~SpaceView() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SpaceView::read(MemoryReader &memoryReader) {
  try {
    mNx = memoryReader.read_uint16();
    mNy = memoryReader.read_uint16();
    mLatitudeOfSubSatellitePoint = memoryReader.read_int24();
    mLongitudeOfSubSatellitePoint = memoryReader.read_int24();
    mResolutionFlags.read(memoryReader);
    mDx = memoryReader.read_uint24();
    mDy = memoryReader.read_uint24();
    mXpInGridLengths = memoryReader.read_uint16();
    mYpInGridLengths = memoryReader.read_uint16();
    mScanningMode.read(memoryReader);
    mOrientationOfTheGrid = memoryReader.read_uint24();
    mNrInRadiusOfEarth = memoryReader.read_uint24();
    mXo = memoryReader.read_uint16();
    mYo = memoryReader.read_uint16();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void SpaceView::write(DataWriter &dataWriter) {
  try {
    dataWriter << mNx;
    dataWriter << mNy;
    dataWriter.write_int24(mLatitudeOfSubSatellitePoint);
    dataWriter.write_int24(mLongitudeOfSubSatellitePoint);
    mResolutionFlags.write(dataWriter);
    dataWriter.write_uint24(mDx);
    dataWriter.write_uint24(mDy);
    dataWriter << mXpInGridLengths;
    dataWriter << mYpInGridLengths;
    mScanningMode.write(dataWriter);
    dataWriter.write_uint24(mOrientationOfTheGrid);
    dataWriter.write_uint24(mNrInRadiusOfEarth);
    dataWriter << mXo;
    dataWriter << mYo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SpaceView::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSpaceView.Nx", prefix.c_str());
    attributeList.addAttribute(name, toString(mNx));
    sprintf(name, "%sSpaceView.Ny", prefix.c_str());
    attributeList.addAttribute(name, toString(mNy));
    sprintf(name, "%sSpaceView.LatitudeOfSubSatellitePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfSubSatellitePoint));
    sprintf(name, "%sSpaceView.LongitudeOfSubSatellitePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfSubSatellitePoint));
    sprintf(name, "%sSpaceView.", prefix.c_str());
    mResolutionFlags.getAttributeList(name, attributeList);
    sprintf(name, "%sSpaceView.Dx", prefix.c_str());
    attributeList.addAttribute(name, toString(mDx));
    sprintf(name, "%sSpaceView.Dy", prefix.c_str());
    attributeList.addAttribute(name, toString(mDy));
    sprintf(name, "%sSpaceView.XpInGridLengths", prefix.c_str());
    attributeList.addAttribute(name, toString(mXpInGridLengths));
    sprintf(name, "%sSpaceView.YpInGridLengths", prefix.c_str());
    attributeList.addAttribute(name, toString(mYpInGridLengths));
    sprintf(name, "%sSpaceView.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sSpaceView.OrientationOfTheGrid", prefix.c_str());
    attributeList.addAttribute(name, toString(mOrientationOfTheGrid));
    sprintf(name, "%sSpaceView.NrInRadiusOfEarth", prefix.c_str());
    attributeList.addAttribute(name, toString(mNrInRadiusOfEarth));
    sprintf(name, "%sSpaceView.Xo", prefix.c_str());
    attributeList.addAttribute(name, toString(mXo));
    sprintf(name, "%sSpaceView.Yo", prefix.c_str());
    attributeList.addAttribute(name, toString(mYo));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
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
    stream << space(level) << "- Nx = " << toString(mNx) << "\n";
    stream << space(level) << "- Ny = " << toString(mNy) << "\n";
    stream << space(level) << "- LatitudeOfSubSatellitePoint = " << toString(mLatitudeOfSubSatellitePoint) << "\n";
    stream << space(level) << "- LongitudeOfSubSatellitePoint = " << toString(mLongitudeOfSubSatellitePoint) << "\n";
    mResolutionFlags.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Dx = " << toString(mDx) << "\n";
    stream << space(level) << "- Dy = " << toString(mDy) << "\n";
    stream << space(level) << "- XpInGridLengths = " << toString(mXpInGridLengths) << "\n";
    stream << space(level) << "- YpInGridLengths = " << toString(mYpInGridLengths) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- OrientationOfTheGrid = " << toString(mOrientationOfTheGrid) << "\n";
    stream << space(level) << "- NrInRadiusOfEarth = " << toString(mNrInRadiusOfEarth) << "\n";
    stream << space(level) << "- Xo = " << toString(mXo) << "\n";
    stream << space(level) << "- Yo = " << toString(mYo) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SpaceView::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNx);
    boost::hash_combine(seed, mNy);
    boost::hash_combine(seed, mLatitudeOfSubSatellitePoint);
    boost::hash_combine(seed, mLongitudeOfSubSatellitePoint);
    boost::hash_combine(seed, mDx);
    boost::hash_combine(seed, mDy);
    boost::hash_combine(seed, mXpInGridLengths);
    boost::hash_combine(seed, mYpInGridLengths);
    boost::hash_combine(seed, mOrientationOfTheGrid);
    boost::hash_combine(seed, mNrInRadiusOfEarth);
    boost::hash_combine(seed, mXo);
    boost::hash_combine(seed, mYo);
    // boost::hash_combine(seed,mResolutionFlags.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint SpaceView::getTemplateNumber() const {
  return 90;
}

GridDefinition *SpaceView::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new SpaceView(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNx} attribute. */

std::uint16_t SpaceView::getNx() const {
  try {
    return mNx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNy} attribute. */

std::uint16_t SpaceView::getNy() const {
  try {
    return mNy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfSubSatellitePoint} attribute. */

std::int24_t SpaceView::getLatitudeOfSubSatellitePoint() const {
  try {
    return mLatitudeOfSubSatellitePoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfSubSatellitePoint} attribute. */

std::int24_t SpaceView::getLongitudeOfSubSatellitePoint() const {
  try {
    return mLongitudeOfSubSatellitePoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mResolutionFlags} attribute. */

ResolutionFlagsSettings *SpaceView::getResolutionFlags() const {
  try {
    return static_cast<ResolutionFlagsSettings *>(&mResolutionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDx} attribute. */

std::uint24_t SpaceView::getDx() const {
  try {
    return mDx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDy} attribute. */

std::uint24_t SpaceView::getDy() const {
  try {
    return mDy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mXpInGridLengths} attribute. */

std::uint16_t SpaceView::getXpInGridLengths() const {
  try {
    return mXpInGridLengths;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mYpInGridLengths} attribute. */

std::uint16_t SpaceView::getYpInGridLengths() const {
  try {
    return mYpInGridLengths;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *SpaceView::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mOrientationOfTheGrid} attribute. */

std::uint24_t SpaceView::getOrientationOfTheGrid() const {
  try {
    return mOrientationOfTheGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNrInRadiusOfEarth} attribute. */

std::uint24_t SpaceView::getNrInRadiusOfEarth() const {
  try {
    return mNrInRadiusOfEarth;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mXo} attribute. */

std::uint16_t SpaceView::getXo() const {
  try {
    return mXo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mYo} attribute. */

std::uint16_t SpaceView::getYo() const {
  try {
    return mYo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setNx(std::uint16_t nx) {
  try {
    mNx = nx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setNy(std::uint16_t ny) {
  try {
    mNy = ny;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setLatitudeOfSubSatellitePoint(std::int24_t latitudeOfSubSatellitePoint) {
  try {
    mLatitudeOfSubSatellitePoint = latitudeOfSubSatellitePoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setLongitudeOfSubSatellitePoint(std::int24_t longitudeOfSubSatellitePoint) {
  try {
    mLongitudeOfSubSatellitePoint = longitudeOfSubSatellitePoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setResolutionFlags(ResolutionFlagsSettings &resolutionFlags) {
  try {
    mResolutionFlags = resolutionFlags;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setDx(std::uint24_t dx) {
  try {
    mDx = dx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setDy(std::uint24_t dy) {
  try {
    mDy = dy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setXpInGridLengths(std::uint16_t xpInGridLengths) {
  try {
    mXpInGridLengths = xpInGridLengths;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setYpInGridLengths(std::uint16_t ypInGridLengths) {
  try {
    mYpInGridLengths = ypInGridLengths;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setOrientationOfTheGrid(std::uint24_t orientationOfTheGrid) {
  try {
    mOrientationOfTheGrid = orientationOfTheGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setNrInRadiusOfEarth(std::uint24_t nrInRadiusOfEarth) {
  try {
    mNrInRadiusOfEarth = nrInRadiusOfEarth;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setXo(std::uint16_t xo) {
  try {
    mXo = xo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpaceView::setYo(std::uint16_t yo) {
  try {
    mYo = yo;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
