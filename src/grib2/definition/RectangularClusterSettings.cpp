// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RectangularClusterSettingsImpl.*' files.
// ***********************************************************************

#include "RectangularClusterSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

RectangularClusterSettings::RectangularClusterSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

RectangularClusterSettings::~RectangularClusterSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void RectangularClusterSettings::read(MemoryReader &memoryReader) {
  try {
    mClusterIdentifier = memoryReader.read_UInt8_opt();
    mNH = memoryReader.read_UInt8_opt();
    mNL = memoryReader.read_UInt8_opt();
    mTotalNumberOfClusters = memoryReader.read_UInt8_opt();
    mClusteringMethod = memoryReader.read_UInt8_opt();
    mNorthernLatitudeOfClusterDomain = memoryReader.read_UInt32_opt();
    mSouthernLatitudeOfClusterDomain = memoryReader.read_UInt32_opt();
    mEasternLongitudeOfClusterDomain = memoryReader.read_UInt32_opt();
    mWesternLongitudeOfClusterDomain = memoryReader.read_UInt32_opt();
    mNumberOfForecastsInTheCluster = memoryReader.read_UInt8_opt();
    mScaleFactorOfStandardDeviation = memoryReader.read_UInt8_opt();
    mScaledValueOfStandardDeviation = memoryReader.read_UInt32_opt();
    mScaleFactorOfDistanceFromEnsembleMean = memoryReader.read_UInt8_opt();
    mScaledValueOfDistanceFromEnsembleMean = memoryReader.read_UInt32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void RectangularClusterSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mClusterIdentifier;
    dataWriter << mNH;
    dataWriter << mNL;
    dataWriter << mTotalNumberOfClusters;
    dataWriter << mClusteringMethod;
    dataWriter << mNorthernLatitudeOfClusterDomain;
    dataWriter << mSouthernLatitudeOfClusterDomain;
    dataWriter << mEasternLongitudeOfClusterDomain;
    dataWriter << mWesternLongitudeOfClusterDomain;
    dataWriter << mNumberOfForecastsInTheCluster;
    dataWriter << mScaleFactorOfStandardDeviation;
    dataWriter << mScaledValueOfStandardDeviation;
    dataWriter << mScaleFactorOfDistanceFromEnsembleMean;
    dataWriter << mScaledValueOfDistanceFromEnsembleMean;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void RectangularClusterSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sRectangularClusterSettings.ClusterIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mClusterIdentifier));
    sprintf(name, "%sRectangularClusterSettings.NH", prefix.c_str());
    attributeList.addAttribute(name, toString(mNH));
    sprintf(name, "%sRectangularClusterSettings.NL", prefix.c_str());
    attributeList.addAttribute(name, toString(mNL));
    sprintf(name, "%sRectangularClusterSettings.TotalNumberOfClusters", prefix.c_str());
    attributeList.addAttribute(name, toString(mTotalNumberOfClusters));
    sprintf(name, "%sRectangularClusterSettings.ClusteringMethod", prefix.c_str());
    attributeList.addAttribute(name, toString(mClusteringMethod));
    sprintf(name, "%sRectangularClusterSettings.NorthernLatitudeOfClusterDomain", prefix.c_str());
    attributeList.addAttribute(name, toString(mNorthernLatitudeOfClusterDomain));
    sprintf(name, "%sRectangularClusterSettings.SouthernLatitudeOfClusterDomain", prefix.c_str());
    attributeList.addAttribute(name, toString(mSouthernLatitudeOfClusterDomain));
    sprintf(name, "%sRectangularClusterSettings.EasternLongitudeOfClusterDomain", prefix.c_str());
    attributeList.addAttribute(name, toString(mEasternLongitudeOfClusterDomain));
    sprintf(name, "%sRectangularClusterSettings.WesternLongitudeOfClusterDomain", prefix.c_str());
    attributeList.addAttribute(name, toString(mWesternLongitudeOfClusterDomain));
    sprintf(name, "%sRectangularClusterSettings.NumberOfForecastsInTheCluster", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfForecastsInTheCluster));
    sprintf(name, "%sRectangularClusterSettings.ScaleFactorOfStandardDeviation", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfStandardDeviation));
    sprintf(name, "%sRectangularClusterSettings.ScaledValueOfStandardDeviation", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfStandardDeviation));
    sprintf(name, "%sRectangularClusterSettings.ScaleFactorOfDistanceFromEnsembleMean", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaleFactorOfDistanceFromEnsembleMean));
    sprintf(name, "%sRectangularClusterSettings.ScaledValueOfDistanceFromEnsembleMean", prefix.c_str());
    attributeList.addAttribute(name, toString(mScaledValueOfDistanceFromEnsembleMean));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void RectangularClusterSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "RectangularClusterSettings\n";
    stream << space(level) << "- ClusterIdentifier = " << toString(mClusterIdentifier) << "\n";
    stream << space(level) << "- NH = " << toString(mNH) << "\n";
    stream << space(level) << "- NL = " << toString(mNL) << "\n";
    stream << space(level) << "- TotalNumberOfClusters = " << toString(mTotalNumberOfClusters) << "\n";
    stream << space(level) << "- ClusteringMethod = " << toString(mClusteringMethod) << "\n";
    stream << space(level) << "- NorthernLatitudeOfClusterDomain = " << toString(mNorthernLatitudeOfClusterDomain) << "\n";
    stream << space(level) << "- SouthernLatitudeOfClusterDomain = " << toString(mSouthernLatitudeOfClusterDomain) << "\n";
    stream << space(level) << "- EasternLongitudeOfClusterDomain = " << toString(mEasternLongitudeOfClusterDomain) << "\n";
    stream << space(level) << "- WesternLongitudeOfClusterDomain = " << toString(mWesternLongitudeOfClusterDomain) << "\n";
    stream << space(level) << "- NumberOfForecastsInTheCluster = " << toString(mNumberOfForecastsInTheCluster) << "\n";
    stream << space(level) << "- ScaleFactorOfStandardDeviation = " << toString(mScaleFactorOfStandardDeviation) << "\n";
    stream << space(level) << "- ScaledValueOfStandardDeviation = " << toString(mScaledValueOfStandardDeviation) << "\n";
    stream << space(level) << "- ScaleFactorOfDistanceFromEnsembleMean = " << toString(mScaleFactorOfDistanceFromEnsembleMean) << "\n";
    stream << space(level) << "- ScaledValueOfDistanceFromEnsembleMean = " << toString(mScaledValueOfDistanceFromEnsembleMean) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash RectangularClusterSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mClusterIdentifier)
      boost::hash_combine(seed, *mClusterIdentifier);
    if (mNH)
      boost::hash_combine(seed, *mNH);
    if (mNL)
      boost::hash_combine(seed, *mNL);
    if (mTotalNumberOfClusters)
      boost::hash_combine(seed, *mTotalNumberOfClusters);
    if (mClusteringMethod)
      boost::hash_combine(seed, *mClusteringMethod);
    if (mNorthernLatitudeOfClusterDomain)
      boost::hash_combine(seed, *mNorthernLatitudeOfClusterDomain);
    if (mSouthernLatitudeOfClusterDomain)
      boost::hash_combine(seed, *mSouthernLatitudeOfClusterDomain);
    if (mEasternLongitudeOfClusterDomain)
      boost::hash_combine(seed, *mEasternLongitudeOfClusterDomain);
    if (mWesternLongitudeOfClusterDomain)
      boost::hash_combine(seed, *mWesternLongitudeOfClusterDomain);
    if (mNumberOfForecastsInTheCluster)
      boost::hash_combine(seed, *mNumberOfForecastsInTheCluster);
    if (mScaleFactorOfStandardDeviation)
      boost::hash_combine(seed, *mScaleFactorOfStandardDeviation);
    if (mScaledValueOfStandardDeviation)
      boost::hash_combine(seed, *mScaledValueOfStandardDeviation);
    if (mScaleFactorOfDistanceFromEnsembleMean)
      boost::hash_combine(seed, *mScaleFactorOfDistanceFromEnsembleMean);
    if (mScaledValueOfDistanceFromEnsembleMean)
      boost::hash_combine(seed, *mScaledValueOfDistanceFromEnsembleMean);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mClusterIdentifier} attribute. */

