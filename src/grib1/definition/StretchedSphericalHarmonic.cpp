// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedSphericalHarmonicImpl.*' files.
// ***********************************************************************

#include "StretchedSphericalHarmonic.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

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
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

StretchedSphericalHarmonic::~StretchedSphericalHarmonic() {
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
    for (uint t = 0; t < 18; t++)
      memoryReader.read_uint8();
    mGridStretching.read(memoryReader);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current section object.

        \param dataWriter  This object controls the write stream.
*/

void StretchedSphericalHarmonic::write(DataWriter &dataWriter) {
  try {
    dataWriter << mJ;
    dataWriter << mK;
    dataWriter << mM;
    dataWriter << mRepresentationType;
    dataWriter << mRepresentationMode;
    for (uint t = 0; t < 18; t++)
      dataWriter.write_uint8(0);
    mGridStretching.write(dataWriter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void StretchedSphericalHarmonic::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
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
    mGridStretching.getAttributeList(name, attributeList);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
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
    mGridStretching.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
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
    boost::hash_combine(seed, mGridStretching.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint StretchedSphericalHarmonic::getTemplateNumber() const {
  return 70;
}

GridDefinition *StretchedSphericalHarmonic::createGridDefinition() const {
  try {
    return static_cast<GridDefinition *>(new StretchedSphericalHarmonic(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mJ} attribute. */

std::uint16_t StretchedSphericalHarmonic::getJ() const {
  try {
    return mJ;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mK} attribute. */

std::uint16_t StretchedSphericalHarmonic::getK() const {
  try {
    return mK;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mM} attribute. */

std::uint16_t StretchedSphericalHarmonic::getM() const {
  try {
    return mM;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mRepresentationType} attribute. */

std::uint8_t StretchedSphericalHarmonic::getRepresentationType() const {
  try {
    return mRepresentationType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mRepresentationMode} attribute. */

std::uint8_t StretchedSphericalHarmonic::getRepresentationMode() const {
  try {
    return mRepresentationMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mGridStretching} attribute. */

GridStretchingSettings *StretchedSphericalHarmonic::getGridStretching() const {
  try {
    return static_cast<GridStretchingSettings *>(&mGridStretching);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedSphericalHarmonic::setJ(std::uint16_t j) {
  try {
    mJ = j;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedSphericalHarmonic::setK(std::uint16_t k) {
  try {
    mK = k;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedSphericalHarmonic::setM(std::uint16_t m) {
  try {
    mM = m;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedSphericalHarmonic::setRepresentationType(std::uint8_t representationType) {
  try {
    mRepresentationType = representationType;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedSphericalHarmonic::setRepresentationMode(std::uint8_t representationMode) {
  try {
    mRepresentationMode = representationMode;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void StretchedSphericalHarmonic::setGridStretching(GridStretchingSettings &gridStretching) {
  try {
    mGridStretching = gridStretching;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB1
} // namespace SmartMet
