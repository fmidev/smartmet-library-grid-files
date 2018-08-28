// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalEnsembleReforecastImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "EpsSettings.h"
#include "HorizontalSettings.h"
#include "ParameterSettings.h"
#include "ReforecastSettings.h"
#include "StatisticalSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.61).*/

class TimeIntervalEnsembleReforecast : public ProductDefinition {
public:
  TimeIntervalEnsembleReforecast();
  TimeIntervalEnsembleReforecast(const TimeIntervalEnsembleReforecast &other);
  virtual ~TimeIntervalEnsembleReforecast();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  ParameterSettings *getParameter() const;
  void setParameter(ParameterSettings &parameter);
  HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings &horizontal);
  EpsSettings *getEps() const;
  void setEps(EpsSettings &eps);
  ReforecastSettings *getReforecast() const;
  void setReforecast(ReforecastSettings &reforecast);
  StatisticalSettings *getStatistical() const;
  void setStatistical(StatisticalSettings &statistical);

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
  // # TEMPLATE 4.61, Individual ensemble re-forecast, control and perturbed, at a horizontal level or in a horizontal layer in a continuous or non-continuous time interval
  //
  // include "template.4.parameter.def"

  ParameterSettings mParameter;

  // include "template.4.horizontal.def"

  HorizontalSettings mHorizontal;

  // include "template.4.eps.def"

  EpsSettings mEps;

  // include "template.4.reforecast.def"

  ReforecastSettings mReforecast;

  // include "template.4.statistical.def"

  StatisticalSettings mStatistical;
};

} // namespace GRIB2
} // namespace SmartMet
