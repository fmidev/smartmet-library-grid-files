// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'LatLonImpl.*' files.
// ***********************************************************************

#include "grib1/definition/LatLon.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

LatLon::LatLon() {
  try {
    mNi = 0;
    mNj = 0;
    mIDirectionIncrement = 0;
    mJDirectionIncrement = 0;
    mZero = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

LatLon::~LatLon() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current
   section object.

        \param memoryReader  This object controls the access to the memory
   mapped file.
*/

void LatLon::read(MemoryReader &memoryReader) {
  try {
    mNi = memoryReader.read_uint16();
    mNj = memoryReader.read_uint16();
    mGridArea.read(memoryReader);
    mIDirectionIncrement = memoryReader.read_uint16();
    mJDirectionIncrement = memoryReader.read_uint16();
    mScanningMode.read(memoryReader);
    mZero = memoryReader.read_uint32();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void LatLon::getAttributeList(std::string prefix,
                              T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sLatLon.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sLatLon.Nj", prefix.c_str());
    attributeList.addAttribute(name, toString(mNj));
    sprintf(name, "%sLatLon.", prefix.c_str());
    mGridArea.getAttributeList(name, attributeList);
    sprintf(name, "%sLatLon.IDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mIDirectionIncrement));
    sprintf(name, "%sLatLon.JDirectionIncrement", prefix.c_str());
    attributeList.addAttribute(name, toString(mJDirectionIncrement));
    sprintf(name, "%sLatLon.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sLatLon.Zero", prefix.c_str());
    attributeList.addAttribute(name, toString(mZero));
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

void LatLon::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "LatLon\n";
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nj = " << toString(mNj) << "\n";
    mGridArea.print(stream, level + 1, optionFlags);
    stream << space(level)
           << "- IDirectionIncrement = " << toString(mIDirectionIncrement)
           << "\n";
    stream << space(level)
           << "- JDirectionIncrement = " << toString(mJDirectionIncrement)
           << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Zero = " << toString(mZero) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash LatLon::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNi);
    boost::hash_combine(seed, mNj);
    boost::hash_combine(seed, mIDirectionIncrement);
    boost::hash_combine(seed, mJDirectionIncrement);
    boost::hash_combine(seed, mZero);
    boost::hash_combine(seed, mGridArea.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

std::uint16_t LatLon::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNj} attribute. */

std::uint16_t LatLon::getNj() const {
  try {
    return mNj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mGridArea} attribute. */

const GridAreaSettings *LatLon::getGridArea() const {
  try {
    return &mGridArea;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mIDirectionIncrement}
 * attribute. */

std::uint16_t LatLon::getIDirectionIncrement() const {
  try {
    return mIDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mJDirectionIncrement}
 * attribute. */

std::uint16_t LatLon::getJDirectionIncrement() const {
  try {
    return mJDirectionIncrement;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode}
 * attribute. */

const ScanningModeSettings *LatLon::getScanningMode() const {
  try {
    return &mScanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mZero} attribute. */

std::uint32_t LatLon::getZero() const {
  try {
    return mZero;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB1
} // namespace SmartMet