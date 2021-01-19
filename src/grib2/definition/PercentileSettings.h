// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PercentileSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.percentile).*/

class PercentileSettings {
public:
  PercentileSettings();
  virtual ~PercentileSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getPercentileValue() const;
  void setPercentileValue(T::UInt8_opt percentileValue);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // #  Percentile value
  // # (from 100% to 0%)
  // unsigned[1] percentileValue  : dump;

  T::UInt8_opt mPercentileValue;
};

} // namespace GRIB2
} // namespace SmartMet
