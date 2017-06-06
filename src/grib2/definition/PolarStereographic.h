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
#include "grib2/GridDefinition.h"
#include "grib2/definition/EarthShapeSettings.h"
#include "grib2/definition/ScanningModeSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.20).*/

class PolarStereographic : public GridDefinition {
public:
  PolarStereographic();
  virtual ~PolarStereographic();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const EarthShapeSettings *getEarthShape() const;
  const T::UInt32_opt &getNx() const;
  const T::UInt32_opt &getNy() const;
  const T::Int32_opt &getLatitudeOfFirstGridPoint() const;
  const T::UInt32_opt &getLongitudeOfFirstGridPoint() const;
  std::uint8_t getResolutionAndComponentFlag() const;
  const T::Int32_opt &getLaD() const;
  const T::Int32_opt &getOrientationOfTheGrid() const;
  const T::UInt32_opt &getDx() const;
  const T::UInt32_opt &getDy() const;
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
  //
  // # START 2/template.3.20
  // ----------------------------------------------------------------------
  // # TEMPLATE 3.20, Polar stereographic projection
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  // transient oneThousand=1000;
  //
  // #  Nx - number of points along X-axis
  // unsigned[4] Nx  : dump;

  T::UInt32_opt mNx;

  // alias Ni =  Nx;
  // alias numberOfPointsAlongXAxis =  Nx;
  // alias geography.Nx=Nx;
  //
  // #  Ny - number of points along Y-axis
  // unsigned[4] Ny  : dump;

  T::UInt32_opt mNy;

  // alias Nj  = Ny;
  // alias numberOfPointsAlongYAxis  = Ny;
  // alias geography.Ny=Ny;
  //
  // #  La1 - latitude of first grid point
  // signed[4] latitudeOfFirstGridPoint : edition_specific ;

  T::Int32_opt mLatitudeOfFirstGridPoint;

  // meta geography.latitudeOfFirstGridPointInDegrees
  // scale(latitudeOfFirstGridPoint,oneConstant,grib2divider,truncateDegrees) :
  // dump;
  // alias La1 =  latitudeOfFirstGridPoint;
  //
  // #  Lo1 - longitude of first grid point
  // unsigned[4] longitudeOfFirstGridPoint : edition_specific;

  T::UInt32_opt mLongitudeOfFirstGridPoint;

  // meta geography.longitudeOfFirstGridPointInDegrees
  // scale(longitudeOfFirstGridPoint,oneConstant,grib2divider,truncateDegrees) :
  // dump;
  // alias Lo1 =  longitudeOfFirstGridPoint;
  //
  // #  Resolution and component flag
  // # NOTE 1 NOT FOUND
  // flags[1] resolutionAndComponentFlag
  // 'grib2/tables/[tablesVersion]/3.3.table' : dump;

  std::uint8_t mResolutionAndComponentFlag;

  //
  // #  LaD - Latitude where Dx and Dy are specified
  // signed[4] LaD  : edition_specific;

  T::Int32_opt mLaD;

  // alias latitudeWhereDxAndDyAreSpecified=LaD;
  // meta geography.LaDInDegrees
  // scale(LaD,oneConstant,grib2divider,truncateDegrees) : dump;
  // alias latitudeWhereDxAndDyAreSpecifiedInDegrees=LaDInDegrees;
  //
  // #  LoV - orientation of the grid
  // # NOTE 2 NOT FOUND
  // signed[4] orientationOfTheGrid  : edition_specific;

  T::Int32_opt mOrientationOfTheGrid;

  // alias LoV =  orientationOfTheGrid ;
  // meta geography.orientationOfTheGridInDegrees
  // scale(orientationOfTheGrid,oneConstant,grib2divider,truncateDegrees) :
  // dump;
  //
  // #  Dx - X-direction grid length
  // # NOTE 3: Grid length is in units of 10-3 m at the latitude specified by
  // LaD
  // unsigned[4] Dx  : edition_specific;

  T::UInt32_opt mDx;

  // meta geography.DxInMetres scale(Dx,one,thousand,truncateDegrees) : dump;
  // alias xDirectionGridLength=Dx;
  //
  // #  Dy - Y-direction grid length
  // # NOTE 3: Grid length is in units of 10-3 m at the latitude specified by
  // LaD
  // unsigned[4] Dy  : edition_specific;

  T::UInt32_opt mDy;

  // meta geography.DyInMetres scale(Dy,one,thousand,truncateDegrees) : dump;
  // alias yDirectionGridLength=Dy;
  //
  // #  Projection centre flag
  // flags[1] projectionCentreFlag 'grib2/tables/[tablesVersion]/3.5.table' :
  // dump;

  std::uint8_t mProjectionCentreFlag;

  // # Note our flagbit numbers go from 7 to 0, while WMO convention is from 1
  // to 8
  // # If bit 1 is 0, then the North Pole is on the projection plane
  // # If bit 1 is 1, then the South Pole is on the projection plane
  // flagbit southPoleOnProjectionPlane(projectionCentreFlag,7) : dump;   # WMO
  // bit 1
  //
  // include "template.3.scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  //
  // iterator polar_stereographic(numberOfPoints,missingValue,values,
  //           radius,Nx,Ny,
  //           latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //           southPoleOnProjectionPlane,
  //           orientationOfTheGridInDegrees,
  //           DxInMetres,DyInMetres,
  //           iScansNegatively,
  //           jScansPositively,
  //           jPointsAreConsecutive,
  //           alternativeRowScanning);
  //
  //
  // # END   2/template.3.20
  // ----------------------------------------------------------------------
};

} // namespace GRIB2
} // namespace SmartMet