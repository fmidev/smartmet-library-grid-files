// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SpectralGridDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/DataDefinition.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.42).*/

class SpectralGridData : public DataDefinition {
public:
  SpectralGridData();
  virtual ~SpectralGridData();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version
  // 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and
  // immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it
  // submit to any jurisdiction.
  // #
  //
  //
  // # START 2/template.7.42
  // ----------------------------------------------------------------------
  // # TEMPLATE 7.42, Grid point data - CCSDS
  //
  //     meta codedValues data_ccsds_packing(
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
  // alias data.packedValues = codedValues;
  //
  // template statistics "common/statistics_grid.def";
};

} // namespace GRIB2
} // namespace SmartMet
