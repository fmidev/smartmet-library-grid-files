// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GridSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/definition/ResolutionSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.grid).*/

class GridSettings {
public:
  GridSettings();
  virtual ~GridSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt32_opt &getNi() const;
  const T::UInt32_opt &getNj() const;
  const T::UInt32_opt &getBasicAngleOfTheInitialProductionDomain() const;
  const T::UInt32_opt &getSubdivisionsOfBasicAngle() const;
  const T::Int32_opt &getLatitudeOfFirstGridPoint() const;
  const T::Int32_opt &getLongitudeOfFirstGridPoint() const;
  const ResolutionSettings *getResolution() const;
  const T::Int32_opt &getLatitudeOfLastGridPoint() const;
  const T::Int32_opt &getLongitudeOfLastGridPoint() const;

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

  // transient
  // mBasicAngle=basicAngleOfTheInitialProductionDomain*oneMillionConstant;
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
  // #  Subdivisions of basic angle used to define extreme longitudes and
  // latitudes, and direction increments
  // unsigned[4] subdivisionsOfBasicAngle = missing() : can_be_missing;

  T::UInt32_opt mSubdivisionsOfBasicAngle;

  //
  // transient angleDivisor = 1000000;
  // when (missing(subdivisionsOfBasicAngle) || subdivisionsOfBasicAngle == 0) {
  //   set angleDivisor  = 1000000;
  //   set angularPrecision = 1000000;
  // } else {
  //   set angleDivisor  = subdivisionsOfBasicAngle;
  //   set angularPrecision = subdivisionsOfBasicAngle;
  // }
  //
  // #  La1 - latitude of first grid point
  // signed[4] latitudeOfFirstGridPoint : edition_specific ;

  T::Int32_opt mLatitudeOfFirstGridPoint;

  // alias La1  = latitudeOfFirstGridPoint;
  // #meta latitudeOfFirstGridPointInMicrodegrees
  // times(latitudeOfFirstGridPoint,mAngleMultiplier,angleDivisor) : no_copy;
  //
  // #  Lo1 - longitude of first grid point
  //
  // signed[4] longitudeOfFirstGridPoint ;

  T::Int32_opt mLongitudeOfFirstGridPoint;

  // alias Lo1  = longitudeOfFirstGridPoint;
  // #meta longitudeOfFirstGridPointInMicrodegrees
  // times(longitudeOfFirstGridPoint,mAngleMultiplier,angleDivisor) : no_copy;
  //
  // include "template.3.resolution_flags.def"

  ResolutionSettings mResolution;

  //
  // #  La2 - latitude of last grid point
  // signed[4] latitudeOfLastGridPoint :  edition_specific;

  T::Int32_opt mLatitudeOfLastGridPoint;

  // alias La2 =  latitudeOfLastGridPoint;
  // #meta latitudeOfLastGridPointInMicrodegrees
  // times(latitudeOfLastGridPoint,mAngleMultiplier,angleDivisor) : no_copy;
  //
  // #  Lo2 - longitude of last grid point
  // signed[4] longitudeOfLastGridPoint :  edition_specific ;

  T::Int32_opt mLongitudeOfLastGridPoint;

  // alias Lo2 =  longitudeOfLastGridPoint;
  // #meta longitudeOfLastGridPointInMicrodegrees
  // times(longitudeOfLastGridPoint,mAngleMultiplier,angleDivisor) : no_copy;
  //
};

} // namespace GRIB2
} // namespace SmartMet
