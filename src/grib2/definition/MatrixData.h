// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'MatrixDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/DataDefinition.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.1).*/

class MatrixData : public DataDefinition {
public:
  MatrixData();
  virtual ~MatrixData();

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
  // # START 2/template.7.1
  // ----------------------------------------------------------------------
  // # TEMPLATE 7.1, Matrix values at grid point -simple packing
  // # Octets 6-nn : Binary data values - binary string, with each
  // # (scaled)
  // # ????          data_values__binary_string_with_each
  //
  //   meta codedValues data_g2simple_packing(
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
  //         decimalScaleFactor
  //   ): read_only;
  //
  //   meta values data_apply_bitmap(codedValues,
  //                                 bitmap,
  //                                 missingValue,
  //                                 binaryScaleFactor,
  //                                 numberOfDataPoints,
  //                                 numberOfValues) : dump;
  //
  // meta packingError
  // simple_packing_error(bitsPerValue,binaryScaleFactor,decimalScaleFactor,referenceValue,ieee)
  // : no_copy;
  // meta unpackedError
  // simple_packing_error(zero,binaryScaleFactor,decimalScaleFactor,referenceValue,ieee)
  // : no_copy;
  //
  // alias data.packedValues = codedValues;
  //
  // template statistics "common/statistics_grid.def";
};

} // namespace GRIB2
} // namespace SmartMet