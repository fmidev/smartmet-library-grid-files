// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'Product_68Impl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "EpsSettings.h"
#include "HorizontalSettings.h"
#include "StatisticalSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.68).*/

class Product_68 : public ProductDefinition {
public:
  Product_68();
  virtual ~Product_68();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings &horizontal);
  EpsSettings *getEps() const;
  void setEps(EpsSettings &eps);
  StatisticalSettings *getStatistical() const;
  void setStatistical(StatisticalSettings &statistical);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.68, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval for
  // atmospheric chemical constituents based on a distribution function
  //
  // include "grib2/template.4.parameter_chemical_distribution.def"

  // include "grib2/template.4.horizontal.def"

  mutable HorizontalSettings mHorizontal;

  // include "grib2/template.4.eps.def"

  mutable EpsSettings mEps;

  // include "grib2/template.4.statistical.def"

  mutable StatisticalSettings mStatistical;
};

} // namespace GRIB2
} // namespace SmartMet
