// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RectangularClusterSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template
 * (4.rectangular_cluster).*/

class RectangularClusterSettings {
public:
  RectangularClusterSettings();
  virtual ~RectangularClusterSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getClusterIdentifier() const;
  const T::UInt8_opt &getNH() const;
  const T::UInt8_opt &getNL() const;
  const T::UInt8_opt &getTotalNumberOfClusters() const;
  const T::UInt8_opt &getClusteringMethod() const;
  const T::UInt32_opt &getNorthernLatitudeOfClusterDomain() const;
  const T::UInt32_opt &getSouthernLatitudeOfClusterDomain() const;
  const T::UInt32_opt &getEasternLongitudeOfClusterDomain() const;
  const T::UInt32_opt &getWesternLongitudeOfClusterDomain() const;
  const T::UInt8_opt &getNumberOfForecastsInTheCluster() const;
  const T::UInt8_opt &getScaleFactorOfStandardDeviation() const;
  const T::UInt32_opt &getScaledValueOfStandardDeviation() const;
  const T::UInt8_opt &getScaleFactorOfDistanceFromEnsembleMean() const;
  const T::UInt32_opt &getScaledValueOfDistanceFromEnsembleMean() const;

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version
  // 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and
  // immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it
  // submit to any jurisdiction.
  // #
  //
  // label "Rectangular cluster";
  //
  // #  Cluster identifier
  // unsigned[1] clusterIdentifier : dump ;

  T::UInt8_opt mClusterIdentifier;

  // alias number=clusterIdentifier;
  //
  // #  Number of cluster to which the high resolution control belongs
  // unsigned[1]  NH : dump;

  T::UInt8_opt mNH;

  //
  // #  Number of cluster to which the low resolution control belongs
  // unsigned[1] NL : dump ;

  T::UInt8_opt mNL;

  //
  // #  Total number of clusters
  // unsigned[1] totalNumberOfClusters : dump ;

  T::UInt8_opt mTotalNumberOfClusters;

  // alias totalNumber=totalNumberOfClusters;
  //
  // #  Clustering method
  // codetable[1] clusteringMethod ('4.8.table',masterDir,localDir) : dump;

  T::UInt8_opt mClusteringMethod;

  //
  // #  Northern latitude of cluster domain
  // unsigned[4] northernLatitudeOfClusterDomain : dump ;

  T::UInt32_opt mNorthernLatitudeOfClusterDomain;

  //
  // #  Southern latitude of cluster domain
  // unsigned[4] southernLatitudeOfClusterDomain : dump ;

  T::UInt32_opt mSouthernLatitudeOfClusterDomain;

  //
  // #  Eastern longitude of cluster domain
  // unsigned[4] easternLongitudeOfClusterDomain  : dump;

  T::UInt32_opt mEasternLongitudeOfClusterDomain;

  //
  // #  Western longitude of cluster domain
  // unsigned[4] westernLongitudeOfClusterDomain : dump ;

  T::UInt32_opt mWesternLongitudeOfClusterDomain;

  //
  // #  NC - Number of forecasts in the cluster
  // unsigned[1] numberOfForecastsInTheCluster : dump ;

  T::UInt8_opt mNumberOfForecastsInTheCluster;

  //
  // alias NC  = numberOfForecastsInTheCluster;
  // #  Scale factor of standard deviation in the cluster
  // unsigned[1] scaleFactorOfStandardDeviation : edition_specific ;

  T::UInt8_opt mScaleFactorOfStandardDeviation;

  // alias
  // scaleFactorOfStandardDeviationInTheCluster=scaleFactorOfStandardDeviation;
  //
  // #  Scaled value of standard deviation in the cluster
  // unsigned[4] scaledValueOfStandardDeviation : dump ;

  T::UInt32_opt mScaledValueOfStandardDeviation;

  // alias
  // scaledValueOfStandardDeviationInTheCluster=scaledValueOfStandardDeviation;
  //
  // #  Scale factor of distance of the cluster from ensemble mean
  // unsigned[1] scaleFactorOfDistanceFromEnsembleMean : dump ;

  T::UInt8_opt mScaleFactorOfDistanceFromEnsembleMean;

  //
  // #  Scaled value of distance of the cluster from ensemble mean
  // unsigned[4] scaledValueOfDistanceFromEnsembleMean : dump ;

  T::UInt32_opt mScaledValueOfDistanceFromEnsembleMean;

  //
  //
};

} // namespace GRIB2
} // namespace SmartMet
