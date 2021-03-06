// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'LogarithmicGridDataRepresentationImpl.*' files.
// ***********************************************************************

#include "LogarithmicGridDataRepresentation.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

LogarithmicGridDataRepresentation::LogarithmicGridDataRepresentation() {
  try {
    mPreProcessingParameter = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

LogarithmicGridDataRepresentation::~LogarithmicGridDataRepresentation() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void LogarithmicGridDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mPreProcessingParameter = memoryReader.read_float();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void LogarithmicGridDataRepresentation::write(DataWriter &dataWriter) {
  try {
    mPacking.write(dataWriter);
    dataWriter << mPreProcessingParameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void LogarithmicGridDataRepresentation::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sLogarithmicGridDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sLogarithmicGridDataRepresentation.PreProcessingParameter", prefix.c_str());
    attributeList.addAttribute(name, toString(mPreProcessingParameter));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void LogarithmicGridDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "LogarithmicGridDataRepresentation\n";
    mPacking.print(stream, level + 1, optionFlags);
    stream << space(level) << "- PreProcessingParameter = " << toString(mPreProcessingParameter) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash LogarithmicGridDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mPreProcessingParameter);
    boost::hash_combine(seed, mPacking.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint LogarithmicGridDataRepresentation::getTemplateNumber() const {
  return 61;
}

RepresentationDefinition *LogarithmicGridDataRepresentation::createRepresentationDefinition() const {
  try {
    return static_cast<RepresentationDefinition *>(new LogarithmicGridDataRepresentation(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

PackingSettings *LogarithmicGridDataRepresentation::getPacking() const {
  try {
    return static_cast<PackingSettings *>(&mPacking);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPreProcessingParameter} attribute. */

float LogarithmicGridDataRepresentation::getPreProcessingParameter() const {
  try {
    return mPreProcessingParameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LogarithmicGridDataRepresentation::setPacking(PackingSettings &packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void LogarithmicGridDataRepresentation::setPreProcessingParameter(float preProcessingParameter) {
  try {
    mPreProcessingParameter = preProcessingParameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
