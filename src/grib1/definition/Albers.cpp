// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AlbersImpl.*' files.
// ***********************************************************************

#include "Albers.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

Albers::Albers() {
  try {
    mNx = 0;
    mNy = 0;
    mLatitudeOfFirstGridPoint = 0;
    mLongitudeOfFirstGridPoint = 0;
    mLoV = 0;
    mDxInMetres = 0;
    mDyInMetres = 0;
    mProjectionCentreFlag = 0;
    mLatin1 = 0;
    mLatin2 = 0;
    mLatitudeOfSouthernPole = 0;
    mLongitudeOfSouthernPole = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

Albers::~Albers() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Albers::read(MemoryReader &memoryReader) {
  try {
    mNx = memoryReader.read_uint16();
    mNy = memoryReader.read_uint16();
    mLatitudeOfFirstGridPoint = memoryReader.read_int24();
    mLongitudeOfFirstGridPoint = memoryReader.read_int24();
    mResolutionFlags.read(memoryReader);
    mLoV = memoryReader.read_int24();
    mDxInMetres = memoryReader.read_uint24();
    mDyInMetres = memoryReader.read_uint24();
    mProjectionCentreFlag = memoryReader.read_uint8();
    mScanningMode.read(memoryReader);
    mLatin1 = memoryReader.read_int24();
    mLatin2 = memoryReader.read_int24();
    mLatitudeOfSouthernPole = memoryReader.read_int24();
    mLongitudeOfSouthernPole = memoryReader.read_int24();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Albers::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAlbers.Nx", prefix.c_str());
    attributeList.addAttribute(name, toString(mNx));
    sprintf(name, "%sAlbers.Ny", prefix.c_str());
    attributeList.addAttribute(name, toString(mNy));
    sprintf(name, "%sAlbers.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sAlbers.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sAlbers.", prefix.c_str());
    mResolutionFlags.getAttributeList(name, attributeList);
    sprintf(name, "%sAlbers.LoV", prefix.c_str());
    attributeList.addAttribute(name, toString(mLoV));
    sprintf(name, "%sAlbers.DxInMetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mDxInMetres));
    sprintf(name, "%sAlbers.DyInMetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mDyInMetres));
    sprintf(name, "%sAlbers.ProjectionCentreFlag", prefix.c_str());
    attributeList.addAttribute(name, toString(mProjectionCentreFlag));
    sprintf(name, "%sAlbers.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sAlbers.Latin1", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatin1));
    sprintf(name, "%sAlbers.Latin2", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatin2));
    sprintf(name, "%sAlbers.LatitudeOfSouthernPole", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfSouthernPole));
    sprintf(name, "%sAlbers.LongitudeOfSouthernPole", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfSouthernPole));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void Albers::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "Albers\n";
    stream << space(level) << "- Nx = " << toString(mNx) << "\n";
    stream << space(level) << "- Ny = " << toString(mNy) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    mResolutionFlags.print(stream, level + 1, optionFlags);
    stream << space(level) << "- LoV = " << toString(mLoV) << "\n";
    stream << space(level) << "- DxInMetres = " << toString(mDxInMetres) << "\n";
    stream << space(level) << "- DyInMetres = " << toString(mDyInMetres) << "\n";
    stream << space(level) << "- ProjectionCentreFlag = " << toString(mProjectionCentreFlag) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Latin1 = " << toString(mLatin1) << "\n";
    stream << space(level) << "- Latin2 = " << toString(mLatin2) << "\n";
    stream << space(level) << "- LatitudeOfSouthernPole = " << toString(mLatitudeOfSouthernPole) << "\n";
    stream << space(level) << "- LongitudeOfSouthernPole = " << toString(mLongitudeOfSouthernPole) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Albers::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNx);
    boost::hash_combine(seed, mNy);
    boost::hash_combine(seed, mLatitudeOfFirstGridPoint);
    boost::hash_combine(seed, mLongitudeOfFirstGridPoint);
    boost::hash_combine(seed, mLoV);
    boost::hash_combine(seed, mDxInMetres);
    boost::hash_combine(seed, mDyInMetres);
    boost::hash_combine(seed, mProjectionCentreFlag);
    boost::hash_combine(seed, mLatin1);
    boost::hash_combine(seed, mLatin2);
    boost::hash_combine(seed, mLatitudeOfSouthernPole);
    boost::hash_combine(seed, mLongitudeOfSouthernPole);
    // boost::hash_combine(seed,mResolutionFlags.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNx} attribute. */

std::uint16_t Albers::getNx() const {
  try {
    return mNx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNy} attribute. */

std::uint16_t Albers::getNy() const {
  try {
    return mNy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

std::int24_t Albers::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

std::int24_t Albers::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mResolutionFlags} attribute. */

const ResolutionFlagsSettings *Albers::getResolutionFlags() const {
  try {
    return &mResolutionFlags;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLoV} attribute. */

std::int24_t Albers::getLoV() const {
  try {
    return mLoV;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mDxInMetres} attribute. */

std::uint24_t Albers::getDxInMetres() const {
  try {
    return mDxInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mDyInMetres} attribute. */

std::uint24_t Albers::getDyInMetres() const {
  try {
    return mDyInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mProjectionCentreFlag} attribute. */

std::uint8_t Albers::getProjectionCentreFlag() const {
  try {
    return mProjectionCentreFlag;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

const ScanningModeSettings *Albers::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatin1} attribute. */

std::int24_t Albers::getLatin1() const {
  try {
    return mLatin1;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatin2} attribute. */

std::int24_t Albers::getLatin2() const {
  try {
    return mLatin2;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfSouthernPole} attribute. */

std::int24_t Albers::getLatitudeOfSouthernPole() const {
  try {
    return mLatitudeOfSouthernPole;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfSouthernPole} attribute. */

std::int24_t Albers::getLongitudeOfSouthernPole() const {
  try {
    return mLongitudeOfSouthernPole;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setNx(std::uint16_t nx) {
  try {
    mNx = nx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setNy(std::uint16_t ny) {
  try {
    mNy = ny;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLatitudeOfFirstGridPoint(std::int24_t latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLongitudeOfFirstGridPoint(std::int24_t longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setResolutionFlags(ResolutionFlagsSettings resolutionFlags) {
  try {
    mResolutionFlags = resolutionFlags;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLoV(std::int24_t loV) {
  try {
    mLoV = loV;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setDxInMetres(std::uint24_t dxInMetres) {
  try {
    mDxInMetres = dxInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setDyInMetres(std::uint24_t dyInMetres) {
  try {
    mDyInMetres = dyInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setProjectionCentreFlag(std::uint8_t projectionCentreFlag) {
  try {
    mProjectionCentreFlag = projectionCentreFlag;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setScanningMode(ScanningModeSettings scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLatin1(std::int24_t latin1) {
  try {
    mLatin1 = latin1;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLatin2(std::int24_t latin2) {
  try {
    mLatin2 = latin2;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLatitudeOfSouthernPole(std::int24_t latitudeOfSouthernPole) {
  try {
    mLatitudeOfSouthernPole = latitudeOfSouthernPole;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLongitudeOfSouthernPole(std::int24_t longitudeOfSouthernPole) {
  try {
    mLongitudeOfSouthernPole = longitudeOfSouthernPole;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB1
} // namespace SmartMet
