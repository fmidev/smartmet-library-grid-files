// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PartitionedEnsembleProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "EpsSettings.h"
#include "PartitionedProduct.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.54).*/

class PartitionedEnsembleProduct : public ProductDefinition {
public:
  PartitionedEnsembleProduct();
  ~PartitionedEnsembleProduct() override;

  uint getTemplateNumber() const override;
  ProductDefinition *createProductDefinition() const override;
  void read(MemoryReader &memoryReader) override;
  void write(DataWriter &dataWriter) override;
  void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const override;
  void print(std::ostream &stream, uint level, uint optionFlags) const override;
  virtual T::Hash countHash();

  PartitionedProduct *getPartitionedProduct() const;
  void setPartitionedProduct(PartitionedProduct &partitionedProduct);
  EpsSettings *getEps() const override;
  void setEps(EpsSettings &eps);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.54, Individual ensemble forecast, control and perturbed, at a horizontal level or in a horizontal layer at a point in time for partitioned parameters
  //
  // include "grib2/template.4.53.def"

  mutable PartitionedProduct mPartitionedProduct;

  // include "grib2/template.4.eps.def"

  mutable EpsSettings mEps;

  //
  // constant cat="cat";
  // alias mars.levtype=cat;
  // alias mars.levelist=partitionNumber;
};

} // namespace GRIB2
} // namespace SmartMet
