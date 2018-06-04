// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CrossSectionImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/MemoryReader.h"
#include "../GridDefinition.h"
#include "EarthShapeSettings.h"
#include "ScanningModeSettings.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.1000).*/

class CrossSection : public GridDefinition {
public:
  CrossSection();
  virtual ~CrossSection();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const EarthShapeSettings *getEarthShape() const;
  void setEarthShape(EarthShapeSettings earthShape);
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
  const ScanningModeSettings *getScanningMode() const;
  void setScanningMode(ScanningModeSettings scanningMode);
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
  // # TEMPLATE 3.1000, Cross-section grid, with points equally spaced on the horizontal
  //
  // include "template.3.shape_of_the_earth.def";

  EarthShapeSettings mEarthShape;

  //
  //
  // #  Number of horizontal points
  // unsigned[4] numberOfHorizontalPoints  : dump ;

  T::UInt32_opt mNumberOfHorizontalPoints;

  //
  // #  Basic angle of the initial production domain
  // # NOTE 1 NOT FOUND
  // unsigned[4] basicAngleOfTheInitialProductionDomain = 0;

  T::UInt32_opt mBasicAngleOfTheInitialProductionDomain;

  //
  // #  Subdivisions of basic angle used to define extreme longitudes and latitudes
  // # NOTE 1 NOT FOUND
  // unsigned[4] subdivisionsOfBasicAngle = missing() : can_be_missing;;

  T::UInt32_opt mSubdivisionsOfBasicAngle;

  //
  // #  La1 - latitude of first grid point
  // # NOTE 1 NOT FOUND
  // signed[4] latitudeOfFirstGridPoint : edition_specific ;

  T::Int32_opt mLatitudeOfFirstGridPoint;

  //
  // alias La1 =  latitudeOfFirstGridPoint;
  // #  Lo1 - longitude of first grid point
  // # NOTE 1 NOT FOUND
  // unsigned[4] longitudeOfFirstGridPoint : edition_specific;

  T::UInt32_opt mLongitudeOfFirstGridPoint;

  //
  // alias Lo1 =  longitudeOfFirstGridPoint;
  //
  // include "template.3.scanning_mode.def";

  ScanningModeSettings mScanningMode;

  //
  // #  La2 - latitude of last grid point
  // # NOTE 1 NOT FOUND
  // signed[4] latitudeOfLastGridPoint : edition_specific;

  T::Int32_opt mLatitudeOfLastGridPoint;

  //
  // alias La2  = latitudeOfLastGridPoint;
  // #  Lo2 - longitude of last grid point
  // # NOTE 1 NOT FOUND
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
