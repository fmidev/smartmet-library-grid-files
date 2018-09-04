// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CrossSectionProductImpl.*' files.
// ***********************************************************************

#include "CrossSectionProduct.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

CrossSectionProduct::CrossSectionProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The copy constructor of the class. */

CrossSectionProduct::CrossSectionProduct(const CrossSectionProduct &other) : ProductDefinition(other) {
  try {
    mParameter = other.mParameter;
    mPointInTime = other.mPointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

CrossSectionProduct::~CrossSectionProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void CrossSectionProduct::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mPointInTime.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void CrossSectionProduct::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mPointInTime.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void CrossSectionProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sCrossSectionProduct.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sCrossSectionProduct.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void CrossSectionProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "CrossSectionProduct\n";
    mParameter.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash CrossSectionProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mPointInTime.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method return the template number of the current class. */

uint CrossSectionProduct::getTemplateNumber() const {
  return 1000;
}

ProductDefinition *CrossSectionProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new CrossSectionProduct(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *CrossSectionProduct::getParameter() const {
  try {
    return static_cast<ParameterSettings *>(&mParameter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *CrossSectionProduct::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void CrossSectionProduct::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void CrossSectionProduct::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
