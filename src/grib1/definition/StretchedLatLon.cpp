// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedLatLonImpl.*' files.
// ***********************************************************************

#include "grib1/definition/StretchedLatLon.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

StretchedLatLon::StretchedLatLon() {
  try {
    mNi = 0;
    mNj = 0;
    mIDirectionIncrement = 0;
    mJDirectionIncrement = 0;
    mZero = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

StretchedLatLon::~StretchedLatLon() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void StretchedLatLon::read(MemoryReader &memoryReader) {
  try {
    mNi = memoryReader.read_uint16();
    mNj = memoryReader.read_uint16();
    mGridArea.read(memoryReader);
    mIDirectionIncrement = memoryReader.read_uint16();
    mJDirectionIncrement = memoryReader.read_uint16();
    mScanningMode.read(memoryReader);
    mZero = memoryReader.read_uint32();
    mGridStretching.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void StretchedLatLon::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sStretchedLatLon.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sStretchedLatLon.Nj", prefix.c_str());
    attributeList.addAttribute(name, toString(mNj));
    sprintf(name, "%sStretchedLatLon.", prefix.c_str());
    mGridArea.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedLatLon.IDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mIDirectionIncrement));
    sprintf(name, "%sStretchedLatLon.JDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mJDirectionIncrement));
    sprintf(name, "%sStretchedLatLon.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedLatLon.Zero", prefix.c_str());
    attributeList.addAttribute(name, toString(mZero));
    sprintf(name, "%sStretchedLatLon.", prefix.c_str());
    mGridStretching.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void StretchedLatLon::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "StretchedLatLon\n";
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nj = " << toString(mNj) << "\n";
    mGridArea.print(stream, level + 1, optionFlags);
    stream << space(level) << "- IDirectionIncrement = " << toString(mIDirectionIncrement) << "\n";
    stream << space(level) << "- JDirectionIncrement = " << toString(mJDirectionIncrement) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Zero = " << toString(mZero) << "\n";
    mGridStretching.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash StretchedLatLon::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNi);
    boost::hash_combine(seed, mNj);
    boost::hash_combine(seed, mIDirectionIncrement);
    boost::hash_combine(seed, mJDirectionIncrement);
    // boost::hash_combine(seed,mZero);
    boost::hash_combine(seed, mGridArea.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    boost::hash_combine(seed, mGridStretching.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

std::uint16_t StretchedLatLon::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNj} attribute. */

std::uint16_t StretchedLatLon::getNj() const {
  try {
    return mNj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mGridArea} attribute. */

const GridAreaSettings *StretchedLatLon::getGridArea() const {
  try {
    return &mGridArea;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mIDirectionIncrement} attribute. */

std::uint16_t StretchedLatLon::getIDirectionIncrement() const {
  try {
    return mIDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mJDirectionIncrement} attribute. */

std::uint16_t StretchedLatLon::getJDirectionIncrement() const {
  try {
    return mJDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

const ScanningModeSettings *StretchedLatLon::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mZero} attribute. */

std::uint32_t StretchedLatLon::getZero() const {
  try {
    return mZero;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mGridStretching} attribute. */

const GridStretchingSettings *StretchedLatLon::getGridStretching() const {
  try {
    return &mGridStretching;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedLatLon::setNi(std::uint16_t ni) {
  try {
    mNi = ni;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedLatLon::setNj(std::uint16_t nj) {
  try {
    mNj = nj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedLatLon::setGridArea(GridAreaSettings gridArea) {
  try {
    mGridArea = gridArea;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedLatLon::setIDirectionIncrement(std::uint16_t iDirectionIncrement) {
  try {
    mIDirectionIncrement = iDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedLatLon::setJDirectionIncrement(std::uint16_t jDirectionIncrement) {
  try {
    mJDirectionIncrement = jDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedLatLon::setScanningMode(ScanningModeSettings scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedLatLon::setZero(std::uint32_t zero) {
  try {
    mZero = zero;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedLatLon::setGridStretching(GridStretchingSettings gridStretching) {
  try {
    mGridStretching = gridStretching;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB1
} // namespace SmartMet
