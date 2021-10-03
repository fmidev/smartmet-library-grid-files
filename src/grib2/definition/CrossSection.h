// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CrossSectionImpl.*' files.
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
/*! \brief The class is automatically created from the template (3.1000).*/

class CrossSection : public GridDefinition {
public:
  CrossSection();
  ~CrossSection() override;

  uint getTemplateNumber() const override;
  GridDefinition *createGridDefinition() const override;
  void read(MemoryReader &memoryReader) override;
  void write(DataWriter &dataWriter) override;
  void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const override;
  void print(std::ostream &stream, uint level, uint optionFlags) const override;
  T::Hash countHash() override;

  EarthShapeSettings *getEarthShape() const override;
  void setEarthShape(EarthShapeSettings &earthShape);
  const T::UInt32_opt &getNumberOfHorizontalPoints() const;
  void setNumberOfHorizontalPoints(T::UInt32_opt numberOfHorizontalPoints);
  const T::UInt32_opt &getBasicAngleOfTheInitialProductionDomain() const;
  void setBasicAngleOfTheInitialProductionDomain(T::UInt32_opt basicAngleOfTheInitialProductionDomain);
  const T::UInt32_opt &getSubdivisionsOfBasicAngle() const;
  void setSubdivisionsOfBasicAngle(T::UInt32_opt subdivisionsOfBasicAngle);
  const T::Int32_opt &getLatitudeOfFirstGridPoint() const;
  void setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint);
  const T::UInt32_opt &getLongitudeOfFirstGridPoint() const;
  void setLongitudeOfFirstGridPoint(T::UInt32_opt longitudeOfFirstGridPoint);
  ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings &scanningMode);
  const T::Int32_opt &getLatitudeOfLastGridPoint() const;
  void setLatitudeOfLastGridPoint(T::Int32_opt latitudeOfLastGridPoint);
  const T::UInt32_opt &getLongitudeOfLastGridPoint() const;
  void setLongitudeOfLastGridPoint(T::UInt32_opt longitudeOfLastGridPoint);
  const T::UInt8_opt &getTypeOfHorizontalLine() const;
  void setTypeOfHorizontalLine(T::UInt8_opt typeOfHorizontalLine);
  const T::UInt16_opt &getNumberOfVerticalPoints() const;
  void setNumberOfVerticalPoints(T::UInt16_opt numberOfVerticalPoints);
  const T::UInt8_opt &getMeaningOfVerticalCoordinate() const;
  void setMeaningOfVerticalCoordinate(T::UInt8_opt meaningOfVerticalCoordinate);
  const T::UInt8_opt &getVerticalCoordinate() const;
  void setVerticalCoordinate(T::UInt8_opt verticalCoordinate);
  const T::UInt16_opt &getNC() const;
  void setNC(T::UInt16_opt nC);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.1000, Cross-section grid, with points equally spaced on the horizontal
  //
  // include "grib2/template.3.shape_of_the_earth.def";

  mutable EarthShapeSettings mEarthShape;

  //
  //
  // #  Number of horizontal points
  // unsigned[4] numberOfHorizontalPoints  : dump ;

  T::UInt32_opt mNumberOfHorizontalPoints;

  //
  // #  Basic angle of the initial production domain
  // unsigned[4] basicAngleOfTheInitialProductionDomain = 0;

  T::UInt32_opt mBasicAngleOfTheInitialProductionDomain;

  //
  // #  Subdivisions of basic angle used to define extreme longitudes and latitudes
  // unsigned[4] subdivisionsOfBasicAngle = missing() : can_be_missing;;

  T::UInt32_opt mSubdivisionsOfBasicAngle;

  //
  // #  La1 - latitude of first grid point
  // signed[4] latitudeOfFirstGridPoint : edition_specific ;

  T::Int32_opt mLatitudeOfFirstGridPoint;

  //
  // alias La1 =  latitudeOfFirstGridPoint;
  // #  Lo1 - longitude of first grid point
  // unsigned[4] longitudeOfFirstGridPoint : edition_specific;

  T::UInt32_opt mLongitudeOfFirstGridPoint;

  //
  // alias Lo1 =  longitudeOfFirstGridPoint;
  //
  // include "grib2/template.3.scanning_mode.def";

  mutable ScanningModeSettings mScanningMode;

  //
  // #  La2 - latitude of last grid point
  // signed[4] latitudeOfLastGridPoint : edition_specific;

  T::Int32_opt mLatitudeOfLastGridPoint;

  //
  // alias La2  = latitudeOfLastGridPoint;
  // #  Lo2 - longitude of last grid point
  // unsigned[4] longitudeOfLastGridPoint: edition_specific ;

  T::UInt32_opt mLongitudeOfLastGridPoint;

  //
  // alias Lo2 =  longitudeOfLastGridPoint;
  // #  Type of horizontal line
  // codetable[1] typeOfHorizontalLine ('3.20.table',masterDir,localDir) : dump ;

  T::UInt8_opt mTypeOfHorizontalLine;

  //
  // #  Number of vertical points
  // unsigned[2] numberOfVerticalPoints  : dump ;

  T::UInt16_opt mNumberOfVerticalPoints;

  //
  // #  Physical meaning of vertical coordinate
  // codetable[1] meaningOfVerticalCoordinate ('3.15.table',masterDir,localDir) : dump ;

  T::UInt8_opt mMeaningOfVerticalCoordinate;

  //
  // #  Vertical dimension coordinate values definition
  // codetable[1] verticalCoordinate ('3.21.table',masterDir,localDir) : dump ;

  T::UInt8_opt mVerticalCoordinate;

  //
  // #  NC - Number of coefficients or values used to specify vertical coordinates
  // unsigned[2] NC  : dump ;

  T::UInt16_opt mNC;

  //
  // # Octets 67-(66+NC*4) : Coefficients to define vertical dimension coordinate values in functional form, or the explicit coordinate values
  // # (IEEE 32-bit floating-point values)
  // # ????          coefficients_to_define_vertical_dimension_coordinate_values_in_functional_form_or_the_explicit_coordinate_values
  //
  //
};

} // namespace GRIB2
} // namespace SmartMet
