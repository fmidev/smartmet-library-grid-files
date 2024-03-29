// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'LambertAzimuthalEqualAreaImpl.*' files.
// ***********************************************************************

#include "LambertAzimuthalEqualArea.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

LambertAzimuthalEqualArea::LambertAzimuthalEqualArea() {
  try {
    mResolutionAndComponentFlags = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

LambertAzimuthalEqualArea::~LambertAzimuthalEqualArea() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void LambertAzimuthalEqualArea::read(MemoryReader &memoryReader) {
  try {
    mEarthShape.read(memoryReader);
    mNumberOfPointsAlongXAxis = memoryReader.read_UInt32_opt();
    mNumberOfPointsAlongYAxis = memoryReader.read_UInt32_opt();
    mLatitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mStandardParallelInMicrodegrees = memoryReader.read_Int32_opt();
    mCentralLongitudeInMicrodegrees = memoryReader.read_Int32_opt();
    mResolutionAndComponentFlags = memoryReader.read_uint8();
    mXDirectionGridLengthInMillimetres = memoryReader.read_UInt32_opt();
    mYDirectionGridLengthInMillimetres = memoryReader.read_UInt32_opt();
    mScanningMode.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void LambertAzimuthalEqualArea::write(DataWriter &dataWriter) {
  try {
    mEarthShape.write(dataWriter);
    dataWriter << mNumberOfPointsAlongXAxis;
    dataWriter << mNumberOfPointsAlongYAxis;
    dataWriter << mLatitudeOfFirstGridPoint;
    dataWriter << mLongitudeOfFirstGridPoint;
    dataWriter << mStandardParallelInMicrodegrees;
    dataWriter << mCentralLongitudeInMicrodegrees;
    dataWriter << mResolutionAndComponentFlags;
    dataWriter << mXDirectionGridLengthInMillimetres;
    dataWriter << mYDirectionGridLengthInMillimetres;
    mScanningMode.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void LambertAzimuthalEqualArea::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sLambertAzimuthalEqualArea.", prefix.c_str());
    mEarthShape.getAttributeList(name, attributeList);
    sprintf(name, "%sLambertAzimuthalEqualArea.NumberOfPointsAlongXAxis", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfPointsAlongXAxis));
    sprintf(name, "%sLambertAzimuthalEqualArea.NumberOfPointsAlongYAxis", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfPointsAlongYAxis));
    sprintf(name, "%sLambertAzimuthalEqualArea.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sLambertAzimuthalEqualArea.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sLambertAzimuthalEqualArea.StandardParallelInMicrodegrees", prefix.c_str());
    attributeList.addAttribute(name, toString(mStandardParallelInMicrodegrees));
    sprintf(name, "%sLambertAzimuthalEqualArea.CentralLongitudeInMicrodegrees", prefix.c_str());
    attributeList.addAttribute(name, toString(mCentralLongitudeInMicrodegrees));
    sprintf(name, "%sLambertAzimuthalEqualArea.ResolutionAndComponentFlags", prefix.c_str());
    attributeList.addAttribute(name, toString(mResolutionAndComponentFlags));
    sprintf(name, "%sLambertAzimuthalEqualArea.XDirectionGridLengthInMillimetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mXDirectionGridLengthInMillimetres));
    sprintf(name, "%sLambertAzimuthalEqualArea.YDirectionGridLengthInMillimetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mYDirectionGridLengthInMillimetres));
    sprintf(name, "%sLambertAzimuthalEqualArea.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool LambertAzimuthalEqualArea::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mEarthShape.getAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "NumberOfPointsAlongXAxis") == 0) {
      attributeValue = toString(mNumberOfPointsAlongXAxis);
      return true;
    }
    if (strcasecmp(attributeName, "NumberOfPointsAlongYAxis") == 0) {
      attributeValue = toString(mNumberOfPointsAlongYAxis);
      return true;
    }
    if (strcasecmp(attributeName, "LatitudeOfFirstGridPoint") == 0) {
      attributeValue = toString(mLatitudeOfFirstGridPoint);
      return true;
    }
    if (strcasecmp(attributeName, "LongitudeOfFirstGridPoint") == 0) {
      attributeValue = toString(mLongitudeOfFirstGridPoint);
      return true;
    }
    if (strcasecmp(attributeName, "StandardParallelInMicrodegrees") == 0) {
      attributeValue = toString(mStandardParallelInMicrodegrees);
      return true;
    }
    if (strcasecmp(attributeName, "CentralLongitudeInMicrodegrees") == 0) {
      attributeValue = toString(mCentralLongitudeInMicrodegrees);
      return true;
    }
    if (strcasecmp(attributeName, "ResolutionAndComponentFlags") == 0) {
      attributeValue = toString(mResolutionAndComponentFlags);
      return true;
    }
    if (strcasecmp(attributeName, "XDirectionGridLengthInMillimetres") == 0) {
      attributeValue = toString(mXDirectionGridLengthInMillimetres);
      return true;
    }
    if (strcasecmp(attributeName, "YDirectionGridLengthInMillimetres") == 0) {
      attributeValue = toString(mYDirectionGridLengthInMillimetres);
      return true;
    }
    if (mScanningMode.getAttributeValue(attributeName, attributeValue))
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool LambertAzimuthalEqualArea::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mEarthShape.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "NumberOfPointsAlongXAxis") == 0 && strcasecmp(attributeValue, toString(mNumberOfPointsAlongXAxis).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "NumberOfPointsAlongYAxis") == 0 && strcasecmp(attributeValue, toString(mNumberOfPointsAlongYAxis).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "LatitudeOfFirstGridPoint") == 0 && strcasecmp(attributeValue, toString(mLatitudeOfFirstGridPoint).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "LongitudeOfFirstGridPoint") == 0 && strcasecmp(attributeValue, toString(mLongitudeOfFirstGridPoint).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "StandardParallelInMicrodegrees") == 0 && strcasecmp(attributeValue, toString(mStandardParallelInMicrodegrees).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "CentralLongitudeInMicrodegrees") == 0 && strcasecmp(attributeValue, toString(mCentralLongitudeInMicrodegrees).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "ResolutionAndComponentFlags") == 0 && strcasecmp(attributeValue, toString(mResolutionAndComponentFlags).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "XDirectionGridLengthInMillimetres") == 0 && strcasecmp(attributeValue, toString(mXDirectionGridLengthInMillimetres).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "YDirectionGridLengthInMillimetres") == 0 && strcasecmp(attributeValue, toString(mYDirectionGridLengthInMillimetres).c_str()) == 0)
      return true;
    if (mScanningMode.hasAttributeValue(attributeName, attributeValue))
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void LambertAzimuthalEqualArea::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "LambertAzimuthalEqualArea\n";
    mEarthShape.print(stream, level + 1, optionFlags);
    stream << space(level) << "- NumberOfPointsAlongXAxis = " << toString(mNumberOfPointsAlongXAxis) << "\n";
    stream << space(level) << "- NumberOfPointsAlongYAxis = " << toString(mNumberOfPointsAlongYAxis) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- StandardParallelInMicrodegrees = " << toString(mStandardParallelInMicrodegrees) << "\n";
    stream << space(level) << "- CentralLongitudeInMicrodegrees = " << toString(mCentralLongitudeInMicrodegrees) << "\n";
    stream << space(level) << "- ResolutionAndComponentFlags = " << toString(mResolutionAndComponentFlags) << "\n";
    stream << space(level) << "- XDirectionGridLengthInMillimetres = " << toString(mXDirectionGridLengthInMillimetres) << "\n";
    stream << space(level) << "- YDirectionGridLengthInMillimetres = " << toString(mYDirectionGridLengthInMillimetres) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash LambertAzimuthalEqualArea::countHash() const {
  try {
    std::size_t seed = 0;
    if (mNumberOfPointsAlongXAxis)
      boost::hash_combine(seed, *mNumberOfPointsAlongXAxis);
    if (mNumberOfPointsAlongYAxis)
      boost::hash_combine(seed, *mNumberOfPointsAlongYAxis);
    if (mLatitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLatitudeOfFirstGridPoint);
    if (mLongitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLongitudeOfFirstGridPoint);
    if (mStandardParallelInMicrodegrees)
      boost::hash_combine(seed, *mStandardParallelInMicrodegrees);
    if (mCentralLongitudeInMicrodegrees)
      boost::hash_combine(seed, *mCentralLongitudeInMicrodegrees);
    boost::hash_combine(seed, mResolutionAndComponentFlags);
    if (mXDirectionGridLengthInMillimetres)
      boost::hash_combine(seed, *mXDirectionGridLengthInMillimetres);
    if (mYDirectionGridLengthInMillimetres)
      boost::hash_combine(seed, *mYDirectionGridLengthInMillimetres);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint LambertAzimuthalEqualArea::getTemplateNumber() const {
  return 140;
}

GridDefinition *LambertAzimuthalEqualArea::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new LambertAzimuthalEqualArea(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEarthShape} attribute. */

EarthShapeSettings *LambertAzimuthalEqualArea::getEarthShape() const {
  try {
    return static_cast<EarthShapeSettings *>(&mEarthShape);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfPointsAlongXAxis} attribute. */

const T::UInt32_opt &LambertAzimuthalEqualArea::getNumberOfPointsAlongXAxis() const {
  try {
    return mNumberOfPointsAlongXAxis;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfPointsAlongYAxis} attribute. */

const T::UInt32_opt &LambertAzimuthalEqualArea::getNumberOfPointsAlongYAxis() const {
  try {
    return mNumberOfPointsAlongYAxis;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

const T::Int32_opt &LambertAzimuthalEqualArea::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

const T::Int32_opt &LambertAzimuthalEqualArea::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mStandardParallelInMicrodegrees} attribute. */

const T::Int32_opt &LambertAzimuthalEqualArea::getStandardParallelInMicrodegrees() const {
  try {
    return mStandardParallelInMicrodegrees;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mCentralLongitudeInMicrodegrees} attribute. */

const T::Int32_opt &LambertAzimuthalEqualArea::getCentralLongitudeInMicrodegrees() const {
  try {
    return mCentralLongitudeInMicrodegrees;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mResolutionAndComponentFlags} attribute. */

std::uint8_t LambertAzimuthalEqualArea::getResolutionAndComponentFlags() const {
  try {
    return mResolutionAndComponentFlags;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mXDirectionGridLengthInMillimetres} attribute. */

const T::UInt32_opt &LambertAzimuthalEqualArea::getXDirectionGridLengthInMillimetres() const {
  try {
    return mXDirectionGridLengthInMillimetres;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mYDirectionGridLengthInMillimetres} attribute. */

const T::UInt32_opt &LambertAzimuthalEqualArea::getYDirectionGridLengthInMillimetres() const {
  try {
    return mYDirectionGridLengthInMillimetres;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *LambertAzimuthalEqualArea::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setEarthShape(EarthShapeSettings &earthShape) {
  try {
    mEarthShape = earthShape;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setNumberOfPointsAlongXAxis(T::UInt32_opt numberOfPointsAlongXAxis) {
  try {
    mNumberOfPointsAlongXAxis = numberOfPointsAlongXAxis;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setNumberOfPointsAlongYAxis(T::UInt32_opt numberOfPointsAlongYAxis) {
  try {
    mNumberOfPointsAlongYAxis = numberOfPointsAlongYAxis;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setLongitudeOfFirstGridPoint(T::Int32_opt longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setStandardParallelInMicrodegrees(T::Int32_opt standardParallelInMicrodegrees) {
  try {
    mStandardParallelInMicrodegrees = standardParallelInMicrodegrees;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setCentralLongitudeInMicrodegrees(T::Int32_opt centralLongitudeInMicrodegrees) {
  try {
    mCentralLongitudeInMicrodegrees = centralLongitudeInMicrodegrees;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setResolutionAndComponentFlags(std::uint8_t resolutionAndComponentFlags) {
  try {
    mResolutionAndComponentFlags = resolutionAndComponentFlags;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setXDirectionGridLengthInMillimetres(T::UInt32_opt xDirectionGridLengthInMillimetres) {
  try {
    mXDirectionGridLengthInMillimetres = xDirectionGridLengthInMillimetres;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setYDirectionGridLengthInMillimetres(T::UInt32_opt yDirectionGridLengthInMillimetres) {
  try {
    mYDirectionGridLengthInMillimetres = yDirectionGridLengthInMillimetres;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LambertAzimuthalEqualArea::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
