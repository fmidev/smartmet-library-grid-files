// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'VariableLatLonSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/MemoryReader.h"
#include "ResolutionSettings.h"
#include "ScanningModeSettings.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.latlon_vares).*/

class VariableLatLonSettings {
public:
  VariableLatLonSettings();
  virtual ~VariableLatLonSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt32_opt &getNi() const;
  void setNi(T::UInt32_opt ni);
  const T::UInt32_opt &getNj() const;
  void setNj(T::UInt32_opt nj);
  const T::UInt32_opt &getBasicAngleOfTheInitialProductionDomain() const;
  void setBasicAngleOfTheInitialProductionDomain(T::UInt32_opt basicAngleOfTheInitialProductionDomain);
  const T::UInt32_opt &getSubdivisionsOfBasicAngle() const;
  void setSubdivisionsOfBasicAngle(T::UInt32_opt subdivisionsOfBasicAngle);
  const ResolutionSettings *getResolution() const;
  void setResolution(ResolutionSettings resolution);
  const ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings scanningMode);
  const T::UInt32_opt &getLongitudes() const;
  void setLongitudes(T::UInt32_opt longitudes);
  const T::Int32_opt &getLatitudes() const;
  void setLatitudes(T::Int32_opt latitudes);

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
  // unsigned[4] Ni : can_be_missing,dump;

  T::UInt32_opt mNi;

  // alias numberOfPointsAlongAParallel=Ni;
  // alias Nx = Ni;
  //
  // unsigned[4] Nj : dump;

  T::UInt32_opt mNj;

  // alias numberOfPointsAlongAMeridian=Nj;
  // alias Ny = Nj;
  //
  // alias geography.Ni=Ni;
  // alias geography.Nj=Nj;
  //
  // #  Basic angle of the initial production domain
  // unsigned[4] basicAngleOfTheInitialProductionDomain = 0;

  T::UInt32_opt mBasicAngleOfTheInitialProductionDomain;

  // transient mBasicAngle=basicAngleOfTheInitialProductionDomain*oneMillionConstant;
  // transient angleMultiplier  = 1;
  // transient mAngleMultiplier = 1000000;
  // when (basicAngleOfTheInitialProductionDomain == 0) {
  //   set angleMultiplier  = 1;
  //   set mAngleMultiplier = 1000000;
  // } else {
  //   set angleMultiplier  = basicAngleOfTheInitialProductionDomain;
  //   set mAngleMultiplier = mBasicAngle;
  // }
  //
  // #  Subdivisions of basic angle used to define extreme longitudes and latitudes, and direction increments
  // unsigned[4] subdivisionsOfBasicAngle = missing() : can_be_missing;

  T::UInt32_opt mSubdivisionsOfBasicAngle;

  //
  // transient angleDivisor = 1000000;
  // when (missing(subdivisionsOfBasicAngle) || subdivisionsOfBasicAngle == 0) {
  //   set angleDivisor  = 1000000;
  // } else {
  //   set angleDivisor  = subdivisionsOfBasicAngle;
  // }
  //
  // include "template.3.resolution_flags.def"

  ResolutionSettings mResolution;

  //
  // include "template.3.scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // longitudesList list(Ni) {
  //     unsigned[4] longitudes;

  T::UInt32_opt mLongitudes;

  // }
  //
  // latitudesList list(Nj) {
  //     signed[4] latitudes;

  T::Int32_opt mLatitudes;

  // }
  //
};

} // namespace GRIB2
} // namespace SmartMet
