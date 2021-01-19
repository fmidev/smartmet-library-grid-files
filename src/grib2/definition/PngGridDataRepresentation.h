// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PngGridDataRepresentationImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../RepresentationDefinition.h"
#include "OriginalValuesSettings.h"
#include "PackingSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (5.41).*/

class PngGridDataRepresentation : public RepresentationDefinition {
public:
  PngGridDataRepresentation();
  virtual ~PngGridDataRepresentation();

  virtual uint getTemplateNumber() const;
  virtual RepresentationDefinition *createRepresentationDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  PackingSettings *getPacking() const;
  void setPacking(PackingSettings &packing);
  OriginalValuesSettings *getOriginalValues() const;
  void setOriginalValues(OriginalValuesSettings &originalValues);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # Grid point data - PNG  Code Stream Format SAME AS 5.40010 !!!!!!
  //
  // include "grib2/template.5.packing.def";

  mutable PackingSettings mPacking;

  // include "grib2/template.5.original_values.def";

  mutable OriginalValuesSettings mOriginalValues;
};

} // namespace GRIB2
} // namespace SmartMet
