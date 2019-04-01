// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'MercatorImpl.*' files.
// ***********************************************************************

#include "Mercator.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

Mercator::Mercator() {
  try {
    mNi = 0;
    mNj = 0;
    mLatin = 0;
    mDiInMetres = 0;
    mDjInMetres = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

Mercator::Mercator(const Mercator &other) : GridDefinition(other) {
  try {
    mNi = other.mNi;
    mNj = other.mNj;
    mGridArea = other.mGridArea;
    mLatin = other.mLatin;
    mScanningMode = other.mScanningMode;
    mDiInMetres = other.mDiInMetres;
    mDjInMetres = other.mDjInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

Mercator::~Mercator() {
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Mercator::read(MemoryReader &memoryReader) {
  try {
    mNi = memoryReader.read_int16();
    mNj = memoryReader.read_int16();
    mGridArea.read(memoryReader);
    mLatin = memoryReader.read_int24();
    memoryReader.read_uint8();  // *** This field was not automatically generated
    mScanningMode.read(memoryReader);
    mDiInMetres = memoryReader.read_int24();
    mDjInMetres = memoryReader.read_int24();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void Mercator::write(DataWriter &dataWriter) {
  try {
    dataWriter.write_int24(mNi);
    dataWriter.write_int24(mNj);
    mGridArea.write(dataWriter);
    dataWriter.write_int24(mLatin);
    dataWriter.write_uint8(0);       // *** This field was not automatically generated
    mScanningMode.write(dataWriter);
    dataWriter.write_int24(mDiInMetres);
    dataWriter.write_int24(mDjInMetres);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Mercator::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sMercator.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sMercator.Nj", prefix.c_str());
    attributeList.addAttribute(name, toString(mNj));
    sprintf(name, "%sMercator.", prefix.c_str());
    mGridArea.getAttributeList(name, attributeList);
    sprintf(name, "%sMercator.Latin", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatin));
    sprintf(name, "%sMercator.", prefix.c_str());
    mScanningMode.getAttributeList(name, attributeList);
    sprintf(name, "%sMercator.DiInMetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mDiInMetres));
    sprintf(name, "%sMercator.DjInMetres", prefix.c_str());
    attributeList.addAttribute(name, toString(mDjInMetres));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void Mercator::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "Mercator\n";
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nj = " << toString(mNj) << "\n";
    mGridArea.print(stream, level + 1, optionFlags);
    stream << space(level) << "- Latin = " << toString(mLatin) << "\n";
    mScanningMode.print(stream, level + 1, optionFlags);
    stream << space(level) << "- DiInMetres = " << toString(mDiInMetres) << "\n";
    stream << space(level) << "- DjInMetres = " << toString(mDjInMetres) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Mercator::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNi);
    boost::hash_combine(seed, mNj);
    boost::hash_combine(seed, mLatin);
    boost::hash_combine(seed, mDiInMetres);
    boost::hash_combine(seed, mDjInMetres);
    boost::hash_combine(seed, mGridArea.countHash());
    boost::hash_combine(seed, mScanningMode.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint Mercator::getTemplateNumber() const {
  return 1;
}

GridDefinition *Mercator::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new Mercator(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

std::int16_t Mercator::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNj} attribute. */

std::int16_t Mercator::getNj() const {
  try {
    return mNj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mGridArea} attribute. */

GridAreaSettings *Mercator::getGridArea() const {
  try {
    return static_cast<GridAreaSettings *>(&mGridArea);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatin} attribute. */

std::int24_t Mercator::getLatin() const {
  try {
    return mLatin;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mScanningMode} attribute. */

ScanningModeSettings *Mercator::getScanningMode() const {
  try {
    return static_cast<ScanningModeSettings *>(&mScanningMode);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDiInMetres} attribute. */

std::int24_t Mercator::getDiInMetres() const {
  try {
    return mDiInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mDjInMetres} attribute. */

std::int24_t Mercator::getDjInMetres() const {
  try {
    return mDjInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void Mercator::setNi(std::int16_t ni) {
  try {
    mNi = ni;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void Mercator::setNj(std::int16_t nj) {
  try {
    mNj = nj;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void Mercator::setGridArea(GridAreaSettings &gridArea) {
  try {
    mGridArea = gridArea;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void Mercator::setLatin(std::int24_t latin) {
  try {
    mLatin = latin;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void Mercator::setScanningMode(ScanningModeSettings &scanningMode) {
  try {
    mScanningMode = scanningMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void Mercator::setDiInMetres(std::int24_t diInMetres) {
  try {
    mDiInMetres = diInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void Mercator::setDjInMetres(std::int24_t djInMetres) {
  try {
    mDjInMetres = djInMetres;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
