// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CharacterStringProductImpl.*' files.
// ***********************************************************************

#include "CharacterStringProduct.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

CharacterStringProduct::CharacterStringProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The copy constructor of the class. */

CharacterStringProduct::CharacterStringProduct(const CharacterStringProduct &other) : ProductDefinition(other) {
  try {
    mParameterCategory = other.mParameterCategory;
    mParameterNumber = other.mParameterNumber;
    mNumberOfCharacters = other.mNumberOfCharacters;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

CharacterStringProduct::~CharacterStringProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void CharacterStringProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterCategory = memoryReader.read_UInt8_opt();
    mParameterNumber = memoryReader.read_UInt8_opt();
    mNumberOfCharacters = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void CharacterStringProduct::write(DataWriter &dataWriter) {
  try {
    dataWriter << mParameterCategory;
    dataWriter << mParameterNumber;
    dataWriter << mNumberOfCharacters;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void CharacterStringProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sCharacterStringProduct.ParameterCategory", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterCategory));
    sprintf(name, "%sCharacterStringProduct.ParameterNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterNumber));
    sprintf(name, "%sCharacterStringProduct.NumberOfCharacters", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfCharacters));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void CharacterStringProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "CharacterStringProduct\n";
    stream << space(level) << "- ParameterCategory = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- ParameterNumber = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- NumberOfCharacters = " << toString(mNumberOfCharacters) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash CharacterStringProduct::countHash() {
  try {
    std::size_t seed = 0;
    if (mParameterCategory)
      boost::hash_combine(seed, *mParameterCategory);
    if (mParameterNumber)
      boost::hash_combine(seed, *mParameterNumber);
    if (mNumberOfCharacters)
      boost::hash_combine(seed, *mNumberOfCharacters);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method return the template number of the current class. */

uint CharacterStringProduct::getTemplateNumber() const {
  return 254;
}

ProductDefinition *CharacterStringProduct::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new CharacterStringProduct(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mParameterCategory} attribute. */

const T::UInt8_opt &CharacterStringProduct::getParameterCategory() const {
  try {
    return mParameterCategory;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mParameterNumber} attribute. */

const T::UInt8_opt &CharacterStringProduct::getParameterNumber() const {
  try {
    return mParameterNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfCharacters} attribute. */

const T::UInt32_opt &CharacterStringProduct::getNumberOfCharacters() const {
  try {
    return mNumberOfCharacters;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void CharacterStringProduct::setParameterCategory(T::UInt8_opt parameterCategory) {
  try {
    mParameterCategory = parameterCategory;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void CharacterStringProduct::setParameterNumber(T::UInt8_opt parameterNumber) {
  try {
    mParameterNumber = parameterNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void CharacterStringProduct::setNumberOfCharacters(T::UInt32_opt numberOfCharacters) {
  try {
    mNumberOfCharacters = numberOfCharacters;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
