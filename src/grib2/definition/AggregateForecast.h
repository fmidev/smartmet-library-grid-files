// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AggregateForecastImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/ProductDefinition.h"
#include "grib2/definition/HorizontalSettings.h"
#include "grib2/definition/ParameterSettings.h"
#include "grib2/definition/StatisticalSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.8).*/

class AggregateForecast : public ProductDefinition {
public:
  AggregateForecast();
  virtual ~AggregateForecast();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const ParameterSettings *getParameter() const;
  const HorizontalSettings *getHorizontal() const;
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
  // # TEMPLATE 4.8, Average, accumulation, and/or extreme values or other
  // statistically processed values at a horizontal level or in a horizontal
  // layer in a continuous or non-continuous time interval
  //
  // include "template.4.parameter.def"

  ParameterSettings mParameter;

  // include "template.4.horizontal.def"

  HorizontalSettings mHorizontal;

  // include "template.4.statistical.def"

  StatisticalSettings mStatistical;
};

} // namespace GRIB2
} // namespace SmartMet
