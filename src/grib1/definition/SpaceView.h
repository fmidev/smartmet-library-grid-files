// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SpaceViewImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/MemoryReader.h"
#include "../GridDefinition.h"
#include "ResolutionFlagsSettings.h"
#include "ScanningModeSettings.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template (grid_definition_90).*/

class SpaceView : public GridDefinition {
public:
  SpaceView();
  virtual ~SpaceView();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  std::uint16_t getNx() const;
  void setNx(std::uint16_t nx);
  std::uint16_t getNy() const;
  void setNy(std::uint16_t ny);
  std::int24_t getLatitudeOfSubSatellitePoint() const;
  void setLatitudeOfSubSatellitePoint(std::int24_t latitudeOfSubSatellitePoint);
  std::int24_t getLongitudeOfSubSatellitePoint() const;
  void setLongitudeOfSubSatellitePoint(std::int24_t longitudeOfSubSatellitePoint);
  const ResolutionFlagsSettings *getResolutionFlags() const;
  void setResolutionFlags(ResolutionFlagsSettings resolutionFlags);
  std::uint24_t getDx() const;
  void setDx(std::uint24_t dx);
  std::uint24_t getDy() const;
  void setDy(std::uint24_t dy);
  std::uint16_t getXpInGridLengths() const;
  void setXpInGridLengths(std::uint16_t xpInGridLengths);
  std::uint16_t getYpInGridLengths() const;
  void setYpInGridLengths(std::uint16_t ypInGridLengths);
  const ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings scanningMode);
  std::uint24_t getOrientationOfTheGrid() const;
  void setOrientationOfTheGrid(std::uint24_t orientationOfTheGrid);
  std::uint24_t getNrInRadiusOfEarth() const;
  void setNrInRadiusOfEarth(std::uint24_t nrInRadiusOfEarth);
  std::uint16_t getXo() const;
  void setXo(std::uint16_t xo);
  std::uint16_t getYo() const;
  void setYo(std::uint16_t yo);

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
  // # GRID DEFINITION Space view, perspective or orthographic
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 90;
  //
  // unsigned[2] Nx  : dump;

  std::uint16_t mNx;

  // alias numberOfPointsAlongXAxis = Nx;
  // alias Ni = Nx;
  // alias geography.Nx=Nx;
  //
  // unsigned[2] Ny  : dump;

  std::uint16_t mNy;

  // alias numberOfPointsAlongYAxis = Ny;
  // alias Nj = Ny;
  // alias geography.Ny=Ny;
  //
  // signed[3] latitudeOfSubSatellitePoint ;

  std::int24_t mLatitudeOfSubSatellitePoint;

  // meta geography.latitudeOfSubSatellitePointInDegrees  scale(latitudeOfSubSatellitePoint,oneConstant,grib1divider,truncateDegrees) : dump;
  // alias Lap=latitudeOfSubSatellitePoint;
  //
  // signed[3] longitudeOfSubSatellitePoint ;

  std::int24_t mLongitudeOfSubSatellitePoint;

  // meta geography.longitudeOfSubSatellitePointInDegrees  scale(longitudeOfSubSatellitePoint,oneConstant,grib1divider,truncateDegrees) : dump;
  // alias Lap=longitudeOfSubSatellitePoint;
  //
  // include "resolution_flags.def";

  ResolutionFlagsSettings mResolutionFlags;

  //
  // unsigned[3] dx  : dump;

  std::uint24_t mDx;

  // alias geography.dx=dx;
  //
  // unsigned[3] dy  : dump;

  std::uint24_t mDy;

  // alias geography.dy=dy;
  //
  // unsigned[2] XpInGridLengths  : dump;

  std::uint16_t mXpInGridLengths;

  // alias geography.XpInGridLengths=XpInGridLengths;
  //
  //
  // unsigned[2] YpInGridLengths  : dump;

  std::uint16_t mYpInGridLengths;

  // alias geography.YpInGridLengths=YpInGridLengths;
  //
  // include "scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // unsigned[3] orientationOfTheGrid : edition_specific ;

  std::uint24_t mOrientationOfTheGrid;

  // meta geography.orientationOfTheGridInDegrees  scale(orientationOfTheGrid,oneConstant,grib1divider,truncateDegrees) : dump;
  //
  // unsigned[3] NrInRadiusOfEarth : edition_specific,no_copy;

  std::uint24_t mNrInRadiusOfEarth;

  // alias altitudeOfTheCameraFromTheEarthSCenterMeasuredInUnitsOfTheEarth = NrInRadiusOfEarth;
  //
  // unsigned[2]  Xo : dump;

  std::uint16_t mXo;

  // alias xCoordinateOfOriginOfSectorImage=Xo;
  // alias geography.Xo=Xo;
  //
  // unsigned[2] Yo  : dump;

  std::uint16_t mYo;

  // alias yCoordinateOfOriginOfSectorImage=Yo;
  // alias geography.Yo=Yo;
  //
  // #Ce      Length is normally 32 + stretched and/or rotated
  // #Ce      parameters + vertical coordinate parameters + list of
  // #Ce      numbers of points.
  // #Ce      (Lambert conformal and Mercator are 42 octets in length,
  // #Ce      while Space view is 40 for ECMWF (44 in GRIB specification)
  // if ( centre != 98 ) {
  //   pad padding_grid90_1(6);
  // }
  //
  // meta numberOfDataPoints number_of_points(Ni,Nj,PLPresent,pl) : dump;
  // alias numberOfPoints=numberOfDataPoints;
  // meta numberOfValues number_of_values(values,bitsPerValue,numberOfDataPoints,bitmapPresent,bitmap,numberOfCodedValues) : dump;
  // #alias ls.valuesCount=numberOfValues;
  //
};

} // namespace GRIB1
} // namespace SmartMet
