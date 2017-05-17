// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TransverseMercatorImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/GridDefinition.h"
#include "grib2/definition/EarthShapeSettings.h"
#include "grib2/definition/ResolutionSettings.h"
#include "grib2/definition/ScanningModeSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.12).*/

class TransverseMercator : public GridDefinition {
public:
  TransverseMercator();
  virtual ~TransverseMercator();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const EarthShapeSettings *getEarthShape() const;
  const T::UInt32_opt &getNi() const;
  const T::UInt32_opt &getNj() const;
  const T::Int32_opt &getLatitudeOfReferencePoint() const;
  const T::Int32_opt &getLongitudeOfReferencePoint() const;
  const ResolutionSettings *getResolution() const;
  float getScaleFactorAtReferencePoint() const;
  const T::Int32_opt &getXR() const;
  const T::Int32_opt &getYR() const;
  const ScanningModeSettings *getScanningMode() const;
  const T::UInt32_opt &getDi() const;
  const T::UInt32_opt &getDj() const;
  const T::Int32_opt &getX1() const;
  const T::Int32_opt &getY1() const;
  const T::Int32_opt &getX2() const;
  const T::Int32_opt &getY2() const;

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
  // # TEMPLATE 3.12, Transverse Mercator
  //
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  //
  // unsigned[4] Ni : dump;

  T::UInt32_opt mNi;

  // alias numberOfPointsAlongAParallel=Ni;
  // alias Nx = Ni;
  // alias geography.Ni=Ni;
  //
  // unsigned[4] Nj : dump;

  T::UInt32_opt mNj;

  // alias numberOfPointsAlongAMeridian=Nj;
  // alias Ny = Nj ;
  // alias geography.Nj=Nj;
  //
  // # LaR - geographic latitude of reference point
  // signed[4] latitudeOfReferencePoint: edition_specific,no_copy ;

  T::Int32_opt mLatitudeOfReferencePoint;

  // alias LaR = latitudeOfReferencePoint;
  // meta geography.latitudeOfReferencePointInDegrees
  // scale(latitudeOfReferencePoint,oneConstant,grib2divider,truncateDegrees) :
  // dump;
  //
  // # LoR - geographic longitude of reference point
  // signed[4] longitudeOfReferencePoint : edition_specific,no_copy;

  T::Int32_opt mLongitudeOfReferencePoint;

  // alias LoR = longitudeOfReferencePoint;
  // meta geography.longitudeOfReferencePointInDegrees
  // scale(longitudeOfReferencePoint,oneConstant,grib2divider,truncateDegrees) :
  // dump;
  //
  // include "template.3.resolution_flags.def";

  ResolutionSettings mResolution;

  //
  // # m - scale factor at reference point ratio of distance on map to distance
  // on spheroid
  // # (IEEE 32-bit floating-point values)
  // ieeefloat scaleFactorAtReferencePoint : edition_specific,no_copy;

  float mScaleFactorAtReferencePoint;

  // alias m = scaleFactorAtReferencePoint;
  // alias geography.m=m;
  //
  // # XR - false easting, i-direction coordinate of reference point in units of
  // 10-2 m
  // signed[4] XR : edition_specific,no_copy;

  T::Int32_opt mXR;

  // alias falseEasting = XR;
  // meta geography.XRInMetres scale(XR,one,hundred) : dump;
  //
  // # YR - false northing, j-direction coordinate of reference point in units
  // of 10-2 m
  // signed[4] YR : edition_specific,no_copy ;

  T::Int32_opt mYR;

  // alias falseNorthing = YR;
  // meta geography.YRInMetres scale(YR,one,hundred) : dump;
  //
  // include "template.3.scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // # Di - i-direction increment length in units of 10-2 m
  // unsigned[4] Di : edition_specific,no_copy;

  T::UInt32_opt mDi;

  // alias iDirectionIncrementGridLength = Di;
  // meta geography.DiInMetres scale(Di,oneConstant,hundred,truncateDegrees) :
  // dump;
  //
  // # Dj - j-direction increment length in units of 10-2 m
  // unsigned[4] Dj : edition_specific,no_copy;

  T::UInt32_opt mDj;

  // alias jDirectionIncrementGridLength = Dj;
  // meta geography.DjInMetres scale(Dj,oneConstant,hundred,truncateDegrees) :
  // dump;
  //
  // # x1 - i-direction coordinate of the first grid point in units of 10-2 m
  // signed[4] X1 : no_copy;

  T::Int32_opt mX1;

  // meta geography.X1InGridLengths scale(X1,one,hundred) : dump;
  //
  // # y1 - j-direction coordinate of the first grid point in units of 10-2 m
  // signed[4] Y1 : no_copy;

  T::Int32_opt mY1;

  // meta geography.Y1InGridLengths scale(Y1,one,hundred) : dump;
  //
  // # x2 - i-direction coordinate of the last grid point in units of 10-2 m
  // signed[4] X2 : no_copy;

  T::Int32_opt mX2;

  // meta geography.X2InGridLengths scale(X2,one,hundred) : dump;
  //
  // # y2 - j-direction coordinate of the last grid point in units of 10-2 m
  // signed[4] Y2 : no_copy;

  T::Int32_opt mY2;

  // meta geography.Y2InGridLengths scale(Y2,one,hundred) : dump;
  //
};

} // namespace GRIB2
} // namespace SmartMet
