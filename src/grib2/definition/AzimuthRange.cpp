// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AzimuthRangeImpl.*' files.
// ***********************************************************************

#include "grib2/definition/AzimuthRange.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AzimuthRange::AzimuthRange() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

AzimuthRange::~AzimuthRange() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void AzimuthRange::read(MemoryReader &memoryReader) {
  try {
    mNumberOfDataBinsAlongRadials = memoryReader.read_UInt32_opt();
    mNumberOfRadials = memoryReader.read_UInt32_opt();
    mLatitudeOfCenterPoint = memoryReader.read_Int32_opt();
    mLongitudeOfCenterPoint = memoryReader.read_UInt32_opt();
    mSpacingOfBinsAlongRadials = memoryReader.read_UInt32_opt();
    mOffsetFromOriginToInnerBound = memoryReader.read_UInt32_opt();
    mScanningMode.read(memoryReader);
    mStartingAzimuth = memoryReader.read_Int16_opt();
    mAzimuthalWidth = memoryReader.read_Int16_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void AzimuthRange::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAzimuthRange.NumberOfDataBinsAlongRadials", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfDataBinsAlongRadials));
    sprintf(name, "%sAzimuthRange.NumberOfRadials", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfRadials));
    sprintf(name, "%sAzimuthRange.LatitudeOfCenterPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfCenterPoint));
    sprintf(name, "%sAzimuthRange.LongitudeOfCenterPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfCenterPoint));
    sprintf(name, "%sAzimuthRange.SpacingOfBinsAlongRadials", prefix.c_str());
    attributeList.addAttribute(name, toString(mSpacingOfBinsAlongRadials));
    sprintf(name, "%sAzimuthRange.OffsetFromOriginToInnerBound", prefix.c_str());
    attributeList.addAttribute(name, toString(mOffsetFromOriginToInnerBound));
    sprintf(name, "%sAzimuthRange.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sAzimuthRange.StartingAzimuth", prefix.c_str());
    attributeList.addAttribute(name, toString(mStartingAzimuth));
    sprintf(name, "%sAzimuthRange.AzimuthalWidth", prefix.c_str());
    attributeList.addAttribute(name, toString(mAzimuthalWidth));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void AzimuthRange::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "AzimuthRange\n";
    stream << space(level) << "- NumberOfDataBinsAlongRadials = " << toString(mNumberOfDataBinsAlongRadials) << "\n";
    stream << space(level) << "- NumberOfRadials = " << toString(mNumberOfRadials) << "\n";
    stream << space(level) << "- LatitudeOfCenterPoint = " << toString(mLatitudeOfCenterPoint) << "\n";
    stream << space(level) << "- LongitudeOfCenterPoint = " << toString(mLongitudeOfCenterPoint) << "\n";
    stream << space(level) << "- SpacingOfBinsAlongRadials = " << toString(mSpacingOfBinsAlongRadials) << "\n";
    stream << space(level) << "- OffsetFromOriginToInnerBound = " << toString(mOffsetFromOriginToInnerBound) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- StartingAzimuth = " << toString(mStartingAzimuth) << "\n";
    stream << space(level) << "- AzimuthalWidth = " << toString(mAzimuthalWidth) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash AzimuthRange::countHash() {
  try {
    std::size_t seed = 0;
    if (mNumberOfDataBinsAlongRadials)
      boost::hash_combine(seed, *mNumberOfDataBinsAlongRadials);
    if (mNumberOfRadials)
      boost::hash_combine(seed, *mNumberOfRadials);
    if (mLatitudeOfCenterPoint)
      boost::hash_combine(seed, *mLatitudeOfCenterPoint);
    if (mLongitudeOfCenterPoint)
      boost::hash_combine(seed, *mLongitudeOfCenterPoint);
    if (mSpacingOfBinsAlongRadials)
      boost::hash_combine(seed, *mSpacingOfBinsAlongRadials);
    if (mOffsetFromOriginToInnerBound)
      boost::hash_combine(seed, *mOffsetFromOriginToInnerBound);
    if (mStartingAzimuth)
      boost::hash_combine(seed, *mStartingAzimuth);
    if (mAzimuthalWidth)
      boost::hash_combine(seed, *mAzimuthalWidth);
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfDataBinsAlongRadials} attribute. */

const T::UInt32_opt &AzimuthRange::getNumberOfDataBinsAlongRadials() const {
  try {
    return mNumberOfDataBinsAlongRadials;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfRadials} attribute. */

const T::UInt32_opt &AzimuthRange::getNumberOfRadials() const {
  try {
    return mNumberOfRadials;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfCenterPoint} attribute. */

const T::Int32_opt &AzimuthRange::getLatitudeOfCenterPoint() const {
  try {
    return mLatitudeOfCenterPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfCenterPoint} attribute. */

const T::UInt32_opt &AzimuthRange::getLongitudeOfCenterPoint() const {
  try {
    return mLongitudeOfCenterPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mSpacingOfBinsAlongRadials} attribute. */

const T::UInt32_opt &AzimuthRange::getSpacingOfBinsAlongRadials() const {
  try {
    return mSpacingOfBinsAlongRadials;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mOffsetFromOriginToInnerBound} attribute. */

const T::UInt32_opt &AzimuthRange::getOffsetFromOriginToInnerBound() const {
  try {
    return mOffsetFromOriginToInnerBound;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

const ScanningModeSettings *AzimuthRange::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mStartingAzimuth} attribute. */

const T::Int16_opt &AzimuthRange::getStartingAzimuth() const {
  try {
    return mStartingAzimuth;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mAzimuthalWidth} attribute. */

const T::Int16_opt &AzimuthRange::getAzimuthalWidth() const {
  try {
    return mAzimuthalWidth;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setNumberOfDataBinsAlongRadials(T::UInt32_opt numberOfDataBinsAlongRadials) {
  try {
    mNumberOfDataBinsAlongRadials = numberOfDataBinsAlongRadials;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setNumberOfRadials(T::UInt32_opt numberOfRadials) {
  try {
    mNumberOfRadials = numberOfRadials;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setLatitudeOfCenterPoint(T::Int32_opt latitudeOfCenterPoint) {
  try {
    mLatitudeOfCenterPoint = latitudeOfCenterPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setLongitudeOfCenterPoint(T::UInt32_opt longitudeOfCenterPoint) {
  try {
    mLongitudeOfCenterPoint = longitudeOfCenterPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setSpacingOfBinsAlongRadials(T::UInt32_opt spacingOfBinsAlongRadials) {
  try {
    mSpacingOfBinsAlongRadials = spacingOfBinsAlongRadials;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setOffsetFromOriginToInnerBound(T::UInt32_opt offsetFromOriginToInnerBound) {
  try {
    mOffsetFromOriginToInnerBound = offsetFromOriginToInnerBound;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setScanningMode(ScanningModeSettings scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setStartingAzimuth(T::Int16_opt startingAzimuth) {
  try {
    mStartingAzimuth = startingAzimuth;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AzimuthRange::setAzimuthalWidth(T::Int16_opt azimuthalWidth) {
  try {
    mAzimuthalWidth = azimuthalWidth;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
