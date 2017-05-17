// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the
//   'TimeIntervalAtmosphericChemicalEnsembleProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/ProductDefinition.h"
#include "grib2/definition/EpsSettings.h"
#include "grib2/definition/HorizontalSettings.h"
#include "grib2/definition/ParameterChemicalSettings.h"
#include "grib2/definition/StatisticalSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.43).*/

class TimeIntervalAtmosphericChemicalEnsembleProduct
    : public ProductDefinition {
public:
  TimeIntervalAtmosphericChemicalEnsembleProduct();
  virtual ~TimeIntervalAtmosphericChemicalEnsembleProduct();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const ParameterChemicalSettings *getParameterChemical() const;
  const HorizontalSettings *getHorizontal() const;
  const EpsSettings *getEps() const;
  const StatisticalSettings *getStatistical() const;

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
  // # TEMPLATE 4.43, Individual ensemble forecast, control and perturbed, at a
  // horizontal level or in a horizontal layer in a continuous or non-continuous
  // time interval
  //
  // include "template.4.parameter_chemical.def"

  ParameterChemicalSettings mParameterChemical;

  // include "template.4.horizontal.def"

  HorizontalSettings mHorizontal;

  // include "template.4.eps.def"

  EpsSettings mEps;

  // include "template.4.statistical.def"

  StatisticalSettings mStatistical;
};

} // namespace GRIB2
} // namespace SmartMet
