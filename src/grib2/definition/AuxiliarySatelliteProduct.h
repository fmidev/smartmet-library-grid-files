// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AuxiliarySatelliteProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib2/ProductDefinition.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.311).*/

class AuxiliarySatelliteProduct : public ProductDefinition {
public:
  AuxiliarySatelliteProduct();
  virtual ~AuxiliarySatelliteProduct();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getParameterCategory() const;
  const T::UInt8_opt &getParameterNumber() const;
  const T::UInt8_opt &getTypeOfGeneratingProcess() const;
  const T::UInt8_opt &getObservationGeneratingProcessIdentifier() const;
  const T::UInt8_opt &getNB() const;
  const T::UInt8_opt &getTypeOfAuxiliaryInformation() const;
  const T::UInt16_opt &getSatelliteSeries() const;
  const T::UInt16_opt &getSatelliteNumber() const;
  const T::UInt16_opt &getInstrumentType() const;
  const T::UInt8_opt &getScaleFactorOfCentralWaveNumber() const;
  const T::UInt32_opt &getScaledValueOfCentralWaveNumber() const;

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version
  // 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and
  // immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it
  // submit to any jurisdiction.
  // #
  //
  // # For grib2 to grib1 convertion
  // constant dataRepresentationType = 90;
  //
  //
  // # START 2/template.4.311
  // ----------------------------------------------------------------------
  // # TEMPLATE 4.311, Satellite Product Auxiliary Information
  // #  Parameter category
  // codetable[1] parameterCategory
  // ('4.1.[discipline:l].table',masterDir,localDir) : dump;

  T::UInt8_opt mParameterCategory;

  //
  // #  Parameter number
  // codetable[1] parameterNumber
  // ('4.2.[discipline:l].[parameterCategory:l].table',masterDir,localDir)  :
  // dump;

  T::UInt8_opt mParameterNumber;

  // meta parameterUnits codetable_units(parameterNumber) : dump;
  // meta parameterName  codetable_title(parameterNumber) : dump;
  //
  // #  Type of generating process
  // codetable[1] typeOfGeneratingProcess ('4.3.table',masterDir,localDir) :
  // dump;

  T::UInt8_opt mTypeOfGeneratingProcess;

  //
  // #  Observation generating process identifier (defined by originating
  // centre)
  // unsigned[1] observationGeneratingProcessIdentifier  : dump;

  T::UInt8_opt mObservationGeneratingProcessIdentifier;

  //
  // #  Number of contributing spectral bands
  // # (NB)
  // unsigned[1] NB  : dump;

  T::UInt8_opt mNB;

  // alias numberOfContributingSpectralBands=NB;
  //
  // codetable[1] typeOfAuxiliaryInformation ('4.15.table',masterDir,localDir) :
  // dump;

  T::UInt8_opt mTypeOfAuxiliaryInformation;

  //
  // listOfContributingSpectralBands list(numberOfContributingSpectralBands){
  //       unsigned[2] satelliteSeries : dump;

  T::UInt16_opt mSatelliteSeries;

  //       unsigned[2] satelliteNumber : dump;

  T::UInt16_opt mSatelliteNumber;

  //       unsigned[2] instrumentType : dump;

  T::UInt16_opt mInstrumentType;

  //       unsigned[1] scaleFactorOfCentralWaveNumber = missing() :
  //       dump,can_be_missing ;

  T::UInt8_opt mScaleFactorOfCentralWaveNumber;

  //       unsigned[4] scaledValueOfCentralWaveNumber = missing() :
  //       dump,can_be_missing ;

  T::UInt32_opt mScaledValueOfCentralWaveNumber;

  // }
  //
  // # END   2/template.4.311
  // ----------------------------------------------------------------------
};

} // namespace GRIB2
} // namespace SmartMet
