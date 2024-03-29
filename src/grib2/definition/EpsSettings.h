// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'EpsSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.eps).*/

class EpsSettings {
public:
  EpsSettings();
  virtual ~EpsSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  const T::UInt8_opt &getTypeOfEnsembleForecast() const;
  void setTypeOfEnsembleForecast(T::UInt8_opt typeOfEnsembleForecast);
  const T::UInt8_opt &getPerturbationNumber() const;
  void setPerturbationNumber(T::UInt8_opt perturbationNumber);
  const T::UInt8_opt &getNumberOfForecastsInEnsemble() const;
  void setNumberOfForecastsInEnsemble(T::UInt8_opt numberOfForecastsInEnsemble);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // #  Type of ensemble forecast
  // codetable[1] typeOfEnsembleForecast ('4.6.table',masterDir,localDir) = 255 : dump;

  T::UInt8_opt mTypeOfEnsembleForecast;

  //
  // #  Perturbation number
  // unsigned[1] perturbationNumber  : dump;

  T::UInt8_opt mPerturbationNumber;

  // alias number=perturbationNumber;
  //
  // #  Number of forecasts in ensemble
  // unsigned[1] numberOfForecastsInEnsemble  : dump;

  T::UInt8_opt mNumberOfForecastsInEnsemble;

  // alias totalNumber=numberOfForecastsInEnsemble;
  //
  // #  Rules for TIGGE, S2S, UERRA and CRRA
  // if (productionStatusOfProcessedData == 4 ||
  //     productionStatusOfProcessedData == 5 ||
  //     productionStatusOfProcessedData == 6 ||
  //     productionStatusOfProcessedData == 7 ||
  //     productionStatusOfProcessedData == 8 ||
  //     productionStatusOfProcessedData == 9 ||
  //     productionStatusOfProcessedData == 10||
  //     productionStatusOfProcessedData == 11)
  // {
  //     alias mars.number=perturbationNumber;
  // }
};

} // namespace GRIB2
} // namespace SmartMet
