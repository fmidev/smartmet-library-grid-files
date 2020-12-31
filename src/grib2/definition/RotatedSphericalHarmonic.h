// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotatedSphericalHarmonicImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "RotationSettings.h"
#include "SphericalHarmonicSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.51).*/

class RotatedSphericalHarmonic : public GridDefinition {
public:
  RotatedSphericalHarmonic();
  virtual ~RotatedSphericalHarmonic();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  SphericalHarmonicSettings *getSphericalHarmonic() const;
  void setSphericalHarmonic(SphericalHarmonicSettings &sphericalHarmonic);
  RotationSettings *getRotation() const;
  void setRotation(RotationSettings &rotation);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.51, Rotated spherical harmonic coefficients
  //
  // include "grib2/template.3.spherical_harmonics.def";

  mutable SphericalHarmonicSettings mSphericalHarmonic;

  // include "grib2/template.3.rotation.def";

  mutable RotationSettings mRotation;
};

} // namespace GRIB2
} // namespace SmartMet
