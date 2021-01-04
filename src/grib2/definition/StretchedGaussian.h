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
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.42, Stretched Gaussian latitude/longitude
  //
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

  // include "grib2/template.3.gaussian.def";

  mutable GaussianSettings mGaussian;

  // include "grib2/template.3.stretching.def";

  mutable StretchingSettings mStretching;
};

} // namespace GRIB2
} // namespace SmartMet
