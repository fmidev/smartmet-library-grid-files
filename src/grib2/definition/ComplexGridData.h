// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ComplexGridDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../DataDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.2).*/

class ComplexGridData : public DataDefinition {
public:
  ComplexGridData();
  ComplexGridData(const ComplexGridData &other);
  virtual ~ComplexGridData();

  virtual uint getTemplateNumber() const;
  virtual DataDefinition *createDataDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

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
  //
  // # START 2/template.7.2 ----------------------------------------------------------------------
  // # TEMPLATE 7.2, Grid point data - complex packing
  // # Octets 6-xx : NG  group reference values
  // # (XI in the decoding formula)
  //
  // position offsetBeforeData;
  //
  // constant orderOfSpatialDifferencing     = 0;
  // constant numberOfOctetsExtraDescriptors = 0;
  //
  // meta codedValues data_g22order_packing(
  //           section7Length,
  //           offsetBeforeData,
  //           offsetSection7,
  //
  //
  //      numberOfValues,
  //      bitsPerValue,
  //      referenceValue,
  //      binaryScaleFactor,
  //      decimalScaleFactor,
  //
  //      typeOfOriginalFieldValues ,
  //      groupSplittingMethodUsed,
  //      missingValueManagementUsed ,
  //      primaryMissingValueSubstitute ,
  //      secondaryMissingValueSubstitute ,
  //      numberOfGroupsOfDataValues ,
  //      referenceForGroupWidths ,
  //      numberOfBitsUsedForTheGroupWidths ,
  //      referenceForGroupLengths ,
  //      lengthIncrementForTheGroupLengths,
  //      trueLengthOfLastGroup ,
  //      numberOfBitsForScaledGroupLengths,
  //      orderOfSpatialDifferencing,
  //      numberOfOctetsExtraDescriptors
  //
  // ): read_only;
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
  //
  // # END   2/template.7.2 ----------------------------------------------------------------------
};

} // namespace GRIB2
} // namespace SmartMet
