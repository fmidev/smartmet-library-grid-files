// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PolarStereographicImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib1/GridDefinition.h"
#include "grib1/definition/ResolutionFlagsSettings.h"
#include "grib1/definition/ScanningModeSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template
 * (grid_definition_5).*/

class PolarStereographic : public GridDefinition {
public:
  PolarStereographic();
  virtual ~PolarStereographic();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  std::uint16_t getNx() const;
  std::uint16_t getNy() const;
  std::int24_t getLatitudeOfFirstGridPoint() const;
  std::int24_t getLongitudeOfFirstGridPoint() const;
  const ResolutionFlagsSettings *getResolutionFlags() const;
  std::int24_t getOrientationOfTheGrid() const;
  std::uint24_t getDxInMetres() const;
  std::uint24_t getDyInMetres() const;
  std::uint8_t getProjectionCentreFlag() const;
  const ScanningModeSettings *getScanningMode() const;

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
  // # GRID DEFINITION polar stereographic
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 20;
  //
  // unsigned[2] Nx  : dump;

  std::uint16_t mNx;

  // alias Ni =  Nx;
  // alias numberOfPointsAlongXAxis =  Nx;
  // alias geography.Nx=Nx;
  //
  // unsigned[2] Ny  : dump;

  std::uint16_t mNy;

  // alias Nj =  Ny;
  // alias numberOfPointsAlongYAxis =  Ny;
  // alias geography.Ny=Ny;
  //
  // signed[3] latitudeOfFirstGridPoint : edition_specific ;

  std::int24_t mLatitudeOfFirstGridPoint;

  // meta geography.latitudeOfFirstGridPointInDegrees
  // scale(latitudeOfFirstGridPoint,oneConstant,grib1divider,truncateDegrees) :
  // dump;
  // alias La1 = latitudeOfFirstGridPoint;
  //
  // signed[3] longitudeOfFirstGridPoint : edition_specific;

  std::int24_t mLongitudeOfFirstGridPoint;

  // meta geography.longitudeOfFirstGridPointInDegrees
  // scale(longitudeOfFirstGridPoint,oneConstant,grib1divider,truncateDegrees) :
  // dump;
  // alias Lo1 = longitudeOfFirstGridPoint;
  //
  // include "resolution_flags.def";

  ResolutionFlagsSettings mResolutionFlags;

  //
  // #  LoV - orientation of the grid; i.e.  the longitude value of the meridian
  // which is parallel to the Y-axis
  // signed[3] orientationOfTheGrid  ;

  std::int24_t mOrientationOfTheGrid;

  // meta geography.orientationOfTheGridInDegrees
  // scale(orientationOfTheGrid,oneConstant,grib1divider,truncateDegrees) :
  // dump;
  // alias LoV = orientationOfTheGrid ;
  //
  // #  Dx - X-direction grid length
  // unsigned[3] DxInMetres  : dump;

  std::uint24_t mDxInMetres;

  // alias xDirectionGridLengthInMetres=DxInMetres;
  // alias Dx=DxInMetres;
  // alias geography.DxInMetres=DxInMetres;
  // alias Di = DxInMetres;
  //
  // #  Dy - Y-direction grid length
  // unsigned[3] DyInMetres  : dump;

  std::uint24_t mDyInMetres;

  // alias yDirectionGridLengthInMetres=DyInMetres;
  // alias Dy = DyInMetres;
  // alias Dj = DyInMetres;
  // alias geography.DyInMetres=DyInMetres;
  //
  // constant latitudeWhereDxAndDyAreSpecifiedInDegrees=60;
  // constant LaDInDegrees=60;
  // alias geography.LaDInDegrees=LaDInDegrees;
  //
  // #  Projection centre flag
  // unsigned[1] projectionCentreFlag : dump ;

  std::uint8_t mProjectionCentreFlag;

  // alias projectionCenterFlag=projectionCentreFlag;
  // # Note our flagbit numbers go from 7 to 0, while WMO convention is from 1
  // to 8
  // # If bit 1 is 0, then the North Pole is on the projection plane
  // # If bit 1 is 1, then the South Pole is on the projection plane
  // flagbit southPoleOnProjectionPlane(projectionCentreFlag,7) : dump; # WMO
  // bit 1
  //
  //
  // # for change_scanning_direction
  // alias yFirst=latitudeOfFirstGridPointInDegrees;
  // alias xFirst=longitudeOfFirstGridPointInDegrees;
  //
  // include "scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // pad padding_grid5_1(4);
  //
  // meta numberOfDataPoints number_of_points(Nx,Ny,PLPresent,pl) : dump;
  // alias numberOfPoints=numberOfDataPoints;
  // meta numberOfValues
  // number_of_values(values,bitsPerValue,numberOfDataPoints,bitmapPresent,bitmap,numberOfCodedValues)
  // : dump;
  // #alias ls.valuesCount=numberOfValues;
  //
  // iterator polar_stereographic(numberOfPoints,missingValue,values,
  //           radius,Nx,Ny,
  //           latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //           southPoleOnProjectionPlane,
  //           orientationOfTheGridInDegrees,
  //           Dx,Dy,
  //           iScansNegatively,
  //           jScansPositively,
  //           jPointsAreConsecutive,
  //           alternativeRowScanning);
  //
};

} // namespace GRIB1
} // namespace SmartMet
