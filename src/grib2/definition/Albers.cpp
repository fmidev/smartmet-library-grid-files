// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AlbersImpl.*' files.
// ***********************************************************************

#include "grib2/definition/Albers.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

Albers::Albers() {
  try {
    mProjectionCentreFlag = 0;
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

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Albers::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mNx = memoryReader.read_UInt32_opt();
    mNy = memoryReader.read_UInt32_opt();
    mLatitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfFirstGridPoint = memoryReader.read_UInt32_opt();
    mResolution.read(memoryReader);
    mLaD = memoryReader.read_Int32_opt();
    mLoV = memoryReader.read_UInt32_opt();
    mXDirectionGridLength = memoryReader.read_UInt32_opt();
    mYDirectionGridLength = memoryReader.read_UInt32_opt();
    mProjectionCentreFlag = memoryReader.read_uint8();
    mScanningMode.read(memoryReader);
    mLatin1 = memoryReader.read_Int32_opt();
    mLatin2 = memoryReader.read_UInt32_opt();
    mLatitudeOfTheSouthernPoleOfProjection = memoryReader.read_Int32_opt();
    mLongitudeOfTheSouthernPoleOfProjection = memoryReader.read_UInt32_opt();
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
    sprintf(name, "%sAlbers.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sAlbers.Nx", prefix.c_str());
    attributeList.addAttribute(name, toString(mNx));
    sprintf(name, "%sAlbers.Ny", prefix.c_str());
    attributeList.addAttribute(name, toString(mNy));
    sprintf(name, "%sAlbers.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sAlbers.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sAlbers.", prefix.c_str());
    mResolution.getAttributeList(name, attributeList);
    sprintf(name, "%sAlbers.LaD", prefix.c_str());
    attributeList.addAttribute(name, toString(mLaD));
    sprintf(name, "%sAlbers.LoV", prefix.c_str());
    attributeList.addAttribute(name, toString(mLoV));
    sprintf(name, "%sAlbers.XDirectionGridLength", prefix.c_str());
    attributeList.addAttribute(name, toString(mXDirectionGridLength));
    sprintf(name, "%sAlbers.YDirectionGridLength", prefix.c_str());
    attributeList.addAttribute(name, toString(mYDirectionGridLength));
    sprintf(name, "%sAlbers.ProjectionCentreFlag", prefix.c_str());
    attributeList.addAttribute(name, toString(mProjectionCentreFlag));
    sprintf(name, "%sAlbers.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sAlbers.Latin1", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatin1));
    sprintf(name, "%sAlbers.Latin2", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatin2));
    sprintf(name, "%sAlbers.LatitudeOfTheSouthernPoleOfProjection", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfTheSouthernPoleOfProjection));
    sprintf(name, "%sAlbers.LongitudeOfTheSouthernPoleOfProjection", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfTheSouthernPoleOfProjection));
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
    mEarthShape.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Nx = " << toString(mNx) << "\n";
    stream << space(level) << "- Ny = " << toString(mNy) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    mResolution.print(stream, level + 1, optionFlags);
    stream << space(level) << "- LaD = " << toString(mLaD) << "\n";
    stream << space(level) << "- LoV = " << toString(mLoV) << "\n";
    stream << space(level) << "- XDirectionGridLength = " << toString(mXDirectionGridLength) << "\n";
    stream << space(level) << "- YDirectionGridLength = " << toString(mYDirectionGridLength) << "\n";
    stream << space(level) << "- ProjectionCentreFlag = " << toString(mProjectionCentreFlag) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Latin1 = " << toString(mLatin1) << "\n";
    stream << space(level) << "- Latin2 = " << toString(mLatin2) << "\n";
    stream << space(level) << "- LatitudeOfTheSouthernPoleOfProjection = " << toString(mLatitudeOfTheSouthernPoleOfProjection) << "\n";
    stream << space(level) << "- LongitudeOfTheSouthernPoleOfProjection = " << toString(mLongitudeOfTheSouthernPoleOfProjection) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Albers::countHash() {
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
    if (mLaD)
      boost::hash_combine(seed, *mLaD);
    if (mLoV)
      boost::hash_combine(seed, *mLoV);
    if (mXDirectionGridLength)
      boost::hash_combine(seed, *mXDirectionGridLength);
    if (mYDirectionGridLength)
      boost::hash_combine(seed, *mYDirectionGridLength);
    boost::hash_combine(seed, mProjectionCentreFlag);
    if (mLatin1)
      boost::hash_combine(seed, *mLatin1);
    if (mLatin2)
      boost::hash_combine(seed, *mLatin2);
    if (mLatitudeOfTheSouthernPoleOfProjection)
      boost::hash_combine(seed, *mLatitudeOfTheSouthernPoleOfProjection);
    if (mLongitudeOfTheSouthernPoleOfProjection)
      boost::hash_combine(seed, *mLongitudeOfTheSouthernPoleOfProjection);
    // boost::hash_combine(seed,mEarthShape.countHash());
    // boost::hash_combine(seed,mResolution.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

const EarthShapeSettings *Albers::getEarthShape() const {
  try {
    return &mEarthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNx} attribute. */

const T::UInt32_opt &Albers::getNx() const {
  try {
    return mNx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNy} attribute. */

const T::UInt32_opt &Albers::getNy() const {
  try {
    return mNy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

const T::Int32_opt &Albers::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

const T::UInt32_opt &Albers::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mResolution} attribute. */

const ResolutionSettings *Albers::getResolution() const {
  try {
    return &mResolution;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLaD} attribute. */

const T::Int32_opt &Albers::getLaD() const {
  try {
    return mLaD;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLoV} attribute. */

const T::UInt32_opt &Albers::getLoV() const {
  try {
    return mLoV;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mXDirectionGridLength} attribute. */

const T::UInt32_opt &Albers::getXDirectionGridLength() const {
  try {
    return mXDirectionGridLength;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mYDirectionGridLength} attribute. */

const T::UInt32_opt &Albers::getYDirectionGridLength() const {
  try {
    return mYDirectionGridLength;
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

const T::Int32_opt &Albers::getLatin1() const {
  try {
    return mLatin1;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatin2} attribute. */

const T::UInt32_opt &Albers::getLatin2() const {
  try {
    return mLatin2;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfTheSouthernPoleOfProjection} attribute. */

const T::Int32_opt &Albers::getLatitudeOfTheSouthernPoleOfProjection() const {
  try {
    return mLatitudeOfTheSouthernPoleOfProjection;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfTheSouthernPoleOfProjection} attribute. */

const T::UInt32_opt &Albers::getLongitudeOfTheSouthernPoleOfProjection() const {
  try {
    return mLongitudeOfTheSouthernPoleOfProjection;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setEarthShape(EarthShapeSettings earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setNx(T::UInt32_opt nx) {
  try {
    mNx = nx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setNy(T::UInt32_opt ny) {
  try {
    mNy = ny;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLongitudeOfFirstGridPoint(T::UInt32_opt longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setResolution(ResolutionSettings resolution) {
  try {
    mResolution = resolution;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLaD(T::Int32_opt laD) {
  try {
    mLaD = laD;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLoV(T::UInt32_opt loV) {
  try {
    mLoV = loV;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setXDirectionGridLength(T::UInt32_opt xDirectionGridLength) {
  try {
    mXDirectionGridLength = xDirectionGridLength;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setYDirectionGridLength(T::UInt32_opt yDirectionGridLength) {
  try {
    mYDirectionGridLength = yDirectionGridLength;
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

void Albers::setLatin1(T::Int32_opt latin1) {
  try {
    mLatin1 = latin1;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLatin2(T::UInt32_opt latin2) {
  try {
    mLatin2 = latin2;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLatitudeOfTheSouthernPoleOfProjection(T::Int32_opt latitudeOfTheSouthernPoleOfProjection) {
  try {
    mLatitudeOfTheSouthernPoleOfProjection = latitudeOfTheSouthernPoleOfProjection;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Albers::setLongitudeOfTheSouthernPoleOfProjection(T::UInt32_opt longitudeOfTheSouthernPoleOfProjection) {
  try {
    mLongitudeOfTheSouthernPoleOfProjection = longitudeOfTheSouthernPoleOfProjection;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
