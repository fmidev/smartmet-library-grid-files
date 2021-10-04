// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AreaProcessedCrossSectionProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"
#include "ParameterSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.1002).*/

class AreaProcessedCrossSectionProduct : public ProductDefinition {
public:
  AreaProcessedCrossSectionProduct();
  virtual ~AreaProcessedCrossSectionProduct();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  ParameterSettings *getParameter() const;
  void setParameter(ParameterSettings &parameter);
  const T::UInt8_opt &getHorizontalDimensionProcessed() const;
  void setHorizontalDimensionProcessed(T::UInt8_opt horizontalDimensionProcessed);
  const T::UInt8_opt &getTreatmentOfMissingData() const;
  void setTreatmentOfMissingData(T::UInt8_opt treatmentOfMissingData);
  const T::UInt8_opt &getTypeOfStatisticalProcessing() const;
  void setTypeOfStatisticalProcessing(T::UInt8_opt typeOfStatisticalProcessing);
  const T::UInt32_opt &getStartOfRange() const;
  void setStartOfRange(T::UInt32_opt startOfRange);
  const T::UInt32_opt &getEndOfRange() const;
  void setEndOfRange(T::UInt32_opt endOfRange);
  const T::UInt16_opt &getNumberOfDataValues() const;
  void setNumberOfDataValues(T::UInt16_opt numberOfDataValues);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.1002, Cross-section of analysis and forecast, averaged or otherwise statistically processed over latitude or longitude
  //
  // include "grib2/template.4.parameter.def"

  mutable ParameterSettings mParameter;

  //
  // #  Horizontal dimension processed
  // codetable[1] horizontalDimensionProcessed ('4.220.table',masterDir,localDir) : dump;

  T::UInt8_opt mHorizontalDimensionProcessed;

  //
  // #  Treatment of missing data (e.g. below ground)
  // codetable[1] treatmentOfMissingData ('4.221.table',masterDir,localDir) : dump;

  T::UInt8_opt mTreatmentOfMissingData;

  //
  // #  Type of statistical processing
  // codetable[1] typeOfStatisticalProcessing ('4.10.table',masterDir,localDir) : dump;

  T::UInt8_opt mTypeOfStatisticalProcessing;

  // #alias typeOfStatisticalProcessing=stepType;
  //
  // #  Start of range
  // unsigned[4] startOfRange  : dump;

  T::UInt32_opt mStartOfRange;

  //
  // #  End of range
  // unsigned[4] endOfRange  : dump;

  T::UInt32_opt mEndOfRange;

  //
  // #  Number of values
  // unsigned[2] numberOfDataValues : read_only,dump;

  T::UInt16_opt mNumberOfDataValues;
};

} // namespace GRIB2
} // namespace SmartMet
