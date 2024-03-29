// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ComplexDifferenceGridDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../DataDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.3).*/

class ComplexDifferenceGridData : public DataDefinition {
public:
  ComplexDifferenceGridData();
  virtual ~ComplexDifferenceGridData();

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
  // # TEMPLATE 7.3, Grid point data - complex packing and spatial differencing
  // # Octets 6-ww : First value(s) of original
  // # (undifferenced)
  // # ????          first_value_s_of_original
  //
  // position offsetBeforeData;
  //
  // meta codedValues data_g22order_packing(
  //      section7Length,
  //      offsetBeforeData,
  //      offsetSection7,
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
  //                               bitmap,
  //                               missingValue,
  //                               binaryScaleFactor,
  //                               numberOfDataPoints,
  //                               numberOfValues) : dump;
  //
  // alias data.packedValues=codedValues;
  //
  // template statistics "common/statistics_grid.def";
};

} // namespace GRIB2
} // namespace SmartMet
