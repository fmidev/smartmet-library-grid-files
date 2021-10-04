// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StatisticalSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.statistical).*/

class StatisticalSettings {
public:
  StatisticalSettings();
  virtual ~StatisticalSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt16_opt &getYearOfEndOfOverallTimeInterval() const;
  void setYearOfEndOfOverallTimeInterval(T::UInt16_opt yearOfEndOfOverallTimeInterval);
  const T::UInt8_opt &getMonthOfEndOfOverallTimeInterval() const;
  void setMonthOfEndOfOverallTimeInterval(T::UInt8_opt monthOfEndOfOverallTimeInterval);
  const T::UInt8_opt &getDayOfEndOfOverallTimeInterval() const;
  void setDayOfEndOfOverallTimeInterval(T::UInt8_opt dayOfEndOfOverallTimeInterval);
  const T::UInt8_opt &getHourOfEndOfOverallTimeInterval() const;
  void setHourOfEndOfOverallTimeInterval(T::UInt8_opt hourOfEndOfOverallTimeInterval);
  const T::UInt8_opt &getMinuteOfEndOfOverallTimeInterval() const;
  void setMinuteOfEndOfOverallTimeInterval(T::UInt8_opt minuteOfEndOfOverallTimeInterval);
  const T::UInt8_opt &getSecondOfEndOfOverallTimeInterval() const;
  void setSecondOfEndOfOverallTimeInterval(T::UInt8_opt secondOfEndOfOverallTimeInterval);
  const T::UInt8_opt &getNumberOfTimeRange() const;
  void setNumberOfTimeRange(T::UInt8_opt numberOfTimeRange);
  const T::UInt32_opt &getNumberOfMissingInStatisticalProcess() const;
  void setNumberOfMissingInStatisticalProcess(T::UInt32_opt numberOfMissingInStatisticalProcess);
  const T::UInt8_opt &getTypeOfStatisticalProcessing() const;
  void setTypeOfStatisticalProcessing(T::UInt8_opt typeOfStatisticalProcessing);
  const T::UInt8_opt &getTypeOfTimeIncrement() const;
  void setTypeOfTimeIncrement(T::UInt8_opt typeOfTimeIncrement);
  const T::UInt8_opt &getIndicatorOfUnitForTimeRange() const;
  void setIndicatorOfUnitForTimeRange(T::UInt8_opt indicatorOfUnitForTimeRange);
  const T::UInt32_opt &getLengthOfTimeRange() const;
  void setLengthOfTimeRange(T::UInt32_opt lengthOfTimeRange);
  const T::UInt8_opt &getIndicatorOfUnitForTimeIncrement() const;
  void setIndicatorOfUnitForTimeIncrement(T::UInt8_opt indicatorOfUnitForTimeIncrement);
  const T::UInt32_opt &getTimeIncrement() const;
  void setTimeIncrement(T::UInt32_opt timeIncrement);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // #  Year of end of overall time interval
  // unsigned[2] yearOfEndOfOverallTimeInterval =0 : edition_specific;

  T::UInt16_opt mYearOfEndOfOverallTimeInterval;

  //
  // #  Month of end of overall time interval
  // unsigned[1] monthOfEndOfOverallTimeInterval =0 : edition_specific;

  T::UInt8_opt mMonthOfEndOfOverallTimeInterval;

  //
  // #  Day of end of overall time interval
  // unsigned[1] dayOfEndOfOverallTimeInterval =0 : edition_specific;

  T::UInt8_opt mDayOfEndOfOverallTimeInterval;

  //
  // #  Hour of end of overall time interval
  // unsigned[1] hourOfEndOfOverallTimeInterval =0 : edition_specific;

  T::UInt8_opt mHourOfEndOfOverallTimeInterval;

  //
  // #  Minute of end of overall time interval
  // unsigned[1] minuteOfEndOfOverallTimeInterval =0 : edition_specific;

  T::UInt8_opt mMinuteOfEndOfOverallTimeInterval;

  //
  // #  Second of end of overall time interval
  // unsigned[1] secondOfEndOfOverallTimeInterval =0 : edition_specific;

  T::UInt8_opt mSecondOfEndOfOverallTimeInterval;

  //
  // #  n - number of time range specifications describing the time intervals used to calculate the statistically-processed field
  // unsigned[1]  numberOfTimeRange = 1 : edition_specific;

  T::UInt8_opt mNumberOfTimeRange;

  // alias n =  numberOfTimeRange;
  //
  // #  Total number of data values missing in statistical process
  // unsigned[4] numberOfMissingInStatisticalProcess = 0  : edition_specific;

  T::UInt32_opt mNumberOfMissingInStatisticalProcess;

  // alias totalNumberOfDataValuesMissingInStatisticalProcess=numberOfMissingInStatisticalProcess;
  //
  // statisticalProcessesList list(numberOfTimeRange)
  // {
  //  #  Statistical process used to calculate the processed field from the field at each time increment during the time range
  //  codetable[1] typeOfStatisticalProcessing ('4.10.table',masterDir,localDir) : edition_specific;

  T::UInt8_opt mTypeOfStatisticalProcessing;

