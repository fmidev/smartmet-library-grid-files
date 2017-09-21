// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'MercatorImpl.*' files.
// ***********************************************************************

#include "grib2/definition/Mercator.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

Mercator::Mercator() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

Mercator::~Mercator() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Mercator::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mNi = memoryReader.read_UInt32_opt();
    mNj = memoryReader.read_UInt32_opt();
    mLatitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mResolution.read(memoryReader);
    mLaD = memoryReader.read_Int32_opt();
    mLatitudeOfLastGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfLastGridPoint = memoryReader.read_Int32_opt();
    mScanningMode.read(memoryReader);
    mOrientationOfTheGrid = memoryReader.read_UInt32_opt();
    mDi = memoryReader.read_UInt32_opt();
    mDj = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Mercator::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sMercator.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sMercator.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sMercator.Nj", prefix.c_str());
    attributeList.addAttribute(name, toString(mNj));
    sprintf(name, "%sMercator.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sMercator.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sMercator.", prefix.c_str());
    mResolution.getAttributeList(name, attributeList);
    sprintf(name, "%sMercator.LaD", prefix.c_str());
    attributeList.addAttribute(name, toString(mLaD));
    sprintf(name, "%sMercator.LatitudeOfLastGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfLastGridPoint));
    sprintf(name, "%sMercator.LongitudeOfLastGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfLastGridPoint));
    sprintf(name, "%sMercator.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sMercator.OrientationOfTheGrid", prefix.c_str());
    attributeList.addAttribute(name, toString(mOrientationOfTheGrid));
    sprintf(name, "%sMercator.Di", prefix.c_str());
    attributeList.addAttribute(name, toString(mDi));
    sprintf(name, "%sMercator.Dj", prefix.c_str());
    attributeList.addAttribute(name, toString(mDj));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void Mercator::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "Mercator\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nj = " << toString(mNj) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    mResolution.print(stream, level + 1, optionFlags);
    stream << space(level) << "- LaD = " << toString(mLaD) << "\n";
    stream << space(level) << "- LatitudeOfLastGridPoint = " << toString(mLatitudeOfLastGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfLastGridPoint = " << toString(mLongitudeOfLastGridPoint) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- OrientationOfTheGrid = " << toString(mOrientationOfTheGrid) << "\n";
    stream << space(level) << "- Di = " << toString(mDi) << "\n";
    stream << space(level) << "- Dj = " << toString(mDj) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Mercator::countHash() {
  try {
    std::size_t seed = 0;
    if (mNi)
      boost::hash_combine(seed, *mNi);
    if (mNj)
      boost::hash_combine(seed, *mNj);
    if (mLatitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLatitudeOfFirstGridPoint);
    if (mLongitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLongitudeOfFirstGridPoint);
    if (mLaD)
      boost::hash_combine(seed, *mLaD);
    // if (mLatitudeOfLastGridPoint) boost::hash_combine(seed,*mLatitudeOfLastGridPoint);
    // if (mLongitudeOfLastGridPoint) boost::hash_combine(seed,*mLongitudeOfLastGridPoint);
    if (mOrientationOfTheGrid)
      boost::hash_combine(seed, *mOrientationOfTheGrid);
    if (mDi)
      boost::hash_combine(seed, *mDi);
    if (mDj)
      boost::hash_combine(seed, *mDj);
    // boost::hash_combine(seed,mEarthShape.countHash());
    // boost::hash_combine(seed,mResolution.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

const EarthShapeSettings *Mercator::getEarthShape() const {
  try {
    return &mEarthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

const T::UInt32_opt &Mercator::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNj} attribute. */

const T::UInt32_opt &Mercator::getNj() const {
  try {
    return mNj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

const T::Int32_opt &Mercator::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

const T::Int32_opt &Mercator::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mResolution} attribute. */

const ResolutionSettings *Mercator::getResolution() const {
  try {
    return &mResolution;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLaD} attribute. */

const T::Int32_opt &Mercator::getLaD() const {
  try {
    return mLaD;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfLastGridPoint} attribute. */

const T::Int32_opt &Mercator::getLatitudeOfLastGridPoint() const {
  try {
    return mLatitudeOfLastGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfLastGridPoint} attribute. */

const T::Int32_opt &Mercator::getLongitudeOfLastGridPoint() const {
  try {
    return mLongitudeOfLastGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

const ScanningModeSettings *Mercator::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mOrientationOfTheGrid} attribute. */

const T::UInt32_opt &Mercator::getOrientationOfTheGrid() const {
  try {
    return mOrientationOfTheGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mDi} attribute. */

const T::UInt32_opt &Mercator::getDi() const {
  try {
    return mDi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mDj} attribute. */

const T::UInt32_opt &Mercator::getDj() const {
  try {
    return mDj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setEarthShape(EarthShapeSettings earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setNi(T::UInt32_opt ni) {
  try {
    mNi = ni;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setNj(T::UInt32_opt nj) {
  try {
    mNj = nj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setLongitudeOfFirstGridPoint(T::Int32_opt longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setResolution(ResolutionSettings resolution) {
  try {
    mResolution = resolution;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setLaD(T::Int32_opt laD) {
  try {
    mLaD = laD;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setLatitudeOfLastGridPoint(T::Int32_opt latitudeOfLastGridPoint) {
  try {
    mLatitudeOfLastGridPoint = latitudeOfLastGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setLongitudeOfLastGridPoint(T::Int32_opt longitudeOfLastGridPoint) {
  try {
    mLongitudeOfLastGridPoint = longitudeOfLastGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setScanningMode(ScanningModeSettings scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setOrientationOfTheGrid(T::UInt32_opt orientationOfTheGrid) {
  try {
    mOrientationOfTheGrid = orientationOfTheGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setDi(T::UInt32_opt di) {
  try {
    mDi = di;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void Mercator::setDj(T::UInt32_opt dj) {
  try {
    mDj = dj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
