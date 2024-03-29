// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ObliqueLambertConformalImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "ResolutionFlagsSettings.h"
#include "ScanningModeSettings.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template (grid_definition_13).*/

class ObliqueLambertConformal : public GridDefinition {
public:
  ObliqueLambertConformal();
  virtual ~ObliqueLambertConformal();

  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual T::Hash countHash() const;

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  std::uint16_t getNx() const;
  void setNx(std::uint16_t nx);
  std::uint16_t getNy() const;
  void setNy(std::uint16_t ny);
  std::int24_t getLatitudeOfFirstGridPoint() const;
  void setLatitudeOfFirstGridPoint(std::int24_t latitudeOfFirstGridPoint);
  std::int24_t getLongitudeOfFirstGridPoint() const;
  void setLongitudeOfFirstGridPoint(std::int24_t longitudeOfFirstGridPoint);
  ResolutionFlagsSettings *getResolutionFlags() const;
  void setResolutionFlags(ResolutionFlagsSettings &resolutionFlags);
  std::int24_t getLoV() const;
  void setLoV(std::int24_t loV);
  std::uint24_t getDxInMetres() const;
  void setDxInMetres(std::uint24_t dxInMetres);
  std::uint24_t getDyInMetres() const;
  void setDyInMetres(std::uint24_t dyInMetres);
  std::uint8_t getProjectionCentreFlag() const;
  void setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);
  std::int24_t getLatin1() const;
  void setLatin1(std::int24_t latin1);
  std::int24_t getLatin2() const;
  void setLatin2(std::int24_t latin2);
  std::int24_t getLatitudeOfSouthernPole() const;
  void setLatitudeOfSouthernPole(std::int24_t latitudeOfSouthernPole);
  std::int24_t getLongitudeOfSouthernPole() const;
  void setLongitudeOfSouthernPole(std::int24_t longitudeOfSouthernPole);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # GRID DEFINITION Oblique Lambert conformal, secant or tangent, conic or bi-polar
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 30;
  //
  // template commonBlock "grib1/grid_definition_lambert.def";
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
  // #  La1 - latitude of first grid point
  // signed[3] latitudeOfFirstGridPoint :  edition_specific;

  std::int24_t mLatitudeOfFirstGridPoint;

  // meta geography.latitudeOfFirstGridPointInDegrees
  //       scale(latitudeOfFirstGridPoint,oneConstant,grib1divider,truncateDegrees) : dump;
  // alias La1 = latitudeOfFirstGridPoint;
  // alias La1InDegrees=latitudeOfFirstGridPointInDegrees;
  // #meta latitudeOfFirstGridPointInMicrodegrees times(latitudeOfFirstGridPoint,thousand);
  //
  //
  // #  Lo1 - longitude of first grid point
  // signed[3] longitudeOfFirstGridPoint  : edition_specific;

  std::int24_t mLongitudeOfFirstGridPoint;

  // meta geography.longitudeOfFirstGridPointInDegrees
  //       scale(longitudeOfFirstGridPoint,oneConstant,grib1divider,truncateDegrees) : dump;
  // alias Lo1 = longitudeOfFirstGridPoint;
  // alias Lo1InDegrees = longitudeOfFirstGridPointInDegrees;
  // #meta longitudeOfFirstGridPointInMicrodegrees times(longitudeOfFirstGridPoint,thousand);
  //
  // #  Resolution and component flags
  // include "grib1/resolution_flags.def";

  mutable ResolutionFlagsSettings mResolutionFlags;

  //
  // #  LoV - orientation of the grid; i.e.  the east longitude value of the meridian which is parallel to the Y-axis
  // signed[3] LoV : edition_specific  ;

  std::int24_t mLoV;

  // meta geography.LoVInDegrees
  //     scale(LoV,oneConstant,grib1divider,truncateDegrees) : dump;
  // alias orientationOfTheGrid = LoV;
  // alias orientationOfTheGridInDegrees = LoVInDegrees;
  //
  // #  Dx - X-direction grid length (in units of metres)
  // unsigned[3] DxInMetres  : dump;

  std::uint24_t mDxInMetres;

  // alias xDirectionGridLength=DxInMetres;
  // alias geography.DxInMetres=DxInMetres ;
  // alias Dx = DxInMetres;
  // alias Di = DxInMetres;
  //
  // #  Dy - Y-direction grid length (in units of metres)
  // unsigned[3] DyInMetres  : dump;

  std::uint24_t mDyInMetres;

  // alias yDirectionGridLength=DyInMetres;
  // alias geography.DyInMetres=DyInMetres;
  // alias Dy= DyInMetres;
  // alias Dj = DyInMetres;
  //
  //
  // unsigned[1] projectionCentreFlag  : dump;

  std::uint8_t mProjectionCentreFlag;

  // # Also add the old spelling  of "centre" for backward compatibility
  // alias projectionCenterFlag=projectionCentreFlag;
  //
  // # for change_scanning_direction
  // alias yFirst=latitudeOfFirstGridPointInDegrees;
  // alias xFirst=longitudeOfFirstGridPointInDegrees;
  //
  // include "grib1/scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
  // #  Latin 1 - first latitude from the pole at which the secant cone cuts the sphere
  // signed[3] Latin1 : edition_specific;

  std::int24_t mLatin1;

  // meta geography.Latin1InDegrees scale(Latin1,oneConstant,grib1divider,truncateDegrees) : dump;
  // alias firstLatitude=Latin1;
  // alias firstLatitudeInDegrees=Latin1InDegrees;
  //
  // # GRIB Edition 1 does not have the LaD parameter so we use Latin1 instead
  // constant LaDInDegrees = Latin1InDegrees : dump;
  // alias geography.LaDInDegrees=LaDInDegrees;
  //
  // #  Latin 2 - second latitude from the pole at which the secant cone cuts the sphere
  // signed[3] Latin2 :edition_specific;

  std::int24_t mLatin2;

  // alias secondLatitude=Latin2;
  // meta geography.Latin2InDegrees scale(Latin2,oneConstant,grib1divider,truncateDegrees) : dump;
  // alias secondLatitudeInDegrees=Latin2InDegrees;
  //
  // signed[3] latitudeOfSouthernPole : no_copy;

  std::int24_t mLatitudeOfSouthernPole;

  // meta  geography.latitudeOfSouthernPoleInDegrees
  //         scale(latitudeOfSouthernPole,oneConstant,grib1divider,truncateDegrees) : dump;
  //
  // signed[3] longitudeOfSouthernPole : no_copy;

  std::int24_t mLongitudeOfSouthernPole;

  // meta  geography.longitudeOfSouthernPoleInDegrees
  //         scale(longitudeOfSouthernPole,oneConstant,grib1divider,truncateDegrees) : dump;
  //
  // meta numberOfDataPoints number_of_points(Nx,Ny,PLPresent,pl) : dump;
  // alias numberOfPoints=numberOfDataPoints;
  // meta numberOfValues number_of_values(values,bitsPerValue,numberOfDataPoints,
  //                                     bitmapPresent,bitmap,numberOfCodedValues) : dump;
  // #alias ls.valuesCount=numberOfValues;
  //
  // iterator lambert_conformal(numberOfPoints,missingValue,values,
  //           radius,Nx,Ny,
  //           LoVInDegrees,LaDInDegrees,
  //           Latin1InDegrees,Latin2InDegrees,
  //           latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //           Dx,Dy,
  //           iScansNegatively,
  //           jScansPositively,
  //           jPointsAreConsecutive,
  //           alternativeRowScanning);
  //
  //
  // meta latLonValues latlonvalues(values);
  // alias latitudeLongitudeValues=latLonValues;
  // meta latitudes latitudes(values,0);
  // meta longitudes longitudes(values,0);
  // meta distinctLatitudes latitudes(values,1);
  // meta distinctLongitudes longitudes(values,1);
  //
  // nearest lambert_conformal(values,radius,Nx,Ny);
  //
  // pad padding_grid3_1(2);
};

} // namespace GRIB1
} // namespace SmartMet
