// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SpectralDataRepresentationImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../RepresentationDefinition.h"
#include "PackingSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (5.50).*/

class SpectralDataRepresentation : public RepresentationDefinition {
public:
  SpectralDataRepresentation();
  SpectralDataRepresentation(const SpectralDataRepresentation &other);
  virtual ~SpectralDataRepresentation();

  virtual uint getTemplateNumber() const;
  virtual RepresentationDefinition *createRepresentationDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  PackingSettings *getPacking() const;
  void setPacking(PackingSettings &packing);
  float getRealPartOf00() const;
  void setRealPartOf00(float realPartOf00);

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
  // # TEMPLATE 5.50, Spectral data - simple packing
  // include "template.5.packing.def";

  mutable PackingSettings mPacking;

  //
  // #  Real part of (0,0)
  // ieeefloat realPartOf00 ;

  float mRealPartOf00;

  //
};

} // namespace GRIB2
} // namespace SmartMet
