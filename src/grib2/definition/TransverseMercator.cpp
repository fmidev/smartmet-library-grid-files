// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TransverseMercatorImpl.*' files.
// ***********************************************************************

#include "TransverseMercator.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TransverseMercator::TransverseMercator() {
  try {
    mScaleFactorAtReferencePoint = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

TransverseMercator::~TransverseMercator() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void TransverseMercator::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mNi = memoryReader.read_UInt32_opt();
    mNj = memoryReader.read_UInt32_opt();
    mLatitudeOfReferencePoint = memoryReader.read_Int32_opt();
    mLongitudeOfReferencePoint = memoryReader.read_Int32_opt();
    mResolution.read(memoryReader);
    mScaleFactorAtReferencePoint = memoryReader.read_float();
    mXR = memoryReader.read_Int32_opt();
    mYR = memoryReader.read_Int32_opt();
    mScanningMode.read(memoryReader);
    mDi = memoryReader.read_UInt32_opt();
    mDj = memoryReader.read_UInt32_opt();
    mX1 = memoryReader.read_Int32_opt();
    mY1 = memoryReader.read_Int32_opt();
    mX2 = memoryReader.read_Int32_opt();
    mY2 = memoryReader.read_Int32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void TransverseMercator::write(DataWriter &dataWriter) {
  try {
    mEarthShape.write(dataWriter);
    dataWriter << mNi;
    dataWriter << mNj;
    dataWriter << mLatitudeOfReferencePoint;
    dataWriter << mLongitudeOfReferencePoint;
    mResolution.write(dataWriter);
    dataWriter << mScaleFactorAtReferencePoint;
    dataWriter << mXR;
    dataWriter << mYR;
    mScanningMode.write(dataWriter);
    dataWriter << mDi;
    dataWriter << mDj;
    dataWriter << mX1;
    dataWriter << mY1;
    dataWriter << mX2;
    dataWriter << mY2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TransverseMercator::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTransverseMercator.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sTransverseMercator.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sTransverseMercator.Nj", prefix.c_str());
    attributeList.addAttribute(name, toString(mNj));
    sprintf(name, "%sTransverseMercator.LatitudeOfReferencePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfReferencePoint));
    sprintf(name, "%sTransverseMercator.LongitudeOfReferencePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfReferencePoint));
    sprintf(name, "%sTransverseMercator.", prefix.c_str());
    mResolution.getAttributeList(name, attributeList);
    sprintf(name, "%sTransverseMercator.ScaleFactorAtReferencePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorAtReferencePoint));
    sprintf(name, "%sTransverseMercator.XR", prefix.c_str());
    attributeList.addAttribute(name, toString(mXR));
    sprintf(name, "%sTransverseMercator.YR", prefix.c_str());
    attributeList.addAttribute(name, toString(mYR));
    sprintf(name, "%sTransverseMercator.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sTransverseMercator.Di", prefix.c_str());
    attributeList.addAttribute(name, toString(mDi));
    sprintf(name, "%sTransverseMercator.Dj", prefix.c_str());
    attributeList.addAttribute(name, toString(mDj));
    sprintf(name, "%sTransverseMercator.X1", prefix.c_str());
    attributeList.addAttribute(name, toString(mX1));
    sprintf(name, "%sTransverseMercator.Y1", prefix.c_str());
    attributeList.addAttribute(name, toString(mY1));
    sprintf(name, "%sTransverseMercator.X2", prefix.c_str());
    attributeList.addAttribute(name, toString(mX2));
    sprintf(name, "%sTransverseMercator.Y2", prefix.c_str());
    attributeList.addAttribute(name, toString(mY2));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void TransverseMercator::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TransverseMercator\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nj = " << toString(mNj) << "\n";
    stream << space(level) << "- LatitudeOfReferencePoint = " << toString(mLatitudeOfReferencePoint) << "\n";
    stream << space(level) << "- LongitudeOfReferencePoint = " << toString(mLongitudeOfReferencePoint) << "\n";
    mResolution.print(stream, level + 1, optionFlags);
    stream << space(level) << "- ScaleFactorAtReferencePoint = " << toString(mScaleFactorAtReferencePoint) << "\n";
    stream << space(level) << "- XR = " << toString(mXR) << "\n";
    stream << space(level) << "- YR = " << toString(mYR) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Di = " << toString(mDi) << "\n";
    stream << space(level) << "- Dj = " << toString(mDj) << "\n";
    stream << space(level) << "- X1 = " << toString(mX1) << "\n";
    stream << space(level) << "- Y1 = " << toString(mY1) << "\n";
    stream << space(level) << "- X2 = " << toString(mX2) << "\n";
    stream << space(level) << "- Y2 = " << toString(mY2) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TransverseMercator::countHash() {
  try {
    std::size_t seed = 0;
    if (mNi)
      boost::hash_combine(seed, *mNi);
    if (mNj)
      boost::hash_combine(seed, *mNj);
    if (mLatitudeOfReferencePoint)
      boost::hash_combine(seed, *mLatitudeOfReferencePoint);
    if (mLongitudeOfReferencePoint)
      boost::hash_combine(seed, *mLongitudeOfReferencePoint);
    boost::hash_combine(seed, mScaleFactorAtReferencePoint);
    if (mXR)
      boost::hash_combine(seed, *mXR);
    if (mYR)
      boost::hash_combine(seed, *mYR);
    if (mDi)
      boost::hash_combine(seed, *mDi);
    if (mDj)
      boost::hash_combine(seed, *mDj);
    if (mX1)
      boost::hash_combine(seed, *mX1);
    if (mY1)
      boost::hash_combine(seed, *mY1);
    if (mX2)
      boost::hash_combine(seed, *mX2);
    if (mY2)
      boost::hash_combine(seed, *mY2);
    // boost::hash_combine(seed,mEarthShape.countHash());
    // boost::hash_combine(seed,mResolution.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint TransverseMercator::getTemplateNumber() const {
  return 12;
}

GridDefinition *TransverseMercator::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new TransverseMercator(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

EarthShapeSettings *TransverseMercator::getEarthShape() const {
  try {
    return static_cast<EarthShapeSettings *>(&mEarthShape);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

const T::UInt32_opt &TransverseMercator::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNj} attribute. */

const T::UInt32_opt &TransverseMercator::getNj() const {
  try {
    return mNj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfReferencePoint} attribute. */

const T::Int32_opt &TransverseMercator::getLatitudeOfReferencePoint() const {
  try {
    return mLatitudeOfReferencePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfReferencePoint} attribute. */

const T::Int32_opt &TransverseMercator::getLongitudeOfReferencePoint() const {
  try {
    return mLongitudeOfReferencePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mResolution} attribute. */

ResolutionSettings *TransverseMercator::getResolution() const {
  try {
    return static_cast<ResolutionSettings *>(&mResolution);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorAtReferencePoint} attribute. */

float TransverseMercator::getScaleFactorAtReferencePoint() const {
  try {
    return mScaleFactorAtReferencePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mXR} attribute. */

const T::Int32_opt &TransverseMercator::getXR() const {
  try {
    return mXR;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mYR} attribute. */

const T::Int32_opt &TransverseMercator::getYR() const {
  try {
    return mYR;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *TransverseMercator::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDi} attribute. */

const T::UInt32_opt &TransverseMercator::getDi() const {
  try {
    return mDi;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDj} attribute. */

const T::UInt32_opt &TransverseMercator::getDj() const {
  try {
    return mDj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mX1} attribute. */

const T::Int32_opt &TransverseMercator::getX1() const {
  try {
    return mX1;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mY1} attribute. */

const T::Int32_opt &TransverseMercator::getY1() const {
  try {
    return mY1;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mX2} attribute. */

const T::Int32_opt &TransverseMercator::getX2() const {
  try {
    return mX2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mY2} attribute. */

const T::Int32_opt &TransverseMercator::getY2() const {
  try {
    return mY2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setEarthShape(EarthShapeSettings &earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setNi(T::UInt32_opt ni) {
  try {
    mNi = ni;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setNj(T::UInt32_opt nj) {
  try {
    mNj = nj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setLatitudeOfReferencePoint(T::Int32_opt latitudeOfReferencePoint) {
  try {
    mLatitudeOfReferencePoint = latitudeOfReferencePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setLongitudeOfReferencePoint(T::Int32_opt longitudeOfReferencePoint) {
  try {
    mLongitudeOfReferencePoint = longitudeOfReferencePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setResolution(ResolutionSettings &resolution) {
  try {
    mResolution = resolution;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setScaleFactorAtReferencePoint(float scaleFactorAtReferencePoint) {
  try {
    mScaleFactorAtReferencePoint = scaleFactorAtReferencePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setXR(T::Int32_opt xR) {
  try {
    mXR = xR;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setYR(T::Int32_opt yR) {
  try {
    mYR = yR;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setDi(T::UInt32_opt di) {
  try {
    mDi = di;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setDj(T::UInt32_opt dj) {
  try {
    mDj = dj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setX1(T::Int32_opt x1) {
  try {
    mX1 = x1;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setY1(T::Int32_opt y1) {
  try {
    mY1 = y1;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setX2(T::Int32_opt x2) {
  try {
    mX2 = x2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void TransverseMercator::setY2(T::Int32_opt y2) {
  try {
    mY2 = y2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
