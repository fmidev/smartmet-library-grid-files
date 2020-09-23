// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotatedGaussianImpl.*' files.
// ***********************************************************************

#include "RotatedGaussian.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

RotatedGaussian::RotatedGaussian() {
  try {
    mNi = 0;
    mNj = 0;
    mIDirectionIncrement = 0;
    mN = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

RotatedGaussian::RotatedGaussian(const RotatedGaussian &other) : GridDefinition(other) {
  try {
    mNi = other.mNi;
    mNj = other.mNj;
    mGridArea = other.mGridArea;
    mIDirectionIncrement = other.mIDirectionIncrement;
    mN = other.mN;
    mScanningMode = other.mScanningMode;
    mRotation = other.mRotation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

RotatedGaussian::~RotatedGaussian() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void RotatedGaussian::read(MemoryReader &memoryReader) {
  try {
    mNi = memoryReader.read_uint16();
    mNj = memoryReader.read_int16();
    mGridArea.read(memoryReader);
    mIDirectionIncrement = memoryReader.read_uint16();
    mN = memoryReader.read_uint16();
    mScanningMode.read(memoryReader);
    for (uint t = 0; t < 4; t++)
      memoryReader.read_uint8();
    mRotation.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void RotatedGaussian::write(DataWriter &dataWriter) {
  try {
    dataWriter << mNi;
    dataWriter << mNj;
    mGridArea.write(dataWriter);
    dataWriter << mIDirectionIncrement;
    dataWriter << mN;
    mScanningMode.write(dataWriter);
    for (uint t = 0; t < 4; t++)
      dataWriter.write_uint8(0);
    mRotation.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void RotatedGaussian::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sRotatedGaussian.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sRotatedGaussian.Nj", prefix.c_str());
    attributeList.addAttribute(name, toString(mNj));
    sprintf(name, "%sRotatedGaussian.", prefix.c_str());
    mGridArea.getAttributeList(name, attributeList);
    sprintf(name, "%sRotatedGaussian.IDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mIDirectionIncrement));
    sprintf(name, "%sRotatedGaussian.N", prefix.c_str());
    attributeList.addAttribute(name, toString(mN));
    sprintf(name, "%sRotatedGaussian.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sRotatedGaussian.", prefix.c_str());
    mRotation.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void RotatedGaussian::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "RotatedGaussian\n";
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nj = " << toString(mNj) << "\n";
    mGridArea.print(stream, level + 1, optionFlags);
    stream << space(level) << "- IDirectionIncrement = " << toString(mIDirectionIncrement) << "\n";
    stream << space(level) << "- N = " << toString(mN) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    mRotation.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash RotatedGaussian::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNi);
    boost::hash_combine(seed, mNj);
    boost::hash_combine(seed, mIDirectionIncrement);
    boost::hash_combine(seed, mN);
    boost::hash_combine(seed, mGridArea.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    boost::hash_combine(seed, mRotation.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint RotatedGaussian::getTemplateNumber() const {
  return 14;
}

GridDefinition *RotatedGaussian::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new RotatedGaussian(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

std::uint16_t RotatedGaussian::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNj} attribute. */

std::int16_t RotatedGaussian::getNj() const {
  try {
    return mNj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mGridArea} attribute. */

GridAreaSettings *RotatedGaussian::getGridArea() const {
  try {
    return static_cast<GridAreaSettings *>(&mGridArea);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mIDirectionIncrement} attribute. */

std::uint16_t RotatedGaussian::getIDirectionIncrement() const {
  try {
    return mIDirectionIncrement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mN} attribute. */

std::uint16_t RotatedGaussian::getN() const {
  try {
    return mN;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *RotatedGaussian::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mRotation} attribute. */

RotationSettings *RotatedGaussian::getRotation() const {
  try {
    return static_cast<RotationSettings *>(&mRotation);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void RotatedGaussian::setNi(std::uint16_t ni) {
  try {
    mNi = ni;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void RotatedGaussian::setNj(std::int16_t nj) {
  try {
    mNj = nj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void RotatedGaussian::setGridArea(GridAreaSettings &gridArea) {
  try {
    mGridArea = gridArea;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void RotatedGaussian::setIDirectionIncrement(std::uint16_t iDirectionIncrement) {
  try {
    mIDirectionIncrement = iDirectionIncrement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void RotatedGaussian::setN(std::uint16_t n) {
  try {
    mN = n;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void RotatedGaussian::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void RotatedGaussian::setRotation(RotationSettings &rotation) {
  try {
    mRotation = rotation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
