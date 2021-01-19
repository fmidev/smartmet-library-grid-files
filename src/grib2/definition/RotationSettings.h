// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotationSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.rotation).*/

class RotationSettings {
public:
  RotationSettings();
  virtual ~RotationSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::Int32_opt &getLatitudeOfSouthernPole() const;
  void setLatitudeOfSouthernPole(T::Int32_opt latitudeOfSouthernPole);
  const T::UInt32_opt &getLongitudeOfSouthernPole() const;
  void setLongitudeOfSouthernPole(T::UInt32_opt longitudeOfSouthernPole);
  float getAngleOfRotation() const;
  void setAngleOfRotation(float angleOfRotation);

protected:
  // # Copyright 2005-2019 ECMWF.
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
  // meta  geography.latitudeOfSouthernPoleInDegrees   scale(latitudeOfSouthernPole
  //                                                  ,one,grib2divider,truncateDegrees) : dump;
  // meta  geography.longitudeOfSouthernPoleInDegrees   g2lon(longitudeOfSouthernPole) : dump;
  //
  // #  Angle of rotation of projection
  // ieeefloat angleOfRotation : dump,edition_specific ;

  float mAngleOfRotation;

  // alias geography.angleOfRotationInDegrees=angleOfRotation;
  //
  // alias angleOfRotationOfProjection=angleOfRotation;
  //
  // alias is_rotated_grid=one;
};

} // namespace GRIB2
} // namespace SmartMet
