// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SpectralGridDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../DataDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.42).*/

class SpectralGridData : public DataDefinition {
public:
  SpectralGridData();
  virtual ~SpectralGridData();

  virtual uint getTemplateNumber() const;
  virtual DataDefinition *createDataDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 7.42, Grid point data - CCSDS
  // meta codedValues data_ccsds_packing(
  //               section7Length,
  //               offsetBeforeData,
  //               offsetSection7,
  //               numberOfValues,
  //               referenceValue,
  //               binaryScaleFactor,
  //               decimalScaleFactor,
  //               bitsPerValue,
  //
  //               numberOfDataPoints,
  //
  //               ccsdsFlags,
  //               ccsdsBlockSize,
  //               ccsdsRsi
  //
  //             ): read_only;
  //
  // meta values data_apply_bitmap(codedValues,
  //                                 bitmap,
  //                                 missingValue,
  //                                 binaryScaleFactor,
  //                                 numberOfDataPoints,
  //                                 numberOfValues) : dump;
  //
  // # See ECC-711
  // meta packingError simple_packing_error(bitsPerValue,binaryScaleFactor,decimalScaleFactor,referenceValue,ieee) : no_copy;
  // meta unpackedError simple_packing_error(zero,binaryScaleFactor,decimalScaleFactor,referenceValue,ieee) : no_copy;
  //
  // alias data.packedValues = codedValues;
  //
  // template statistics "common/statistics_grid.def";
};

} // namespace GRIB2
} // namespace SmartMet
