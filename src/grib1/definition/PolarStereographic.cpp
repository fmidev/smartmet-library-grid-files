// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PolarStereographicImpl.*' files.
// ***********************************************************************

#include "PolarStereographic.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

PolarStereographic::PolarStereographic() {
  try {
    mNx = 0;
    mNy = 0;
    mLatitudeOfFirstGridPoint = 0;
    mLongitudeOfFirstGridPoint = 0;
    mOrientationOfTheGrid = 0;
    mDxInMetres = 0;
    mDyInMetres = 0;
    mProjectionCentreFlag = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

PolarStereographic::PolarStereographic(const PolarStereographic &other) : GridDefinition(other) {
  try {
    mNx = other.mNx;
    mNy = other.mNy;
    mLatitudeOfFirstGridPoint = other.mLatitudeOfFirstGridPoint;
    mLongitudeOfFirstGridPoint = other.mLongitudeOfFirstGridPoint;
    mResolutionFlags = other.mResolutionFlags;
    mOrientationOfTheGrid = other.mOrientationOfTheGrid;
    mDxInMetres = other.mDxInMetres;
    mDyInMetres = other.mDyInMetres;
    mProjectionCentreFlag = other.mProjectionCentreFlag;
    mScanningMode = other.mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

PolarStereographic::~PolarStereographic() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PolarStereographic::read(MemoryReader &memoryReader) {
  try {
    mNx = memoryReader.read_uint16();
    mNy = memoryReader.read_uint16();
    mLatitudeOfFirstGridPoint = memoryReader.read_int24();
    mLongitudeOfFirstGridPoint = memoryReader.read_int24();
    mResolutionFlags.read(memoryReader);
    mOrientationOfTheGrid = memoryReader.read_int24();
    mDxInMetres = memoryReader.read_uint24();
    mDyInMetres = memoryReader.read_uint24();
    mProjectionCentreFlag = memoryReader.read_uint8();
    mScanningMode.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void PolarStereographic::write(DataWriter &dataWriter) {
  try {
    dataWriter << mNx;
    dataWriter << mNy;
    dataWriter.write_int24(mLatitudeOfFirstGridPoint);
    dataWriter.write_int24(mLongitudeOfFirstGridPoint);
    mResolutionFlags.write(dataWriter);
    dataWriter.write_int24(mOrientationOfTheGrid);
    dataWriter.write_uint24(mDxInMetres);
    dataWriter.write_uint24(mDyInMetres);
    dataWriter << mProjectionCentreFlag;
    mScanningMode.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void PolarStereographic::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sPolarStereographic.Nx", prefix.c_str());
    attributeList.addAttribute(name, toString(mNx));
    sprintf(name, "%sPolarStereographic.Ny", prefix.c_str());
    attributeList.addAttribute(name, toString(mNy));
    sprintf(name, "%sPolarStereographic.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sPolarStereographic.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sPolarStereographic.", prefix.c_str());
    mResolutionFlags.getAttributeList(name, attributeList);
    sprintf(name, "%sPolarStereographic.OrientationOfTheGrid", prefix.c_str());
    attributeList.addAttribute(name, toString(mOrientationOfTheGrid));
    sprintf(name, "%sPolarStereographic.DxInMetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mDxInMetres));
    sprintf(name, "%sPolarStereographic.DyInMetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mDyInMetres));
    sprintf(name, "%sPolarStereographic.ProjectionCentreFlag", prefix.c_str());
    attributeList.addAttribute(name, toString(mProjectionCentreFlag));
    sprintf(name, "%sPolarStereographic.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void PolarStereographic::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "PolarStereographic\n";
    stream << space(level) << "- Nx = " << toString(mNx) << "\n";
    stream << space(level) << "- Ny = " << toString(mNy) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    mResolutionFlags.print(stream, level + 1, optionFlags);
    stream << space(level) << "- OrientationOfTheGrid = " << toString(mOrientationOfTheGrid) << "\n";
    stream << space(level) << "- DxInMetres = " << toString(mDxInMetres) << "\n";
    stream << space(level) << "- DyInMetres = " << toString(mDyInMetres) << "\n";
    stream << space(level) << "- ProjectionCentreFlag = " << toString(mProjectionCentreFlag) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash PolarStereographic::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNx);
    boost::hash_combine(seed, mNy);
    boost::hash_combine(seed, mLatitudeOfFirstGridPoint);
    boost::hash_combine(seed, mLongitudeOfFirstGridPoint);
    boost::hash_combine(seed, mOrientationOfTheGrid);
    boost::hash_combine(seed, mDxInMetres);
    boost::hash_combine(seed, mDyInMetres);
    boost::hash_combine(seed, mProjectionCentreFlag);
    // boost::hash_combine(seed,mResolutionFlags.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint PolarStereographic::getTemplateNumber() const {
  return 5;
}

GridDefinition *PolarStereographic::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new PolarStereographic(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNx} attribute. */

std::uint16_t PolarStereographic::getNx() const {
  try {
    return mNx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNy} attribute. */

std::uint16_t PolarStereographic::getNy() const {
  try {
    return mNy;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

std::int24_t PolarStereographic::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

std::int24_t PolarStereographic::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mResolutionFlags} attribute. */

ResolutionFlagsSettings *PolarStereographic::getResolutionFlags() const {
  try {
    return static_cast<ResolutionFlagsSettings *>(&mResolutionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mOrientationOfTheGrid} attribute. */

std::int24_t PolarStereographic::getOrientationOfTheGrid() const {
  try {
    return mOrientationOfTheGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDxInMetres} attribute. */

std::uint24_t PolarStereographic::getDxInMetres() const {
  try {
    return mDxInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDyInMetres} attribute. */

std::uint24_t PolarStereographic::getDyInMetres() const {
  try {
    return mDyInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mProjectionCentreFlag} attribute. */

std::uint8_t PolarStereographic::getProjectionCentreFlag() const {
  try {
    return mProjectionCentreFlag;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *PolarStereographic::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setNx(std::uint16_t nx) {
  try {
    mNx = nx;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setNy(std::uint16_t ny) {
  try {
    mNy = ny;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setLatitudeOfFirstGridPoint(std::int24_t latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setLongitudeOfFirstGridPoint(std::int24_t longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setResolutionFlags(ResolutionFlagsSettings &resolutionFlags) {
  try {
    mResolutionFlags = resolutionFlags;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setOrientationOfTheGrid(std::int24_t orientationOfTheGrid) {
  try {
    mOrientationOfTheGrid = orientationOfTheGrid;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setDxInMetres(std::uint24_t dxInMetres) {
  try {
    mDxInMetres = dxInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setDyInMetres(std::uint24_t dyInMetres) {
  try {
    mDyInMetres = dyInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setProjectionCentreFlag(std::uint8_t projectionCentreFlag) {
  try {
    mProjectionCentreFlag = projectionCentreFlag;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void PolarStereographic::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
