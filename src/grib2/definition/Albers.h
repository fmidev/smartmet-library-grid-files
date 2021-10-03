// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AlbersImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"
#include "EarthShapeSettings.h"
#include "ResolutionSettings.h"
#include "ScanningModeSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.31).*/

class Albers : public GridDefinition {
public:
  Albers();
  ~Albers() override;

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
  ResolutionSettings *getResolution() const override;
  void setResolution(ResolutionSettings &resolution);
  const T::Int32_opt &getLaD() const;
  void setLaD(T::Int32_opt laD);
  const T::UInt32_opt &getLoV() const;
  void setLoV(T::UInt32_opt loV);
  const T::UInt32_opt &getXDirectionGridLength() const;
  void setXDirectionGridLength(T::UInt32_opt xDirectionGridLength);
  const T::UInt32_opt &getYDirectionGridLength() const;
  void setYDirectionGridLength(T::UInt32_opt yDirectionGridLength);
  std::uint8_t getProjectionCentreFlag() const;
  void setProjectionCentreFlag(std::uint8_t projectionCentreFlag);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);
  const T::Int32_opt &getLatin1() const;
  void setLatin1(T::Int32_opt latin1);
  const T::UInt32_opt &getLatin2() const;
  void setLatin2(T::UInt32_opt latin2);
  const T::Int32_opt &getLatitudeOfTheSouthernPoleOfProjection() const;
  void setLatitudeOfTheSouthernPoleOfProjection(T::Int32_opt latitudeOfTheSouthernPoleOfProjection);
  const T::UInt32_opt &getLongitudeOfTheSouthernPoleOfProjection() const;
  void setLongitudeOfTheSouthernPoleOfProjection(T::UInt32_opt longitudeOfTheSouthernPoleOfProjection);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.31, Albers equal area
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

  //
  // #  Nx - number of points along the X-axis
  // unsigned[4] Nx  : dump;

  T::UInt32_opt mNx;

  // alias numberOfPointsAlongTheXAxis=Nx;
  // alias geography.Nx=Nx;
  //
  // #  Ny - number of points along the Y-axis
  // unsigned[4] Ny  : dump;

  T::UInt32_opt mNy;

  // alias numberOfPointsAlongTheYAxis=Ny;
  // alias geography.Ny=Ny;
  //
  // #  La1 - latitude of first grid point
  // signed[4] latitudeOfFirstGridPoint : edition_specific,dump;

  T::Int32_opt mLatitudeOfFirstGridPoint;

  // alias La1  = latitudeOfFirstGridPoint;
  //
  // #  Lo1 - longitude of first grid point
  // unsigned[4] longitudeOfFirstGridPoint : edition_specific,dump;

  T::UInt32_opt mLongitudeOfFirstGridPoint;

  // alias Lo1  = longitudeOfFirstGridPoint;
  //
  // include "grib2/template.3.resolution_flags.def";

  mutable ResolutionSettings mResolution;

  //
  // #  LaD - Latitude where Dx and Dy are specified
  // signed[4] LaD  : dump;

  T::Int32_opt mLaD;

  // alias latitudeWhereDxAndDyAreSpecified=LaD ;
  //
  // #  LoV - Longitude of meridian parallel to Y-axis along which latitude increases as the Y-coordinate increases
  // unsigned[4] LoV  : dump;

  T::UInt32_opt mLoV;

  //
  // #  Dx - X-direction grid length
  // unsigned[4] xDirectionGridLength  : dump;

  T::UInt32_opt mXDirectionGridLength;

  // alias Dx  = xDirectionGridLength;
  //
  // #  Dy - Y-direction grid length
  // unsigned[4] yDirectionGridLength  : dump;

  T::UInt32_opt mYDirectionGridLength;

  // alias Dy =  yDirectionGridLength;
  //
  // #  Projection centre flag
  // flags[1] projectionCentreFlag 'grib2/tables/[tablesVersion]/3.5.table' : dump;

  std::uint8_t mProjectionCentreFlag;

  // include "grib2/template.3.scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
  // #  Latin 1 - first latitude from the pole at which the secant cone cuts the sphere
  // signed[4] Latin1 :edition_specific;

  T::Int32_opt mLatin1;

  // meta  geography.Latin1InDegrees scale(Latin1,one,grib2divider,truncateDegrees) : dump;
  //
  // #  Latin 2 - second latitude from the pole at which the secant cone cuts the sphere
  // unsigned[4] Latin2  : edition_specific;

  T::UInt32_opt mLatin2;

  // meta  geography.Latin2InDegrees scale(Latin2,one,grib2divider,truncateDegrees) : dump;
  //
  // #  Latitude of the southern pole of projection
  // signed[4] latitudeOfTheSouthernPoleOfProjection : edition_specific ;

  T::Int32_opt mLatitudeOfTheSouthernPoleOfProjection;

  // alias latitudeOfSouthernPole=latitudeOfTheSouthernPoleOfProjection;
  // meta  geography.latitudeOfSouthernPoleInDegrees   scale(latitudeOfTheSouthernPoleOfProjection          ,one,grib2divider,truncateDegrees) : dump;
  //
  //
  // #  Longitude of the southern pole of projection
  // unsigned[4] longitudeOfTheSouthernPoleOfProjection :edition_specific;

  T::UInt32_opt mLongitudeOfTheSouthernPoleOfProjection;

  // alias longitudeOfSouthernPole=longitudeOfTheSouthernPoleOfProjection;
  // meta  geography.longitudeOfSouthernPoleInDegrees   scale(longitudeOfTheSouthernPoleOfProjection,oneConstant,grib2divider,truncateDegrees) : dump;
};

} // namespace GRIB2
} // namespace SmartMet
