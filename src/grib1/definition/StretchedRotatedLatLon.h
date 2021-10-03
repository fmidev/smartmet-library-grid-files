// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'StretchedRotatedLatLonImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "GridAreaSettings.h"
#include "GridStretchingSettings.h"
#include "RotationSettings.h"
#include "ScanningModeSettings.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template (grid_definition_30).*/

class StretchedRotatedLatLon : public GridDefinition {
public:
  StretchedRotatedLatLon();
  ~StretchedRotatedLatLon() override;

  void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const override;
  void read(MemoryReader &memoryReader) override;
  void write(DataWriter &dataWriter) override;
  void print(std::ostream &stream, uint level, uint optionFlags) const override;
  T::Hash countHash() override;

  uint getTemplateNumber() const override;
  GridDefinition *createGridDefinition() const override;
  std::uint16_t getNi() const;
  void setNi(std::uint16_t ni);
  std::uint16_t getNj() const;
  void setNj(std::uint16_t nj);
  GridAreaSettings *getGridArea() const override;
  void setGridArea(GridAreaSettings &gridArea);
  std::uint16_t getIDirectionIncrement() const;
  void setIDirectionIncrement(std::uint16_t iDirectionIncrement);
  std::uint16_t getJDirectionIncrement() const;
  void setJDirectionIncrement(std::uint16_t jDirectionIncrement);
  ScanningModeSettings *getScanningMode() const override;
  void setScanningMode(ScanningModeSettings &scanningMode);
  std::uint32_t getZero() const;
  void setZero(std::uint32_t zero);
  RotationSettings *getRotation() const override;
  void setRotation(RotationSettings &rotation);
  GridStretchingSettings *getGridStretching() const;
  void setGridStretching(GridStretchingSettings &gridStretching);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # GRID DEFINITION stretched and rotated latitude/longitude grids
  // # grib 1 -> 2
  // constant gridDefinitionTemplateNumber     = 3;
  //
  // template commonBlock "grib1/grid_definition_latlon.def";
  // unsigned[2] Ni  : can_be_missing,dump;

  std::uint16_t mNi;

  // alias numberOfPointsAlongAParallel=Ni;
  // alias Nx = Ni;
  //
  // unsigned[2] Nj : can_be_missing,dump;

  std::uint16_t mNj;

  // alias numberOfPointsAlongAMeridian=Nj;
  // alias Ny = Nj;
  //
  // # Latitudes and Longitudes of the first and the last points
  // # Resolution and component flags
  // include "grib1/grid_first_last_resandcomp.def";

  mutable GridAreaSettings mGridArea;

  //
  // unsigned[2] iDirectionIncrement : can_be_missing, edition_specific;

  std::uint16_t mIDirectionIncrement;

  // unsigned[2] jDirectionIncrement : can_be_missing, edition_specific;

  std::uint16_t mJDirectionIncrement;

  // alias Dj = jDirectionIncrement;
  // alias Dy = jDirectionIncrement;
  // alias Di = iDirectionIncrement;
  // alias Dx = iDirectionIncrement;
  //
  // include "grib1/scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
  // meta  geography.jDirectionIncrementInDegrees latlon_increment(ijDirectionIncrementGiven,jDirectionIncrement,
  //   jScansPositively,
  //   latitudeOfFirstGridPointInDegrees,latitudeOfLastGridPointInDegrees,
  //   numberOfPointsAlongAMeridian,oneConstant,grib1divider,0) : can_be_missing,dump;
  //
  // alias DjInDegrees=jDirectionIncrementInDegrees;
  // alias DyInDegrees=jDirectionIncrementInDegrees;
  //
  // meta  geography.iDirectionIncrementInDegrees latlon_increment(ijDirectionIncrementGiven,iDirectionIncrement,
  //   iScansPositively,
  //   longitudeOfFirstGridPointInDegrees,longitudeOfLastGridPointInDegrees,
  //   Ni,oneConstant,grib1divider,1) : can_be_missing,dump;
  // alias DiInDegrees=iDirectionIncrementInDegrees;
  // alias DxInDegrees=iDirectionIncrementInDegrees;
  //
  // meta numberOfDataPoints number_of_points(Ni,Nj,PLPresent,pl) : dump;
  // alias numberOfPoints=numberOfDataPoints;
  // meta numberOfValues number_of_values(values,bitsPerValue,numberOfDataPoints,
  //                             bitmapPresent,bitmap,numberOfCodedValues) : dump;
  // #alias ls.valuesCount=numberOfValues;
  //
  // if(missing(Ni)){
  //    iterator latlon_reduced(numberOfPoints,missingValue,values,
  //         latitudeFirstInDegrees,longitudeFirstInDegrees,
  //         latitudeLastInDegrees,longitudeLastInDegrees,
  //       Nj,DjInDegrees,pl);
  //    nearest latlon_reduced(values,radius,Nj,pl,longitudeFirstInDegrees,longitudeLastInDegrees);
  // } else {
  //    transient iteratorDisableUnrotate = 0 : hidden; # ECC-808
  //    iterator latlon(numberOfPoints,missingValue,values,longitudeFirstInDegrees,
  //                    DiInDegrees ,Ni,Nj,iScansNegatively ,
  //                    latitudeFirstInDegrees,DjInDegrees,jScansPositively,jPointsAreConsecutive);
  //    nearest regular(values,radius,Ni,Nj);
  // }
  //
  //
  // meta latLonValues latlonvalues(values);
  // alias latitudeLongitudeValues=latLonValues;
  // meta latitudes latitudes(values,0);
  // meta longitudes longitudes(values,0);
  // meta distinctLatitudes latitudes(values,1);
  // meta distinctLongitudes longitudes(values,1);
  //
  // ascii[4] zero : read_only;

  std::uint32_t mZero;

  //
  // # Rotation parameters
  // include "grib1/grid_rotation.def"

  mutable RotationSettings mRotation;

  //
  // # Stretching parameters
  // include "grib1/grid_stretching.def"

  mutable GridStretchingSettings mGridStretching;
};

} // namespace GRIB1
} // namespace SmartMet
