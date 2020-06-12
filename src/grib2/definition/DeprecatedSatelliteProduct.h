// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'DeprecatedSatelliteProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.30).*/

class DeprecatedSatelliteProduct : public ProductDefinition {
public:
  DeprecatedSatelliteProduct();
  DeprecatedSatelliteProduct(const DeprecatedSatelliteProduct &other);
  virtual ~DeprecatedSatelliteProduct();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getParameterCategory() const;
  void setParameterCategory(T::UInt8_opt parameterCategory);
  const T::UInt8_opt &getParameterNumber() const;
  void setParameterNumber(T::UInt8_opt parameterNumber);
  const T::UInt8_opt &getTypeOfGeneratingProcess() const;
  void setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess);
  const T::UInt8_opt &getObservationGeneratingProcessIdentifier() const;
  void setObservationGeneratingProcessIdentifier(T::UInt8_opt observationGeneratingProcessIdentifier);
  const T::UInt8_opt &getNB() const;
  void setNB(T::UInt8_opt nB);
  const T::UInt16_opt &getSatelliteSeries() const;
  void setSatelliteSeries(T::UInt16_opt satelliteSeries);
  const T::UInt16_opt &getSatelliteNumber() const;
  void setSatelliteNumber(T::UInt16_opt satelliteNumber);
  const T::UInt8_opt &getInstrumentType() const;
  void setInstrumentType(T::UInt8_opt instrumentType);
  const T::UInt8_opt &getScaleFactorOfCentralWaveNumber() const;
  void setScaleFactorOfCentralWaveNumber(T::UInt8_opt scaleFactorOfCentralWaveNumber);
  const T::UInt32_opt &getScaledValueOfCentralWaveNumber() const;
  void setScaledValueOfCentralWaveNumber(T::UInt32_opt scaledValueOfCentralWaveNumber);

protected:
  // # Copyright 2005-2017 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // # For grib2 to grib1 convertion
  // constant dataRepresentationType = 90;
  //
  //
  // # START 2/template.4.30 ----------------------------------------------------------------------
  // # TEMPLATE 4.30, Satellite Product
  //
  // # Note: This template is deprecated. Template 4.31 should be used instead.
  //
  // #  Parameter category
  // codetable[1] parameterCategory ('4.1.[discipline:l].table',masterDir,localDir) : dump;

  T::UInt8_opt mParameterCategory;

  //
  // #  Parameter number
  // codetable[1] parameterNumber ('4.2.[discipline:l].[parameterCategory:l].table',masterDir,localDir)  : dump;

  T::UInt8_opt mParameterNumber;

  // meta parameterUnits codetable_units(parameterNumber) : dump;
  // meta parameterName  codetable_title(parameterNumber) : dump;
  //
  // #  Type of generating process
  // codetable[1] typeOfGeneratingProcess 'grib2/tables/[tablesVersion]/4.3.table' : dump;

  T::UInt8_opt mTypeOfGeneratingProcess;

  //
  // #  Observation generating process identifier (defined by originating centre)
  // unsigned[1] observationGeneratingProcessIdentifier  : dump;

  T::UInt8_opt mObservationGeneratingProcessIdentifier;

  //
  // #  Number of contributing spectral bands
  // # (NB)
  // unsigned[1]  NB : dump;

  T::UInt8_opt mNB;

  // alias numberOfContributingSpectralBands=NB;
  //
  // if (new() || section4Length>14) {
  // listOfContributingSpectralBands list(numberOfContributingSpectralBands){
  //       unsigned[2] satelliteSeries;

  T::UInt16_opt mSatelliteSeries;

  //       unsigned[2] satelliteNumber;

  T::UInt16_opt mSatelliteNumber;

  //       unsigned[1] instrumentType;

  T::UInt8_opt mInstrumentType;

  //       unsigned[1] scaleFactorOfCentralWaveNumber = missing() : can_be_missing ;

  T::UInt8_opt mScaleFactorOfCentralWaveNumber;

  //       unsigned[4] scaledValueOfCentralWaveNumber = missing() : can_be_missing ;

  T::UInt32_opt mScaledValueOfCentralWaveNumber;

  // }
  // }
  //
  //
  // # END   2/template.4.30 ----------------------------------------------------------------------
};

} // namespace GRIB2
} // namespace SmartMet
