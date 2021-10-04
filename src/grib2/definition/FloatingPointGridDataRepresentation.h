// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'FloatingPointGridDataRepresentationImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../RepresentationDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (5.4).*/

class FloatingPointGridDataRepresentation : public RepresentationDefinition {
public:
  FloatingPointGridDataRepresentation();
  virtual ~FloatingPointGridDataRepresentation();

  virtual uint getTemplateNumber() const;
  virtual RepresentationDefinition *createRepresentationDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getPrecision() const;
  void setPrecision(T::UInt8_opt precision);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 5.4, Grid point data - IEEE packing
  // # added for conversion from other packing
  // transient bitsPerValue=0 : hidden;
  // transient referenceValue=0  : hidden;
  // transient binaryScaleFactor=0 : hidden;
  // transient decimalScaleFactor=0 : hidden;
  // alias numberOfBits = bitsPerValue;
  // alias numberOfBitsContainingEachPackedValue = bitsPerValue;
  //
  // codetable[1] precision  ('5.7.table',masterDir,localDir)  = 1 : edition_specific;

  T::UInt8_opt mPrecision;
};

} // namespace GRIB2
} // namespace SmartMet
