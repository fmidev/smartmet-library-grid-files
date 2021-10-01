// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CategoricalSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.categorical).*/

class CategoricalSettings {
public:
  CategoricalSettings();
  virtual ~CategoricalSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getNumberOfCategories() const;
  void setNumberOfCategories(T::UInt8_opt numberOfCategories);
  const T::UInt8_opt &getCategoryType() const;
  void setCategoryType(T::UInt8_opt categoryType);
  const T::UInt8_opt &getCodeFigure() const;
  void setCodeFigure(T::UInt8_opt codeFigure);
  const T::UInt8_opt &getScaleFactorOfLowerLimit() const;
  void setScaleFactorOfLowerLimit(T::UInt8_opt scaleFactorOfLowerLimit);
  const T::UInt32_opt &getScaledValueOfLowerLimit() const;
  void setScaledValueOfLowerLimit(T::UInt32_opt scaledValueOfLowerLimit);
  const T::UInt8_opt &getScaleFactorOfUpperLimit() const;
  void setScaleFactorOfUpperLimit(T::UInt8_opt scaleFactorOfUpperLimit);
  const T::UInt32_opt &getScaledValueOfUpperLimit() const;
  void setScaledValueOfUpperLimit(T::UInt32_opt scaledValueOfUpperLimit);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // #  Total number of forecast probabilities
  // unsigned[1] numberOfCategories  : dump;

  T::UInt8_opt mNumberOfCategories;

  //
  // #  categories
  // categories list(numberOfCategories) {
  //   codetable[1] categoryType ('4.91.table',masterDir,localDir): dump;

  T::UInt8_opt mCategoryType;

  //   unsigned[1] codeFigure : dump;

  T::UInt8_opt mCodeFigure;

  //   #  Scale factor of lower limit
  //   unsigned[1] scaleFactorOfLowerLimit : can_be_missing,dump ;

  T::UInt8_opt mScaleFactorOfLowerLimit;

  //
  //   #  Scaled value of lower limit
  //   unsigned[4] scaledValueOfLowerLimit : can_be_missing,dump ;

  T::UInt32_opt mScaledValueOfLowerLimit;

  //
  //   #  Scale factor of upper limit
  //   unsigned[1] scaleFactorOfUpperLimit : can_be_missing,dump;

  T::UInt8_opt mScaleFactorOfUpperLimit;

  //
  //   #  Scaled value of upper limit
  //   unsigned[4] scaledValueOfUpperLimit : can_be_missing,dump;

  T::UInt32_opt mScaledValueOfUpperLimit;

  // }
};

} // namespace GRIB2
} // namespace SmartMet
