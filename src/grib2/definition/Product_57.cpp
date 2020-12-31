// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'Product_57Impl.*' files.
// ***********************************************************************

#include "Product_57.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

Product_57::Product_57() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

Product_57::~Product_57() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Product_57::read(MemoryReader &memoryReader) {
  try {
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void Product_57::write(DataWriter &dataWriter) {
  try {
    mPointInTime.write(dataWriter);
    mHorizontal.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Product_57::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sProduct_57.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sProduct_57.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void Product_57::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "Product_57\n";
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Product_57::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mPointInTime.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint Product_57::getTemplateNumber() const {
  return 57;
}

ProductDefinition *Product_57::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new Product_57(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *Product_57::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *Product_57::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Product_57::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Product_57::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
