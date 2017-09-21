// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedSphericalHarmonicImpl.*' files.
// ***********************************************************************

#include "grib1/definition/StretchedSphericalHarmonic.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB1 {

/*! \brief The constructor of the class. */

StretchedSphericalHarmonic::StretchedSphericalHarmonic() {
  try {
    mJ = 0;
    mK = 0;
    mM = 0;
    mRepresentationType = 0;
    mRepresentationMode = 0;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

StretchedSphericalHarmonic::~StretchedSphericalHarmonic() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current section object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void StretchedSphericalHarmonic::read(MemoryReader &memoryReader) {
  try {
    mJ = memoryReader.read_uint16();
    mK = memoryReader.read_uint16();
    mM = memoryReader.read_uint16();
    mRepresentationType = memoryReader.read_uint8();
    mRepresentationMode = memoryReader.read_uint8();
    mRotation.read(memoryReader);
    mGridStretching.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void StretchedSphericalHarmonic::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sStretchedSphericalHarmonic.J", prefix.c_str());
    attributeList.addAttribute(name, toString(mJ));
    sprintf(name, "%sStretchedSphericalHarmonic.K", prefix.c_str());
    attributeList.addAttribute(name, toString(mK));
    sprintf(name, "%sStretchedSphericalHarmonic.M", prefix.c_str());
    attributeList.addAttribute(name, toString(mM));
    sprintf(name, "%sStretchedSphericalHarmonic.RepresentationType", prefix.c_str());
    attributeList.addAttribute(name, toString(mRepresentationType));
    sprintf(name, "%sStretchedSphericalHarmonic.RepresentationMode", prefix.c_str());
    attributeList.addAttribute(name, toString(mRepresentationMode));
    sprintf(name, "%sStretchedSphericalHarmonic.", prefix.c_str());
    mRotation.getAttributeList(name, attributeList);
    sprintf(name, "%sStretchedSphericalHarmonic.", prefix.c_str());
    mGridStretching.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void StretchedSphericalHarmonic::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "StretchedSphericalHarmonic\n";
    stream << space(level) << "- J = " << toString(mJ) << "\n";
    stream << space(level) << "- K = " << toString(mK) << "\n";
    stream << space(level) << "- M = " << toString(mM) << "\n";
    stream << space(level) << "- RepresentationType = " << toString(mRepresentationType) << "\n";
    stream << space(level) << "- RepresentationMode = " << toString(mRepresentationMode) << "\n";
    mRotation.print(stream, level + 1, optionFlags);
    mGridStretching.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash StretchedSphericalHarmonic::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mJ);
    boost::hash_combine(seed, mK);
    boost::hash_combine(seed, mM);
    boost::hash_combine(seed, mRepresentationType);
    boost::hash_combine(seed, mRepresentationMode);
    boost::hash_combine(seed, mRotation.countHash());
    boost::hash_combine(seed, mGridStretching.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mJ} attribute. */

std::uint16_t StretchedSphericalHarmonic::getJ() const {
  try {
    return mJ;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mK} attribute. */

std::uint16_t StretchedSphericalHarmonic::getK() const {
  try {
    return mK;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mM} attribute. */

std::uint16_t StretchedSphericalHarmonic::getM() const {
  try {
    return mM;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mRepresentationType} attribute. */

std::uint8_t StretchedSphericalHarmonic::getRepresentationType() const {
  try {
    return mRepresentationType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mRepresentationMode} attribute. */

std::uint8_t StretchedSphericalHarmonic::getRepresentationMode() const {
  try {
    return mRepresentationMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mRotation} attribute. */

const RotationSettings *StretchedSphericalHarmonic::getRotation() const {
  try {
    return &mRotation;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mGridStretching} attribute. */

const GridStretchingSettings *StretchedSphericalHarmonic::getGridStretching() const {
  try {
    return &mGridStretching;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setJ(std::uint16_t j) {
  try {
    mJ = j;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setK(std::uint16_t k) {
  try {
    mK = k;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setM(std::uint16_t m) {
  try {
    mM = m;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setRepresentationType(std::uint8_t representationType) {
  try {
    mRepresentationType = representationType;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setRepresentationMode(std::uint8_t representationMode) {
  try {
    mRepresentationMode = representationMode;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setRotation(RotationSettings rotation) {
  try {
    mRotation = rotation;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void StretchedSphericalHarmonic::setGridStretching(GridStretchingSettings gridStretching) {
  try {
    mGridStretching = gridStretching;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB1
} // namespace SmartMet
