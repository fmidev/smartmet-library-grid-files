// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'Product_49Impl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "EpsSettings.h"
#include "HorizontalSettings.h"
#include "ParameterAerosolOpticalSettings.h"
#include "PointInTimeSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.49).*/

class Product_49 : public ProductDefinition {
public:
  Product_49();
  Product_49(const Product_49 &other);
  virtual ~Product_49();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  ParameterAerosolOpticalSettings *getParameterAerosolOptical() const;
  void setParameterAerosolOptical(ParameterAerosolOpticalSettings &parameterAerosolOptical);
  PointInTimeSettings *getPointInTime() const;
  void setPointInTime(PointInTimeSettings &pointInTime);
  HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings &horizontal);
  EpsSettings *getEps() const;
  void setEps(EpsSettings &eps);

protected:
  // # Copyright 2005-2017 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // # TEMPLATE 4.49, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for optical properties of aerosol
  //
  // include "grib2/template.4.parameter_aerosol_optical.def";

  mutable ParameterAerosolOpticalSettings mParameterAerosolOptical;

  // include "grib2/template.4.point_in_time.def";

  mutable PointInTimeSettings mPointInTime;

  // include "grib2/template.4.horizontal.def";

  mutable HorizontalSettings mHorizontal;

  // include "grib2/template.4.eps.def"

  mutable EpsSettings mEps;
};

} // namespace GRIB2
} // namespace SmartMet
