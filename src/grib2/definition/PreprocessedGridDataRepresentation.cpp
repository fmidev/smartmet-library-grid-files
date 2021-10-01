// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PreprocessedGridDataRepresentationImpl.*' files.
// ***********************************************************************

#include "PreprocessedGridDataRepresentation.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

PreprocessedGridDataRepresentation::PreprocessedGridDataRepresentation() {
  try {
    mPreProcessingParameter = 0;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

PreprocessedGridDataRepresentation::~PreprocessedGridDataRepresentation() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void PreprocessedGridDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mTypeOfPreProcessing = memoryReader.read_UInt8_opt();
    mPreProcessingParameter = memoryReader.read_float();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void PreprocessedGridDataRepresentation::write(DataWriter &dataWriter) {
  try {
    mPacking.write(dataWriter);
    dataWriter << mTypeOfPreProcessing;
    dataWriter << mPreProcessingParameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void PreprocessedGridDataRepresentation::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sPreprocessedGridDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sPreprocessedGridDataRepresentation.TypeOfPreProcessing", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfPreProcessing));
    sprintf(name, "%sPreprocessedGridDataRepresentation.PreProcessingParameter", prefix.c_str());
    attributeList.addAttribute(name, toString(mPreProcessingParameter));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool PreprocessedGridDataRepresentation::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (mPacking.getAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "TypeOfPreProcessing") == 0) {
      attributeValue = toString(mTypeOfPreProcessing);
      return true;
    }
    if (strcasecmp(attributeName, "PreProcessingParameter") == 0) {
      attributeValue = toString(mPreProcessingParameter);
      return true;
    }
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool PreprocessedGridDataRepresentation::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (mPacking.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "TypeOfPreProcessing") == 0 && strcasecmp(attributeValue, toString(mTypeOfPreProcessing).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "PreProcessingParameter") == 0 && strcasecmp(attributeValue, toString(mPreProcessingParameter).c_str()) == 0)
      return true;
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

void PreprocessedGridDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "PreprocessedGridDataRepresentation\n";
    mPacking.print(stream, level + 1, optionFlags);
    stream << space(level) << "- TypeOfPreProcessing = " << toString(mTypeOfPreProcessing) << "\n";
    stream << space(level) << "- PreProcessingParameter = " << toString(mPreProcessingParameter) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash PreprocessedGridDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    if (mTypeOfPreProcessing)
      boost::hash_combine(seed, *mTypeOfPreProcessing);
    boost::hash_combine(seed, mPreProcessingParameter);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint PreprocessedGridDataRepresentation::getTemplateNumber() const {
  return 6;
}

RepresentationDefinition *PreprocessedGridDataRepresentation::createRepresentationDefinition() const {
  try {
    return static_cast<RepresentationDefinition *>(new PreprocessedGridDataRepresentation(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

PackingSettings *PreprocessedGridDataRepresentation::getPacking() const {
  try {
    return static_cast<PackingSettings *>(&mPacking);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfPreProcessing} attribute. */

const T::UInt8_opt &PreprocessedGridDataRepresentation::getTypeOfPreProcessing() const {
  try {
    return mTypeOfPreProcessing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPreProcessingParameter} attribute. */

float PreprocessedGridDataRepresentation::getPreProcessingParameter() const {
  try {
    return mPreProcessingParameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PreprocessedGridDataRepresentation::setPacking(PackingSettings &packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PreprocessedGridDataRepresentation::setTypeOfPreProcessing(T::UInt8_opt typeOfPreProcessing) {
  try {
    mTypeOfPreProcessing = typeOfPreProcessing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void PreprocessedGridDataRepresentation::setPreProcessingParameter(float preProcessingParameter) {
  try {
    mPreProcessingParameter = preProcessingParameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
