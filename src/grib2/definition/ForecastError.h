// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ForecastErrorImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "NormalProduct.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.7).*/

class ForecastError : public ProductDefinition {
public:
  ForecastError();
  ForecastError(const ForecastError &other);
  virtual ~ForecastError();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  NormalProduct *getNormalProduct() const;
  void setNormalProduct(NormalProduct &normalProduct);

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
  // # TEMPLATE 4.7, Analysis or forecast error at a horizontal level or in a horizontal layer at a point in time
  // # Same as 4.0 Should not be used
  //
  // include "template.4.0.def"
  NormalProduct mNormalProduct;
};

} // namespace GRIB2
} // namespace SmartMet
