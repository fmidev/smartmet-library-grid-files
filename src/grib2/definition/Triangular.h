// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TriangularImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../GridDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.100).*/

class Triangular : public GridDefinition {
public:
  Triangular();
  virtual ~Triangular();

  virtual uint getTemplateNumber() const;
  virtual GridDefinition *createGridDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getN2() const;
  void setN2(T::UInt8_opt n2);
  const T::UInt8_opt &getN3() const;
  void setN3(T::UInt8_opt n3);
  const T::UInt16_opt &getNi() const;
  void setNi(T::UInt16_opt ni);
  const T::UInt8_opt &getNd() const;
  void setNd(T::UInt8_opt nd);
  const T::Int32_opt &getLatitudeOfThePolePoint() const;
  void setLatitudeOfThePolePoint(T::Int32_opt latitudeOfThePolePoint);
  const T::UInt32_opt &getLongitudeOfThePolePoint() const;
  void setLongitudeOfThePolePoint(T::UInt32_opt longitudeOfThePolePoint);
  const T::UInt32_opt &getLongitudeOfFirstDiamondCenterLine() const;
  void setLongitudeOfFirstDiamondCenterLine(T::UInt32_opt longitudeOfFirstDiamondCenterLine);
  const T::UInt8_opt &getGridPointPosition() const;
  void setGridPointPosition(T::UInt8_opt gridPointPosition);
  std::uint8_t getNumberingOrderOfDiamonds() const;
  void setNumberingOrderOfDiamonds(std::uint8_t numberingOrderOfDiamonds);
  std::uint8_t getScanningModeForOneDiamond() const;
  void setScanningModeForOneDiamond(std::uint8_t scanningModeForOneDiamond);
  const T::UInt32_opt &getTotalNumberOfGridPoints() const;
  void setTotalNumberOfGridPoints(T::UInt32_opt totalNumberOfGridPoints);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 3.100, Triangular grid based on an icosahedron (see Attachment I.2-GRIB-Att.)
  //
  // #  n2 - exponent of 2 for the number of intervals on main triangle sides
  // unsigned[1] n2  : dump ;

  T::UInt8_opt mN2;

  //
  // #  n3 - exponent of 3 for the number of intervals on main triangle sides
  // unsigned[1] n3  : dump ;

  T::UInt8_opt mN3;

  //
  // #  Ni - number of intervals on main triangle sides of the icosahedron
  // unsigned[2] Ni  : dump ;

  T::UInt16_opt mNi;

  //
  // #  nd - Number of diamonds
  // unsigned[1] nd  : dump ;

  T::UInt8_opt mNd;

  // alias numberOfDiamonds=nd;
  //
  // #  Latitude of the pole point of the icosahedron on the sphere
  // signed[4] latitudeOfThePolePoint  : dump ;

  T::Int32_opt mLatitudeOfThePolePoint;

  // meta geography.latitudeOfThePolePointInDegrees scale(latitudeOfThePolePoint,one,grib2divider,truncateDegrees) : dump;
  //
  // #  Longitude of the pole point of the icosahedron on the sphere
  // unsigned[4] longitudeOfThePolePoint  : dump ;

  T::UInt32_opt mLongitudeOfThePolePoint;

  // meta geography.longitudeOfThePolePointInDegrees g2lon(longitudeOfThePolePoint);
  //
  // #  Longitude of the centre line of the first diamond of the icosahedron on the sphere
  // unsigned[4] longitudeOfFirstDiamondCenterLine  : dump ;

  T::UInt32_opt mLongitudeOfFirstDiamondCenterLine;

  // meta geography.longitudeOfFirstDiamondCenterLineInDegrees g2lon(longitudeOfFirstDiamondCenterLine);
  //
  // #  Grid point position
  // codetable[1] gridPointPosition ('3.8.table',masterDir,localDir);

  T::UInt8_opt mGridPointPosition;

  //
  // #  Numbering order of diamonds
  // flags[1] numberingOrderOfDiamonds 'grib2/tables/[tablesVersion]/3.9.table';

  std::uint8_t mNumberingOrderOfDiamonds;

  //
  // #  Scanning mode for one diamond
  // flags[1] scanningModeForOneDiamond 'grib2/tables/[tablesVersion]/3.10.table';

  std::uint8_t mScanningModeForOneDiamond;

  //
  // #  nt - total number of grid points
  // unsigned[4] totalNumberOfGridPoints  : dump ;

  T::UInt32_opt mTotalNumberOfGridPoints;

  //
  // alias nt  = totalNumberOfGridPoints;
  //
};

} // namespace GRIB2
} // namespace SmartMet
