// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CrossSectionProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/ProductDefinition.h"
#include "grib2/definition/ParameterSettings.h"
#include "grib2/definition/PointInTimeSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.1000).*/

class CrossSectionProduct : public ProductDefinition {
public:
  CrossSectionProduct();
  virtual ~CrossSectionProduct();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const ParameterSettings *getParameter() const;
  void setParameter(ParameterSettings parameter);
  const PointInTimeSettings *getPointInTime() const;
  void setPointInTime(PointInTimeSettings pointInTime);

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
  // # TEMPLATE 4.1000, Cross section of analysis and forecast at a point in time
  //
  // include "template.4.parameter.def"

  ParameterSettings mParameter;

  // include "template.4.point_in_time.def";

  PointInTimeSettings mPointInTime;
};

} // namespace GRIB2
} // namespace SmartMet
