// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedSphericalHarmonicImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "GridStretchingSettings.h"
#include "RotationSettings.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template (grid_definition_70).*/

class StretchedSphericalHarmonic : public GridDefinition {
public:
  StretchedSphericalHarmonic();
  StretchedSphericalHarmonic(const StretchedSphericalHarmonic &other);
  virtual ~StretchedSphericalHarmonic();

  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  std::uint16_t getJ() const;
  void setJ(std::uint16_t j);
  std::uint16_t getK() const;
  void setK(std::uint16_t k);
  std::uint16_t getM() const;
  void setM(std::uint16_t m);
  std::uint8_t getRepresentationType() const;
  void setRepresentationType(std::uint8_t representationType);
  std::uint8_t getRepresentationMode() const;
  void setRepresentationMode(std::uint8_t representationMode);
  RotationSettings *getRotation() const;
  void setRotation(RotationSettings &rotation);
  GridStretchingSettings *getGridStretching() const;
  void setGridStretching(GridStretchingSettings &gridStretching);

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
  // # GRID DEFINITION Stretched spherical harmonics
  //
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 52;
  //
  // template commonBlock "grib1/grid_definition_spherical_harmonics.def";
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // # GRID DEFINITION spherical harmonic coefficients (including rotated, stretched, or stretched and rotated)
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
  //
  // # Rotation parameters
  // include  "grid_rotation.def"

  RotationSettings mRotation;

  //
  // # Stretching parameters
  // include "grid_stretching.def"

  GridStretchingSettings mGridStretching;
};

} // namespace GRIB1
} // namespace SmartMet
