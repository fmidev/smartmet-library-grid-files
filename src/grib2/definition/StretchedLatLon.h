// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedLatLonImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/GridDefinition.h"
#include "grib2/definition/EarthShapeSettings.h"
#include "grib2/definition/LatLonSettings.h"
#include "grib2/definition/StretchingSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.2).*/

class StretchedLatLon : public GridDefinition {
public:
  StretchedLatLon();
  virtual ~StretchedLatLon();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const EarthShapeSettings *getEarthShape() const;
  const LatLonSettings *getLatLon() const;
  const StretchingSettings *getStretching() const;

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
  // # TEMPLATE 3.2, Stretched Latitude/longitude (or equidistant cylindrical,
  // or Plate Carree)
  //
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  // include "template.3.latlon.def";

  LatLonSettings mLatLon;

  // include "template.3.stretching.def";

  StretchingSettings mStretching;
};

} // namespace GRIB2
} // namespace SmartMet