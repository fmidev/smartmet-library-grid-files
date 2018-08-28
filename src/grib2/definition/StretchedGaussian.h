// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedGaussianImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "EarthShapeSettings.h"
#include "GaussianSettings.h"
#include "StretchingSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.42).*/

class StretchedGaussian : public GridDefinition {
public:
  StretchedGaussian();
  StretchedGaussian(const StretchedGaussian &other);
  virtual ~StretchedGaussian();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings &earthShape);
  GaussianSettings *getGaussian() const;
  void setGaussian(GaussianSettings &gaussian);
  StretchingSettings *getStretching() const;
  void setStretching(StretchingSettings &stretching);

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
  // # TEMPLATE 3.42, Stretched Gaussian latitude/longitude
  //
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  // include "template.3.gaussian.def";

  GaussianSettings mGaussian;

  // include "template.3.stretching.def";

  StretchingSettings mStretching;
};

} // namespace GRIB2
} // namespace SmartMet
