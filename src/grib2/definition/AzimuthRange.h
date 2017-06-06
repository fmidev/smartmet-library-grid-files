// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AzimuthRangeImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/GridDefinition.h"
#include "grib2/definition/ScanningModeSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.120).*/

class AzimuthRange : public GridDefinition {
public:
  AzimuthRange();
  virtual ~AzimuthRange();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt32_opt &getNumberOfDataBinsAlongRadials() const;
  const T::UInt32_opt &getNumberOfRadials() const;
  const T::Int32_opt &getLatitudeOfCenterPoint() const;
  const T::UInt32_opt &getLongitudeOfCenterPoint() const;
  const T::UInt32_opt &getSpacingOfBinsAlongRadials() const;
  const T::UInt32_opt &getOffsetFromOriginToInnerBound() const;
  const ScanningModeSettings *getScanningMode() const;
  const T::Int16_opt &getStartingAzimuth() const;
  const T::Int16_opt &getAzimuthalWidth() const;

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
  // # TEMPLATE 3.120, Azimuth-range projection
  // #  Nb - number of data bins along radials (A data bin is a data point
  // representing the volume centred on it)
  // unsigned[4] numberOfDataBinsAlongRadials ;

  T::UInt32_opt mNumberOfDataBinsAlongRadials;

  // alias Nb =  numberOfDataBinsAlongRadials;
  //
  // #  Nr - number of radials
  // unsigned[4] numberOfRadials ;

  T::UInt32_opt mNumberOfRadials;

  // alias Nr  = numberOfRadials;
  //
  // #  La1 - latitude of centre point
  // signed[4] latitudeOfCenterPoint ;

  T::Int32_opt mLatitudeOfCenterPoint;

  // alias La1 =  latitudeOfCenterPoint;
  // meta  geography.latitudeOfCenterPointInDegrees
  //         scale(latitudeOfCenterPoint,one,grib2divider,truncateDegrees) :
  //         dump;
  // alias La1InDegrees=latitudeOfCenterPointInDegrees;
  //
  // #  Lo1 - longitude of centre point
  // unsigned[4] longitudeOfCenterPoint ;

  T::UInt32_opt mLongitudeOfCenterPoint;

  // alias Lo1 =  longitudeOfCenterPoint;
  // meta  geography.longitudeOfCenterPointInDegrees
  //         scale(longitudeOfCenterPoint,one,grib2divider,truncateDegrees) :
  //         dump;
  // alias Lo1InDegrees=longitudeOfCenterPointInDegrees;
  //
  // #  Dx - spacing of bins along radials
  // unsigned[4] spacingOfBinsAlongRadials ;

  T::UInt32_opt mSpacingOfBinsAlongRadials;

  // alias Dx  = spacingOfBinsAlongRadials;
  //
  // #  Dstart - offset from origin to inner bound
  // unsigned[4] offsetFromOriginToInnerBound ;

  T::UInt32_opt mOffsetFromOriginToInnerBound;

  // alias Dstart =  offsetFromOriginToInnerBound;
  //
  // include "template.3.scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // # Octets 40-(39+4Nr) : For each of Nr radials:
  // radials list(numberOfRadials){
  //   # Azi - starting azimuth, degrees x 10 (degrees as north)
  //   signed[2] startingAzimuth;

  T::Int16_opt mStartingAzimuth;

  //   alias Azi = startingAzimuth;
  //   # Adelta - azimuthal width, degrees x 100 (+ clockwise, -
  //   counterclockwise)
  //   signed[2] azimuthalWidth;

  T::Int16_opt mAzimuthalWidth;

  //   alias Adelta = azimuthalWidth;
  // }
};

} // namespace GRIB2
} // namespace SmartMet