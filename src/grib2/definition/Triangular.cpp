// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TriangularImpl.*' files.
// ***********************************************************************

#include "Triangular.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

Triangular::Triangular() {
  try {
    mNumberingOrderOfDiamonds = 0;
    mScanningModeForOneDiamond = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

Triangular::~Triangular() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Triangular::read(MemoryReader &memoryReader) {
  try {
    mN2 = memoryReader.read_UInt8_opt();
    mN3 = memoryReader.read_UInt8_opt();
    mNi = memoryReader.read_UInt16_opt();
    mNd = memoryReader.read_UInt8_opt();
    mLatitudeOfThePolePoint = memoryReader.read_Int32_opt();
    mLongitudeOfThePolePoint = memoryReader.read_UInt32_opt();
    mLongitudeOfFirstDiamondCenterLine = memoryReader.read_UInt32_opt();
    mGridPointPosition = memoryReader.read_UInt8_opt();
    mNumberingOrderOfDiamonds = memoryReader.read_uint8();
    mScanningModeForOneDiamond = memoryReader.read_uint8();
    mTotalNumberOfGridPoints = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void Triangular::write(DataWriter &dataWriter) {
  try {
    dataWriter << mN2;
    dataWriter << mN3;
    dataWriter << mNi;
    dataWriter << mNd;
    dataWriter << mLatitudeOfThePolePoint;
    dataWriter << mLongitudeOfThePolePoint;
    dataWriter << mLongitudeOfFirstDiamondCenterLine;
    dataWriter << mGridPointPosition;
    dataWriter << mNumberingOrderOfDiamonds;
    dataWriter << mScanningModeForOneDiamond;
    dataWriter << mTotalNumberOfGridPoints;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Triangular::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTriangular.N2", prefix.c_str());
    attributeList.addAttribute(name, toString(mN2));
    sprintf(name, "%sTriangular.N3", prefix.c_str());
    attributeList.addAttribute(name, toString(mN3));
    sprintf(name, "%sTriangular.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sTriangular.Nd", prefix.c_str());
    attributeList.addAttribute(name, toString(mNd));
    sprintf(name, "%sTriangular.LatitudeOfThePolePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfThePolePoint));
    sprintf(name, "%sTriangular.LongitudeOfThePolePoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfThePolePoint));
    sprintf(name, "%sTriangular.LongitudeOfFirstDiamondCenterLine", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstDiamondCenterLine));
    sprintf(name, "%sTriangular.GridPointPosition", prefix.c_str());
    attributeList.addAttribute(name, toString(mGridPointPosition));
    sprintf(name, "%sTriangular.NumberingOrderOfDiamonds", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberingOrderOfDiamonds));
    sprintf(name, "%sTriangular.ScanningModeForOneDiamond", prefix.c_str());
    attributeList.addAttribute(name, toString(mScanningModeForOneDiamond));
    sprintf(name, "%sTriangular.TotalNumberOfGridPoints", prefix.c_str());
    attributeList.addAttribute(name, toString(mTotalNumberOfGridPoints));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void Triangular::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "Triangular\n";
    stream << space(level) << "- N2 = " << toString(mN2) << "\n";
    stream << space(level) << "- N3 = " << toString(mN3) << "\n";
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nd = " << toString(mNd) << "\n";
    stream << space(level) << "- LatitudeOfThePolePoint = " << toString(mLatitudeOfThePolePoint) << "\n";
    stream << space(level) << "- LongitudeOfThePolePoint = " << toString(mLongitudeOfThePolePoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstDiamondCenterLine = " << toString(mLongitudeOfFirstDiamondCenterLine) << "\n";
    stream << space(level) << "- GridPointPosition = " << toString(mGridPointPosition) << "\n";
    stream << space(level) << "- NumberingOrderOfDiamonds = " << toString(mNumberingOrderOfDiamonds) << "\n";
    stream << space(level) << "- ScanningModeForOneDiamond = " << toString(mScanningModeForOneDiamond) << "\n";
    stream << space(level) << "- TotalNumberOfGridPoints = " << toString(mTotalNumberOfGridPoints) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Triangular::countHash() {
  try {
    std::size_t seed = 0;
    if (mN2)
      boost::hash_combine(seed, *mN2);
    if (mN3)
      boost::hash_combine(seed, *mN3);
    if (mNi)
      boost::hash_combine(seed, *mNi);
    if (mNd)
      boost::hash_combine(seed, *mNd);
    if (mLatitudeOfThePolePoint)
      boost::hash_combine(seed, *mLatitudeOfThePolePoint);
    if (mLongitudeOfThePolePoint)
      boost::hash_combine(seed, *mLongitudeOfThePolePoint);
    if (mLongitudeOfFirstDiamondCenterLine)
      boost::hash_combine(seed, *mLongitudeOfFirstDiamondCenterLine);
    if (mGridPointPosition)
      boost::hash_combine(seed, *mGridPointPosition);
    boost::hash_combine(seed, mNumberingOrderOfDiamonds);
    boost::hash_combine(seed, mScanningModeForOneDiamond);
    if (mTotalNumberOfGridPoints)
      boost::hash_combine(seed, *mTotalNumberOfGridPoints);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint Triangular::getTemplateNumber() const {
  return 100;
}

GridDefinition *Triangular::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new Triangular(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mN2} attribute. */

const T::UInt8_opt &Triangular::getN2() const {
  try {
    return mN2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mN3} attribute. */

const T::UInt8_opt &Triangular::getN3() const {
  try {
    return mN3;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

const T::UInt16_opt &Triangular::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNd} attribute. */

const T::UInt8_opt &Triangular::getNd() const {
  try {
    return mNd;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfThePolePoint} attribute. */

const T::Int32_opt &Triangular::getLatitudeOfThePolePoint() const {
  try {
    return mLatitudeOfThePolePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfThePolePoint} attribute. */

const T::UInt32_opt &Triangular::getLongitudeOfThePolePoint() const {
  try {
    return mLongitudeOfThePolePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstDiamondCenterLine} attribute. */

const T::UInt32_opt &Triangular::getLongitudeOfFirstDiamondCenterLine() const {
  try {
    return mLongitudeOfFirstDiamondCenterLine;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mGridPointPosition} attribute. */

const T::UInt8_opt &Triangular::getGridPointPosition() const {
  try {
    return mGridPointPosition;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberingOrderOfDiamonds} attribute. */

std::uint8_t Triangular::getNumberingOrderOfDiamonds() const {
  try {
    return mNumberingOrderOfDiamonds;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScanningModeForOneDiamond} attribute. */

std::uint8_t Triangular::getScanningModeForOneDiamond() const {
  try {
    return mScanningModeForOneDiamond;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTotalNumberOfGridPoints} attribute. */

const T::UInt32_opt &Triangular::getTotalNumberOfGridPoints() const {
  try {
    return mTotalNumberOfGridPoints;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setN2(T::UInt8_opt n2) {
  try {
    mN2 = n2;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setN3(T::UInt8_opt n3) {
  try {
    mN3 = n3;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setNi(T::UInt16_opt ni) {
  try {
    mNi = ni;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setNd(T::UInt8_opt nd) {
  try {
    mNd = nd;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setLatitudeOfThePolePoint(T::Int32_opt latitudeOfThePolePoint) {
  try {
    mLatitudeOfThePolePoint = latitudeOfThePolePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setLongitudeOfThePolePoint(T::UInt32_opt longitudeOfThePolePoint) {
  try {
    mLongitudeOfThePolePoint = longitudeOfThePolePoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setLongitudeOfFirstDiamondCenterLine(T::UInt32_opt longitudeOfFirstDiamondCenterLine) {
  try {
    mLongitudeOfFirstDiamondCenterLine = longitudeOfFirstDiamondCenterLine;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setGridPointPosition(T::UInt8_opt gridPointPosition) {
  try {
    mGridPointPosition = gridPointPosition;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setNumberingOrderOfDiamonds(std::uint8_t numberingOrderOfDiamonds) {
  try {
    mNumberingOrderOfDiamonds = numberingOrderOfDiamonds;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setScanningModeForOneDiamond(std::uint8_t scanningModeForOneDiamond) {
  try {
    mScanningModeForOneDiamond = scanningModeForOneDiamond;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Triangular::setTotalNumberOfGridPoints(T::UInt32_opt totalNumberOfGridPoints) {
  try {
    mTotalNumberOfGridPoints = totalNumberOfGridPoints;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
