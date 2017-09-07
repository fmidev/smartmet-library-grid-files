// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ReforecastSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.reforecast).*/

class ReforecastSettings {
public:
  ReforecastSettings();
  virtual ~ReforecastSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt16_opt &getYearOfModelVersion() const;
  void setYearOfModelVersion(T::UInt16_opt yearOfModelVersion);
  const T::UInt8_opt &getMonthOfModelVersion() const;
  void setMonthOfModelVersion(T::UInt8_opt monthOfModelVersion);
  const T::UInt8_opt &getDayOfModelVersion() const;
  void setDayOfModelVersion(T::UInt8_opt dayOfModelVersion);
  const T::UInt8_opt &getHourOfModelVersion() const;
  void setHourOfModelVersion(T::UInt8_opt hourOfModelVersion);
  const T::UInt8_opt &getMinuteOfModelVersion() const;
  void setMinuteOfModelVersion(T::UInt8_opt minuteOfModelVersion);
  const T::UInt8_opt &getSecondOfModelVersion() const;
  void setSecondOfModelVersion(T::UInt8_opt secondOfModelVersion);

protected:
  // label "S2S reforecasts";
  //
  // # The Model Version Date
  // # This is the date when the reforecast is produced with a particular version of the model
  //
  // unsigned[2] YearOfModelVersion   = 0: edition_specific;

  T::UInt16_opt mYearOfModelVersion;

  // unsigned[1] MonthOfModelVersion  = 0: edition_specific;

  T::UInt8_opt mMonthOfModelVersion;

  // unsigned[1] DayOfModelVersion    = 0: edition_specific;

  T::UInt8_opt mDayOfModelVersion;

  // unsigned[1] HourOfModelVersion   = 0: edition_specific;

  T::UInt8_opt mHourOfModelVersion;

  // unsigned[1] MinuteOfModelVersion = 0: edition_specific;

  T::UInt8_opt mMinuteOfModelVersion;

  // unsigned[1] SecondOfModelVersion = 0: edition_specific;

  T::UInt8_opt mSecondOfModelVersion;

  //
  // meta modelVersionDate  g2date(YearOfModelVersion,MonthOfModelVersion,DayOfModelVersion) : dump;
  // meta modelVersionTime  time(HourOfModelVersion, MinuteOfModelVersion, SecondOfModelVersion) : dump;
  //
  // constant isHindcast = 1;
};

} // namespace GRIB2
} // namespace SmartMet
