// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PreprocessedGridDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../DataDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.6).*/

class PreprocessedGridData : public DataDefinition {
public:
  PreprocessedGridData();
  virtual ~PreprocessedGridData();

  virtual uint getTemplateNumber() const;
  virtual DataDefinition *createDataDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 7.6, Grid point data - simple packing with preprocessing
  // # Octets 6-nn : Binary data values - binary string, with each (scaled)
  //
  // meta codedValues data_g2simple_packing_with_preprocessing(
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
  //         optimizeScaleFactor,
  //         typeOfPreProcessing,
  //         preProcessingParameter
  //   ): read_only;
  //
  // meta values data_apply_bitmap(codedValues,
  //                               bitmap,
  //                               missingValue,
  //                               binaryScaleFactor,
  //                               numberOfDataPoints,
  //                               numberOfValues) : dump;
  //
  // alias data.packedValues = codedValues;
  //
  // template statistics "common/statistics_grid.def";
};

} // namespace GRIB2
} // namespace SmartMet
