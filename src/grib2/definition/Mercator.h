// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'MercatorImpl.*' files.
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
/*! \brief The class is automatically created from the template (3.10).*/

class Mercator : public GridDefinition {
public:
  Mercator();
  virtual ~Mercator();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings &earthShape);
  const T::UInt32_opt &getNi() const;
  void setNi(T::UInt32_opt ni);
  const T::UInt32_opt &getNj() const;
  void setNj(T::UInt32_opt nj);
  const T::Int32_opt &getLatitudeOfFirstGridPoint() const;
  void setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint);
  const T::Int32_opt &getLongitudeOfFirstGridPoint() const;
  void setLongitudeOfFirstGridPoint(T::Int32_opt longitudeOfFirstGridPoint);
  ResolutionSettings *getResolution() const;
  void setResolution(ResolutionSettings &resolution);
  const T::Int32_opt &getLaD() const;
  void setLaD(T::Int32_opt laD);
  const T::Int32_opt &getLatitudeOfLastGridPoint() const;
  void setLatitudeOfLastGridPoint(T::Int32_opt latitudeOfLastGridPoint);
  const T::Int32_opt &getLongitudeOfLastGridPoint() const;
  void setLongitudeOfLastGridPoint(T::Int32_opt longitudeOfLastGridPoint);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);
  const T::UInt32_opt &getOrientationOfTheGrid() const;
  void setOrientationOfTheGrid(T::UInt32_opt orientationOfTheGrid);
  const T::UInt32_opt &getDi() const;
  void setDi(T::UInt32_opt di);
  const T::UInt32_opt &getDj() const;
  void setDj(T::UInt32_opt dj);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.10, Mercator
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

  //
  // unsigned[4] Ni : dump;

  T::UInt32_opt mNi;

  // alias numberOfPointsAlongAParallel=Ni;
  // alias Nx = Ni;
  // alias geography.Ni=Ni;
  //
  // unsigned[4] Nj : dump;

  T::UInt32_opt mNj;

  // alias numberOfPointsAlongAMeridian=Nj;
  // alias Ny = Nj ;
  // alias geography.Nj=Nj;
  //
  // # La1 - latitude of first grid point
  // signed[4] latitudeOfFirstGridPoint: edition_specific,no_copy ;

  T::Int32_opt mLatitudeOfFirstGridPoint;

  // alias La1 =  latitudeOfFirstGridPoint;
  // meta geography.latitudeOfFirstGridPointInDegrees scale(latitudeOfFirstGridPoint,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // # Lo1 - longitude of first grid point
  // signed[4] longitudeOfFirstGridPoint : edition_specific,no_copy;

  T::Int32_opt mLongitudeOfFirstGridPoint;

  // alias Lo1 =  longitudeOfFirstGridPoint;
  // meta geography.longitudeOfFirstGridPointInDegrees scale(longitudeOfFirstGridPoint,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // include "grib2/template.3.resolution_flags.def";

  mutable ResolutionSettings mResolution;

  //
  // # LaD - Latitude(s) at which the Mercator projection intersects the Earth
  // # (Latitude(s) where Di and Dj are specified)
  // signed[4] LaD : edition_specific,no_copy;

  T::Int32_opt mLaD;

  // meta geography.LaDInDegrees scale(LaD,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // # La2 - latitude of last grid point
  // signed[4] latitudeOfLastGridPoint : edition_specific,no_copy;

  T::Int32_opt mLatitudeOfLastGridPoint;

  // alias La2 =  latitudeOfLastGridPoint;
  // meta geography.latitudeOfLastGridPointInDegrees scale(latitudeOfLastGridPoint,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // # Lo2 - longitude of last grid point
  // signed[4] longitudeOfLastGridPoint: edition_specific,no_copy ;

  T::Int32_opt mLongitudeOfLastGridPoint;

  // alias Lo2 =  longitudeOfLastGridPoint;
  // meta geography.longitudeOfLastGridPointInDegrees scale(longitudeOfLastGridPoint,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // include "grib2/template.3.scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
  // # Orientation of the grid, angle between i direction on the map and the equator
  // # NOTE 1: Limited to the range of 0 to 90 degrees; if the angle of orientation of the grid is neither 0 nor 90 degrees,
  // #         Di and Dj must be equal to each other
  // unsigned[4] orientationOfTheGrid : dump ;

  T::UInt32_opt mOrientationOfTheGrid;

  // meta geography.orientationOfTheGridInDegrees
  //     scale(orientationOfTheGrid,oneConstant,grib2divider,truncateDegrees) : dump;
  //
  // # Di - longitudinal direction grid length
  // # NOTE 2: Grid lengths are in units of 10**-3 m, at the latitude specified by LaD
  // unsigned[4] Di  : edition_specific,no_copy ;

  T::UInt32_opt mDi;

  // alias longitudinalDirectionGridLength = Di   ;
  // meta geography.DiInMetres
  //     scale(Di,oneConstant,thousand,truncateDegrees) : dump;
  //
  // # Dj - latitudinal direction grid length
  // # NOTE 2: Grid lengths are in units of 10**-3 m, at the latitude specified by LaD
  // unsigned[4] Dj  : edition_specific,no_copy ;

  T::UInt32_opt mDj;

  // alias latitudinalDirectionGridLength =  Dj;
  // meta geography.DjInMetres
  //     scale(Dj,oneConstant,thousand,truncateDegrees) : dump;
};

} // namespace GRIB2
} // namespace SmartMet
