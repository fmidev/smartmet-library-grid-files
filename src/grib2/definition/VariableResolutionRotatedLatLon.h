// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'VariableResolutionRotatedLatLonImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "EarthShapeSettings.h"
#include "RotationSettings.h"
#include "VariableLatLonSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.5).*/

class VariableResolutionRotatedLatLon : public GridDefinition {
public:
  VariableResolutionRotatedLatLon();
  virtual ~VariableResolutionRotatedLatLon();

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
  VariableLatLonSettings *getVariableLatLon() const;
  void setVariableLatLon(VariableLatLonSettings &variableLatLon);
  RotationSettings *getRotation() const;
  void setRotation(RotationSettings &rotation);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.5, Variable resolution rotated latitude/longitude
  //
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

  // include "grib2/template.3.latlon_vares.def";

  mutable VariableLatLonSettings mVariableLatLon;

  // include "grib2/template.3.rotation.def";

  mutable RotationSettings mRotation;
};

} // namespace GRIB2
} // namespace SmartMet
