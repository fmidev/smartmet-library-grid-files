// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedRotatedLatLonImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "EarthShapeSettings.h"
#include "LatLonSettings.h"
#include "RotationSettings.h"
#include "StretchingSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.3).*/

class StretchedRotatedLatLon : public GridDefinition {
public:
  StretchedRotatedLatLon();
  virtual ~StretchedRotatedLatLon();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings &earthShape);
  LatLonSettings *getLatLon() const;
  void setLatLon(LatLonSettings &latLon);
  RotationSettings *getRotation() const;
  void setRotation(RotationSettings &rotation);
  StretchingSettings *getStretching() const;
  void setStretching(StretchingSettings &stretching);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.3, Stretched and Rotated Latitude/longitude (or equidistant cylindrical, or Plate Carree)
  //
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

  // include "grib2/template.3.latlon.def";

  mutable LatLonSettings mLatLon;

  // include "grib2/template.3.rotation.def";

  mutable RotationSettings mRotation;

  // include "grib2/template.3.stretching.def";

  mutable StretchingSettings mStretching;

  //
};

} // namespace GRIB2
} // namespace SmartMet
