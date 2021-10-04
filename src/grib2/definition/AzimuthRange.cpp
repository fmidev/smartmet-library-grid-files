// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AzimuthRangeImpl.*' files.
// ***********************************************************************

#include "AzimuthRange.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AzimuthRange::AzimuthRange() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

AzimuthRange::~AzimuthRange() {
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void AzimuthRange::write(DataWriter &dataWriter) {
  try {
    dataWriter << mNumberOfDataBinsAlongRadials;
    dataWriter << mNumberOfRadials;
    dataWriter << mLatitudeOfCenterPoint;
    dataWriter << mLongitudeOfCenterPoint;
    dataWriter << mSpacingOfBinsAlongRadials;
    dataWriter << mOffsetFromOriginToInnerBound;
    mScanningMode.write(dataWriter);
    dataWriter << mStartingAzimuth;
    dataWriter << mAzimuthalWidth;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void AzimuthRange::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool AzimuthRange::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (strcasecmp(attributeName, "NumberOfDataBinsAlongRadials") == 0) {
      attributeValue = toString(mNumberOfDataBinsAlongRadials);
      return true;
    }
    if (strcasecmp(attributeName, "NumberOfRadials") == 0) {
      attributeValue = toString(mNumberOfRadials);
      return true;
    }
    if (strcasecmp(attributeName, "LatitudeOfCenterPoint") == 0) {
      attributeValue = toString(mLatitudeOfCenterPoint);
      return true;
    }
    if (strcasecmp(attributeName, "LongitudeOfCenterPoint") == 0) {
      attributeValue = toString(mLongitudeOfCenterPoint);
      return true;
    }
    if (strcasecmp(attributeName, "SpacingOfBinsAlongRadials") == 0) {
      attributeValue = toString(mSpacingOfBinsAlongRadials);
      return true;
    }
    if (strcasecmp(attributeName, "OffsetFromOriginToInnerBound") == 0) {
      attributeValue = toString(mOffsetFromOriginToInnerBound);
      return true;
    }
    if (mScanningMode.getAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "StartingAzimuth") == 0) {
      attributeValue = toString(mStartingAzimuth);
      return true;
    }
    if (strcasecmp(attributeName, "AzimuthalWidth") == 0) {
      attributeValue = toString(mAzimuthalWidth);
      return true;
    }
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool AzimuthRange::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "NumberOfDataBinsAlongRadials") == 0 && strcasecmp(attributeValue, toString(mNumberOfDataBinsAlongRadials).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "NumberOfRadials") == 0 && strcasecmp(attributeValue, toString(mNumberOfRadials).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "LatitudeOfCenterPoint") == 0 && strcasecmp(attributeValue, toString(mLatitudeOfCenterPoint).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "LongitudeOfCenterPoint") == 0 && strcasecmp(attributeValue, toString(mLongitudeOfCenterPoint).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "SpacingOfBinsAlongRadials") == 0 && strcasecmp(attributeValue, toString(mSpacingOfBinsAlongRadials).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "OffsetFromOriginToInnerBound") == 0 && strcasecmp(attributeValue, toString(mOffsetFromOriginToInnerBound).c_str()) == 0)
      return true;
    if (mScanningMode.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "StartingAzimuth") == 0 && strcasecmp(attributeValue, toString(mStartingAzimuth).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "AzimuthalWidth") == 0 && strcasecmp(attributeValue, toString(mAzimuthalWidth).c_str()) == 0)
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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
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
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint AzimuthRange::getTemplateNumber() const {
  return 120;
}

GridDefinition *AzimuthRange::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new AzimuthRange(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfDataBinsAlongRadials} attribute. */

const T::UInt32_opt &AzimuthRange::getNumberOfDataBinsAlongRadials() const {
  try {
    return mNumberOfDataBinsAlongRadials;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfRadials} attribute. */

const T::UInt32_opt &AzimuthRange::getNumberOfRadials() const {
  try {
    return mNumberOfRadials;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfCenterPoint} attribute. */

const T::Int32_opt &AzimuthRange::getLatitudeOfCenterPoint() const {
  try {
    return mLatitudeOfCenterPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfCenterPoint} attribute. */

const T::UInt32_opt &AzimuthRange::getLongitudeOfCenterPoint() const {
  try {
    return mLongitudeOfCenterPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSpacingOfBinsAlongRadials} attribute. */

const T::UInt32_opt &AzimuthRange::getSpacingOfBinsAlongRadials() const {
  try {
    return mSpacingOfBinsAlongRadials;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mOffsetFromOriginToInnerBound} attribute. */

const T::UInt32_opt &AzimuthRange::getOffsetFromOriginToInnerBound() const {
  try {
    return mOffsetFromOriginToInnerBound;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *AzimuthRange::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mStartingAzimuth} attribute. */

const T::Int16_opt &AzimuthRange::getStartingAzimuth() const {
  try {
    return mStartingAzimuth;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mAzimuthalWidth} attribute. */

const T::Int16_opt &AzimuthRange::getAzimuthalWidth() const {
  try {
    return mAzimuthalWidth;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setNumberOfDataBinsAlongRadials(T::UInt32_opt numberOfDataBinsAlongRadials) {
  try {
    mNumberOfDataBinsAlongRadials = numberOfDataBinsAlongRadials;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setNumberOfRadials(T::UInt32_opt numberOfRadials) {
  try {
    mNumberOfRadials = numberOfRadials;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setLatitudeOfCenterPoint(T::Int32_opt latitudeOfCenterPoint) {
  try {
    mLatitudeOfCenterPoint = latitudeOfCenterPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setLongitudeOfCenterPoint(T::UInt32_opt longitudeOfCenterPoint) {
  try {
    mLongitudeOfCenterPoint = longitudeOfCenterPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setSpacingOfBinsAlongRadials(T::UInt32_opt spacingOfBinsAlongRadials) {
  try {
    mSpacingOfBinsAlongRadials = spacingOfBinsAlongRadials;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setOffsetFromOriginToInnerBound(T::UInt32_opt offsetFromOriginToInnerBound) {
  try {
    mOffsetFromOriginToInnerBound = offsetFromOriginToInnerBound;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setStartingAzimuth(T::Int16_opt startingAzimuth) {
  try {
    mStartingAzimuth = startingAzimuth;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void AzimuthRange::setAzimuthalWidth(T::Int16_opt azimuthalWidth) {
  try {
    mAzimuthalWidth = azimuthalWidth;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
