// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PackingSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (5.packing).*/

class PackingSettings {
public:
  PackingSettings();
  virtual ~PackingSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  float getReferenceValue() const;
  void setReferenceValue(float referenceValue);
  const T::Int16_opt &getBinaryScaleFactor() const;
  void setBinaryScaleFactor(T::Int16_opt binaryScaleFactor);
  const T::Int16_opt &getDecimalScaleFactor() const;
  void setDecimalScaleFactor(T::Int16_opt decimalScaleFactor);
  const T::UInt8_opt &getBitsPerValue() const;
  void setBitsPerValue(T::UInt8_opt bitsPerValue);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // #  Reference value (R)
  // # The copy_ok means that the value is copied when changing the representation
  // # e.g. from jpeg to simple packing.
  // ieeefloat   referenceValue  : read_only, copy_ok;

  float mReferenceValue;

  // meta referenceValueError reference_value_error(referenceValue,ieee);
  //
  //
  // #  Binary scale factor (E)
  // signed[2]   binaryScaleFactor : read_only, copy_ok;

  T::Int16_opt mBinaryScaleFactor;

  //
  // #  Decimal scale factor (D)
  // signed[2]   decimalScaleFactor ;

  T::Int16_opt mDecimalScaleFactor;

  //
  // # Try different values of binaryScaleFactor and decimalScaleFactor to reduce packing error
  // transient optimizeScaleFactor = 0;
  //
  //
  // #  Number of bits used for each packed value for simple packing, or for each group reference value for complex packing or spatial differencing
  // unsigned[1] bitsPerValue;

  T::UInt8_opt mBitsPerValue;

  // alias numberOfBits = bitsPerValue;
  // alias numberOfBitsContainingEachPackedValue = bitsPerValue;
};

} // namespace GRIB2
} // namespace SmartMet
