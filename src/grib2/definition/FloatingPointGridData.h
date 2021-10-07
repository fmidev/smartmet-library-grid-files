// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'FloatingPointGridDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../DataDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.4).*/

class FloatingPointGridData : public DataDefinition {
public:
  FloatingPointGridData();
  virtual ~FloatingPointGridData();

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
  // # TEMPLATE 7.4, Grid point data - simple packing
  // # Octets 6-nn : Binary data values - binary string, with each
  // # (scaled)
  // # ????          data_values__binary_string_with_each
  //
  // meta   codedValues data_raw_packing(
  //               section7Length,
  //               offsetBeforeData,
  //               offsetSection7,
  //               numberOfValues,
  //               precision
  //             ): read_only;
  //
  // meta values data_apply_bitmap(codedValues,
  //                                 bitmap,
  //                                 missingValue,
  //                                 binaryScaleFactor,
  //                                 numberOfDataPoints,
  //                                 numberOfValues) : dump;
  //
  // alias data.packedValues = codedValues;
  //
  // template statistics "common/statistics_grid.def";
};

} // namespace GRIB2
} // namespace SmartMet
