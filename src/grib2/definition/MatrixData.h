// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'MatrixDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../DataDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.1).*/

class MatrixData : public DataDefinition {
public:
  MatrixData();
  virtual ~MatrixData();

  virtual uint getTemplateNumber() const;
  virtual DataDefinition *createDataDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 7.1, Matrix values at grid point -simple packing
  // # Octets 6-nn : Binary data values - binary string, with each
  // # (scaled)
  // # ????          data_values__binary_string_with_each
  //
  // meta codedValues data_g2simple_packing(
  //         section7Length,
  //         offsetBeforeData,
  //         offsetSection7,
  //         unitsFactor,
  //         unitsBias,
  //         changingPrecision,
  //         numberOfValues,
  //         bitsPerValue,
  //         referenceValue,
  //         binaryScaleFactor,
  //         decimalScaleFactor,
  //         optimizeScaleFactor
  //   ): read_only;
  //
  // meta values data_apply_bitmap(codedValues,
  //                               bitmap,
  //                               missingValue,
  //                               binaryScaleFactor,
  //                               numberOfDataPoints,
  //                               numberOfValues) : dump;
  //
  // meta packingError simple_packing_error(bitsPerValue,binaryScaleFactor,decimalScaleFactor,referenceValue,ieee) : no_copy;
  // meta unpackedError simple_packing_error(zero,binaryScaleFactor,decimalScaleFactor,referenceValue,ieee) : no_copy;
  //
  // alias data.packedValues = codedValues;
  //
  // template statistics "common/statistics_grid.def";
};

} // namespace GRIB2
} // namespace SmartMet
