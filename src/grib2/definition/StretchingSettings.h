// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchingSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.stretching).*/

class StretchingSettings {
public:
  StretchingSettings();
  StretchingSettings(const StretchingSettings &other);
  virtual ~StretchingSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::Int32_opt &getLatitudeOfThePoleOfStretching() const;
  void setLatitudeOfThePoleOfStretching(T::Int32_opt latitudeOfThePoleOfStretching);
  const T::Int32_opt &getLongitudeOfThePoleOfStretching() const;
  void setLongitudeOfThePoleOfStretching(T::Int32_opt longitudeOfThePoleOfStretching);
  const T::UInt32_opt &getStretchingFactorScaled() const;
  void setStretchingFactorScaled(T::UInt32_opt stretchingFactorScaled);

protected:
  // # Copyright 2005-2017 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // #  Latitude of the pole of stretching
  // signed[4] latitudeOfThePoleOfStretching  : edition_specific,no_copy;

  T::Int32_opt mLatitudeOfThePoleOfStretching;

  //
  // #  Longitude of the pole of stretching
  // signed[4] longitudeOfThePoleOfStretching  : edition_specific,no_copy;

  T::Int32_opt mLongitudeOfThePoleOfStretching;

  //
  // meta  geography.latitudeOfStretchingPoleInDegrees
  //       scale(latitudeOfThePoleOfStretching,oneConstant,grib2divider,truncateDegrees) : dump;
  // meta  geography.longitudeOfStretchingPoleInDegrees
  //       scale(longitudeOfThePoleOfStretching,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // #  Stretching factor
  // unsigned[4] stretchingFactorScaled  : edition_specific,no_copy;

  T::UInt32_opt mStretchingFactorScaled;

  //
  // meta  geography.stretchingFactor
  //       scale(stretchingFactorScaled,oneConstant,grib2divider) : dump;
  //
};

} // namespace GRIB2
} // namespace SmartMet
