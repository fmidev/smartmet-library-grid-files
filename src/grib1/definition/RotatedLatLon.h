// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'RotatedLatLonImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib1/GridDefinition.h"
#include "grib1/definition/GridAreaSettings.h"
#include "grib1/definition/RotationSettings.h"
#include "grib1/definition/ScanningModeSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template
 * (grid_definition_10).*/

class RotatedLatLon : public GridDefinition {
public:
  RotatedLatLon();
  virtual ~RotatedLatLon();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  std::uint16_t getNi() const;
  std::uint16_t getNj() const;
  const GridAreaSettings *getGridArea() const;
  std::uint16_t getIDirectionIncrement() const;
  std::uint16_t getJDirectionIncrement() const;
  const ScanningModeSettings *getScanningMode() const;
  std::uint32_t getZero() const;
  const RotationSettings *getRotation() const;

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
  // # GRID DEFINITION rotated latitude/longitude grid (or equidistant
  // cylindrical)
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 1;
  //
  // template commonBlock "grib1/grid_definition_latlon.def";
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
  //
  // unsigned[2] Ni  : can_be_missing,dump;

  std::uint16_t mNi;

  // alias numberOfPointsAlongAParallel=Ni;
  // alias Nx = Ni;
  //
  // unsigned[2] Nj : can_be_missing,dump;

  std::uint16_t mNj;

  // alias numberOfPointsAlongAMeridian=Nj;
  // alias Ny = Nj;
  //
  // # Latitudes and Longitudes of the first and the last points
  // # Resolution and component flags
  // include "grid_first_last_resandcomp.def";

  GridAreaSettings mGridArea;

  //
  // unsigned[2] iDirectionIncrement : can_be_missing, edition_specific;

  std::uint16_t mIDirectionIncrement;

  // unsigned[2] jDirectionIncrement : can_be_missing, edition_specific;

  std::uint16_t mJDirectionIncrement;

  // alias Dj = jDirectionIncrement;
  // alias Dy = jDirectionIncrement;
  // alias Di = iDirectionIncrement;
  // alias Dx = iDirectionIncrement;
  //
  // include "scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // meta  geography.jDirectionIncrementInDegrees
  // latlon_increment(ijDirectionIncrementGiven,jDirectionIncrement,
  //   jScansPositively,
  //   latitudeOfFirstGridPointInDegrees,latitudeOfLastGridPointInDegrees,
  //   numberOfPointsAlongAMeridian,oneConstant,grib1divider,0) :
  //   can_be_missing,dump;
  //
  // alias DjInDegrees=jDirectionIncrementInDegrees;
  // alias DyInDegrees=jDirectionIncrementInDegrees;
  //
  // meta  geography.iDirectionIncrementInDegrees
  // latlon_increment(ijDirectionIncrementGiven,iDirectionIncrement,
  //   iScansPositively,
  //   longitudeOfFirstGridPointInDegrees,longitudeOfLastGridPointInDegrees,
  //   Ni,oneConstant,grib1divider,1) : can_be_missing,dump;
  // alias DiInDegrees=iDirectionIncrementInDegrees;
  // alias DxInDegrees=iDirectionIncrementInDegrees;
  //
  // meta numberOfDataPoints number_of_points(Ni,Nj,PLPresent,pl) : dump;
  // alias numberOfPoints=numberOfDataPoints;
  // meta numberOfValues
  // number_of_values(values,bitsPerValue,numberOfDataPoints,
  //                             bitmapPresent,bitmap,numberOfCodedValues) :
  //                             dump;
  // #alias ls.valuesCount=numberOfValues;
  //
  // if(missing(Ni)){
  //    iterator latlon_reduced(numberOfPoints,missingValue,values,
  //         latitudeFirstInDegrees,longitudeFirstInDegrees,
  //         latitudeLastInDegrees,longitudeLastInDegrees,
  //       Nj,DjInDegrees,pl);
  //    nearest
  //    latlon_reduced(values,radius,Nj,pl,longitudeFirstInDegrees,longitudeLastInDegrees);
  // } else {
  //    iterator
  //    latlon(numberOfPoints,missingValue,values,longitudeFirstInDegrees,
  //                    DiInDegrees ,Ni,Nj,iScansNegatively ,
  //                    latitudeFirstInDegrees,DjInDegrees,jScansPositively );
  //    nearest regular(values,radius,Ni,Nj);
  // }
  //
  //
  // meta latLonValues latlonvalues(values);
  // alias latitudeLongitudeValues=latLonValues;
  // meta latitudes latitudes(values,0);
  // meta longitudes longitudes(values,0);
  // meta distinctLatitudes latitudes(values,1);
  // meta distinctLongitudes longitudes(values,1);
  //
  //
  // ascii[4] zero : read_only;

  std::uint32_t mZero;

  //
  // # Rotation parameters
  // include  "grid_rotation.def"
  RotationSettings mRotation;
};

} // namespace GRIB1
} // namespace SmartMet