const T::UInt8_opt &RectangularClusterSettings::getClusterIdentifier() const {
  try {
    return mClusterIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNH} attribute. */

const T::UInt8_opt &RectangularClusterSettings::getNH() const {
  try {
    return mNH;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNL} attribute. */

const T::UInt8_opt &RectangularClusterSettings::getNL() const {
  try {
    return mNL;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTotalNumberOfClusters} attribute. */

const T::UInt8_opt &RectangularClusterSettings::getTotalNumberOfClusters() const {
  try {
    return mTotalNumberOfClusters;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mClusteringMethod} attribute. */

const T::UInt8_opt &RectangularClusterSettings::getClusteringMethod() const {
  try {
    return mClusteringMethod;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNorthernLatitudeOfClusterDomain} attribute. */

const T::UInt32_opt &RectangularClusterSettings::getNorthernLatitudeOfClusterDomain() const {
  try {
    return mNorthernLatitudeOfClusterDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSouthernLatitudeOfClusterDomain} attribute. */

const T::UInt32_opt &RectangularClusterSettings::getSouthernLatitudeOfClusterDomain() const {
  try {
    return mSouthernLatitudeOfClusterDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mEasternLongitudeOfClusterDomain} attribute. */

const T::UInt32_opt &RectangularClusterSettings::getEasternLongitudeOfClusterDomain() const {
  try {
    return mEasternLongitudeOfClusterDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mWesternLongitudeOfClusterDomain} attribute. */

const T::UInt32_opt &RectangularClusterSettings::getWesternLongitudeOfClusterDomain() const {
  try {
    return mWesternLongitudeOfClusterDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfForecastsInTheCluster} attribute. */

const T::UInt8_opt &RectangularClusterSettings::getNumberOfForecastsInTheCluster() const {
  try {
    return mNumberOfForecastsInTheCluster;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfStandardDeviation} attribute. */

const T::UInt8_opt &RectangularClusterSettings::getScaleFactorOfStandardDeviation() const {
  try {
    return mScaleFactorOfStandardDeviation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfStandardDeviation} attribute. */

const T::UInt32_opt &RectangularClusterSettings::getScaledValueOfStandardDeviation() const {
  try {
    return mScaledValueOfStandardDeviation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaleFactorOfDistanceFromEnsembleMean} attribute. */

const T::UInt8_opt &RectangularClusterSettings::getScaleFactorOfDistanceFromEnsembleMean() const {
  try {
    return mScaleFactorOfDistanceFromEnsembleMean;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mScaledValueOfDistanceFromEnsembleMean} attribute. */

const T::UInt32_opt &RectangularClusterSettings::getScaledValueOfDistanceFromEnsembleMean() const {
  try {
    return mScaledValueOfDistanceFromEnsembleMean;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setClusterIdentifier(T::UInt8_opt clusterIdentifier) {
  try {
    mClusterIdentifier = clusterIdentifier;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setNH(T::UInt8_opt nH) {
  try {
    mNH = nH;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setNL(T::UInt8_opt nL) {
  try {
    mNL = nL;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setTotalNumberOfClusters(T::UInt8_opt totalNumberOfClusters) {
  try {
    mTotalNumberOfClusters = totalNumberOfClusters;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setClusteringMethod(T::UInt8_opt clusteringMethod) {
  try {
    mClusteringMethod = clusteringMethod;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setNorthernLatitudeOfClusterDomain(T::UInt32_opt northernLatitudeOfClusterDomain) {
  try {
    mNorthernLatitudeOfClusterDomain = northernLatitudeOfClusterDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setSouthernLatitudeOfClusterDomain(T::UInt32_opt southernLatitudeOfClusterDomain) {
  try {
    mSouthernLatitudeOfClusterDomain = southernLatitudeOfClusterDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setEasternLongitudeOfClusterDomain(T::UInt32_opt easternLongitudeOfClusterDomain) {
  try {
    mEasternLongitudeOfClusterDomain = easternLongitudeOfClusterDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setWesternLongitudeOfClusterDomain(T::UInt32_opt westernLongitudeOfClusterDomain) {
  try {
    mWesternLongitudeOfClusterDomain = westernLongitudeOfClusterDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setNumberOfForecastsInTheCluster(T::UInt8_opt numberOfForecastsInTheCluster) {
  try {
    mNumberOfForecastsInTheCluster = numberOfForecastsInTheCluster;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setScaleFactorOfStandardDeviation(T::UInt8_opt scaleFactorOfStandardDeviation) {
  try {
    mScaleFactorOfStandardDeviation = scaleFactorOfStandardDeviation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setScaledValueOfStandardDeviation(T::UInt32_opt scaledValueOfStandardDeviation) {
  try {
    mScaledValueOfStandardDeviation = scaledValueOfStandardDeviation;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setScaleFactorOfDistanceFromEnsembleMean(T::UInt8_opt scaleFactorOfDistanceFromEnsembleMean) {
  try {
    mScaleFactorOfDistanceFromEnsembleMean = scaleFactorOfDistanceFromEnsembleMean;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void RectangularClusterSettings::setScaledValueOfDistanceFromEnsembleMean(T::UInt32_opt scaledValueOfDistanceFromEnsembleMean) {
  try {
    mScaledValueOfDistanceFromEnsembleMean = scaledValueOfDistanceFromEnsembleMean;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
