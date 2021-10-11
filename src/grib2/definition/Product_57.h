// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'Product_57Impl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "HorizontalSettings.h"
#include "PointInTimeSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.57).*/

class Product_57 : public ProductDefinition {
public:
  Product_57();
  virtual ~Product_57();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  PointInTimeSettings *getPointInTime() const;
  void setPointInTime(PointInTimeSettings &pointInTime);
  HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings &horizontal);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.57, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for atmospheric chemical constituents based on a distribution function
  //
  // include "grib2/template.4.parameter_chemical_distribution.def";

  // include "grib2/template.4.point_in_time.def";

  mutable PointInTimeSettings mPointInTime;

  // include "grib2/template.4.horizontal.def";

  mutable HorizontalSettings mHorizontal;
};

} // namespace GRIB2
} // namespace SmartMet
