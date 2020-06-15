// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'Product_56Impl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "EpsSettings.h"
#include "HorizontalSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.56).*/

class Product_56 : public ProductDefinition {
public:
  Product_56();
  Product_56(const Product_56 &other);
  virtual ~Product_56();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings &horizontal);
  EpsSettings *getEps() const;
  void setEps(EpsSettings &eps);
  const T::UInt8_opt &getPerturbationNumber() const;
  void setPerturbationNumber(T::UInt8_opt perturbationNumber);
  const T::UInt8_opt &getNumberOfForecastsInEnsemble() const;
  void setNumberOfForecastsInEnsemble(T::UInt8_opt numberOfForecastsInEnsemble);

protected:
  // # Copyright 2005-2017 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  // # TEMPLATE 4.56, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for spatio-temporal changing tile
  // parameters
  //
  // # Note: This template is deprecated. Template 4.59 should be used instead.
  //
  // include "grib2/template.4.parameter_tile.def"

  // include "grib2/template.4.horizontal.def"

  mutable HorizontalSettings mHorizontal;

  //
  // # Note: This template is missing the entry:
  // #  Type of ensemble forecast
  // # which is present in all other templates with EPS info! Mistake by WMO?
  //
  // # So we cannot include the eps template due to this missing entry!

  // # include "grib2/template.4.eps.def"

  mutable EpsSettings mEps;

  // # Have to manually define the keys
  // unsigned[1] perturbationNumber  : dump;

  T::UInt8_opt mPerturbationNumber;

  // alias number=perturbationNumber;
  //
  // unsigned[1] numberOfForecastsInEnsemble  : dump;

  T::UInt8_opt mNumberOfForecastsInEnsemble;

  // alias totalNumber=numberOfForecastsInEnsemble;
};

} // namespace GRIB2
} // namespace SmartMet