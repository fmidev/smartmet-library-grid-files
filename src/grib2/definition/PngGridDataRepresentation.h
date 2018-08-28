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
  PngGridDataRepresentation(const PngGridDataRepresentation &other);
  virtual ~PngGridDataRepresentation();

  virtual uint getTemplateNumber() const;
  virtual RepresentationDefinition *createRepresentationDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  PackingSettings *getPacking() const;
  void setPacking(PackingSettings &packing);
  OriginalValuesSettings *getOriginalValues() const;
  void setOriginalValues(OriginalValuesSettings &originalValues);

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // # Grid point data - PNG  Code Stream Format SAME AS 5.40010 !!!!!!
  //
  // include "template.5.packing.def";

  PackingSettings mPacking;

  // include "template.5.original_values.def";

  OriginalValuesSettings mOriginalValues;

  //
};

} // namespace GRIB2
} // namespace SmartMet
