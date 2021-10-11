// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AggregateAerosolProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "HorizontalSettings.h"
#include "ParameterAerosolSettings.h"
#include "StatisticalSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.46).*/

class AggregateAerosolProduct : public ProductDefinition {
public:
  AggregateAerosolProduct();
  virtual ~AggregateAerosolProduct();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  ParameterAerosolSettings *getParameterAerosol() const;
  void setParameterAerosol(ParameterAerosolSettings &parameterAerosol);
  HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings &horizontal);
  StatisticalSettings *getStatistical() const;
  void setStatistical(StatisticalSettings &statistical);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.46, Average, accumulation, and/or extreme values or other statistically processed values at a horizontal level or in a horizontal layer in a continuous or
  // non-continuous time interval for aerosol
  //
  // include "grib2/template.4.parameter_aerosol.def"

  mutable ParameterAerosolSettings mParameterAerosol;

  // include "grib2/template.4.horizontal.def"

  mutable HorizontalSettings mHorizontal;

  // include "grib2/template.4.statistical.def"

  mutable StatisticalSettings mStatistical;
};

} // namespace GRIB2
} // namespace SmartMet
