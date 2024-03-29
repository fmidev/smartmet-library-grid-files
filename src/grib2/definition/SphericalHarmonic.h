// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SphericalHarmonicImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "SphericalHarmonicSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.50).*/

class SphericalHarmonic : public GridDefinition {
public:
  SphericalHarmonic();
  virtual ~SphericalHarmonic();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  SphericalHarmonicSettings *getSphericalHarmonic() const;
  void setSphericalHarmonic(SphericalHarmonicSettings &sphericalHarmonic);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.50, Spherical harmonic coefficients
  //
  // include "grib2/template.3.spherical_harmonics.def";

  mutable SphericalHarmonicSettings mSphericalHarmonic;
};

} // namespace GRIB2
} // namespace SmartMet
