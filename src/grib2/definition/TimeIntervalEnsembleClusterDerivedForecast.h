// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalEnsembleClusterDerivedForecastImpl.*' files.
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
#include "RectangularClusterSettings.h"
#include "StatisticalSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.13).*/

class TimeIntervalEnsembleClusterDerivedForecast : public ProductDefinition {
public:
  TimeIntervalEnsembleClusterDerivedForecast();
  virtual ~TimeIntervalEnsembleClusterDerivedForecast();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  ParameterSettings *getParameter() const;
  void setParameter(ParameterSettings &parameter);
  HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings &horizontal);
  DerivedSettings *getDerived() const;
  void setDerived(DerivedSettings &derived);
  RectangularClusterSettings *getRectangularCluster() const;
  void setRectangularCluster(RectangularClusterSettings &rectangularCluster);
  StatisticalSettings *getStatistical() const;
  void setStatistical(StatisticalSettings &statistical);
  const T::UInt8_opt &getEnsembleForecastNumbers() const;
  void setEnsembleForecastNumbers(T::UInt8_opt ensembleForecastNumbers);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.13, Derived forecasts based on a cluster of ensemble members over a rectangular area at a horizontal level or in a horizontal layer in a continuous or
  // non-continuous time interval
  //
  // include "grib2/template.4.parameter.def"

  mutable ParameterSettings mParameter;

  // include "grib2/template.4.horizontal.def"

  mutable HorizontalSettings mHorizontal;

  // include "grib2/template.4.derived.def"

  mutable DerivedSettings mDerived;

  // include "grib2/template.4.rectangular_cluster.def"

  mutable RectangularClusterSettings mRectangularCluster;

  // include "grib2/template.4.statistical.def"

  mutable StatisticalSettings mStatistical;

  //
  // ensembleForecastNumbersList list(numberOfForecastsInTheCluster) {
  //   unsigned[1] ensembleForecastNumbers : dump;

  T::UInt8_opt mEnsembleForecastNumbers;

  // }
  //
};

} // namespace GRIB2
} // namespace SmartMet
