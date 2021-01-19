// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'Product_68Impl.*' files.
// ***********************************************************************

#include "Product_68.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

Product_68::Product_68() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

Product_68::~Product_68() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Product_68::read(MemoryReader &memoryReader) {
  try {
    mHorizontal.read(memoryReader);
    mEps.read(memoryReader);
    mStatistical.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void Product_68::write(DataWriter &dataWriter) {
  try {
    mHorizontal.write(dataWriter);
    mEps.write(dataWriter);
    mStatistical.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Product_68::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sProduct_68.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sProduct_68.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
    sprintf(name, "%sProduct_68.", prefix.c_str());
    mStatistical.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void Product_68::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "Product_68\n";
    mHorizontal.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Product_68::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mEps.countHash());
    boost::hash_combine(seed, mStatistical.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint Product_68::getTemplateNumber() const {
  return 68;
}

ProductDefinition *Product_68::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new Product_68(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *Product_68::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

EpsSettings *Product_68::getEps() const {
  try {
    return static_cast<EpsSettings *>(&mEps);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

StatisticalSettings *Product_68::getStatistical() const {
  try {
    return static_cast<StatisticalSettings *>(&mStatistical);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Product_68::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Product_68::setEps(EpsSettings &eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void Product_68::setStatistical(StatisticalSettings &statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
