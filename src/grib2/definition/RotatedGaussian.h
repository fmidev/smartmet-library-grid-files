// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotatedGaussianImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/GridDefinition.h"
#include "grib2/definition/EarthShapeSettings.h"
#include "grib2/definition/GaussianSettings.h"
#include "grib2/definition/RotationSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.41).*/

class RotatedGaussian : public GridDefinition {
public:
  RotatedGaussian();
  virtual ~RotatedGaussian();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings earthShape);
  const GaussianSettings *getGaussian() const;
  void setGaussian(GaussianSettings gaussian);
  const RotationSettings *getRotation() const;
  void setRotation(RotationSettings rotation);

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
  // # TEMPLATE 3.41, Rotated Gaussian latitude/longitude
  //
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  // include "template.3.gaussian.def";

  GaussianSettings mGaussian;

  // include "template.3.rotation.def";

  RotationSettings mRotation;
};

} // namespace GRIB2
} // namespace SmartMet
