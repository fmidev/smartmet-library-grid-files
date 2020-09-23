// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ComplexSphericalHarmonicsDataImpl.*' files.
// ***********************************************************************

#include "ComplexSphericalHarmonicsData.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

ComplexSphericalHarmonicsData::ComplexSphericalHarmonicsData() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

ComplexSphericalHarmonicsData::ComplexSphericalHarmonicsData(const ComplexSphericalHarmonicsData &other) : DataDefinition(other) {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

ComplexSphericalHarmonicsData::~ComplexSphericalHarmonicsData() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ComplexSphericalHarmonicsData::read(MemoryReader &memoryReader) {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void ComplexSphericalHarmonicsData::write(DataWriter &dataWriter) {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ComplexSphericalHarmonicsData::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ComplexSphericalHarmonicsData::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ComplexSphericalHarmonicsData\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ComplexSphericalHarmonicsData::countHash() {
  try {
    std::size_t seed = 0;
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint ComplexSphericalHarmonicsData::getTemplateNumber() const {
  return 50000;
}

DataDefinition *ComplexSphericalHarmonicsData::createDataDefinition() const {
  try {
    return static_cast<DataDefinition *>(new ComplexSphericalHarmonicsData(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
