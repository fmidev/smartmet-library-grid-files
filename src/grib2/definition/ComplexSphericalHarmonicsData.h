// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ComplexSphericalHarmonicsDataImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../DataDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (7.50000).*/

class ComplexSphericalHarmonicsData : public DataDefinition {
public:
  ComplexSphericalHarmonicsData();
  virtual ~ComplexSphericalHarmonicsData();

  virtual uint getTemplateNumber() const;
  virtual DataDefinition *createDataDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // constant GRIBEXShBugPresent = 0;
  // constant sphericalHarmonics = 1;
  // constant complexPacking = 1;
  //
  // meta codedValues data_g2complex_packing(
  //           section7Length,
  //           offsetBeforeData,
  //           offsetSection7,
  //
  //           unitsFactor,
  //       	  unitsBias,
  //           changingPrecision,
  //           numberOfValues,
  //           bitsPerValue,
  //           referenceValue,
  //           binaryScaleFactor,
  //           decimalScaleFactor,
  //           optimizeScaleFactor,
  //
  //           GRIBEXShBugPresent,
  //           unpackedSubsetPrecision,
  //
  //           laplacianOperatorIsSet,
  //           laplacianOperator,
  //
  //           J,
  //           K,
  //           M,
  //
  //           J,
  //           J,
  //           J,
  //
  //           numberOfValues
  //       ): read_only;
  //
  //  meta data.packedValues data_sh_packed(
  //           section7Length,
  //           offsetBeforeData,
  //           offsetSection7,
  //
  //           unitsFactor,
  //           unitsBias,
  //           changingPrecision,
  //           numberOfValues,
  //           bitsPerValue,
  //           referenceValue,
  //           binaryScaleFactor,
  //           decimalScaleFactor,
  //           optimizeScaleFactor,
  //
  //           GRIBEXShBugPresent,
  //           unpackedSubsetPrecision,
  //
  //           laplacianOperatorIsSet,
  //           laplacianOperator,
  //
  //           J,
  //           K,
  //           M,
  //
  //           J,
  //           J,
  //           J
  //  ) : read_only;
  //
  //  meta data.unpackedValues data_sh_unpacked(
  //           section7Length,
  //           offsetBeforeData,
  //           offsetSection7,
  //
  //           unitsFactor,
  //           unitsBias,
  //           changingPrecision,
  //           numberOfValues,
  //           bitsPerValue,
  //           referenceValue,
  //           binaryScaleFactor,
  //           decimalScaleFactor,
  //           optimizeScaleFactor,
  //
  //           GRIBEXShBugPresent,
  //           unpackedSubsetPrecision,
  //
  //           laplacianOperatorIsSet,
  //           laplacianOperator,
  //
  //           J,
  //           K,
  //           M,
  //
  //           J,
  //           K,
  //           M
  //  ) : read_only;
  //
  // meta packingError simple_packing_error(bitsPerValue,binaryScaleFactor,decimalScaleFactor,referenceValue,ieee) : no_copy;
  // meta unpackedError simple_packing_error(zero,binaryScaleFactor,decimalScaleFactor,referenceValue,ieee) : no_copy;
  //
  // meta values data_apply_bitmap(codedValues,
  //                                 bitmap,
  //                                 missingValue,
  //                                 binaryScaleFactor,
  //                                 numberOfDataPoints,
  //                                 numberOfValues) : dump;
  //
  // template statistics "common/statistics_spectral.def";
};

} // namespace GRIB2
} // namespace SmartMet
