// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'NormalProductImpl.*' files.
// ***********************************************************************

#include "NormalProduct.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

NormalProduct::NormalProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The copy constructor of the class. */

NormalProduct::NormalProduct(const NormalProduct &other) : ProductDefinition(other) {
  try {
    mParameter = other.mParameter;
    mPointInTime = other.mPointInTime;
    mHorizontal = other.mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

NormalProduct::~NormalProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void NormalProduct::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void NormalProduct::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mPointInTime.write(dataWriter);
    mHorizontal.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void NormalProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sNormalProduct.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sNormalProduct.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sNormalProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void NormalProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "NormalProduct\n";
    mParameter.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash NormalProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mPointInTime.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method return the template number of the current class. */

uint NormalProduct::getTemplateNumber() const {
  return 0;
}

ProductDefinition *NormalProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new NormalProduct(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *NormalProduct::getParameter() const {
  try {
    return static_cast<ParameterSettings *>(&mParameter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *NormalProduct::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *NormalProduct::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void NormalProduct::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void NormalProduct::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void NormalProduct::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