  //
  //  #  Type of time increment between successive fields used in the statistical processing
  //  codetable[1]  typeOfTimeIncrement ('4.11.table',masterDir,localDir) = 2 : edition_specific;

  T::UInt8_opt mTypeOfTimeIncrement;

  //  alias typeOfTimeIncrementBetweenSuccessiveFieldsUsedInTheStatisticalProcessing=typeOfTimeIncrement;
  //
  //  #  Indicator of unit of time for time range over which statistical processing is done
  //  codetable[1]  indicatorOfUnitForTimeRange ('4.4.table',masterDir,localDir) =1 ;

  T::UInt8_opt mIndicatorOfUnitForTimeRange;

  //
  //  #  Length of the time range over which statistical processing is done, in units defined by the previous octet
  //  unsigned[4] lengthOfTimeRange=0 ;

  T::UInt32_opt mLengthOfTimeRange;

  //
  //  #  Indicator of unit of time for the increment between the successive fields used
  //  codetable[1]  indicatorOfUnitForTimeIncrement ('4.4.table',masterDir,localDir)=255 ;

  T::UInt8_opt mIndicatorOfUnitForTimeIncrement;

  //
  //  #  Time increment between successive fields, in units defined by the previous octet
  //  unsigned[4] timeIncrement=0 ;

  T::UInt32_opt mTimeIncrement;

  //  alias timeIncrementBetweenSuccessiveFields=timeIncrement;
  //
  // }
  //
  // # See GRIB-488. We only support maximum of 2 time ranges
  // if (numberOfTimeRange == 1 || numberOfTimeRange == 2) {
  //   concept stepTypeInternal {
  //     "instant" = {typeOfStatisticalProcessing=255;}
  //     "avg"     = {typeOfStatisticalProcessing=0;typeOfTimeIncrement=2;}
  //     "avg"     = {typeOfStatisticalProcessing=0;typeOfTimeIncrement=3;}
  //     "avgd"    = {typeOfStatisticalProcessing=0;typeOfTimeIncrement=1;}
  //     "accum"   = {typeOfStatisticalProcessing=1;typeOfTimeIncrement=2;}
  //     "max"     = {typeOfStatisticalProcessing=2;}
  //     "min"     = {typeOfStatisticalProcessing=3;}
  //     "diff"    = {typeOfStatisticalProcessing=4;} # end-start
  //     "rms"     = {typeOfStatisticalProcessing=5;}
  //     "sd"      = {typeOfStatisticalProcessing=6;}
  //     "cov"     = {typeOfStatisticalProcessing=7;}
  //     "sdiff"   = {typeOfStatisticalProcessing=8;} # start-end
  //     "ratio"   = {typeOfStatisticalProcessing=9;}
  //     "stdanom" = {typeOfStatisticalProcessing=10;}
  //     "sum"     = {typeOfStatisticalProcessing=11;}
  //   }
  //   meta startStep step_in_units(forecastTime,indicatorOfUnitOfTimeRange,stepUnits,
  //     indicatorOfUnitForTimeRange,lengthOfTimeRange) : no_copy;
  //   meta endStep g2end_step(
  //     startStep,
  //     stepUnits,
  //
  //     year,
  //     month,
  //     day,
  //     hour,
  //     minute,
  //     second,
  //
  //     yearOfEndOfOverallTimeInterval,
  //     monthOfEndOfOverallTimeInterval,
  //     dayOfEndOfOverallTimeInterval,
  //     hourOfEndOfOverallTimeInterval,
  //     minuteOfEndOfOverallTimeInterval,
  //     secondOfEndOfOverallTimeInterval,
  //
  //     indicatorOfUnitForTimeRange,
  //     lengthOfTimeRange,
  //     typeOfTimeIncrement,
  //     numberOfTimeRange
  //   ) : dump,no_copy;
  //
  //   meta stepRange g2step_range(startStep,endStep): dump;
  // } else {
  //   constant stepType  = "multiple steps";
  //   constant stepTypeInternal  = "multiple steps";
  //   constant endStep   = "unavailable";
  //   constant startStep   = "unavailable";
  //   constant stepRange = "unavailable";
  // }
  //
  // #meta  marsStep mars_step(stepRange,stepType) : edition_specific;
  //
  // alias ls.stepRange=stepRange;
  // alias mars.step=endStep;
  //
  // alias time.stepType=stepType;
  // alias time.stepRange=stepRange;
  // alias time.stepUnits=stepUnits;
  // alias time.dataDate=dataDate;
  // alias time.dataTime=dataTime;
  // alias time.startStep=startStep;
  // alias time.endStep=endStep;
  //
  // meta time.validityDate validity_date(date,dataTime,step,stepUnits,yearOfEndOfOverallTimeInterval,
  //     monthOfEndOfOverallTimeInterval,dayOfEndOfOverallTimeInterval) : no_copy;
  // meta time.validityTime validity_time(date,dataTime,step,stepUnits,hourOfEndOfOverallTimeInterval,
  //     minuteOfEndOfOverallTimeInterval) : no_copy;
};

} // namespace GRIB2
} // namespace SmartMet
