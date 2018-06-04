// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AerosolOpticalPropertiesProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/MemoryReader.h"
#include "../ProductDefinition.h"
#include "HorizontalSettings.h"
#include "ParameterAerosolOpticalSettings.h"
#include "PointInTimeSettings.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.48).*/

class AerosolOpticalPropertiesProduct : public ProductDefinition {
public:
  AerosolOpticalPropertiesProduct();
  virtual ~AerosolOpticalPropertiesProduct();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const ParameterAerosolOpticalSettings *getParameterAerosolOptical() const;
  void setParameterAerosolOptical(ParameterAerosolOpticalSettings parameterAerosolOptical);
  const PointInTimeSettings *getPointInTime() const;
  void setPointInTime(PointInTimeSettings pointInTime);
  const HorizontalSettings *getHorizontal() const;
  void setHorizontal(HorizontalSettings horizontal);

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
  // # TEMPLATE 4.48, Analysis or forecast at a horizontal level or in a horizontal layer at a point in time for optical properties of aerosol
  //
  // include "template.4.parameter_aerosol_optical.def";

  ParameterAerosolOpticalSettings mParameterAerosolOptical;

  // include "template.4.point_in_time.def";

  PointInTimeSettings mPointInTime;

  // include "template.4.horizontal.def";

  HorizontalSettings mHorizontal;
};

} // namespace GRIB2
} // namespace SmartMet
