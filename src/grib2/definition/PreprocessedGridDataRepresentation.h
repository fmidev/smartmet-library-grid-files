// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PreprocessedGridDataRepresentationImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/RepresentationDefinition.h"
#include "grib2/definition/PackingSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (5.6).*/

class PreprocessedGridDataRepresentation : public RepresentationDefinition {
public:
  PreprocessedGridDataRepresentation();
  virtual ~PreprocessedGridDataRepresentation();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const PackingSettings *getPacking() const;
  void setPacking(PackingSettings packing);
  const T::UInt8_opt &getTypeOfPreProcessing() const;
  void setTypeOfPreProcessing(T::UInt8_opt typeOfPreProcessing);
  float getPreProcessingParameter() const;
  void setPreProcessingParameter(float preProcessingParameter);

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
  // label "grib 2 Section 5 template 5.6";
  // # START 2/template.5.6 ----------------------------------------------------------------------
  // # Grid point data - Simple packing with preprocessing
  //
  // include "template.5.packing.def";

  PackingSettings mPacking;

  //
  // codetable[1] typeOfPreProcessing   ('5.9.table',masterDir,localDir)  :edition_specific;

  T::UInt8_opt mTypeOfPreProcessing;

  // ieeefloat   preProcessingParameter  : read_only;

  float mPreProcessingParameter;

  //
  // # END   2/template.5.6 ----------------------------------------------------------------------
};

} // namespace GRIB2
} // namespace SmartMet
