// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'FloatingPointGridDataImpl.*' files.
// ***********************************************************************

#include "FloatingPointGridData.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

FloatingPointGridData::FloatingPointGridData() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

FloatingPointGridData::~FloatingPointGridData() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void FloatingPointGridData::read(MemoryReader &memoryReader) {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void FloatingPointGridData::write(DataWriter &dataWriter) {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void FloatingPointGridData::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool FloatingPointGridData::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool FloatingPointGridData::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void FloatingPointGridData::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "FloatingPointGridData\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash FloatingPointGridData::countHash() const {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint FloatingPointGridData::getTemplateNumber() const {
  return 4;
}

DataDefinition *FloatingPointGridData::createDataDefinition() const {
  try {
    return static_cast<DataDefinition *>(new FloatingPointGridData(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
