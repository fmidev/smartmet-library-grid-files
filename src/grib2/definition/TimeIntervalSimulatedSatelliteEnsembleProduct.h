// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalSimulatedSatelliteEnsembleProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "EpsSettings.h"
#include "SimulatedSatelliteProduct.h"
#include "StatisticalSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.34).*/

class TimeIntervalSimulatedSatelliteEnsembleProduct : public ProductDefinition {
public:
  TimeIntervalSimulatedSatelliteEnsembleProduct();
  virtual ~TimeIntervalSimulatedSatelliteEnsembleProduct();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  SimulatedSatelliteProduct *getSimulatedSatelliteProduct() const;
  void setSimulatedSatelliteProduct(SimulatedSatelliteProduct &simulatedSatelliteProduct);
  EpsSettings *getEps() const;
  void setEps(EpsSettings &eps);
  StatisticalSettings *getStatistical() const;
  void setStatistical(StatisticalSettings &statistical);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.34, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer, in a continuous or non-continuous interval for simulated
  // (synthetic) satellite data
  //
  // include "grib2/template.4.32.def"

  mutable SimulatedSatelliteProduct mSimulatedSatelliteProduct;

  // include "grib2/template.4.eps.def"

  mutable EpsSettings mEps;

  // include "grib2/template.4.statistical.def"

  mutable StatisticalSettings mStatistical;

  //
  // alias instrument = instrumentType;
  // alias ident = satelliteNumber;
  //
};

} // namespace GRIB2
} // namespace SmartMet
