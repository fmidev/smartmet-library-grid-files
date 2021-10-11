// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SphericalHarmonicsDataRepresentationImpl.*' files.
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
/*! \brief The class is automatically created from the template (5.51).*/

class SphericalHarmonicsDataRepresentation : public RepresentationDefinition {
public:
  SphericalHarmonicsDataRepresentation();
  virtual ~SphericalHarmonicsDataRepresentation();

  virtual uint getTemplateNumber() const;
  virtual RepresentationDefinition *createRepresentationDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  PackingSettings *getPacking() const;
  void setPacking(PackingSettings &packing);
  const T::Int32_opt &getLaplacianScalingFactor() const;
  void setLaplacianScalingFactor(T::Int32_opt laplacianScalingFactor);
  const T::UInt16_opt &getJS() const;
  void setJS(T::UInt16_opt jS);
  const T::UInt16_opt &getKS() const;
  void setKS(T::UInt16_opt kS);
  const T::UInt16_opt &getMS() const;
  void setMS(T::UInt16_opt mS);
  const T::UInt32_opt &getTS() const;
  void setTS(T::UInt32_opt tS);
  const T::UInt8_opt &getUnpackedSubsetPrecision() const;
  void setUnpackedSubsetPrecision(T::UInt8_opt unpackedSubsetPrecision);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 5.51, Spherical harmonics data - complex packing
  //
  // include "grib2/template.5.packing.def";

  mutable PackingSettings mPacking;

  //
  // if (gribex_mode_on()) {
  //   transient computeLaplacianOperator=0 : hidden;
  // } else {
  //     transient computeLaplacianOperator=1 : hidden;
  // }
  //
  // meta _numberOfValues spectral_truncation(J,K,M,numberOfValues): read_only;
  //
  // constant laplacianScalingFactorUnset  = -2147483647;
  // signed[4] laplacianScalingFactor : edition_specific ;

  T::Int32_opt mLaplacianScalingFactor;

  //
  // meta  data.laplacianOperator    scale(laplacianScalingFactor,one,million,truncateLaplacian) ;
  // meta  laplacianOperatorIsSet    evaluate(laplacianScalingFactor != laplacianScalingFactorUnset && !computeLaplacianOperator);
  //
  // unsigned[2] JS ;

  T::UInt16_opt mJS;

  // unsigned[2] KS ;

  T::UInt16_opt mKS;

  // unsigned[2] MS ;

  T::UInt16_opt mMS;

  //
  // alias subSetJ=JS ;
  // alias subSetK=KS ;
  // alias subSetM=MS ;
  //
  // unsigned[4] TS ;

  T::UInt32_opt mTS;

  //
  // meta _TS spectral_truncation(JS,KS,MS,TS) : read_only,hidden;
  //
  // # This is read_only until we support other values
  // codetable[1] unpackedSubsetPrecision ('5.7.table',masterDir,localDir) = 1 : dump;

  T::UInt8_opt mUnpackedSubsetPrecision;

  //
  // alias precisionOfTheUnpackedSubset=unpackedSubsetPrecision;
};

} // namespace GRIB2
} // namespace SmartMet
