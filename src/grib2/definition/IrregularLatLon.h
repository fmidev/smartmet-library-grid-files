// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'IrregularLatLonImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "EarthShapeSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.130).*/

class IrregularLatLon : public GridDefinition {
public:
  IrregularLatLon();
  virtual ~IrregularLatLon();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings &earthShape);
  const T::Int32_opt &getLatitude() const;
  void setLatitude(T::Int32_opt latitude);
  const T::Int32_opt &getLongitude() const;
  void setLongitude(T::Int32_opt longitude);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.130, Irregular Latitude/longitude grid
  //
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

  //
  // points list(numberOfDataPoints) {
  //     signed[4] latitude;

  T::Int32_opt mLatitude;

  //     signed[4] longitude;

  T::Int32_opt mLongitude;

  // }
};

} // namespace GRIB2
} // namespace SmartMet
