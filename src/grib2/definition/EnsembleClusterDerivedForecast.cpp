// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'EnsembleClusterDerivedForecastImpl.*'
//   files.
// ***********************************************************************

#include "grib2/definition/EnsembleClusterDerivedForecast.h"
#include "common/Exception.h"
#include "common/GeneralFunctions.h"
#include "common/GeneralDefinitions.h"
#include <iostream>
#include <boost/functional/hash.hpp>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

EnsembleClusterDerivedForecast::EnsembleClusterDerivedForecast() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The destructor of the class. */

EnsembleClusterDerivedForecast::~EnsembleClusterDerivedForecast() {
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

void EnsembleClusterDerivedForecast::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mPointInTime.read(memoryReader);
    mHorizontal.read(memoryReader);
    mDerived.read(memoryReader);
    mRectangularCluster.read(memoryReader);
    mEnsembleForecastNumbers = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void EnsembleClusterDerivedForecast::getAttributeList(
    std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sEnsembleClusterDerivedForecast.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sEnsembleClusterDerivedForecast.", prefix.c_str());
    mPointInTime.getAttributeList(name, attributeList);
    sprintf(name, "%sEnsembleClusterDerivedForecast.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sEnsembleClusterDerivedForecast.", prefix.c_str());
    mDerived.getAttributeList(name, attributeList);
    sprintf(name, "%sEnsembleClusterDerivedForecast.", prefix.c_str());
    mRectangularCluster.getAttributeList(name, attributeList);
    sprintf(name, "%sEnsembleClusterDerivedForecast.EnsembleForecastNumbers",
            prefix.c_str());
    attributeList.addAttribute(name, toString(mEnsembleForecastNumbers));
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

void EnsembleClusterDerivedForecast::print(std::ostream &stream, uint level,
                                           uint optionFlags) const {
  try {
    stream << space(level) << "EnsembleClusterDerivedForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mDerived.print(stream, level + 1, optionFlags);
    mRectangularCluster.print(stream, level + 1, optionFlags);
    stream << space(level) << "- EnsembleForecastNumbers = "
           << toString(mEnsembleForecastNumbers) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash EnsembleClusterDerivedForecast::countHash() {
  try {
    std::size_t seed = 0;
    if (mEnsembleForecastNumbers)
      boost::hash_combine(seed, *mEnsembleForecastNumbers);
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mPointInTime.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mDerived.countHash());
    boost::hash_combine(seed, mRectangularCluster.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute.
 */

const ParameterSettings *EnsembleClusterDerivedForecast::getParameter() const {
  try {
    return &mParameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute.
 */

const PointInTimeSettings *
EnsembleClusterDerivedForecast::getPointInTime() const {
  try {
    return &mPointInTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute.
 */

const HorizontalSettings *
EnsembleClusterDerivedForecast::getHorizontal() const {
  try {
    return &mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mDerived} attribute. */

const DerivedSettings *EnsembleClusterDerivedForecast::getDerived() const {
  try {
    return &mDerived;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mRectangularCluster}
 * attribute. */

const RectangularClusterSettings *
EnsembleClusterDerivedForecast::getRectangularCluster() const {
  try {
    return &mRectangularCluster;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

/*! \brief The method returns the value of the {@link mEnsembleForecastNumbers}
 * attribute. */

const T::UInt8_opt &
EnsembleClusterDerivedForecast::getEnsembleForecastNumbers() const {
  try {
    return mEnsembleForecastNumbers;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, "Operation failed!", NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet