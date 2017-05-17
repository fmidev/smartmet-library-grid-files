// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotationSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.rotation).*/

class RotationSettings {
public:
  RotationSettings();
  virtual ~RotationSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::Int32_opt &getLatitudeOfSouthernPole() const;
  const T::UInt32_opt &getLongitudeOfSouthernPole() const;
  float getAngleOfRotation() const;

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
  // #  Latitude of the southern pole of projection
  // signed[4] latitudeOfSouthernPole : no_copy;

  T::Int32_opt mLatitudeOfSouthernPole;

  // alias latitudeOfTheSouthernPoleOfProjection=latitudeOfSouthernPole;
  //
  // #  Longitude of the southern pole of projection
  // unsigned[4] longitudeOfSouthernPole : no_copy;

  T::UInt32_opt mLongitudeOfSouthernPole;

  // alias longitudeOfTheSouthernPoleOfProjection=longitudeOfSouthernPole;
  //
  // meta  geography.latitudeOfSouthernPoleInDegrees
  // scale(latitudeOfSouthernPole
  //                                                  ,one,grib2divider,truncateDegrees)
  //                                                  : dump;
  // meta  geography.longitudeOfSouthernPoleInDegrees
  // g2lon(longitudeOfSouthernPole) : dump;
  //
  // #  Angle of rotation of projection
  // ieeefloat angleOfRotation : dump,edition_specific ;

  float mAngleOfRotation;

  // alias geography.angleOfRotationInDegrees=angleOfRotation;
  //
  // alias angleOfRotationOfProjection=angleOfRotation;
  //
};

} // namespace GRIB2
} // namespace SmartMet
