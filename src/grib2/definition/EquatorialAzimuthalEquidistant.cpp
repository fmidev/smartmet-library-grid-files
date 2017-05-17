// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'EquatorialAzimuthalEquidistantImpl.*'
//   files.
// ***********************************************************************

#include "grib2/definition/EquatorialAzimuthalEquidistant.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

EquatorialAzimuthalEquidistant::EquatorialAzimuthalEquidistant() {
  try {
    mResolutionAndComponentFlag = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

EquatorialAzimuthalEquidistant::~EquatorialAzimuthalEquidistant() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current
   object.

        \param memoryReader  This object controls the access to the memory
   mapped file.
*/

void EquatorialAzimuthalEquidistant::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mNumberOfPointsAlongXAxis = memoryReader.read_UInt32_opt();
    mNumberOfPointsAlongYAxis = memoryReader.read_UInt32_opt();
    mLatitudeOfTangencyPoint = memoryReader.read_Int32_opt();
    mLongitudeOfTangencyPoint = memoryReader.read_UInt32_opt();
    mResolutionAndComponentFlag = memoryReader.read_uint8();
    mDx = memoryReader.read_UInt32_opt();
    mDy = memoryReader.read_UInt32_opt();
    mProjectionCenterFlag = memoryReader.read_UInt8_opt();
    mScanningMode.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void EquatorialAzimuthalEquidistant::getAttributeList(
    std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sEquatorialAzimuthalEquidistant.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sEquatorialAzimuthalEquidistant.NumberOfPointsAlongXAxis",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfPointsAlongXAxis));
    sprintf(name, "%sEquatorialAzimuthalEquidistant.NumberOfPointsAlongYAxis",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfPointsAlongYAxis));
    sprintf(name, "%sEquatorialAzimuthalEquidistant.LatitudeOfTangencyPoint",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfTangencyPoint));
    sprintf(name, "%sEquatorialAzimuthalEquidistant.LongitudeOfTangencyPoint",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfTangencyPoint));
    sprintf(name, "%sEquatorialAzimuthalEquidistant.ResolutionAndComponentFlag",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mResolutionAndComponentFlag));
    sprintf(name, "%sEquatorialAzimuthalEquidistant.Dx", prefix.c_str());
    attributeList.addAttribute(name, toString(mDx));
    sprintf(name, "%sEquatorialAzimuthalEquidistant.Dy", prefix.c_str());
    attributeList.addAttribute(name, toString(mDy));
    sprintf(name, "%sEquatorialAzimuthalEquidistant.ProjectionCenterFlag",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mProjectionCenterFlag));
    sprintf(name, "%sEquatorialAzimuthalEquidistant.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given
   stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level
   structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void EquatorialAzimuthalEquidistant::print(std::ostream &stream, uint level,
                                           uint optionFlags) const {
  try {
    stream << space(level) << "EquatorialAzimuthalEquidistant\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    stream << space(level) << "- NumberOfPointsAlongXAxis = "
           << toString(mNumberOfPointsAlongXAxis) << "\n";
    stream << space(level) << "- NumberOfPointsAlongYAxis = "
           << toString(mNumberOfPointsAlongYAxis) << "\n";
    stream << space(level) << "- LatitudeOfTangencyPoint = "
           << toString(mLatitudeOfTangencyPoint) << "\n";
    stream << space(level) << "- LongitudeOfTangencyPoint = "
           << toString(mLongitudeOfTangencyPoint) << "\n";
    stream << space(level) << "- ResolutionAndComponentFlag = "
           << toString(mResolutionAndComponentFlag) << "\n";
    stream << space(level) << "- Dx = " << toString(mDx) << "\n";
    stream << space(level) << "- Dy = " << toString(mDy) << "\n";
    stream << space(level)
           << "- ProjectionCenterFlag = " << toString(mProjectionCenterFlag)
           << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash EquatorialAzimuthalEquidistant::countHash() {
  try {
    std::size_t seed = 0;
    if (mNumberOfPointsAlongXAxis)
      boost::hash_combine(seed, *mNumberOfPointsAlongXAxis);
    if (mNumberOfPointsAlongYAxis)
      boost::hash_combine(seed, *mNumberOfPointsAlongYAxis);
    if (mLatitudeOfTangencyPoint)
      boost::hash_combine(seed, *mLatitudeOfTangencyPoint);
    if (mLongitudeOfTangencyPoint)
      boost::hash_combine(seed, *mLongitudeOfTangencyPoint);
    boost::hash_combine(seed, mResolutionAndComponentFlag);
    if (mDx)
      boost::hash_combine(seed, *mDx);
    if (mDy)
      boost::hash_combine(seed, *mDy);
    if (mProjectionCenterFlag)
      boost::hash_combine(seed, *mProjectionCenterFlag);
    boost::hash_combine(seed, mEarthShape.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute.
 */

const EarthShapeSettings *
EquatorialAzimuthalEquidistant::getEarthShape() const {
  try {
    return &mEarthShape;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfPointsAlongXAxis}
 * attribute. */

const T::UInt32_opt &
EquatorialAzimuthalEquidistant::getNumberOfPointsAlongXAxis() const {
  try {
    return mNumberOfPointsAlongXAxis;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfPointsAlongYAxis}
 * attribute. */

const T::UInt32_opt &
EquatorialAzimuthalEquidistant::getNumberOfPointsAlongYAxis() const {
  try {
    return mNumberOfPointsAlongYAxis;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfTangencyPoint}
 * attribute. */

const T::Int32_opt &
EquatorialAzimuthalEquidistant::getLatitudeOfTangencyPoint() const {
  try {
    return mLatitudeOfTangencyPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfTangencyPoint}
 * attribute. */

const T::UInt32_opt &
EquatorialAzimuthalEquidistant::getLongitudeOfTangencyPoint() const {
  try {
    return mLongitudeOfTangencyPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link
 * mResolutionAndComponentFlag} attribute. */

std::uint8_t
EquatorialAzimuthalEquidistant::getResolutionAndComponentFlag() const {
  try {
    return mResolutionAndComponentFlag;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mDx} attribute. */

const T::UInt32_opt &EquatorialAzimuthalEquidistant::getDx() const {
  try {
    return mDx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mDy} attribute. */

const T::UInt32_opt &EquatorialAzimuthalEquidistant::getDy() const {
  try {
    return mDy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mProjectionCenterFlag}
 * attribute. */

const T::UInt8_opt &
EquatorialAzimuthalEquidistant::getProjectionCenterFlag() const {
  try {
    return mProjectionCenterFlag;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode}
 * attribute. */

const ScanningModeSettings *
EquatorialAzimuthalEquidistant::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
