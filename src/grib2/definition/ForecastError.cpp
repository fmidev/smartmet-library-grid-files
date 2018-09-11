// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ForecastErrorImpl.*' files.
// ***********************************************************************

#include "ForecastError.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

ForecastError::ForecastError() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

ForecastError::ForecastError(const ForecastError &other) : ProductDefinition(other) {
  try {
    mNormalProduct = other.mNormalProduct;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

ForecastError::~ForecastError() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ForecastError::read(MemoryReader &memoryReader) {
  try {
    mNormalProduct.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void ForecastError::write(DataWriter &dataWriter) {
  try {
    mNormalProduct.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ForecastError::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sForecastError.", prefix.c_str());
    mNormalProduct.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ForecastError::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ForecastError\n";
    mNormalProduct.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ForecastError::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mNormalProduct.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint ForecastError::getTemplateNumber() const {
  return 7;
}

ProductDefinition *ForecastError::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new ForecastError(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mNormalProduct} attribute. */

NormalProduct *ForecastError::getNormalProduct() const {
  try {
    return static_cast<NormalProduct *>(&mNormalProduct);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ForecastError::setNormalProduct(NormalProduct &normalProduct) {
  try {
    mNormalProduct = normalProduct;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
