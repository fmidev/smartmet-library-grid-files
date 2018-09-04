// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedGaussianImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "GridAreaSettings.h"
#include "GridStretchingSettings.h"
#include "ScanningModeSettings.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template (grid_definition_24).*/

class StretchedGaussian : public GridDefinition {
public:
  StretchedGaussian();
  StretchedGaussian(const StretchedGaussian &other);
  virtual ~StretchedGaussian();

  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  std::uint16_t getNi() const;
  void setNi(std::uint16_t ni);
  std::int16_t getNj() const;
  void setNj(std::int16_t nj);
  GridAreaSettings *getGridArea() const;
  void setGridArea(GridAreaSettings &gridArea);
  std::uint16_t getIDirectionIncrement() const;
  void setIDirectionIncrement(std::uint16_t iDirectionIncrement);
  std::uint16_t getN() const;
  void setN(std::uint16_t n);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);
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
  // # GRID DEFINITION Stretched Gaussian latitude/longitude grid
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 42;
  //
  // template commonBlock "grib1/grid_definition_gaussian.def";
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // unsigned[2] Ni : can_be_missing,dump;

  std::uint16_t mNi;

  // alias numberOfPointsAlongAParallel= Ni ;
  // alias Nx =Ni;
  //
  // signed[2] Nj : dump;

  std::int16_t mNj;

  // alias numberOfPointsAlongAMeridian=Nj;
  // alias Ny=Nj;
  //
  // # Latitudes and Longitudes of the first and the last points
  // # Resolution and component flags
  // include "grid_first_last_resandcomp.def";

  mutable GridAreaSettings mGridArea;

  //
  // #  Di - i direction increment
  // unsigned[2] iDirectionIncrement : can_be_missing,dump,edition_specific;

  std::uint16_t mIDirectionIncrement;

  // meta geography.iDirectionIncrementInDegrees scale(iDirectionIncrement,oneConstant,grib1divider,truncateDegrees) : can_be_missing,dump;
  // alias Di = iDirectionIncrement;
  //
  // #  N - number of parallels between a pole and the equator
  // unsigned[2] N : dump ;

  std::uint16_t mN;

  // alias numberOfParallelsBetweenAPoleAndTheEquator=N;
  // alias geography.N=N;
  //
  // # for change_scanning_direction
  // alias yFirst=latitudeOfFirstGridPointInDegrees;
  // alias yLast=latitudeOfLastGridPointInDegrees;
  // alias xFirst=longitudeOfFirstGridPointInDegrees;
  // alias xLast=longitudeOfLastGridPointInDegrees;
  //
  // include "scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
  // pad padding_grid4_1(4);
  //
  // alias latitudeFirstInDegrees  = latitudeOfFirstGridPointInDegrees;
  // alias longitudeFirstInDegrees = longitudeOfFirstGridPointInDegrees;
  // alias latitudeLastInDegrees   = latitudeOfLastGridPointInDegrees;
  // alias longitudeLastInDegrees  = longitudeOfLastGridPointInDegrees;
  // alias DiInDegrees = iDirectionIncrementInDegrees;
  //
  // meta global global_gaussian(N,Ni,iDirectionIncrement,
  //                             latitudeOfFirstGridPoint,
  //                             longitudeOfFirstGridPoint,
  //                             latitudeOfLastGridPoint,
  //                             longitudeOfLastGridPoint,
  //                             PLPresent,pl) = 0 : dump;
  //
  // meta numberOfDataPoints number_of_points_gaussian(Ni,Nj,PLPresent,pl,
  //   N,
  //   latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //   latitudeOfLastGridPointInDegrees,longitudeOfLastGridPointInDegrees) : dump;
  //
  // alias numberOfPoints=numberOfDataPoints;
  // # alias numberOfExpectedPoints=numberOfDataPoints;
  // meta numberOfValues number_of_values(values,bitsPerValue,numberOfDataPoints,bitmapPresent,bitmap,numberOfCodedValues) : dump;
  // #alias ls.valuesCount=numberOfValues;
  //
  // if(missing(Ni)){
  //    iterator gaussian_reduced(numberOfPoints,missingValue,values,
  //        latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //        latitudeOfLastGridPointInDegrees,longitudeOfLastGridPointInDegrees,
  //        N,pl,Nj);
  //    nearest reduced(values,radius,Nj,pl);
  //    box reduced_gaussian(latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //           latitudeOfLastGridPointInDegrees,longitudeOfLastGridPointInDegrees,
  // 		  N,pl);
  // } else {
  //    iterator   gaussian(numberOfPoints,missingValue,values,longitudeFirstInDegrees,
  //             DiInDegrees  ,Ni,Nj,iScansNegatively ,
  //             latitudeFirstInDegrees, latitudeLastInDegrees,
  //             N,jScansPositively);
  //    nearest regular(values,radius,Ni,Nj);
  //  #  box regular_gaussian(latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //  #         latitudeOfLastGridPointInDegrees,longitudeOfLastGridPointInDegrees,
  // #		  DiInDegrees,Ni,N,iScansNegatively,jScansPositively);
  // }
  //
  // meta latLonValues latlonvalues(values);
  // alias latitudeLongitudeValues=latLonValues;
  // meta latitudes latitudes(values,0);
  // meta longitudes longitudes(values,0);
  // meta distinctLatitudes latitudes(values,1);
  // meta distinctLongitudes longitudes(values,1);
  //
  // meta isOctahedral octahedral_gaussian(N, Ni, PLPresent, pl) = 0 : no_copy,dump;
  //
  // meta gaussianGridName gaussian_grid_name(N, Ni, isOctahedral);
  // alias gridName=gaussianGridName;
  //
  //
  // # Stretching parameters
  // include "grid_stretching.def"

  mutable GridStretchingSettings mGridStretching;
};

} // namespace GRIB1
} // namespace SmartMet
