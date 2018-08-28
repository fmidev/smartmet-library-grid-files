// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SpectralGridDataRepresentationImpl.*' files.
// ***********************************************************************

#include "SpectralGridDataRepresentation.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SpectralGridDataRepresentation::SpectralGridDataRepresentation() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

SpectralGridDataRepresentation::SpectralGridDataRepresentation(const SpectralGridDataRepresentation &other) : RepresentationDefinition(other) {
  try {
    mPacking = other.mPacking;
    mOriginalValues = other.mOriginalValues;
    mCcsdsFlags = other.mCcsdsFlags;
    mCcsdsBlockSize = other.mCcsdsBlockSize;
    mCcsdsRsi = other.mCcsdsRsi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

SpectralGridDataRepresentation::~SpectralGridDataRepresentation() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SpectralGridDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mOriginalValues.read(memoryReader);
    mCcsdsFlags = memoryReader.read_UInt8_opt();
    mCcsdsBlockSize = memoryReader.read_UInt8_opt();
    mCcsdsRsi = memoryReader.read_UInt16_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void SpectralGridDataRepresentation::write(DataWriter &dataWriter) {
  try {
    mPacking.write(dataWriter);
    mOriginalValues.write(dataWriter);
    dataWriter << mCcsdsFlags;
    dataWriter << mCcsdsBlockSize;
    dataWriter << mCcsdsRsi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SpectralGridDataRepresentation::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSpectralGridDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sSpectralGridDataRepresentation.", prefix.c_str());
    mOriginalValues.getAttributeList(name, attributeList);
    sprintf(name, "%sSpectralGridDataRepresentation.CcsdsFlags", prefix.c_str());
    attributeList.addAttribute(name, toString(mCcsdsFlags));
    sprintf(name, "%sSpectralGridDataRepresentation.CcsdsBlockSize", prefix.c_str());
    attributeList.addAttribute(name, toString(mCcsdsBlockSize));
    sprintf(name, "%sSpectralGridDataRepresentation.CcsdsRsi", prefix.c_str());
    attributeList.addAttribute(name, toString(mCcsdsRsi));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SpectralGridDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SpectralGridDataRepresentation\n";
    mPacking.print(stream, level + 1, optionFlags);
    mOriginalValues.print(stream, level + 1, optionFlags);
    stream << space(level) << "- CcsdsFlags = " << toString(mCcsdsFlags) << "\n";
    stream << space(level) << "- CcsdsBlockSize = " << toString(mCcsdsBlockSize) << "\n";
    stream << space(level) << "- CcsdsRsi = " << toString(mCcsdsRsi) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SpectralGridDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    if (mCcsdsFlags)
      boost::hash_combine(seed, *mCcsdsFlags);
    if (mCcsdsBlockSize)
      boost::hash_combine(seed, *mCcsdsBlockSize);
    if (mCcsdsRsi)
      boost::hash_combine(seed, *mCcsdsRsi);
    boost::hash_combine(seed, mPacking.countHash());
    boost::hash_combine(seed, mOriginalValues.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint SpectralGridDataRepresentation::getTemplateNumber() const {
  return 42;
}

RepresentationDefinition *SpectralGridDataRepresentation::createRepresentationDefinition() const {
  try {
    return (RepresentationDefinition *)new SpectralGridDataRepresentation(*this);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

PackingSettings *SpectralGridDataRepresentation::getPacking() const {
  try {
    return (PackingSettings *)&mPacking;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mOriginalValues} attribute. */

OriginalValuesSettings *SpectralGridDataRepresentation::getOriginalValues() const {
  try {
    return (OriginalValuesSettings *)&mOriginalValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mCcsdsFlags} attribute. */

const T::UInt8_opt &SpectralGridDataRepresentation::getCcsdsFlags() const {
  try {
    return mCcsdsFlags;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mCcsdsBlockSize} attribute. */

const T::UInt8_opt &SpectralGridDataRepresentation::getCcsdsBlockSize() const {
  try {
    return mCcsdsBlockSize;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mCcsdsRsi} attribute. */

const T::UInt16_opt &SpectralGridDataRepresentation::getCcsdsRsi() const {
  try {
    return mCcsdsRsi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpectralGridDataRepresentation::setPacking(PackingSettings &packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpectralGridDataRepresentation::setOriginalValues(OriginalValuesSettings &originalValues) {
  try {
    mOriginalValues = originalValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpectralGridDataRepresentation::setCcsdsFlags(T::UInt8_opt ccsdsFlags) {
  try {
    mCcsdsFlags = ccsdsFlags;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpectralGridDataRepresentation::setCcsdsBlockSize(T::UInt8_opt ccsdsBlockSize) {
  try {
    mCcsdsBlockSize = ccsdsBlockSize;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void SpectralGridDataRepresentation::setCcsdsRsi(T::UInt16_opt ccsdsRsi) {
  try {
    mCcsdsRsi = ccsdsRsi;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
