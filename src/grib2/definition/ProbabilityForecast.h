// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ProbabilityForecastImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/MemoryReader.h"
#include "../ProductDefinition.h"
#include "HorizontalSettings.h"
#include "ParameterSettings.h"
#include "PointInTimeSettings.h"
#include "ProbabilitySettings.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.5).*/

class ProbabilityForecast : public ProductDefinition {
public:
  ProbabilityForecast();
  virtual ~ProbabilityForecast();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const ParameterSettings *getParameter() const;
  void setParameter(ParameterSettings parameter);
  const PointInTimeSettings *getPointInTime() const;
  void setPointInTime(PointInTimeSettings pointInTime);
  const HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings horizontal);
  const ProbabilitySettings *getProbability() const;
  void setProbability(ProbabilitySettings probability);

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // # TEMPLATE 4.5, Probability forecasts at a horizontal level or in a horizontal layer at a point in time
  //
  // include "template.4.parameter.def"

  ParameterSettings mParameter;

  // include "template.4.point_in_time.def";

  PointInTimeSettings mPointInTime;

  // include "template.4.horizontal.def"

  HorizontalSettings mHorizontal;

  // include "template.4.probability.def"

  ProbabilitySettings mProbability;
};

} // namespace GRIB2
} // namespace SmartMet
