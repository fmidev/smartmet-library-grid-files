// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'HovmollerProductImpl.*' files.
// ***********************************************************************

#include "HovmollerProduct.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

HovmollerProduct::HovmollerProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

HovmollerProduct::HovmollerProduct(const HovmollerProduct &other) : ProductDefinition(other) {
  try {
    mParameter = other.mParameter;
    mHorizontal = other.mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

HovmollerProduct::~HovmollerProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void HovmollerProduct::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mHorizontal.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void HovmollerProduct::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mHorizontal.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void HovmollerProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sHovmollerProduct.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sHovmollerProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void HovmollerProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "HovmollerProduct\n";
    mParameter.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash HovmollerProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint HovmollerProduct::getTemplateNumber() const {
  return 1100;
}

ProductDefinition *HovmollerProduct::createProductDefinition() const {
  try {
    return (ProductDefinition *)new HovmollerProduct(*this);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *HovmollerProduct::getParameter() const {
  try {
    return (ParameterSettings *)&mParameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *HovmollerProduct::getHorizontal() const {
  try {
    return (HorizontalSettings *)&mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void HovmollerProduct::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void HovmollerProduct::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
