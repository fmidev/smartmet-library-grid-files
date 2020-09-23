// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'EnsembleClusterDerivedForecastImpl.*' files.
// ***********************************************************************

#include "EnsembleClusterDerivedForecast.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

EnsembleClusterDerivedForecast::EnsembleClusterDerivedForecast() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

EnsembleClusterDerivedForecast::EnsembleClusterDerivedForecast(const EnsembleClusterDerivedForecast &other) : ProductDefinition(other) {
  try {
    mParameter = other.mParameter;
    mPointInTime = other.mPointInTime;
    mHorizontal = other.mHorizontal;
    mDerived = other.mDerived;
    mRectangularCluster = other.mRectangularCluster;
    mEnsembleForecastNumbers = other.mEnsembleForecastNumbers;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

EnsembleClusterDerivedForecast::~EnsembleClusterDerivedForecast() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void EnsembleClusterDerivedForecast::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mPointInTime.write(dataWriter);
    mHorizontal.write(dataWriter);
    mDerived.write(dataWriter);
    mRectangularCluster.write(dataWriter);
    dataWriter << mEnsembleForecastNumbers;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void EnsembleClusterDerivedForecast::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
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
    sprintf(name, "%sEnsembleClusterDerivedForecast.EnsembleForecastNumbers", prefix.c_str());
    attributeList.addAttribute(name, toString(mEnsembleForecastNumbers));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void EnsembleClusterDerivedForecast::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "EnsembleClusterDerivedForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mPointInTime.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mDerived.print(stream, level + 1, optionFlags);
    mRectangularCluster.print(stream, level + 1, optionFlags);
    stream << space(level) << "- EnsembleForecastNumbers = " << toString(mEnsembleForecastNumbers) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
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
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint EnsembleClusterDerivedForecast::getTemplateNumber() const {
  return 3;
}

ProductDefinition *EnsembleClusterDerivedForecast::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new EnsembleClusterDerivedForecast(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *EnsembleClusterDerivedForecast::getParameter() const {
  try {
    return static_cast<ParameterSettings *>(&mParameter);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPointInTime} attribute. */

PointInTimeSettings *EnsembleClusterDerivedForecast::getPointInTime() const {
  try {
    return static_cast<PointInTimeSettings *>(&mPointInTime);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *EnsembleClusterDerivedForecast::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mDerived} attribute. */

DerivedSettings *EnsembleClusterDerivedForecast::getDerived() const {
  try {
    return static_cast<DerivedSettings *>(&mDerived);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mRectangularCluster} attribute. */

RectangularClusterSettings *EnsembleClusterDerivedForecast::getRectangularCluster() const {
  try {
    return static_cast<RectangularClusterSettings *>(&mRectangularCluster);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mEnsembleForecastNumbers} attribute. */

const T::UInt8_opt &EnsembleClusterDerivedForecast::getEnsembleForecastNumbers() const {
  try {
    return mEnsembleForecastNumbers;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void EnsembleClusterDerivedForecast::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void EnsembleClusterDerivedForecast::setPointInTime(PointInTimeSettings &pointInTime) {
  try {
    mPointInTime = pointInTime;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void EnsembleClusterDerivedForecast::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void EnsembleClusterDerivedForecast::setDerived(DerivedSettings &derived) {
  try {
    mDerived = derived;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void EnsembleClusterDerivedForecast::setRectangularCluster(RectangularClusterSettings &rectangularCluster) {
  try {
    mRectangularCluster = rectangularCluster;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void EnsembleClusterDerivedForecast::setEnsembleForecastNumbers(T::UInt8_opt ensembleForecastNumbers) {
  try {
    mEnsembleForecastNumbers = ensembleForecastNumbers;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
