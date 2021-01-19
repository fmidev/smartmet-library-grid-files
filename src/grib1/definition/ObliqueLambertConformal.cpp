// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ObliqueLambertConformalImpl.*' files.
// ***********************************************************************

#include "ObliqueLambertConformal.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

ObliqueLambertConformal::ObliqueLambertConformal() {
  try {
    mNx = 0;
    mNy = 0;
    mLatitudeOfFirstGridPoint = 0;
    mLongitudeOfFirstGridPoint = 0;
    mLoV = 0;
    mDxInMetres = 0;
    mDyInMetres = 0;
    mProjectionCentreFlag = 0;
    mLatin1 = 0;
    mLatin2 = 0;
    mLatitudeOfSouthernPole = 0;
    mLongitudeOfSouthernPole = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

ObliqueLambertConformal::~ObliqueLambertConformal() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ObliqueLambertConformal::read(MemoryReader &memoryReader) {
  try {
    mNx = memoryReader.read_uint16();
    mNy = memoryReader.read_uint16();
    mLatitudeOfFirstGridPoint = memoryReader.read_int24();
    mLongitudeOfFirstGridPoint = memoryReader.read_int24();
    mResolutionFlags.read(memoryReader);
    mLoV = memoryReader.read_int24();
    mDxInMetres = memoryReader.read_uint24();
    mDyInMetres = memoryReader.read_uint24();
    mProjectionCentreFlag = memoryReader.read_uint8();
    mScanningMode.read(memoryReader);
    mLatin1 = memoryReader.read_int24();
    mLatin2 = memoryReader.read_int24();
    mLatitudeOfSouthernPole = memoryReader.read_int24();
    mLongitudeOfSouthernPole = memoryReader.read_int24();
    for (uint t = 0; t < 2; t++)
      memoryReader.read_uint8();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void ObliqueLambertConformal::write(DataWriter &dataWriter) {
  try {
    dataWriter << mNx;
    dataWriter << mNy;
    dataWriter.write_int24(mLatitudeOfFirstGridPoint);
    dataWriter.write_int24(mLongitudeOfFirstGridPoint);
    mResolutionFlags.write(dataWriter);
    dataWriter.write_int24(mLoV);
    dataWriter.write_uint24(mDxInMetres);
    dataWriter.write_uint24(mDyInMetres);
    dataWriter << mProjectionCentreFlag;
    mScanningMode.write(dataWriter);
    dataWriter.write_int24(mLatin1);
    dataWriter.write_int24(mLatin2);
    dataWriter.write_int24(mLatitudeOfSouthernPole);
    dataWriter.write_int24(mLongitudeOfSouthernPole);
    for (uint t = 0; t < 2; t++)
      dataWriter.write_uint8(0);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ObliqueLambertConformal::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sObliqueLambertConformal.Nx", prefix.c_str());
    attributeList.addAttribute(name, toString(mNx));
    sprintf(name, "%sObliqueLambertConformal.Ny", prefix.c_str());
    attributeList.addAttribute(name, toString(mNy));
    sprintf(name, "%sObliqueLambertConformal.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sObliqueLambertConformal.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sObliqueLambertConformal.", prefix.c_str());
    mResolutionFlags.getAttributeList(name, attributeList);
    sprintf(name, "%sObliqueLambertConformal.LoV", prefix.c_str());
    attributeList.addAttribute(name, toString(mLoV));
    sprintf(name, "%sObliqueLambertConformal.DxInMetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mDxInMetres));
    sprintf(name, "%sObliqueLambertConformal.DyInMetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mDyInMetres));
    sprintf(name, "%sObliqueLambertConformal.ProjectionCentreFlag", prefix.c_str());
    attributeList.addAttribute(name, toString(mProjectionCentreFlag));
    sprintf(name, "%sObliqueLambertConformal.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sObliqueLambertConformal.Latin1", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatin1));
    sprintf(name, "%sObliqueLambertConformal.Latin2", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatin2));
    sprintf(name, "%sObliqueLambertConformal.LatitudeOfSouthernPole", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfSouthernPole));
    sprintf(name, "%sObliqueLambertConformal.LongitudeOfSouthernPole", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfSouthernPole));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ObliqueLambertConformal::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ObliqueLambertConformal\n";
    stream << space(level) << "- Nx = " << toString(mNx) << "\n";
    stream << space(level) << "- Ny = " << toString(mNy) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    mResolutionFlags.print(stream, level + 1, optionFlags);
    stream << space(level) << "- LoV = " << toString(mLoV) << "\n";
    stream << space(level) << "- DxInMetres = " << toString(mDxInMetres) << "\n";
    stream << space(level) << "- DyInMetres = " << toString(mDyInMetres) << "\n";
    stream << space(level) << "- ProjectionCentreFlag = " << toString(mProjectionCentreFlag) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Latin1 = " << toString(mLatin1) << "\n";
    stream << space(level) << "- Latin2 = " << toString(mLatin2) << "\n";
    stream << space(level) << "- LatitudeOfSouthernPole = " << toString(mLatitudeOfSouthernPole) << "\n";
    stream << space(level) << "- LongitudeOfSouthernPole = " << toString(mLongitudeOfSouthernPole) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ObliqueLambertConformal::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNx);
    boost::hash_combine(seed, mNy);
    boost::hash_combine(seed, mLatitudeOfFirstGridPoint);
    boost::hash_combine(seed, mLongitudeOfFirstGridPoint);
    boost::hash_combine(seed, mLoV);
    boost::hash_combine(seed, mDxInMetres);
    boost::hash_combine(seed, mDyInMetres);
    boost::hash_combine(seed, mProjectionCentreFlag);
    boost::hash_combine(seed, mLatin1);
    boost::hash_combine(seed, mLatin2);
    boost::hash_combine(seed, mLatitudeOfSouthernPole);
    boost::hash_combine(seed, mLongitudeOfSouthernPole);
    // boost::hash_combine(seed,mResolutionFlags.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint ObliqueLambertConformal::getTemplateNumber() const {
  return 13;
}

GridDefinition *ObliqueLambertConformal::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new ObliqueLambertConformal(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNx} attribute. */

std::uint16_t ObliqueLambertConformal::getNx() const {
  try {
    return mNx;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNy} attribute. */

std::uint16_t ObliqueLambertConformal::getNy() const {
  try {
    return mNy;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

std::int24_t ObliqueLambertConformal::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

std::int24_t ObliqueLambertConformal::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mResolutionFlags} attribute. */

ResolutionFlagsSettings *ObliqueLambertConformal::getResolutionFlags() const {
  try {
    return static_cast<ResolutionFlagsSettings *>(&mResolutionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLoV} attribute. */

std::int24_t ObliqueLambertConformal::getLoV() const {
  try {
    return mLoV;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDxInMetres} attribute. */

std::uint24_t ObliqueLambertConformal::getDxInMetres() const {
  try {
    return mDxInMetres;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDyInMetres} attribute. */

std::uint24_t ObliqueLambertConformal::getDyInMetres() const {
  try {
    return mDyInMetres;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mProjectionCentreFlag} attribute. */

std::uint8_t ObliqueLambertConformal::getProjectionCentreFlag() const {
  try {
    return mProjectionCentreFlag;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *ObliqueLambertConformal::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatin1} attribute. */

std::int24_t ObliqueLambertConformal::getLatin1() const {
  try {
    return mLatin1;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatin2} attribute. */

std::int24_t ObliqueLambertConformal::getLatin2() const {
  try {
    return mLatin2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfSouthernPole} attribute. */

std::int24_t ObliqueLambertConformal::getLatitudeOfSouthernPole() const {
  try {
    return mLatitudeOfSouthernPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfSouthernPole} attribute. */

std::int24_t ObliqueLambertConformal::getLongitudeOfSouthernPole() const {
  try {
    return mLongitudeOfSouthernPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setNx(std::uint16_t nx) {
  try {
    mNx = nx;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setNy(std::uint16_t ny) {
  try {
    mNy = ny;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setLatitudeOfFirstGridPoint(std::int24_t latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setLongitudeOfFirstGridPoint(std::int24_t longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setResolutionFlags(ResolutionFlagsSettings &resolutionFlags) {
  try {
    mResolutionFlags = resolutionFlags;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setLoV(std::int24_t loV) {
  try {
    mLoV = loV;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setDxInMetres(std::uint24_t dxInMetres) {
  try {
    mDxInMetres = dxInMetres;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setDyInMetres(std::uint24_t dyInMetres) {
  try {
    mDyInMetres = dyInMetres;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setProjectionCentreFlag(std::uint8_t projectionCentreFlag) {
  try {
    mProjectionCentreFlag = projectionCentreFlag;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setLatin1(std::int24_t latin1) {
  try {
    mLatin1 = latin1;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setLatin2(std::int24_t latin2) {
  try {
    mLatin2 = latin2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setLatitudeOfSouthernPole(std::int24_t latitudeOfSouthernPole) {
  try {
    mLatitudeOfSouthernPole = latitudeOfSouthernPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ObliqueLambertConformal::setLongitudeOfSouthernPole(std::int24_t longitudeOfSouthernPole) {
  try {
    mLongitudeOfSouthernPole = longitudeOfSouthernPole;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
