// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'MatrixDataRepresentationImpl.*' files.
// ***********************************************************************

#include "grib2/definition/MatrixDataRepresentation.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

MatrixDataRepresentation::MatrixDataRepresentation() {
  try {
    mCoefsFirst = 0;
    mCoefsSecond = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

MatrixDataRepresentation::~MatrixDataRepresentation() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void MatrixDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mMatrixBitmapsPresent = memoryReader.read_UInt8_opt();
    mNumberOfCodedValues = memoryReader.read_UInt32_opt();
    mFirstDimension = memoryReader.read_UInt16_opt();
    mSecondDimension = memoryReader.read_UInt16_opt();
    mFirstDimensionCoordinateValueDefinition = memoryReader.read_UInt8_opt();
    mNC1 = memoryReader.read_UInt8_opt();
    mSecondDimensionCoordinateValueDefinition = memoryReader.read_UInt8_opt();
    mNC2 = memoryReader.read_UInt8_opt();
    mFirstDimensionPhysicalSignificance = memoryReader.read_UInt8_opt();
    mSecondDimensionPhysicalSignificance = memoryReader.read_UInt8_opt();
    mCoefsFirst = memoryReader.read_float();
    mCoefsSecond = memoryReader.read_float();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void MatrixDataRepresentation::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sMatrixDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sMatrixDataRepresentation.MatrixBitmapsPresent", prefix.c_str());
    attributeList.addAttribute(name, toString(mMatrixBitmapsPresent));
    sprintf(name, "%sMatrixDataRepresentation.NumberOfCodedValues", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfCodedValues));
    sprintf(name, "%sMatrixDataRepresentation.FirstDimension", prefix.c_str());
    attributeList.addAttribute(name, toString(mFirstDimension));
    sprintf(name, "%sMatrixDataRepresentation.SecondDimension", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecondDimension));
    sprintf(name, "%sMatrixDataRepresentation.FirstDimensionCoordinateValueDefinition", prefix.c_str());
    attributeList.addAttribute(name, toString(mFirstDimensionCoordinateValueDefinition));
    sprintf(name, "%sMatrixDataRepresentation.NC1", prefix.c_str());
    attributeList.addAttribute(name, toString(mNC1));
    sprintf(name, "%sMatrixDataRepresentation.SecondDimensionCoordinateValueDefinition", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecondDimensionCoordinateValueDefinition));
    sprintf(name, "%sMatrixDataRepresentation.NC2", prefix.c_str());
    attributeList.addAttribute(name, toString(mNC2));
    sprintf(name, "%sMatrixDataRepresentation.FirstDimensionPhysicalSignificance", prefix.c_str());
    attributeList.addAttribute(name, toString(mFirstDimensionPhysicalSignificance));
    sprintf(name, "%sMatrixDataRepresentation.SecondDimensionPhysicalSignificance", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecondDimensionPhysicalSignificance));
    sprintf(name, "%sMatrixDataRepresentation.CoefsFirst", prefix.c_str());
    attributeList.addAttribute(name, toString(mCoefsFirst));
    sprintf(name, "%sMatrixDataRepresentation.CoefsSecond", prefix.c_str());
    attributeList.addAttribute(name, toString(mCoefsSecond));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void MatrixDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "MatrixDataRepresentation\n";
    mPacking.print(stream, level + 1, optionFlags);
    stream << space(level) << "- MatrixBitmapsPresent = " << toString(mMatrixBitmapsPresent) << "\n";
    stream << space(level) << "- NumberOfCodedValues = " << toString(mNumberOfCodedValues) << "\n";
    stream << space(level) << "- FirstDimension = " << toString(mFirstDimension) << "\n";
    stream << space(level) << "- SecondDimension = " << toString(mSecondDimension) << "\n";
    stream << space(level) << "- FirstDimensionCoordinateValueDefinition = " << toString(mFirstDimensionCoordinateValueDefinition) << "\n";
    stream << space(level) << "- NC1 = " << toString(mNC1) << "\n";
    stream << space(level) << "- SecondDimensionCoordinateValueDefinition = " << toString(mSecondDimensionCoordinateValueDefinition) << "\n";
    stream << space(level) << "- NC2 = " << toString(mNC2) << "\n";
    stream << space(level) << "- FirstDimensionPhysicalSignificance = " << toString(mFirstDimensionPhysicalSignificance) << "\n";
    stream << space(level) << "- SecondDimensionPhysicalSignificance = " << toString(mSecondDimensionPhysicalSignificance) << "\n";
    stream << space(level) << "- CoefsFirst = " << toString(mCoefsFirst) << "\n";
    stream << space(level) << "- CoefsSecond = " << toString(mCoefsSecond) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash MatrixDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    if (mMatrixBitmapsPresent)
      boost::hash_combine(seed, *mMatrixBitmapsPresent);
    if (mNumberOfCodedValues)
      boost::hash_combine(seed, *mNumberOfCodedValues);
    if (mFirstDimension)
      boost::hash_combine(seed, *mFirstDimension);
    if (mSecondDimension)
      boost::hash_combine(seed, *mSecondDimension);
    if (mFirstDimensionCoordinateValueDefinition)
      boost::hash_combine(seed, *mFirstDimensionCoordinateValueDefinition);
    if (mNC1)
      boost::hash_combine(seed, *mNC1);
    if (mSecondDimensionCoordinateValueDefinition)
      boost::hash_combine(seed, *mSecondDimensionCoordinateValueDefinition);
    if (mNC2)
      boost::hash_combine(seed, *mNC2);
    if (mFirstDimensionPhysicalSignificance)
      boost::hash_combine(seed, *mFirstDimensionPhysicalSignificance);
    if (mSecondDimensionPhysicalSignificance)
      boost::hash_combine(seed, *mSecondDimensionPhysicalSignificance);
    boost::hash_combine(seed, mCoefsFirst);
    boost::hash_combine(seed, mCoefsSecond);
    boost::hash_combine(seed, mPacking.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

const PackingSettings *MatrixDataRepresentation::getPacking() const {
  try {
    return &mPacking;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mMatrixBitmapsPresent} attribute. */

const T::UInt8_opt &MatrixDataRepresentation::getMatrixBitmapsPresent() const {
  try {
    return mMatrixBitmapsPresent;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfCodedValues} attribute. */

const T::UInt32_opt &MatrixDataRepresentation::getNumberOfCodedValues() const {
  try {
    return mNumberOfCodedValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mFirstDimension} attribute. */

const T::UInt16_opt &MatrixDataRepresentation::getFirstDimension() const {
  try {
    return mFirstDimension;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSecondDimension} attribute. */

const T::UInt16_opt &MatrixDataRepresentation::getSecondDimension() const {
  try {
    return mSecondDimension;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mFirstDimensionCoordinateValueDefinition} attribute. */

const T::UInt8_opt &MatrixDataRepresentation::getFirstDimensionCoordinateValueDefinition() const {
  try {
    return mFirstDimensionCoordinateValueDefinition;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNC1} attribute. */

const T::UInt8_opt &MatrixDataRepresentation::getNC1() const {
  try {
    return mNC1;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSecondDimensionCoordinateValueDefinition} attribute. */

const T::UInt8_opt &MatrixDataRepresentation::getSecondDimensionCoordinateValueDefinition() const {
  try {
    return mSecondDimensionCoordinateValueDefinition;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mNC2} attribute. */

const T::UInt8_opt &MatrixDataRepresentation::getNC2() const {
  try {
    return mNC2;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mFirstDimensionPhysicalSignificance} attribute. */

const T::UInt8_opt &MatrixDataRepresentation::getFirstDimensionPhysicalSignificance() const {
  try {
    return mFirstDimensionPhysicalSignificance;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mSecondDimensionPhysicalSignificance} attribute. */

const T::UInt8_opt &MatrixDataRepresentation::getSecondDimensionPhysicalSignificance() const {
  try {
    return mSecondDimensionPhysicalSignificance;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mCoefsFirst} attribute. */

float MatrixDataRepresentation::getCoefsFirst() const {
  try {
    return mCoefsFirst;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mCoefsSecond} attribute. */

float MatrixDataRepresentation::getCoefsSecond() const {
  try {
    return mCoefsSecond;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setPacking(PackingSettings packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setMatrixBitmapsPresent(T::UInt8_opt matrixBitmapsPresent) {
  try {
    mMatrixBitmapsPresent = matrixBitmapsPresent;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setNumberOfCodedValues(T::UInt32_opt numberOfCodedValues) {
  try {
    mNumberOfCodedValues = numberOfCodedValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setFirstDimension(T::UInt16_opt firstDimension) {
  try {
    mFirstDimension = firstDimension;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setSecondDimension(T::UInt16_opt secondDimension) {
  try {
    mSecondDimension = secondDimension;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setFirstDimensionCoordinateValueDefinition(T::UInt8_opt firstDimensionCoordinateValueDefinition) {
  try {
    mFirstDimensionCoordinateValueDefinition = firstDimensionCoordinateValueDefinition;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setNC1(T::UInt8_opt nC1) {
  try {
    mNC1 = nC1;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setSecondDimensionCoordinateValueDefinition(T::UInt8_opt secondDimensionCoordinateValueDefinition) {
  try {
    mSecondDimensionCoordinateValueDefinition = secondDimensionCoordinateValueDefinition;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setNC2(T::UInt8_opt nC2) {
  try {
    mNC2 = nC2;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setFirstDimensionPhysicalSignificance(T::UInt8_opt firstDimensionPhysicalSignificance) {
  try {
    mFirstDimensionPhysicalSignificance = firstDimensionPhysicalSignificance;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setSecondDimensionPhysicalSignificance(T::UInt8_opt secondDimensionPhysicalSignificance) {
  try {
    mSecondDimensionPhysicalSignificance = secondDimensionPhysicalSignificance;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setCoefsFirst(float coefsFirst) {
  try {
    mCoefsFirst = coefsFirst;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

void MatrixDataRepresentation::setCoefsSecond(float coefsSecond) {
  try {
    mCoefsSecond = coefsSecond;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
