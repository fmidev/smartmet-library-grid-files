// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'CharacterStringProductImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../ProductDefinition.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.254).*/

class CharacterStringProduct : public ProductDefinition {
public:
  CharacterStringProduct();
  virtual ~CharacterStringProduct();

  virtual uint getTemplateNumber() const;
  virtual ProductDefinition *createProductDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  const T::UInt8_opt &getParameterCategory() const;
  void setParameterCategory(T::UInt8_opt parameterCategory);
  const T::UInt8_opt &getParameterNumber() const;
  void setParameterNumber(T::UInt8_opt parameterNumber);
  const T::UInt32_opt &getNumberOfCharacters() const;
  void setNumberOfCharacters(T::UInt32_opt numberOfCharacters);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // # TEMPLATE 4.254, CCITT IA5 character string
  //
  // #  Parameter category
  // codetable[1] parameterCategory ('4.1.[discipline:l].table',masterDir,localDir): dump;

  T::UInt8_opt mParameterCategory;

  //
  // #  Parameter number
  // codetable[1] parameterNumber ('4.2.[discipline:l].[parameterCategory:l].table',masterDir,localDir)  : dump;

  T::UInt8_opt mParameterNumber;

  // meta parameterUnits codetable_units(parameterNumber) : dump;
  // meta parameterName  codetable_title(parameterNumber) : dump;
  //
  // #  Number of characters
  // unsigned[4] numberOfCharacters  : dump;

  T::UInt32_opt mNumberOfCharacters;
};

} // namespace GRIB2
} // namespace SmartMet
