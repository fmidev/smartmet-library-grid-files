// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'LatLonSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "GridSettings.h"
#include "ScanningModeSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.latlon).*/

class LatLonSettings {
public:
  LatLonSettings();
  LatLonSettings(const LatLonSettings &other);
  virtual ~LatLonSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  GridSettings *getGrid() const;
  void setGrid(GridSettings &grid);
  const T::UInt32_opt &getIDirectionIncrement() const;
  void setIDirectionIncrement(T::UInt32_opt iDirectionIncrement);
  const T::UInt32_opt &getJDirectionIncrement() const;
  void setJDirectionIncrement(T::UInt32_opt jDirectionIncrement);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);

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
  // include "template.3.grid.def";

  mutable GridSettings mGrid;

  //
  // #  Di - i direction increment
  //
  // unsigned[4] iDirectionIncrement : can_be_missing,edition_specific;

  T::UInt32_opt mIDirectionIncrement;

  // alias Di =  iDirectionIncrement;
  // alias Dx =  iDirectionIncrement;
  //
  // #  Dj - j direction increment
  //
  // unsigned[4] jDirectionIncrement : can_be_missing,edition_specific;

  T::UInt32_opt mJDirectionIncrement;

  // alias Dj =  jDirectionIncrement;
  // alias Dy =  jDirectionIncrement;
  //
  // include "template.3.scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
  // meta g2grid g2grid(
  //   latitudeOfFirstGridPoint,
  //   longitudeOfFirstGridPoint,
  //   latitudeOfLastGridPoint,
  //   longitudeOfLastGridPoint,
  //   iDirectionIncrement,
  //   jDirectionIncrement,
  //   basicAngleOfTheInitialProductionDomain,
  //   subdivisionsOfBasicAngle
  //   );
  //
  // meta      geography.latitudeOfFirstGridPointInDegrees    g2latlon(g2grid,0) : dump;
  // meta      geography.longitudeOfFirstGridPointInDegrees   g2latlon(g2grid,1) : dump;
  // meta      geography.latitudeOfLastGridPointInDegrees     g2latlon(g2grid,2) : dump;
  // meta      geography.longitudeOfLastGridPointInDegrees    g2latlon(g2grid,3) : dump;
  //
  // alias xFirst=longitudeOfFirstGridPointInDegrees;
  // alias yFirst=latitudeOfFirstGridPointInDegrees;
  // alias xLast=longitudeOfLastGridPointInDegrees;
  // alias yLast=latitudeOfLastGridPointInDegrees;
  //
  // meta geography.iDirectionIncrementInDegrees    g2latlon(g2grid,4,
  //   iDirectionIncrementGiven) : can_be_missing,dump;
  //
  // meta geography.jDirectionIncrementInDegrees    g2latlon(g2grid,5,
  //   jDirectionIncrementGiven) : can_be_missing,dump;
  //
  // alias latitudeFirstInDegrees  = latitudeOfFirstGridPointInDegrees;
  // alias longitudeFirstInDegrees = longitudeOfFirstGridPointInDegrees;
  // alias latitudeLastInDegrees   = latitudeOfLastGridPointInDegrees;
  // alias longitudeLastInDegrees  = longitudeOfLastGridPointInDegrees;
  // alias DiInDegrees = iDirectionIncrementInDegrees;
  // alias DxInDegrees = iDirectionIncrementInDegrees;
  // alias DjInDegrees = jDirectionIncrementInDegrees;
  // alias DyInDegrees = jDirectionIncrementInDegrees;
  //
  // _if ( missing(Ni) && PLPresent == 1 ) {
  //   iterator latlon_reduced(numberOfPoints,missingValue,values,
  //       latitudeFirstInDegrees,longitudeFirstInDegrees,
  //       latitudeLastInDegrees,longitudeLastInDegrees,
  //       Nj,DjInDegrees,pl);
  //   nearest latlon_reduced(values,radius,Nj,pl,longitudeFirstInDegrees,longitudeLastInDegrees);
  // } else {
  //   iterator latlon(numberOfPoints,missingValue,values,
  //                   longitudeFirstInDegrees,DiInDegrees  ,
  //                   Ni,Nj,iScansNegatively,
  //                   latitudeFirstInDegrees, DjInDegrees,jScansPositively);
  //   nearest regular(values,radius,Ni,Nj);
  // }
  // meta latLonValues latlonvalues(values);
  // alias latitudeLongitudeValues=latLonValues;
  // meta latitudes latitudes(values,0);
  // meta longitudes longitudes(values,0);
  // meta distinctLatitudes latitudes(values,1);
  // meta distinctLongitudes longitudes(values,1);
  //
};

} // namespace GRIB2
} // namespace SmartMet
