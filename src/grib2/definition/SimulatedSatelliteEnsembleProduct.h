// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SimulatedSatelliteEnsembleProductImpl.*'
//   files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/ProductDefinition.h"
#include "grib2/definition/EpsSettings.h"
#include "grib2/definition/SimulatedSatelliteProduct.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.33).*/

class SimulatedSatelliteEnsembleProduct : public ProductDefinition {
public:
  SimulatedSatelliteEnsembleProduct();
  virtual ~SimulatedSatelliteEnsembleProduct();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const SimulatedSatelliteProduct *getSimulatedSatelliteProduct() const;
  const EpsSettings *getEps() const;

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
  // # TEMPLATE 4.33, Individual ensemble forecast, control and perturbed, at a
  // horizontal level or in a horizontal layer at a point in time for simulated
  // (synthetic) satellite data
  //
  // include "template.4.32.def"

  SimulatedSatelliteProduct mSimulatedSatelliteProduct;

  // include "template.4.eps.def"

  EpsSettings mEps;

  //
  // alias instrument = instrumentType;
  // alias ident = satelliteNumber;
  //
};

} // namespace GRIB2
} // namespace SmartMet