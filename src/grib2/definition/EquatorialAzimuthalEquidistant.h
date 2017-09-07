// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'EquatorialAzimuthalEquidistantImpl.*' files.
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
/*! \brief The class is automatically created from the template (3.110).*/

class EquatorialAzimuthalEquidistant : public GridDefinition {
public:
  EquatorialAzimuthalEquidistant();
  virtual ~EquatorialAzimuthalEquidistant();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings earthShape);
  const T::UInt32_opt &getNumberOfPointsAlongXAxis() const;
  void setNumberOfPointsAlongXAxis(T::UInt32_opt numberOfPointsAlongXAxis);
  const T::UInt32_opt &getNumberOfPointsAlongYAxis() const;
  void setNumberOfPointsAlongYAxis(T::UInt32_opt numberOfPointsAlongYAxis);
  const T::Int32_opt &getLatitudeOfTangencyPoint() const;
  void setLatitudeOfTangencyPoint(T::Int32_opt latitudeOfTangencyPoint);
  const T::UInt32_opt &getLongitudeOfTangencyPoint() const;
  void setLongitudeOfTangencyPoint(T::UInt32_opt longitudeOfTangencyPoint);
  std::uint8_t getResolutionAndComponentFlag() const;
  void setResolutionAndComponentFlag(std::uint8_t resolutionAndComponentFlag);
  const T::UInt32_opt &getDx() const;
  void setDx(T::UInt32_opt dx);
  const T::UInt32_opt &getDy() const;
  void setDy(T::UInt32_opt dy);
  const T::UInt8_opt &getProjectionCenterFlag() const;
  void setProjectionCenterFlag(T::UInt8_opt projectionCenterFlag);
  const ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings scanningMode);

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
  //
  // # TEMPLATE 3.110, Equatorial azimuthal equidistant projection
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  //
  // #  Nx - number of points along X-axis
  // unsigned[4] numberOfPointsAlongXAxis : dump  ;

  T::UInt32_opt mNumberOfPointsAlongXAxis;

  //
  // alias Nx  = numberOfPointsAlongXAxis;
  // #  Ny - number of points along Y-axis
  // unsigned[4] numberOfPointsAlongYAxis : dump  ;

  T::UInt32_opt mNumberOfPointsAlongYAxis;

  //
  // alias Ny =  numberOfPointsAlongYAxis;
  // #  La1 - latitude of tangency point
  // # (centre of grid)
  // signed[4] latitudeOfTangencyPoint  : dump ;

  T::Int32_opt mLatitudeOfTangencyPoint;

  //
  // alias La1  = latitudeOfTangencyPoint;
  // #  Lo1 - longitude of tangency point
  // unsigned[4] longitudeOfTangencyPoint  : dump ;

  T::UInt32_opt mLongitudeOfTangencyPoint;

  //
  // alias Lo1  = longitudeOfTangencyPoint;
  // #  Resolution and component flag
  // flags[1] resolutionAndComponentFlag 'grib2/tables/[tablesVersion]/3.3.table' : dump ;

  std::uint8_t mResolutionAndComponentFlag;

  //
  // #  Dx - X-direction grid length in units of 10 -3 m as measured at the point of the axis
  // unsigned[4] Dx  : dump ;

  T::UInt32_opt mDx;

  //
  // #  Dy - Y-direction grid length in units of 10 -3 m as measured at the point of the axis
  // unsigned[4] Dy  : dump ;

  T::UInt32_opt mDy;

  //
  // #  Projection centre flag
  // unsigned[1] projectionCenterFlag  : dump ;

  T::UInt8_opt mProjectionCenterFlag;

  //
  // include "template.3.scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
};

} // namespace GRIB2
} // namespace SmartMet
