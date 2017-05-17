// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'EarthShapeSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template
 * (3.shape_of_the_earth).*/

class EarthShapeSettings {
public:
  EarthShapeSettings();
  virtual ~EarthShapeSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getShapeOfTheEarth() const;
  const T::UInt8_opt &getScaleFactorOfRadiusOfSphericalEarth() const;
  const T::UInt32_opt &getScaledValueOfRadiusOfSphericalEarth() const;
  const T::UInt8_opt &getScaleFactorOfEarthMajorAxis() const;
  const T::UInt32_opt &getScaledValueOfEarthMajorAxis() const;
  const T::UInt8_opt &getScaleFactorOfEarthMinorAxis() const;
  const T::UInt32_opt &getScaledValueOfEarthMinorAxis() const;

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
  //
  // codetable[1] shapeOfTheEarth ('3.2.table',masterDir,localDir) : dump;

  T::UInt8_opt mShapeOfTheEarth;

  //
  // #  Scale factor of radius of spherical earth
  // unsigned[1] scaleFactorOfRadiusOfSphericalEarth = missing() :
  // can_be_missing, edition_specific;

  T::UInt8_opt mScaleFactorOfRadiusOfSphericalEarth;

  //
  // #  Scaled value of radius of spherical earth
  // unsigned[4] scaledValueOfRadiusOfSphericalEarth = missing():
  // can_be_missing, edition_specific;

  T::UInt32_opt mScaledValueOfRadiusOfSphericalEarth;

  //
  // #  Scale factor of major axis of oblate spheroid earth
  // unsigned[1] scaleFactorOfEarthMajorAxis = missing(): can_be_missing,
  // edition_specific;

  T::UInt8_opt mScaleFactorOfEarthMajorAxis;

  // alias
  // scaleFactorOfMajorAxisOfOblateSpheroidEarth=scaleFactorOfEarthMajorAxis;
  //
  // #  Scaled value of major axis of oblate spheroid earth
  // unsigned[4] scaledValueOfEarthMajorAxis = missing(): can_be_missing,
  // edition_specific;

  T::UInt32_opt mScaledValueOfEarthMajorAxis;

  // alias
  // scaledValueOfMajorAxisOfOblateSpheroidEarth=scaledValueOfEarthMajorAxis;
  //
  // #  Scale factor of minor axis of oblate spheroid earth
  // unsigned[1] scaleFactorOfEarthMinorAxis = missing(): can_be_missing,
  // edition_specific;

  T::UInt8_opt mScaleFactorOfEarthMinorAxis;

  // alias
  // scaleFactorOfMinorAxisOfOblateSpheroidEarth=scaleFactorOfEarthMinorAxis ;
  //
  // #  Scaled value of minor axis of oblate spheroid earth
  // unsigned[4] scaledValueOfEarthMinorAxis = missing(): can_be_missing,
  // edition_specific;

  T::UInt32_opt mScaledValueOfEarthMinorAxis;

  // alias
  // scaledValueOfMinorAxisOfOblateSpheroidEarth=scaledValueOfEarthMinorAxis;
  //
  // alias earthIsOblate=one;
  //
  // _if (shapeOfTheEarth == 0) {
  //   transient radius=6367470;
  //   alias radiusOfTheEarth=radius;
  //   alias radiusInMetres=radius;
  //   alias earthIsOblate=zero;
  // }
  // _if (shapeOfTheEarth == 1){
  //   meta radius from_scale_factor_scaled_value(
  //                           scaleFactorOfRadiusOfSphericalEarth,
  //                           scaledValueOfRadiusOfSphericalEarth);
  //   alias radiusOfTheEarth=radius;
  //   alias radiusInMetres=radius;
  //   alias earthIsOblate=zero;
  // }
  // _if (shapeOfTheEarth == 6){
  //   transient radius=6371229;
  //   alias radiusOfTheEarth=radius;
  //   alias radiusInMetres=radius;
  //   alias earthIsOblate=zero;
  // }
  //
  // _if (shapeOfTheEarth == 8){
  //   transient radius=6371200;
  //   alias radiusOfTheEarth=radius;
  //   alias radiusInMetres=radius;
  //   alias earthIsOblate=zero;
  // }
  //
  //
  // # Oblate spheroid cases
  // _if (shapeOfTheEarth == 2){
  //   # IAU in 1965
  //   transient earthMajorAxis = 6378160.0;
  //   transient earthMinorAxis = 6356775.0;
  //   alias earthMajorAxisInMetres=earthMajorAxis;
  //   alias earthMinorAxisInMetres=earthMinorAxis;
  // }
  // _if (shapeOfTheEarth == 4 || shapeOfTheEarth == 5){
  //   # 4 -> IAG-GRS80 model
  //   # 5 -> WGS84
  //   transient earthMajorAxis = 6378137.0;
  //   transient earthMinorAxis = 6356752.314;
  //   alias earthMajorAxisInMetres=earthMajorAxis;
  //   alias earthMinorAxisInMetres=earthMinorAxis;
  // }
  // _if (shapeOfTheEarth == 9){
  //   # Airy 1830
  //   transient earthMajorAxis = 6377563.396;
  //   transient earthMinorAxis = 6356256.909;
  //   alias earthMajorAxisInMetres=earthMajorAxis;
  //   alias earthMinorAxisInMetres=earthMinorAxis;
  // }
};

} // namespace GRIB2
} // namespace SmartMet
