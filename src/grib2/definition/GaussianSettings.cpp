// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GaussianSettingsImpl.*' files.
// ***********************************************************************

#include "GaussianSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

GaussianSettings::GaussianSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

GaussianSettings::~GaussianSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GaussianSettings::read(MemoryReader &memoryReader) {
  try {
    mGrid.read(memoryReader);
    mIDirectionIncrement = memoryReader.read_UInt32_opt();
    mN = memoryReader.read_UInt32_opt();
    mScanningMode.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void GaussianSettings::write(DataWriter &dataWriter) {
  try {
    mGrid.write(dataWriter);
    dataWriter << mIDirectionIncrement;
    dataWriter << mN;
    mScanningMode.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void GaussianSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sGaussianSettings.", prefix.c_str());
    mGrid.getAttributeList(name, attributeList);
    sprintf(name, "%sGaussianSettings.IDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mIDirectionIncrement));
    sprintf(name, "%sGaussianSettings.N", prefix.c_str());
    attributeList.addAttribute(name, toString(mN));
    sprintf(name, "%sGaussianSettings.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool GaussianSettings::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mGrid.getAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "IDirectionIncrement") == 0) {
      attributeValue = toString(mIDirectionIncrement);
      return true;
    }
    if (strcasecmp(attributeName, "N") == 0) {
      attributeValue = toString(mN);
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

bool GaussianSettings::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mGrid.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "IDirectionIncrement") == 0 && strcasecmp(attributeValue, toString(mIDirectionIncrement).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "N") == 0 && strcasecmp(attributeValue, toString(mN).c_str()) == 0)
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

void GaussianSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "GaussianSettings\n";
    mGrid.print(stream, level + 1, optionFlags);
    stream << space(level) << "- IDirectionIncrement = " << toString(mIDirectionIncrement) << "\n";
    stream << space(level) << "- N = " << toString(mN) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash GaussianSettings::countHash() const {
  try {
    std::size_t seed = 0;
    if (mIDirectionIncrement)
      boost::hash_combine(seed, *mIDirectionIncrement);
    if (mN)
      boost::hash_combine(seed, *mN);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mGrid} attribute. */

GridSettings *GaussianSettings::getGrid() const {
  try {
    return static_cast<GridSettings *>(&mGrid);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mIDirectionIncrement} attribute. */

const T::UInt32_opt &GaussianSettings::getIDirectionIncrement() const {
  try {
    return mIDirectionIncrement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mN} attribute. */

const T::UInt32_opt &GaussianSettings::getN() const {
  try {
    return mN;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *GaussianSettings::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GaussianSettings::setGrid(GridSettings &grid) {
  try {
    mGrid = grid;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GaussianSettings::setIDirectionIncrement(T::UInt32_opt iDirectionIncrement) {
  try {
    mIDirectionIncrement = iDirectionIncrement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GaussianSettings::setN(T::UInt32_opt n) {
  try {
    mN = n;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GaussianSettings::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
