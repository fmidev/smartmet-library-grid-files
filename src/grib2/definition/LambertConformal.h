// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'LambertConformalImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/MemoryReader.h"
#include "../GridDefinition.h"
#include "EarthShapeSettings.h"
#include "ResolutionSettings.h"
#include "ScanningModeSettings.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.30).*/

class LambertConformal : public GridDefinition {
public:
  LambertConformal();
  virtual ~LambertConformal();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings earthShape);
  const T::UInt32_opt &getNx() const;
  void setNx(T::UInt32_opt nx);
  const T::UInt32_opt &getNy() const;
  void setNy(T::UInt32_opt ny);
  const T::Int32_opt &getLatitudeOfFirstGridPoint() const;
  void setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint);
  const T::UInt32_opt &getLongitudeOfFirstGridPoint() const;
  void setLongitudeOfFirstGridPoint(T::UInt32_opt longitudeOfFirstGridPoint);
  const ResolutionSettings *getResolution() const;
  void setResolution(ResolutionSettings resolution);
  const T::Int32_opt &getLaD() const;
  void setLaD(T::Int32_opt laD);
  const T::UInt32_opt &getLoV() const;
  void setLoV(T::UInt32_opt loV);
  const T::UInt32_opt &getDx() const;
  void setDx(T::UInt32_opt dx);
  const T::UInt32_opt &getDy() const;
  void setDy(T::UInt32_opt dy);
  std::uint8_t getProjectionCentreFlag() const;
  void setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
  const ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings scanningMode);
  const T::Int32_opt &getLatin1() const;
  void setLatin1(T::Int32_opt latin1);
  const T::Int32_opt &getLatin2() const;
  void setLatin2(T::Int32_opt latin2);
  const T::Int32_opt &getLatitudeOfSouthernPole() const;
  void setLatitudeOfSouthernPole(T::Int32_opt latitudeOfSouthernPole);
  const T::UInt32_opt &getLongitudeOfSouthernPole() const;
  void setLongitudeOfSouthernPole(T::UInt32_opt longitudeOfSouthernPole);

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
  // # TEMPLATE 3.30, Lambert conformal
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  //
  // unsigned[4] Nx  : dump;

  T::UInt32_opt mNx;

  // alias Ni  = Nx;
  // alias numberOfPointsAlongXAxis  = Nx;
  // alias geography.Nx=Nx;
  //
  // unsigned[4] Ny  : dump;

  T::UInt32_opt mNy;

  // alias Nj  = Ny;
  // alias numberOfPointsAlongYAxis  = Ny;
  // alias geography.Ny=Ny;
  //
  // #  La1 - latitude of first grid point
  // signed[4] latitudeOfFirstGridPoint : edition_specific;

  T::Int32_opt mLatitudeOfFirstGridPoint;

  // alias La1  = latitudeOfFirstGridPoint;
  // meta  geography.latitudeOfFirstGridPointInDegrees
  //         scale(latitudeOfFirstGridPoint,one,grib2divider,truncateDegrees) : dump;
  // alias La1InDegrees=latitudeOfFirstGridPointInDegrees;
  // #meta latitudeOfFirstGridPointInMicrodegrees times(latitudeOfFirstGridPointInDegrees,oneConstant): no_copy;
  //
  // #  Lo1 - longitude of first grid point
  // unsigned[4] longitudeOfFirstGridPoint : edition_specific;

  T::UInt32_opt mLongitudeOfFirstGridPoint;

  // alias Lo1  = longitudeOfFirstGridPoint;
  // meta  geography.longitudeOfFirstGridPointInDegrees
  //         scale(longitudeOfFirstGridPoint,one,grib2divider,truncateDegrees) : dump;
  // alias Lo1InDegrees = longitudeOfFirstGridPointInDegrees;
  // #meta longitudeOfFirstGridPointInMicrodegrees times(longitudeOfFirstGridPoint,oneConstant) : no_copy;
  //
  // include "template.3.resolution_flags.def";

  ResolutionSettings mResolution;

  //
  // #  LaD - Latitude where Dx and Dy are specified
  // signed[4] LaD : edition_specific ;

  T::Int32_opt mLaD;

  // alias latitudeWhereDxAndDyAreSpecified=LaD;
  // meta  geography.LaDInDegrees scale(LaD,one,grib2divider,truncateDegrees) : dump;
  //
  // #  LoV - Longitude of meridian parallel to Y-axis along which latitude increases as the Y-coordinate increases
  // unsigned[4] LoV  : edition_specific;

  T::UInt32_opt mLoV;

  // meta  geography.LoVInDegrees scale(LoV,one,grib2divider,truncateDegrees) : dump;
  //
  // #  Dx - X-direction grid length
  // # NOTE 1 NOT FOUND
  // unsigned[4] Dx : edition_specific ;

  T::UInt32_opt mDx;

  // alias xDirectionGridLength=Dx;
  // alias Di =  Dx;
  // meta  geography.DxInMetres scale(Dx,one,thousand) : dump;
  //
  // #  Dy - Y-direction grid length
  // # NOTE 1 NOT FOUND
  // unsigned[4] Dy : edition_specific ;

  T::UInt32_opt mDy;

  // alias yDirectionGridLength=Dy ;
  // alias Dj =  Dy;
  // meta  geography.DyInMetres scale(Dy,one,thousand) : dump;
  //
  // #  Projection centre flag
  // flags[1] projectionCentreFlag 'grib2/tables/[tablesVersion]/3.5.table' : dump;

  std::uint8_t mProjectionCentreFlag;

  //
  // include "template.3.scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // #  Latin 1 - first latitude from the pole at which the secant cone cuts the sphere
  // signed[4] Latin1   : edition_specific;

  T::Int32_opt mLatin1;

  // alias FirstLatitude=Latin1;
  // meta  geography.Latin1InDegrees scale(Latin1,one,grib2divider,truncateDegrees) : dump;
  //
  // #  Latin 2 - second latitude from the pole at which the secant cone cuts the sphere
  // signed[4] Latin2  : dump;

  T::Int32_opt mLatin2;

  // alias SecondLatitude=Latin2;
  // meta  geography.Latin2InDegrees scale(Latin2,one,grib2divider,truncateDegrees) : dump;
  //
  // #  Latitude of the southern pole of projection
  // signed[4] latitudeOfSouthernPole : edition_specific;

  T::Int32_opt mLatitudeOfSouthernPole;

  // alias latitudeOfTheSouthernPoleOfProjection=latitudeOfSouthernPole;
  // meta  geography.latitudeOfSouthernPoleInDegrees   scale(latitudeOfSouthernPole          ,one,grib2divider,truncateDegrees) : dump;
  //
  // #  Longitude of the southern pole of projection
  // unsigned[4] longitudeOfSouthernPole : edition_specific;

  T::UInt32_opt mLongitudeOfSouthernPole;

  // alias longitudeOfTheSouthernPoleOfProjection=longitudeOfSouthernPole;
  // meta  geography.longitudeOfSouthernPoleInDegrees   scale(longitudeOfSouthernPole,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // iterator lambert_conformal(numberOfPoints,missingValue,values,
  //           radius,Nx,Ny,
  //           LoVInDegrees,LaDInDegrees,
  //           Latin1InDegrees,Latin2InDegrees,
  //           latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //           DxInMetres,DyInMetres,
  //           iScansNegatively,
  //           jScansPositively,
  //           jPointsAreConsecutive,
  //           alternativeRowScanning);
  //
  // nearest lambert_conformal(values,radius,Nx,Ny);
  //
  // meta latLonValues latlonvalues(values);
  // alias latitudeLongitudeValues=latLonValues;
  // meta latitudes latitudes(values,0);
  // meta longitudes longitudes(values,0);
  //
};

} // namespace GRIB2
} // namespace SmartMet
