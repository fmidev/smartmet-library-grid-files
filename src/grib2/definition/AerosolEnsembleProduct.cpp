// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AerosolEnsembleProductImpl.*' files.
// ***********************************************************************

#include "grib2/definition/AerosolEnsembleProduct.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AerosolEnsembleProduct::AerosolEnsembleProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

AerosolEnsembleProduct::~AerosolEnsembleProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current
   object.

        \param memoryReader  This object controls the access to the memory
   mapped file.
*/

void AerosolEnsembleProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterAerosol.read(memoryReader);
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
    mEps.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void AerosolEnsembleProduct::getAttributeList(
    std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAerosolEnsembleProduct.", prefix.c_str());
    mParameterAerosol.getAttributeList(name, attributeList);
    sprintf(name, "%sAerosolEnsembleProduct.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sAerosolEnsembleProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sAerosolEnsembleProduct.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method prints the content of the current object into the given
   stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level
   structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void AerosolEnsembleProduct::print(std::ostream &stream, uint level,
                                   uint optionFlags) const {
  try {
    stream << space(level) << "AerosolEnsembleProduct\n";
    mParameterAerosol.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash AerosolEnsembleProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameterAerosol.countHash());
    boost::hash_combine(seed, mPointInTime.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mEps.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameterAerosol}
 * attribute. */

const ParameterAerosolSettings *
AerosolEnsembleProduct::getParameterAerosol() const {
  try {
    return &mParameterAerosol;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute.
 */

const PointInTimeSettings *AerosolEnsembleProduct::getPointInTime() const {
  try {
    return &mPointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute.
 */

const HorizontalSettings *AerosolEnsembleProduct::getHorizontal() const {
  try {
    return &mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

const EpsSettings *AerosolEnsembleProduct::getEps() const {
  try {
    return &mEps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
