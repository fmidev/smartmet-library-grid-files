// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'EquatorialAzimuthalEquidistantImpl.*' files.
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
/*! \brief The class is automatically created from the template (3.110).*/

class EquatorialAzimuthalEquidistant : public GridDefinition {
public:
  EquatorialAzimuthalEquidistant();
  virtual ~EquatorialAzimuthalEquidistant();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings &earthShape);
  const T::UInt32_opt &getNumberOfPointsAlongXAxis() const;
  void setNumberOfPointsAlongXAxis(T::UInt32_opt numberOfPointsAlongXAxis);
  const T::UInt32_opt &getNumberOfPointsAlongYAxis() const;
  void setNumberOfPointsAlongYAxis(T::UInt32_opt numberOfPointsAlongYAxis);
  const T::Int32_opt &getLatitudeOfTangencyPoint() const;
  void setLatitudeOfTangencyPoint(T::Int32_opt latitudeOfTangencyPoint);
  const T::UInt32_opt &getLongitudeOfTangencyPoint() const;
  void setLongitudeOfTangencyPoint(T::UInt32_opt longitudeOfTangencyPoint);
  std::uint8_t getResolutionAndComponentFlags() const;
  void setResolutionAndComponentFlags(std::uint8_t resolutionAndComponentFlags);
  const T::UInt32_opt &getDx() const;
  void setDx(T::UInt32_opt dx);
  const T::UInt32_opt &getDy() const;
  void setDy(T::UInt32_opt dy);
  const T::UInt8_opt &getProjectionCenterFlag() const;
  void setProjectionCenterFlag(T::UInt8_opt projectionCenterFlag);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.110, Equatorial azimuthal equidistant projection
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

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
  // flags[1] resolutionAndComponentFlags 'grib2/tables/[tablesVersion]/3.3.table' : dump ;

  std::uint8_t mResolutionAndComponentFlags;

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
  // include "grib2/template.3.scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
};

} // namespace GRIB2
} // namespace SmartMet
