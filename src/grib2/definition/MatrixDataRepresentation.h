// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'MatrixDataRepresentationImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../RepresentationDefinition.h"
#include "PackingSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (5.1).*/

class MatrixDataRepresentation : public RepresentationDefinition {
public:
  MatrixDataRepresentation();
  virtual ~MatrixDataRepresentation();

  virtual uint getTemplateNumber() const;
  virtual RepresentationDefinition *createRepresentationDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  PackingSettings *getPacking() const;
  void setPacking(PackingSettings &packing);
  const T::UInt8_opt &getMatrixBitmapsPresent() const;
  void setMatrixBitmapsPresent(T::UInt8_opt matrixBitmapsPresent);
  const T::UInt32_opt &getNumberOfCodedValues() const;
  void setNumberOfCodedValues(T::UInt32_opt numberOfCodedValues);
  const T::UInt16_opt &getFirstDimension() const;
  void setFirstDimension(T::UInt16_opt firstDimension);
  const T::UInt16_opt &getSecondDimension() const;
  void setSecondDimension(T::UInt16_opt secondDimension);
  const T::UInt8_opt &getFirstDimensionCoordinateValueDefinition() const;
  void setFirstDimensionCoordinateValueDefinition(T::UInt8_opt firstDimensionCoordinateValueDefinition);
  const T::UInt8_opt &getNC1() const;
  void setNC1(T::UInt8_opt nC1);
  const T::UInt8_opt &getSecondDimensionCoordinateValueDefinition() const;
  void setSecondDimensionCoordinateValueDefinition(T::UInt8_opt secondDimensionCoordinateValueDefinition);
  const T::UInt8_opt &getNC2() const;
  void setNC2(T::UInt8_opt nC2);
  const T::UInt8_opt &getFirstDimensionPhysicalSignificance() const;
  void setFirstDimensionPhysicalSignificance(T::UInt8_opt firstDimensionPhysicalSignificance);
  const T::UInt8_opt &getSecondDimensionPhysicalSignificance() const;
  void setSecondDimensionPhysicalSignificance(T::UInt8_opt secondDimensionPhysicalSignificance);
  float getCoefsFirst() const;
  void setCoefsFirst(float coefsFirst);
  float getCoefsSecond() const;
  void setCoefsSecond(float coefsSecond);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 5.1, Matrix values at grid point -simple packing
  //
  // include "grib2/template.5.packing.def";

  mutable PackingSettings mPacking;

  //
  // unsigned[1] matrixBitmapsPresent ;

  T::UInt8_opt mMatrixBitmapsPresent;

  // # same as in edition 1
  // alias secondaryBitmapPresent=matrixBitmapsPresent;
  //
  // #  Number of data values encoded in Section 7
  // unsigned[4] numberOfCodedValues ;

  T::UInt32_opt mNumberOfCodedValues;

  //
  // #  NR - first dimension
  // # (rows)
  // unsigned[2] firstDimension ;

  T::UInt16_opt mFirstDimension;

  //
  // alias NR  = firstDimension;
  // #  NC - second dimension
  // # (columns)
  // unsigned[2] secondDimension ;

  T::UInt16_opt mSecondDimension;

  //
  // alias NC =  secondDimension;
  // #  First dimension coordinate value definition
  // # (Code Table 5.2)
  // unsigned[1] firstDimensionCoordinateValueDefinition ;

  T::UInt8_opt mFirstDimensionCoordinateValueDefinition;

  //
  // #  NC1 - number of coefficients or values used to specify first dimension coordinate function
  // unsigned[1] NC1 : dump ;

  T::UInt8_opt mNC1;

  // alias numberOfCoefficientsOrValuesUsedToSpecifyFirstDimensionCoordinateFunction=NC1;
  //
  // #  Second dimension coordinate value definition
  // # (Code Table 5.2)
  // unsigned[1] secondDimensionCoordinateValueDefinition ;

  T::UInt8_opt mSecondDimensionCoordinateValueDefinition;

  //
  // #  NC2 - number of coefficients or values used to specify second dimension coordinate function
  // unsigned[1] NC2 : dump ;

  T::UInt8_opt mNC2;

  // alias numberOfCoefficientsOrValuesUsedToSpecifySecondDimensionCoordinateFunction = NC2;
  //
  // #  First dimension physical significance
  // # (Code Table 5.3)
  // unsigned[1] firstDimensionPhysicalSignificance ;

  T::UInt8_opt mFirstDimensionPhysicalSignificance;

  //
  // #  Second dimension physical significance
  // # (Code Table 5.3)
  // unsigned[1] secondDimensionPhysicalSignificance ;

  T::UInt8_opt mSecondDimensionPhysicalSignificance;

  //
  // ieeefloat coefsFirst[NC1];  # TODO: find proper names

  float mCoefsFirst;

  // ieeefloat coefsSecond[NC2];# TODO: find proper names

  float mCoefsSecond;

  //
  // alias data.coefsFirst = coefsFirst;
  // alias data.coefsSecond=coefsSecond;
  //
  // if(matrixBitmapsPresent == 1)
  // {
  //
  //   constant datumSize             = NC*NR;
  //   constant secondaryBitmapsCount = numberOfValues + 0; #
  //   constant secondaryBitmapsSize  = secondaryBitmapsCount/8;
  //
  //   transient numberOfDataMatrices  = numberOfDataPoints/datumSize;
  //
  //   position offsetBBitmap;
  //   meta secondaryBitmaps g2bitmap(
  //           dummy,
  //           missingValue,
  //           offsetBSection5,
  //           section5Length,
  //           numberOfCodedValues ,
  //           dummy) : read_only
  //                     ;
  //
  //     meta bitmap  data_g2secondary_bitmap(primaryBitmap,
  //       secondaryBitmaps,
  //       missingValue,datumSize,numberOfDataPoints) : read_only;
  //
  // }
};

} // namespace GRIB2
} // namespace SmartMet
