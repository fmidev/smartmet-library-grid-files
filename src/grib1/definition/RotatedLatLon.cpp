// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotatedLatLonImpl.*' files.
// ***********************************************************************

#include "RotatedLatLon.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

RotatedLatLon::RotatedLatLon() {
  try {
    mNi = 0;
    mNj = 0;
    mIDirectionIncrement = 0;
    mJDirectionIncrement = 0;
    mZero = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

RotatedLatLon::~RotatedLatLon() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void RotatedLatLon::read(MemoryReader &memoryReader) {
  try {
    mNi = memoryReader.read_uint16();
    mNj = memoryReader.read_uint16();
    mGridArea.read(memoryReader);
    mIDirectionIncrement = memoryReader.read_uint16();
    mJDirectionIncrement = memoryReader.read_uint16();
    mScanningMode.read(memoryReader);
    mZero = memoryReader.read_uint32();
    mRotation.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void RotatedLatLon::write(DataWriter &dataWriter) {
  try {
    dataWriter << mNi;
    dataWriter << mNj;
    mGridArea.write(dataWriter);
    dataWriter << mIDirectionIncrement;
    dataWriter << mJDirectionIncrement;
    mScanningMode.write(dataWriter);
    dataWriter << mZero;
    mRotation.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void RotatedLatLon::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sRotatedLatLon.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sRotatedLatLon.Nj", prefix.c_str());
    attributeList.addAttribute(name, toString(mNj));
    sprintf(name, "%sRotatedLatLon.", prefix.c_str());
    mGridArea.getAttributeList(name, attributeList);
    sprintf(name, "%sRotatedLatLon.IDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mIDirectionIncrement));
    sprintf(name, "%sRotatedLatLon.JDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mJDirectionIncrement));
    sprintf(name, "%sRotatedLatLon.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sRotatedLatLon.Zero", prefix.c_str());
    attributeList.addAttribute(name, toString(mZero));
    sprintf(name, "%sRotatedLatLon.", prefix.c_str());
    mRotation.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool RotatedLatLon::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (strcasecmp(attributeName, "Ni") == 0) {
      attributeValue = toString(mNi);
      return true;
    }
    if (strcasecmp(attributeName, "Nj") == 0) {
      attributeValue = toString(mNj);
      return true;
    }
    if (mGridArea.getAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "IDirectionIncrement") == 0) {
      attributeValue = toString(mIDirectionIncrement);
      return true;
    }
    if (strcasecmp(attributeName, "JDirectionIncrement") == 0) {
      attributeValue = toString(mJDirectionIncrement);
      return true;
    }
    if (mScanningMode.getAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "Zero") == 0) {
      attributeValue = toString(mZero);
      return true;
    }
    if (mRotation.getAttributeValue(attributeName, attributeValue))
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

bool RotatedLatLon::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "Ni") == 0 && strcasecmp(attributeValue, toString(mNi).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "Nj") == 0 && strcasecmp(attributeValue, toString(mNj).c_str()) == 0)
      return true;
    if (mGridArea.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "IDirectionIncrement") == 0 && strcasecmp(attributeValue, toString(mIDirectionIncrement).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "JDirectionIncrement") == 0 && strcasecmp(attributeValue, toString(mJDirectionIncrement).c_str()) == 0)
      return true;
    if (mScanningMode.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "Zero") == 0 && strcasecmp(attributeValue, toString(mZero).c_str()) == 0)
      return true;
    if (mRotation.hasAttributeValue(attributeName, attributeValue))
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

void RotatedLatLon::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "RotatedLatLon\n";
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nj = " << toString(mNj) << "\n";
    mGridArea.print(stream, level + 1, optionFlags);
    stream << space(level) << "- IDirectionIncrement = " << toString(mIDirectionIncrement) << "\n";
    stream << space(level) << "- JDirectionIncrement = " << toString(mJDirectionIncrement) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Zero = " << toString(mZero) << "\n";
    mRotation.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash RotatedLatLon::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNi);
    boost::hash_combine(seed, mNj);
    boost::hash_combine(seed, mIDirectionIncrement);
    boost::hash_combine(seed, mJDirectionIncrement);
    // boost::hash_combine(seed,mZero);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint RotatedLatLon::getTemplateNumber() const {
  return 10;
}

GridDefinition *RotatedLatLon::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new RotatedLatLon(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

std::uint16_t RotatedLatLon::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNj} attribute. */

std::uint16_t RotatedLatLon::getNj() const {
  try {
    return mNj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mGridArea} attribute. */

GridAreaSettings *RotatedLatLon::getGridArea() const {
  try {
    return static_cast<GridAreaSettings *>(&mGridArea);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mIDirectionIncrement} attribute. */

std::uint16_t RotatedLatLon::getIDirectionIncrement() const {
  try {
    return mIDirectionIncrement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mJDirectionIncrement} attribute. */

std::uint16_t RotatedLatLon::getJDirectionIncrement() const {
  try {
    return mJDirectionIncrement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *RotatedLatLon::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mZero} attribute. */

std::uint32_t RotatedLatLon::getZero() const {
  try {
    return mZero;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mRotation} attribute. */

RotationSettings *RotatedLatLon::getRotation() const {
  try {
    return static_cast<RotationSettings *>(&mRotation);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedLatLon::setNi(std::uint16_t ni) {
  try {
    mNi = ni;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedLatLon::setNj(std::uint16_t nj) {
  try {
    mNj = nj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedLatLon::setGridArea(GridAreaSettings &gridArea) {
  try {
    mGridArea = gridArea;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedLatLon::setIDirectionIncrement(std::uint16_t iDirectionIncrement) {
  try {
    mIDirectionIncrement = iDirectionIncrement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedLatLon::setJDirectionIncrement(std::uint16_t jDirectionIncrement) {
  try {
    mJDirectionIncrement = jDirectionIncrement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedLatLon::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedLatLon::setZero(std::uint32_t zero) {
  try {
    mZero = zero;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RotatedLatLon::setRotation(RotationSettings &rotation) {
  try {
    mRotation = rotation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
