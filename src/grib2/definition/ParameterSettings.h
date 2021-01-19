// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ParameterSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.parameter).*/

class ParameterSettings {
public:
  ParameterSettings();
  virtual ~ParameterSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getParameterCategory() const;
  void setParameterCategory(T::UInt8_opt parameterCategory);
  const T::UInt8_opt &getParameterNumber() const;
  void setParameterNumber(T::UInt8_opt parameterNumber);
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
  const T::Int32_opt &getForecastTime() const;
  void setForecastTime(T::Int32_opt forecastTime);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // #  Parameter category
  // codetable[1] parameterCategory ('4.1.[discipline:l].table',masterDir,localDir) : dump;

  T::UInt8_opt mParameterCategory;

  //
  // #  Parameter number
  // codetable[1] parameterNumber ('4.2.[discipline:l].[parameterCategory:l].table',masterDir,localDir)  : dump;

  T::UInt8_opt mParameterNumber;

  // meta parameterUnits codetable_units(parameterNumber) : dump;
  // meta parameterName  codetable_title(parameterNumber) : dump;
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
  // #  Analysis or forecast generating processes identifier
  // # (defined by originating centre)
  // unsigned[1] generatingProcessIdentifier  : dump;

  T::UInt8_opt mGeneratingProcessIdentifier;

  //
  // #  Hours of observational data cut-off after reference time
  // unsigned[2] hoursAfterDataCutoff =missing() : edition_specific,can_be_missing;

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

  // alias defaultStepUnits = one; # 1 means Hour. See code table 4.4
  // template_nofail default_step_units "grib2/localConcepts/[centre:s]/default_step_units.def";
  // codetable[1] stepUnits 'stepUnits.table' = defaultStepUnits : transient,dump,no_copy;
  // (The above is a phony setting)
  //
  // #  Forecast time in units defined by octet 18 (GRIB-29: supports negative forecast time)
  // signed[4] forecastTime  : dump;

  T::Int32_opt mForecastTime;
};

} // namespace GRIB2
} // namespace SmartMet
