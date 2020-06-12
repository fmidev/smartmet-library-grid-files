// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ComplexGridDataRepresentationImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"
#include "../RepresentationDefinition.h"
#include "OriginalValuesSettings.h"
#include "PackingSettings.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (5.2).*/

class ComplexGridDataRepresentation : public RepresentationDefinition {
public:
  ComplexGridDataRepresentation();
  ComplexGridDataRepresentation(const ComplexGridDataRepresentation &other);
  virtual ~ComplexGridDataRepresentation();

  virtual uint getTemplateNumber() const;
  virtual RepresentationDefinition *createRepresentationDefinition() const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  PackingSettings *getPacking() const;
  void setPacking(PackingSettings &packing);
  OriginalValuesSettings *getOriginalValues() const;
  void setOriginalValues(OriginalValuesSettings &originalValues);
  const T::UInt8_opt &getGroupSplittingMethodUsed() const;
  void setGroupSplittingMethodUsed(T::UInt8_opt groupSplittingMethodUsed);
  const T::UInt8_opt &getMissingValueManagementUsed() const;
  void setMissingValueManagementUsed(T::UInt8_opt missingValueManagementUsed);
  const T::UInt32_opt &getPrimaryMissingValueSubstitute() const;
  void setPrimaryMissingValueSubstitute(T::UInt32_opt primaryMissingValueSubstitute);
  const T::UInt32_opt &getSecondaryMissingValueSubstitute() const;
  void setSecondaryMissingValueSubstitute(T::UInt32_opt secondaryMissingValueSubstitute);
  const T::UInt32_opt &getNumberOfGroupsOfDataValues() const;
  void setNumberOfGroupsOfDataValues(T::UInt32_opt numberOfGroupsOfDataValues);
  const T::UInt8_opt &getReferenceForGroupWidths() const;
  void setReferenceForGroupWidths(T::UInt8_opt referenceForGroupWidths);
  const T::UInt8_opt &getNumberOfBitsUsedForTheGroupWidths() const;
  void setNumberOfBitsUsedForTheGroupWidths(T::UInt8_opt numberOfBitsUsedForTheGroupWidths);
  const T::UInt32_opt &getReferenceForGroupLengths() const;
  void setReferenceForGroupLengths(T::UInt32_opt referenceForGroupLengths);
  const T::UInt8_opt &getLengthIncrementForTheGroupLengths() const;
  void setLengthIncrementForTheGroupLengths(T::UInt8_opt lengthIncrementForTheGroupLengths);
  const T::UInt32_opt &getTrueLengthOfLastGroup() const;
  void setTrueLengthOfLastGroup(T::UInt32_opt trueLengthOfLastGroup);
  const T::UInt8_opt &getNumberOfBitsForScaledGroupLengths() const;
  void setNumberOfBitsForScaledGroupLengths(T::UInt8_opt numberOfBitsForScaledGroupLengths);

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
  //
  // # START 2/template.5.2 ----------------------------------------------------------------------
  // # TEMPLATE 5.2, Grid point data - complex packing
  //
  // include "grib2/template.5.packing.def";

  mutable PackingSettings mPacking;

  // include "grib2/template.5.original_values.def";

  mutable OriginalValuesSettings mOriginalValues;

  //
  // #  Group splitting method used
  // codetable[1] groupSplittingMethodUsed ('5.4.table',masterDir,localDir);

  T::UInt8_opt mGroupSplittingMethodUsed;

  //
  // #  Missing value management used
  // codetable[1] missingValueManagementUsed ('5.5.table',masterDir,localDir);

  T::UInt8_opt mMissingValueManagementUsed;

  //
  // #  Primary missing value substitute
  // unsigned[4] primaryMissingValueSubstitute ;

  T::UInt32_opt mPrimaryMissingValueSubstitute;

  //
  // #  Secondary missing value substitute
  // unsigned[4] secondaryMissingValueSubstitute ;

  T::UInt32_opt mSecondaryMissingValueSubstitute;

  //
  // #  NG - Number of groups of data values into which field is split
  // unsigned[4] numberOfGroupsOfDataValues ;

  T::UInt32_opt mNumberOfGroupsOfDataValues;

  //
  // alias NG  = numberOfGroupsOfDataValues;
  // #  Reference for group widths
  // # NOTE 12 NOT FOUND
  // unsigned[1] referenceForGroupWidths ;

  T::UInt8_opt mReferenceForGroupWidths;

  //
  // #  Number of bits used for the group widths
  // # (after the reference value in octet 36 has been removed)
  // unsigned[1] numberOfBitsUsedForTheGroupWidths ;

  T::UInt8_opt mNumberOfBitsUsedForTheGroupWidths;

  //
  // #  Reference for group lengths
  // # NOTE 13 NOT FOUND
  // unsigned[4] referenceForGroupLengths ;

  T::UInt32_opt mReferenceForGroupLengths;

  //
  // #  Length increment for the group lengths
  // # NOTE 14 NOT FOUND
  // unsigned[1] lengthIncrementForTheGroupLengths ;

  T::UInt8_opt mLengthIncrementForTheGroupLengths;

  //
  // #  True length of last group
  // unsigned[4] trueLengthOfLastGroup ;

  T::UInt32_opt mTrueLengthOfLastGroup;

  //
  // #  Number of bits used for the scaled group lengths
  // # (after subtraction of the reference value given in octets 38-41 and division
  // # by the length increment given in octet 42)
  // unsigned[1] numberOfBitsForScaledGroupLengths ;

  T::UInt8_opt mNumberOfBitsForScaledGroupLengths;

  // alias numberOfBitsUsedForTheScaledGroupLengths=numberOfBitsForScaledGroupLengths;
  //
  //
  // # END   2/template.5.2 ----------------------------------------------------------------------
};

} // namespace GRIB2
} // namespace SmartMet
