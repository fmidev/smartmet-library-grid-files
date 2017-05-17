// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ParameterPartitionSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template
 * (4.parameter_partition).*/

class ParameterPartitionSettings {
public:
  ParameterPartitionSettings();
  virtual ~ParameterPartitionSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getParameterCategory() const;
  const T::UInt8_opt &getParameterNumber() const;
  const T::UInt8_opt &getPartitionTable() const;
  const T::UInt8_opt &getNumberOfPartitions() const;
  const T::UInt16_opt &getPartitionItems() const;
  const T::UInt16_opt &getPartitionNumber() const;
  const T::UInt8_opt &getTypeOfGeneratingProcess() const;
  const T::UInt8_opt &getBackgroundProcess() const;
  const T::UInt8_opt &getGeneratingProcessIdentifier() const;
  const T::UInt16_opt &getHoursAfterDataCutoff() const;
  const T::UInt8_opt &getMinutesAfterDataCutoff() const;
  const T::UInt8_opt &getIndicatorOfUnitOfTimeRange() const;
  const T::UInt32_opt &getForecastTime() const;

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
  // label "Parameter information";
  //
  // #  Parameter category
  // codetable[1] parameterCategory
  // ('4.1.[discipline:l].table',masterDir,localDir) : dump;

  T::UInt8_opt mParameterCategory;

  //
  // #  Parameter number
  // codetable[1] parameterNumber
  // ('4.2.[discipline:l].[parameterCategory:l].table',masterDir,localDir)  :
  // dump;

  T::UInt8_opt mParameterNumber;

  // meta parameterUnits codetable_units(parameterNumber) : dump;
  // meta parameterName  codetable_title(parameterNumber) : dump;
  // unsigned[1] partitionTable : dump;

  T::UInt8_opt mPartitionTable;

  // unsigned[1] numberOfPartitions=1 :dump;

  T::UInt8_opt mNumberOfPartitions;

  // partitions list(numberOfPartitions) {
  //     unsigned[2] partitionItems ;

  T::UInt16_opt mPartitionItems;

  // }
  //
  // codetable[2] partitionNumber
  // ('4.[partitionTable].table',masterDir,localDir) : dump;

  T::UInt16_opt mPartitionNumber;

  //
  // #  Type of generating process
  // codetable[1] typeOfGeneratingProcess ('4.3.table',masterDir,localDir) :
  // dump;

  T::UInt8_opt mTypeOfGeneratingProcess;

  //
  // #  Background generating process identifier
  // # (defined by originating centre)
  // unsigned[1] backgroundProcess = 255 : edition_specific;

  T::UInt8_opt mBackgroundProcess;

  // alias backgroundGeneratingProcessIdentifier=backgroundProcess;
  //
  //
  // #  Analysis or forecast generating processes identifier
  // # (defined by originating centre)
  // unsigned[1] generatingProcessIdentifier  : dump;

  T::UInt8_opt mGeneratingProcessIdentifier;

  //
  // #  Hours of observational data cut-off after reference time
  // # NOTE 1 NOT FOUND
  // unsigned[2] hoursAfterDataCutoff =missing() :
  // edition_specific,can_be_missing;

  T::UInt16_opt mHoursAfterDataCutoff;

  // alias hoursAfterReferenceTimeOfDataCutoff=hoursAfterDataCutoff;
  //
  // #  Minutes of observational data cut-off after reference time
  // unsigned[1]  minutesAfterDataCutoff = missing() :
  // edition_specific,can_be_missing;

  T::UInt8_opt mMinutesAfterDataCutoff;

  // alias minutesAfterReferenceTimeOfDataCutoff=minutesAfterDataCutoff;
  //
  // #  Indicator of unit of time range
  // codetable[1] indicatorOfUnitOfTimeRange ('4.4.table',masterDir,localDir)  :
  // dump;

  T::UInt8_opt mIndicatorOfUnitOfTimeRange;

  // codetable[1] stepUnits 'stepUnits.table' = 1 : transient,dump,no_copy;
  // (The above is a phony setting)
  //
  // #  Forecast time in units defined by octet 18
  // unsigned[4] forecastTime  : dump;

  T::UInt32_opt mForecastTime;

  //
};

} // namespace GRIB2
} // namespace SmartMet
