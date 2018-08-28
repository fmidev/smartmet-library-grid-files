// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'MercatorImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "GridAreaSettings.h"
#include "ScanningModeSettings.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template (grid_definition_1).*/

class Mercator : public GridDefinition {
public:
  Mercator();
  Mercator(const Mercator &other);
  virtual ~Mercator();

  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  std::int16_t getNi() const;
  void setNi(std::int16_t ni);
  std::int16_t getNj() const;
  void setNj(std::int16_t nj);
  GridAreaSettings *getGridArea() const;
  void setGridArea(GridAreaSettings &gridArea);
  std::int24_t getLatin() const;
  void setLatin(std::int24_t latin);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);
  std::int24_t getDiInMetres() const;
  void setDiInMetres(std::int24_t diInMetres);
  std::int24_t getDjInMetres() const;
  void setDjInMetres(std::int24_t djInMetres);

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
  // # GRID DEFINITION Mercator projection
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 20;
  //
  // signed[2] Ni : dump;

  std::int16_t mNi;

  // alias numberOfPointsAlongAParallel= Ni ;
  // alias Nx =Ni;
  // alias geography.Ni=Ni;
  //
  // signed[2] Nj : dump;

  std::int16_t mNj;

  // alias numberOfPointsAlongAMeridian=Nj;
  // alias Nx=Nj;
  // alias geography.Nj=Nj;
  //
  // include "grid_first_last_resandcomp.def";

  GridAreaSettings mGridArea;

  //
  // signed[3] Latin : edition_specific,no_copy;

  std::int24_t mLatin;

  // meta geography.LaDInDegrees scale(Latin,oneConstant,grib1divider,truncateDegrees) : dump;
  //
  // pad padding_grid1_1(1);
  //
  // # for change_scanning_direction
  // alias yFirst=latitudeOfFirstGridPointInDegrees;
  // alias yLast=latitudeOfLastGridPointInDegrees;
  // alias xFirst=longitudeOfFirstGridPointInDegrees;
  // alias xLast=longitudeOfLastGridPointInDegrees;
  //
  // include "scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // signed[3] DiInMetres   : dump;

  std::int24_t mDiInMetres;

  // alias longitudinalDirectionGridLength=DiInMetres;
  // alias Di=DiInMetres;
  // alias geography.DiInMetres=DiInMetres;
  //
  // signed[3] DjInMetres   : dump;

  std::int24_t mDjInMetres;

  // alias latitudinalDirectionGridLength=DjInMetres;
  // alias Dj=DjInMetres;
  // alias geography.DjInMetres=DjInMetres;
  //
  // constant orientationOfTheGridInDegrees=0;
  //
  // pad padding_grid1_2(8);
  //
  // meta numberOfDataPoints number_of_points(Ni,Nj) : dump;
  // alias numberOfPoints=numberOfDataPoints;
  // meta numberOfValues number_of_values(values,bitsPerValue,numberOfDataPoints,bitmapPresent,bitmap,numberOfCodedValues) : dump;
  // #alias ls.valuesCount=numberOfValues;
  //
};

} // namespace GRIB1
} // namespace SmartMet
