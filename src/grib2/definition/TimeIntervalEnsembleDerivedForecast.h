// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalEnsembleDerivedForecastImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "DerivedSettings.h"
#include "HorizontalSettings.h"
#include "ParameterSettings.h"
#include "StatisticalSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.12).*/

class TimeIntervalEnsembleDerivedForecast : public ProductDefinition {
public:
  TimeIntervalEnsembleDerivedForecast();
  ~TimeIntervalEnsembleDerivedForecast() override;

  uint getTemplateNumber() const override;
  ProductDefinition *createProductDefinition() const override;
  void read(MemoryReader &memoryReader) override;
  void write(DataWriter &dataWriter) override;
  void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const override;
  void print(std::ostream &stream, uint level, uint optionFlags) const override;
  virtual T::Hash countHash();

  ParameterSettings *getParameter() const override;
  void setParameter(ParameterSettings &parameter);
  HorizontalSettings *getHorizontal() const override;
  void setHorizontal(HorizontalSettings &horizontal);
  DerivedSettings *getDerived() const override;
  void setDerived(DerivedSettings &derived);
  StatisticalSettings *getStatistical() const override;
  void setStatistical(StatisticalSettings &statistical);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.12, Derived forecasts based on all ensemble members at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval
  //
  // include "grib2/template.4.parameter.def"

  mutable ParameterSettings mParameter;

  // include "grib2/template.4.horizontal.def"

  mutable HorizontalSettings mHorizontal;

  // include "grib2/template.4.derived.def"

  mutable DerivedSettings mDerived;

  // include "grib2/template.4.statistical.def"

  mutable StatisticalSettings mStatistical;
};

} // namespace GRIB2
} // namespace SmartMet
