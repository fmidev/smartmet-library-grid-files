// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'PolarStereographicImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "EarthShapeSettings.h"
#include "ScanningModeSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.20).*/

class PolarStereographic : public GridDefinition {
public:
  PolarStereographic();
  ~PolarStereographic() override;

  uint getTemplateNumber() const override;
  GridDefinition *createGridDefinition() const override;
  void read(MemoryReader &memoryReader) override;
  void write(DataWriter &dataWriter) override;
  void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const override;
  void print(std::ostream &stream, uint level, uint optionFlags) const override;
  T::Hash countHash() override;

  EarthShapeSettings *getEarthShape() const override;
  void setEarthShape(EarthShapeSettings &earthShape);
  const T::UInt32_opt &getNx() const;
  void setNx(T::UInt32_opt nx);
  const T::UInt32_opt &getNy() const;
  void setNy(T::UInt32_opt ny);
  const T::Int32_opt &getLatitudeOfFirstGridPoint() const;
  void setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint);
  const T::UInt32_opt &getLongitudeOfFirstGridPoint() const;
  void setLongitudeOfFirstGridPoint(T::UInt32_opt longitudeOfFirstGridPoint);
  std::uint8_t getResolutionAndComponentFlags() const;
  void setResolutionAndComponentFlags(std::uint8_t resolutionAndComponentFlags);
  const T::Int32_opt &getLaD() const;
  void setLaD(T::Int32_opt laD);
  const T::Int32_opt &getOrientationOfTheGrid() const;
  void setOrientationOfTheGrid(T::Int32_opt orientationOfTheGrid);
  const T::UInt32_opt &getDx() const;
  void setDx(T::UInt32_opt dx);
  const T::UInt32_opt &getDy() const;
  void setDy(T::UInt32_opt dy);
  std::uint8_t getProjectionCentreFlag() const;
  void setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.20, Polar stereographic projection
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

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

  // meta geography.latitudeOfFirstGridPointInDegrees scale(latitudeOfFirstGridPoint,oneConstant,grib2divider,truncateDegrees) : dump;
  // alias La1 =  latitudeOfFirstGridPoint;
  //
  // #  Lo1 - longitude of first grid point
  // unsigned[4] longitudeOfFirstGridPoint : edition_specific;

  T::UInt32_opt mLongitudeOfFirstGridPoint;

  // meta geography.longitudeOfFirstGridPointInDegrees scale(longitudeOfFirstGridPoint,oneConstant,grib2divider,truncateDegrees) : dump;
  // alias Lo1 =  longitudeOfFirstGridPoint;
  //
  // #  Resolution and component flag
  // flags[1] resolutionAndComponentFlags 'grib2/tables/[tablesVersion]/3.3.table' : dump;

  std::uint8_t mResolutionAndComponentFlags;

  //
  // #  LaD - Latitude where Dx and Dy are specified
  // signed[4] LaD  : edition_specific;

  T::Int32_opt mLaD;

  // alias latitudeWhereDxAndDyAreSpecified=LaD;
  // meta geography.LaDInDegrees scale(LaD,oneConstant,grib2divider,truncateDegrees) : dump;
  // alias latitudeWhereDxAndDyAreSpecifiedInDegrees=LaDInDegrees;
  //
  // #  LoV - orientation of the grid
  // #  LoV is the longitude value of the meridian which is parallel to the y-axis (or columns of the grid)
  // #  along which latitude increases as the y-coordinate increases
  // signed[4] orientationOfTheGrid  : edition_specific;

  T::Int32_opt mOrientationOfTheGrid;

  // alias LoV =  orientationOfTheGrid ;
  // meta geography.orientationOfTheGridInDegrees scale(orientationOfTheGrid,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // #  Dx - X-direction grid length
  // #  Grid length is in units of 10-3 m at the latitude specified by LaD
  // unsigned[4] Dx  : edition_specific;

  T::UInt32_opt mDx;

  // meta geography.DxInMetres scale(Dx,one,thousand,truncateDegrees) : dump;
  // alias xDirectionGridLength=Dx;
  //
  // #  Dy - Y-direction grid length
  // #  Grid length is in units of 10-3 m at the latitude specified by LaD
  // unsigned[4] Dy  : edition_specific;

  T::UInt32_opt mDy;

  // meta geography.DyInMetres scale(Dy,one,thousand,truncateDegrees) : dump;
  // alias yDirectionGridLength=Dy;
  //
  // #  Projection centre flag
  // flags[1] projectionCentreFlag 'grib2/tables/[tablesVersion]/3.5.table' : dump;

  std::uint8_t mProjectionCentreFlag;

  // # Note our flagbit numbers go from 7 to 0, while WMO convention is from 1 to 8
  // # If bit 1 is 0, then the North Pole is on the projection plane
  // # If bit 1 is 1, then the South Pole is on the projection plane
  // flagbit southPoleOnProjectionPlane(projectionCentreFlag,7) : dump;   # WMO bit 1
  //
  // include "grib2/template.3.scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
  //
  // iterator polar_stereographic(numberOfPoints,missingValue,values,
  //           radius,Nx,Ny,
  //           latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //           southPoleOnProjectionPlane,
  //           orientationOfTheGridInDegrees,
  //           LaDInDegrees,
  //           DxInMetres,DyInMetres,
  //           iScansNegatively,
  //           jScansPositively,
  //           jPointsAreConsecutive,
  //           alternativeRowScanning);
  //
  // nearest polar_stereographic(values,radius,Nx,Ny);
  //
  // meta latLonValues latlonvalues(values);
  // alias latitudeLongitudeValues=latLonValues;
  // meta latitudes latitudes(values,0);
  // meta longitudes longitudes(values,0);
};

} // namespace GRIB2
} // namespace SmartMet
