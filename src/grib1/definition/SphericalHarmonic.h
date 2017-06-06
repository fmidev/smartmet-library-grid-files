// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SphericalHarmonicImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib1/GridDefinition.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template
 * (grid_definition_50).*/

class SphericalHarmonic : public GridDefinition {
public:
  SphericalHarmonic();
  virtual ~SphericalHarmonic();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  std::uint16_t getJ() const;
  std::uint16_t getK() const;
  std::uint16_t getM() const;
  std::uint8_t getRepresentationType() const;
  std::uint8_t getRepresentationMode() const;

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version
  // 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and
  // immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it
  // submit to any jurisdiction.
  // #
  //
  // # GRID DEFINITION spherical harmonic coefficients (including rotated,
  // stretched, or stretched and rotated)
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 50;
  //
  // template commonBlock "grib1/grid_definition_spherical_harmonics.def";
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version
  // 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and
  // immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it
  // submit to any jurisdiction.
  // #
  //
  // # GRID DEFINITION spherical harmonic coefficients (including rotated,
  // stretched, or stretched and rotated)
  //
  // #  J - pentagonal resolution parameter
  // unsigned[2] J : dump ;

  std::uint16_t mJ;

  // alias pentagonalResolutionParameterJ= J;
  // alias geography.J=J;
  //
  // #  K - pentagonal resolution parameter
  // unsigned[2] K  : dump;

  std::uint16_t mK;

  // alias pentagonalResolutionParameterK=K;
  // alias geography.K=K;
  //
  // #  M - pentagonal resolution parameter
  // unsigned[2] M : dump ;

  std::uint16_t mM;

  // alias pentagonalResolutionParameterM=M;
  // alias geography.M=M;
  //
  // constant _T = -1 : hidden;
  // meta numberOfValues spectral_truncation(J,K,M,_T)  : dump;
  // alias numberOfPoints=numberOfValues;
  // alias numberOfDataPoints=numberOfValues;
  // #alias ls.valuesCount=numberOfValues;
  //
  // #  Representation type
  // codetable[1] representationType 'grib1/9.table' = 1 : no_copy;

  std::uint8_t mRepresentationType;

  //
  // #  Representation mode
  // codetable[1] representationMode 'grib1/10.table' = 2 : no_copy;

  std::uint8_t mRepresentationMode;

  //
  // #  Set to zero
  // # (reserved)
  // pad padding_grid50_1(18);
  //
  // # For now, to make section2 happy
  // constant Nj = 0;
};

} // namespace GRIB1
} // namespace SmartMet