// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'LambertAzimuthalEqualAreaImpl.*' files.
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
/*! \brief The class is automatically created from the template (3.140).*/

class LambertAzimuthalEqualArea : public GridDefinition {
public:
  LambertAzimuthalEqualArea();
  virtual ~LambertAzimuthalEqualArea();

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
  const T::Int32_opt &getLatitudeOfFirstGridPoint() const;
  void setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint);
  const T::Int32_opt &getLongitudeOfFirstGridPoint() const;
  void setLongitudeOfFirstGridPoint(T::Int32_opt longitudeOfFirstGridPoint);
  const T::Int32_opt &getStandardParallelInMicrodegrees() const;
  void setStandardParallelInMicrodegrees(T::Int32_opt standardParallelInMicrodegrees);
  const T::Int32_opt &getCentralLongitudeInMicrodegrees() const;
  void setCentralLongitudeInMicrodegrees(T::Int32_opt centralLongitudeInMicrodegrees);
  std::uint8_t getResolutionAndComponentFlag() const;
  void setResolutionAndComponentFlag(std::uint8_t resolutionAndComponentFlag);
  const T::UInt32_opt &getXDirectionGridLengthInMillimetres() const;
  void setXDirectionGridLengthInMillimetres(T::UInt32_opt xDirectionGridLengthInMillimetres);
  const T::UInt32_opt &getYDirectionGridLengthInMillimetres() const;
  void setYDirectionGridLengthInMillimetres(T::UInt32_opt yDirectionGridLengthInMillimetres);
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
  // # START 2/template.3.140 ----------------------------------------------------------------------
  // # TEMPLATE 3.140, Lambert azimuthal equal area projection
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  //
  // #  Nx - number of points along X-axis
  // unsigned[4] numberOfPointsAlongXAxis : dump  ;

  T::UInt32_opt mNumberOfPointsAlongXAxis;

  // alias Nx  = numberOfPointsAlongXAxis;
  //
  // #  Ny - number of points along Y-axis
  // unsigned[4] numberOfPointsAlongYAxis : dump  ;

  T::UInt32_opt mNumberOfPointsAlongYAxis;

  // alias Ny =  numberOfPointsAlongYAxis;
  //
  // #  La1 - latitude of first grid point
  // signed[4] latitudeOfFirstGridPoint: edition_specific ;

  T::Int32_opt mLatitudeOfFirstGridPoint;

  // alias La1 =  latitudeOfFirstGridPoint;
  // meta  geography.latitudeOfFirstGridPointInDegrees   scale(latitudeOfFirstGridPoint
  //                                                  ,one,grib2divider,truncateDegrees) : dump;
  // #meta latitudeOfFirstGridPointInMicrodegrees times(latitudeOfFirstGridPoint,mAngleMultiplier,angleDivisor): no_copy;
  //
  // #  Lo1 - longitude of first grid point
  // signed[4] longitudeOfFirstGridPoint: edition_specific ;

  T::Int32_opt mLongitudeOfFirstGridPoint;

  // alias La1 =  longitudeOfFirstGridPoint;
  // meta  geography.longitudeOfFirstGridPointInDegrees   scale(longitudeOfFirstGridPoint
  //                                                  ,one,grib2divider,truncateDegrees) : dump;
  // #meta longitudeOfFirstGridPointInMicrodegrees times(longitudeOfFirstGridPoint,mAngleMultiplier,angleDivisor) : no_copy;
  //
  // signed[4] standardParallelInMicrodegrees  : dump;

  T::Int32_opt mStandardParallelInMicrodegrees;

  // alias standardParallel=standardParallelInMicrodegrees;
  //
  // signed[4] centralLongitudeInMicrodegrees  : dump;

  T::Int32_opt mCentralLongitudeInMicrodegrees;

  // alias centralLongitude=centralLongitudeInMicrodegrees;
  //
  // #  Resolution and component flag
  // flags[1] resolutionAndComponentFlag 'grib2/tables/[tablesVersion]/3.3.table' : dump ;

  std::uint8_t mResolutionAndComponentFlag;

  //
  // #  Dx - X-direction grid length in millimetres
  // unsigned[4] xDirectionGridLengthInMillimetres  : dump ;

  T::UInt32_opt mXDirectionGridLengthInMillimetres;

  // alias Dx  = xDirectionGridLengthInMillimetres ;
  //
  // #  Dy - Y-direction grid length in millimetres
  // unsigned[4] yDirectionGridLengthInMillimetres  : dump ;

  T::UInt32_opt mYDirectionGridLengthInMillimetres;

  // alias Dy  = yDirectionGridLengthInMillimetres ;
  //
  // include "template.3.scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // iterator lambert_azimuthal_equal_area(numberOfPoints,missingValue,values,
  //           radius,Nx,Ny,
  //           latitudeOfFirstGridPointInDegrees,longitudeOfFirstGridPointInDegrees,
  //           standardParallel,centralLongitude,
  //           Dx,Dy,
  //           iScansNegatively,
  //           jScansPositively,
  //           jPointsAreConsecutive,
  //           alternativeRowScanning);
  //
  // meta latLonValues latlonvalues(values);
  // alias latitudeLongitudeValues=latLonValues;
  // meta latitudes latitudes(values,0);
  // meta longitudes longitudes(values,0);
  //
  // # END   2/template.3.140 ----------------------------------------------------------------------
};

} // namespace GRIB2
} // namespace SmartMet
