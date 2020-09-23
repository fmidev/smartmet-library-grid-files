// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'UnstructuredImpl.*' files.
// ***********************************************************************

#include "Unstructured.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

Unstructured::Unstructured() {
  try {
    mUuidOfHGrid = {0};
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

Unstructured::Unstructured(const Unstructured &other) : GridDefinition(other) {
  try {
    mShapeOfTheEarth = other.mShapeOfTheEarth;
    mNumberOfGridUsed = other.mNumberOfGridUsed;
    mNumberOfGridInReference = other.mNumberOfGridInReference;
    mUuidOfHGrid = other.mUuidOfHGrid;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

Unstructured::~Unstructured() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Unstructured::read(MemoryReader &memoryReader) {
  try {
    mShapeOfTheEarth = memoryReader.read_UInt8_opt();
    mNumberOfGridUsed = memoryReader.read_UInt24_opt();
    mNumberOfGridInReference = memoryReader.read_UInt8_opt();
    mUuidOfHGrid = memoryReader.read_uuid();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void Unstructured::write(DataWriter &dataWriter) {
  try {
    dataWriter << mShapeOfTheEarth;
    dataWriter << mNumberOfGridUsed;
    dataWriter << mNumberOfGridInReference;
    dataWriter << mUuidOfHGrid;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Unstructured::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sUnstructured.ShapeOfTheEarth", prefix.c_str());
    attributeList.addAttribute(name, toString(mShapeOfTheEarth));
    sprintf(name, "%sUnstructured.NumberOfGridUsed", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfGridUsed));
    sprintf(name, "%sUnstructured.NumberOfGridInReference", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfGridInReference));
    sprintf(name, "%sUnstructured.UuidOfHGrid", prefix.c_str());
    attributeList.addAttribute(name, toString(mUuidOfHGrid));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void Unstructured::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "Unstructured\n";
    stream << space(level) << "- ShapeOfTheEarth = " << toString(mShapeOfTheEarth) << "\n";
    stream << space(level) << "- NumberOfGridUsed = " << toString(mNumberOfGridUsed) << "\n";
    stream << space(level) << "- NumberOfGridInReference = " << toString(mNumberOfGridInReference) << "\n";
    stream << space(level) << "- UuidOfHGrid = " << toString(mUuidOfHGrid) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Unstructured::countHash() {
  try {
    std::size_t seed = 0;
    if (mShapeOfTheEarth)
      boost::hash_combine(seed, *mShapeOfTheEarth);
    if (mNumberOfGridUsed)
      boost::hash_combine(seed, *mNumberOfGridUsed);
    if (mNumberOfGridInReference)
      boost::hash_combine(seed, *mNumberOfGridInReference);
    boost::hash_combine(seed, mUuidOfHGrid);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint Unstructured::getTemplateNumber() const {
  return 101;
}

GridDefinition *Unstructured::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new Unstructured(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mShapeOfTheEarth} attribute. */

const T::UInt8_opt &Unstructured::getShapeOfTheEarth() const {
  try {
    return mShapeOfTheEarth;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfGridUsed} attribute. */

const T::UInt24_opt &Unstructured::getNumberOfGridUsed() const {
  try {
    return mNumberOfGridUsed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfGridInReference} attribute. */

const T::UInt8_opt &Unstructured::getNumberOfGridInReference() const {
  try {
    return mNumberOfGridInReference;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mUuidOfHGrid} attribute. */

const std::array<char, 16> &Unstructured::getUuidOfHGrid() const {
  try {
    return mUuidOfHGrid;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void Unstructured::setShapeOfTheEarth(T::UInt8_opt shapeOfTheEarth) {
  try {
    mShapeOfTheEarth = shapeOfTheEarth;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void Unstructured::setNumberOfGridUsed(T::UInt24_opt numberOfGridUsed) {
  try {
    mNumberOfGridUsed = numberOfGridUsed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void Unstructured::setNumberOfGridInReference(T::UInt8_opt numberOfGridInReference) {
  try {
    mNumberOfGridInReference = numberOfGridInReference;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void Unstructured::setUuidOfHGrid(std::array<char, 16> uuidOfHGrid) {
  try {
    mUuidOfHGrid = uuidOfHGrid;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
