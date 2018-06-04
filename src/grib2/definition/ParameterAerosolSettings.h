// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ParameterAerosolSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.parameter_aerosol).*/

class ParameterAerosolSettings {
public:
  ParameterAerosolSettings();
  virtual ~ParameterAerosolSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getParameterCategory() const;
  void setParameterCategory(T::UInt8_opt parameterCategory);
  const T::UInt8_opt &getParameterNumber() const;
  void setParameterNumber(T::UInt8_opt parameterNumber);
  const T::UInt16_opt &getAerosolType() const;
  void setAerosolType(T::UInt16_opt aerosolType);
  const T::UInt8_opt &getTypeOfSizeInterval() const;
  void setTypeOfSizeInterval(T::UInt8_opt typeOfSizeInterval);
  const T::Int8_opt &getScaleFactorOfFirstSize() const;
  void setScaleFactorOfFirstSize(T::Int8_opt scaleFactorOfFirstSize);
  const T::Int32_opt &getScaledValueOfFirstSize() const;
  void setScaledValueOfFirstSize(T::Int32_opt scaledValueOfFirstSize);
  const T::Int8_opt &getScaleFactorOfSecondSize() const;
  void setScaleFactorOfSecondSize(T::Int8_opt scaleFactorOfSecondSize);
  const T::Int32_opt &getScaledValueOfSecondSize() const;
  void setScaledValueOfSecondSize(T::Int32_opt scaledValueOfSecondSize);
  const T::UInt8_opt &getTypeOfGeneratingProcess() const;
  void setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess);
  const T::UInt8_opt &getBackgroundProcess() const;
  void setBackgroundProcess(T::UInt8_opt backgroundProcess);
  const T::UInt8_opt &getGeneratingProcessIdentifier() const;
  void setGeneratingProcessIdentifier(T::UInt8_opt generatingProcessIdentifier);
  const T::UInt16_opt &getHoursAfterDataCutoff() const;
  void setHoursAfterDataCutoff(T::UInt16_opt hoursAfterDataCutoff);
  const T::UInt8_opt &getMinutesAfterDataCutoff() const;
  void setMinutesAfterDataCutoff(T::UInt8_opt minutesAfterDataCutoff);
  const T::UInt8_opt &getIndicatorOfUnitOfTimeRange() const;
  void setIndicatorOfUnitOfTimeRange(T::UInt8_opt indicatorOfUnitOfTimeRange);
  const T::UInt32_opt &getForecastTime() const;
  void setForecastTime(T::UInt32_opt forecastTime);

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // label "Parameter information";
  //
  // #  Parameter category
  // codetable[1] parameterCategory ('4.1.[discipline:l].table',masterDir,localDir) : dump;

  T::UInt8_opt mParameterCategory;

  //
  // #  Parameter number
  // codetable[1] parameterNumber ('4.2.[discipline:l].[parameterCategory:l].table',masterDir,localDir) : dump;

  T::UInt8_opt mParameterNumber;

  // meta parameterUnits codetable_units(parameterNumber) : dump;
  // meta parameterName  codetable_title(parameterNumber) : dump;
  //
  // # Atmospheric chemical or physical constitutent type
  // codetable[2] aerosolType ('4.233.table',masterDir,localDir) : dump;

  T::UInt16_opt mAerosolType;

  //
  // codetable[1] typeOfSizeInterval ('4.91.table',masterDir,localDir) : dump;

  T::UInt8_opt mTypeOfSizeInterval;

  // alias typeOfIntervalForFirstAndSecondSize=typeOfSizeInterval;
  //
  // signed[1] scaleFactorOfFirstSize : dump;

  T::Int8_opt mScaleFactorOfFirstSize;

  // signed[4] scaledValueOfFirstSize :dump;

  T::Int32_opt mScaledValueOfFirstSize;

  // signed[1] scaleFactorOfSecondSize = missing() : can_be_missing,dump;

  T::Int8_opt mScaleFactorOfSecondSize;

  // signed[4] scaledValueOfSecondSize = missing() : can_be_missing,dump;

  T::Int32_opt mScaledValueOfSecondSize;

  //
  // #  Type of generating process
  // codetable[1] typeOfGeneratingProcess ('4.3.table',masterDir,localDir) : dump;

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
  // unsigned[2] hoursAfterDataCutoff = missing() : edition_specific,can_be_missing;

  T::UInt16_opt mHoursAfterDataCutoff;

  // alias hoursAfterReferenceTimeOfDataCutoff=hoursAfterDataCutoff;
  //
  // #  Minutes of observational data cut-off after reference time
  // unsigned[1]  minutesAfterDataCutoff = missing() : edition_specific,can_be_missing;

  T::UInt8_opt mMinutesAfterDataCutoff;

  // alias minutesAfterReferenceTimeOfDataCutoff=minutesAfterDataCutoff;
  //
  // #  Indicator of unit of time range
  // codetable[1] indicatorOfUnitOfTimeRange ('4.4.table',masterDir,localDir)  : dump;

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
