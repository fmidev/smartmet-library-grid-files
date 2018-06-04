// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GridStretchingSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template (grid_stretching).*/

class GridStretchingSettings {
public:
  GridStretchingSettings();
  virtual ~GridStretchingSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  std::int24_t getLatitudeOfStretchingPole() const;
  void setLatitudeOfStretchingPole(std::int24_t latitudeOfStretchingPole);
  std::int24_t getLongitudeOfStretchingPole() const;
  void setLongitudeOfStretchingPole(std::int24_t longitudeOfStretchingPole);
  ibmfloat getStretchingFactor() const;
  void setStretchingFactor(ibmfloat stretchingFactor);

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
  // signed[3] latitudeOfStretchingPole : edition_specific,no_copy;

  std::int24_t mLatitudeOfStretchingPole;

  // signed[3] longitudeOfStretchingPole : edition_specific,no_copy;

  std::int24_t mLongitudeOfStretchingPole;

  //
  // meta  geography.latitudeOfStretchingPoleInDegrees
  //       scale(latitudeOfStretchingPole,oneConstant,grib1divider,truncateDegrees) : dump;
  // meta  geography.longitudeOfStretchingPoleInDegrees
  //       scale(longitudeOfStretchingPole,oneConstant,grib1divider,truncateDegrees) : dump;
  // ibmfloat stretchingFactor : dump;

  ibmfloat mStretchingFactor;

  // alias geography.stretchingFactor=stretchingFactor;
  //
};

} // namespace GRIB1
} // namespace SmartMet
