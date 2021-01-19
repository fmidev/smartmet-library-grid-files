// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ComplexDifferenceGridDataRepresentationImpl.*' files.
// ***********************************************************************

#include "ComplexDifferenceGridDataRepresentation.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

ComplexDifferenceGridDataRepresentation::ComplexDifferenceGridDataRepresentation() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

ComplexDifferenceGridDataRepresentation::~ComplexDifferenceGridDataRepresentation() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ComplexDifferenceGridDataRepresentation::read(MemoryReader &memoryReader) {
  try {
    mPacking.read(memoryReader);
    mOriginalValues.read(memoryReader);
    mGroupSplittingMethodUsed = memoryReader.read_UInt8_opt();
    mMissingValueManagementUsed = memoryReader.read_UInt8_opt();
    mPrimaryMissingValueSubstitute = memoryReader.read_UInt32_opt();
    mSecondaryMissingValueSubstitute = memoryReader.read_UInt32_opt();
    mNumberOfGroupsOfDataValues = memoryReader.read_UInt32_opt();
    mReferenceForGroupWidths = memoryReader.read_UInt8_opt();
    mNumberOfBitsUsedForTheGroupWidths = memoryReader.read_UInt8_opt();
    mReferenceForGroupLengths = memoryReader.read_UInt32_opt();
    mLengthIncrementForTheGroupLengths = memoryReader.read_UInt8_opt();
    mTrueLengthOfLastGroup = memoryReader.read_UInt32_opt();
    mNumberOfBitsForScaledGroupLengths = memoryReader.read_UInt8_opt();
    mOrderOfSpatialDifferencing = memoryReader.read_UInt8_opt();
    mNumberOfOctetsExtraDescriptors = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void ComplexDifferenceGridDataRepresentation::write(DataWriter &dataWriter) {
  try {
    mPacking.write(dataWriter);
    mOriginalValues.write(dataWriter);
    dataWriter << mGroupSplittingMethodUsed;
    dataWriter << mMissingValueManagementUsed;
    dataWriter << mPrimaryMissingValueSubstitute;
    dataWriter << mSecondaryMissingValueSubstitute;
    dataWriter << mNumberOfGroupsOfDataValues;
    dataWriter << mReferenceForGroupWidths;
    dataWriter << mNumberOfBitsUsedForTheGroupWidths;
    dataWriter << mReferenceForGroupLengths;
    dataWriter << mLengthIncrementForTheGroupLengths;
    dataWriter << mTrueLengthOfLastGroup;
    dataWriter << mNumberOfBitsForScaledGroupLengths;
    dataWriter << mOrderOfSpatialDifferencing;
    dataWriter << mNumberOfOctetsExtraDescriptors;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ComplexDifferenceGridDataRepresentation::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.", prefix.c_str());
    mPacking.getAttributeList(name, attributeList);
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.", prefix.c_str());
    mOriginalValues.getAttributeList(name, attributeList);
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.GroupSplittingMethodUsed", prefix.c_str());
    attributeList.addAttribute(name, toString(mGroupSplittingMethodUsed));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.MissingValueManagementUsed", prefix.c_str());
    attributeList.addAttribute(name, toString(mMissingValueManagementUsed));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.PrimaryMissingValueSubstitute", prefix.c_str());
    attributeList.addAttribute(name, toString(mPrimaryMissingValueSubstitute));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.SecondaryMissingValueSubstitute", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecondaryMissingValueSubstitute));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.NumberOfGroupsOfDataValues", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfGroupsOfDataValues));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.ReferenceForGroupWidths", prefix.c_str());
    attributeList.addAttribute(name, toString(mReferenceForGroupWidths));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.NumberOfBitsUsedForTheGroupWidths", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfBitsUsedForTheGroupWidths));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.ReferenceForGroupLengths", prefix.c_str());
    attributeList.addAttribute(name, toString(mReferenceForGroupLengths));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.LengthIncrementForTheGroupLengths", prefix.c_str());
    attributeList.addAttribute(name, toString(mLengthIncrementForTheGroupLengths));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.TrueLengthOfLastGroup", prefix.c_str());
    attributeList.addAttribute(name, toString(mTrueLengthOfLastGroup));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.NumberOfBitsForScaledGroupLengths", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfBitsForScaledGroupLengths));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.OrderOfSpatialDifferencing", prefix.c_str());
    attributeList.addAttribute(name, toString(mOrderOfSpatialDifferencing));
    sprintf(name, "%sComplexDifferenceGridDataRepresentation.NumberOfOctetsExtraDescriptors", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfOctetsExtraDescriptors));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ComplexDifferenceGridDataRepresentation::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ComplexDifferenceGridDataRepresentation\n";
    mPacking.print(stream, level + 1, optionFlags);
    mOriginalValues.print(stream, level + 1, optionFlags);
    stream << space(level) << "- GroupSplittingMethodUsed = " << toString(mGroupSplittingMethodUsed) << "\n";
    stream << space(level) << "- MissingValueManagementUsed = " << toString(mMissingValueManagementUsed) << "\n";
    stream << space(level) << "- PrimaryMissingValueSubstitute = " << toString(mPrimaryMissingValueSubstitute) << "\n";
    stream << space(level) << "- SecondaryMissingValueSubstitute = " << toString(mSecondaryMissingValueSubstitute) << "\n";
    stream << space(level) << "- NumberOfGroupsOfDataValues = " << toString(mNumberOfGroupsOfDataValues) << "\n";
    stream << space(level) << "- ReferenceForGroupWidths = " << toString(mReferenceForGroupWidths) << "\n";
    stream << space(level) << "- NumberOfBitsUsedForTheGroupWidths = " << toString(mNumberOfBitsUsedForTheGroupWidths) << "\n";
    stream << space(level) << "- ReferenceForGroupLengths = " << toString(mReferenceForGroupLengths) << "\n";
    stream << space(level) << "- LengthIncrementForTheGroupLengths = " << toString(mLengthIncrementForTheGroupLengths) << "\n";
    stream << space(level) << "- TrueLengthOfLastGroup = " << toString(mTrueLengthOfLastGroup) << "\n";
    stream << space(level) << "- NumberOfBitsForScaledGroupLengths = " << toString(mNumberOfBitsForScaledGroupLengths) << "\n";
    stream << space(level) << "- OrderOfSpatialDifferencing = " << toString(mOrderOfSpatialDifferencing) << "\n";
    stream << space(level) << "- NumberOfOctetsExtraDescriptors = " << toString(mNumberOfOctetsExtraDescriptors) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ComplexDifferenceGridDataRepresentation::countHash() {
  try {
    std::size_t seed = 0;
    if (mGroupSplittingMethodUsed)
      boost::hash_combine(seed, *mGroupSplittingMethodUsed);
    if (mMissingValueManagementUsed)
      boost::hash_combine(seed, *mMissingValueManagementUsed);
    if (mPrimaryMissingValueSubstitute)
      boost::hash_combine(seed, *mPrimaryMissingValueSubstitute);
    if (mSecondaryMissingValueSubstitute)
      boost::hash_combine(seed, *mSecondaryMissingValueSubstitute);
    if (mNumberOfGroupsOfDataValues)
      boost::hash_combine(seed, *mNumberOfGroupsOfDataValues);
    if (mReferenceForGroupWidths)
      boost::hash_combine(seed, *mReferenceForGroupWidths);
    if (mNumberOfBitsUsedForTheGroupWidths)
      boost::hash_combine(seed, *mNumberOfBitsUsedForTheGroupWidths);
    if (mReferenceForGroupLengths)
      boost::hash_combine(seed, *mReferenceForGroupLengths);
    if (mLengthIncrementForTheGroupLengths)
      boost::hash_combine(seed, *mLengthIncrementForTheGroupLengths);
    if (mTrueLengthOfLastGroup)
      boost::hash_combine(seed, *mTrueLengthOfLastGroup);
    if (mNumberOfBitsForScaledGroupLengths)
      boost::hash_combine(seed, *mNumberOfBitsForScaledGroupLengths);
    if (mOrderOfSpatialDifferencing)
      boost::hash_combine(seed, *mOrderOfSpatialDifferencing);
    if (mNumberOfOctetsExtraDescriptors)
      boost::hash_combine(seed, *mNumberOfOctetsExtraDescriptors);
    boost::hash_combine(seed, mPacking.countHash());
    boost::hash_combine(seed, mOriginalValues.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint ComplexDifferenceGridDataRepresentation::getTemplateNumber() const {
  return 3;
}

RepresentationDefinition *ComplexDifferenceGridDataRepresentation::createRepresentationDefinition() const {
  try {
    return static_cast<RepresentationDefinition *>(new ComplexDifferenceGridDataRepresentation(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mPacking} attribute. */

PackingSettings *ComplexDifferenceGridDataRepresentation::getPacking() const {
  try {
    return static_cast<PackingSettings *>(&mPacking);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mOriginalValues} attribute. */

OriginalValuesSettings *ComplexDifferenceGridDataRepresentation::getOriginalValues() const {
  try {
    return static_cast<OriginalValuesSettings *>(&mOriginalValues);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mGroupSplittingMethodUsed} attribute. */

const T::UInt8_opt &ComplexDifferenceGridDataRepresentation::getGroupSplittingMethodUsed() const {
  try {
    return mGroupSplittingMethodUsed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mMissingValueManagementUsed} attribute. */

const T::UInt8_opt &ComplexDifferenceGridDataRepresentation::getMissingValueManagementUsed() const {
  try {
    return mMissingValueManagementUsed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPrimaryMissingValueSubstitute} attribute. */

const T::UInt32_opt &ComplexDifferenceGridDataRepresentation::getPrimaryMissingValueSubstitute() const {
  try {
    return mPrimaryMissingValueSubstitute;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSecondaryMissingValueSubstitute} attribute. */

const T::UInt32_opt &ComplexDifferenceGridDataRepresentation::getSecondaryMissingValueSubstitute() const {
  try {
    return mSecondaryMissingValueSubstitute;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfGroupsOfDataValues} attribute. */

const T::UInt32_opt &ComplexDifferenceGridDataRepresentation::getNumberOfGroupsOfDataValues() const {
  try {
    return mNumberOfGroupsOfDataValues;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mReferenceForGroupWidths} attribute. */

const T::UInt8_opt &ComplexDifferenceGridDataRepresentation::getReferenceForGroupWidths() const {
  try {
    return mReferenceForGroupWidths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfBitsUsedForTheGroupWidths} attribute. */

const T::UInt8_opt &ComplexDifferenceGridDataRepresentation::getNumberOfBitsUsedForTheGroupWidths() const {
  try {
    return mNumberOfBitsUsedForTheGroupWidths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mReferenceForGroupLengths} attribute. */

const T::UInt32_opt &ComplexDifferenceGridDataRepresentation::getReferenceForGroupLengths() const {
  try {
    return mReferenceForGroupLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLengthIncrementForTheGroupLengths} attribute. */

const T::UInt8_opt &ComplexDifferenceGridDataRepresentation::getLengthIncrementForTheGroupLengths() const {
  try {
    return mLengthIncrementForTheGroupLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTrueLengthOfLastGroup} attribute. */

const T::UInt32_opt &ComplexDifferenceGridDataRepresentation::getTrueLengthOfLastGroup() const {
  try {
    return mTrueLengthOfLastGroup;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfBitsForScaledGroupLengths} attribute. */

const T::UInt8_opt &ComplexDifferenceGridDataRepresentation::getNumberOfBitsForScaledGroupLengths() const {
  try {
    return mNumberOfBitsForScaledGroupLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mOrderOfSpatialDifferencing} attribute. */

const T::UInt8_opt &ComplexDifferenceGridDataRepresentation::getOrderOfSpatialDifferencing() const {
  try {
    return mOrderOfSpatialDifferencing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfOctetsExtraDescriptors} attribute. */

const T::UInt8_opt &ComplexDifferenceGridDataRepresentation::getNumberOfOctetsExtraDescriptors() const {
  try {
    return mNumberOfOctetsExtraDescriptors;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setPacking(PackingSettings &packing) {
  try {
    mPacking = packing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setOriginalValues(OriginalValuesSettings &originalValues) {
  try {
    mOriginalValues = originalValues;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setGroupSplittingMethodUsed(T::UInt8_opt groupSplittingMethodUsed) {
  try {
    mGroupSplittingMethodUsed = groupSplittingMethodUsed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setMissingValueManagementUsed(T::UInt8_opt missingValueManagementUsed) {
  try {
    mMissingValueManagementUsed = missingValueManagementUsed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setPrimaryMissingValueSubstitute(T::UInt32_opt primaryMissingValueSubstitute) {
  try {
    mPrimaryMissingValueSubstitute = primaryMissingValueSubstitute;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setSecondaryMissingValueSubstitute(T::UInt32_opt secondaryMissingValueSubstitute) {
  try {
    mSecondaryMissingValueSubstitute = secondaryMissingValueSubstitute;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setNumberOfGroupsOfDataValues(T::UInt32_opt numberOfGroupsOfDataValues) {
  try {
    mNumberOfGroupsOfDataValues = numberOfGroupsOfDataValues;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setReferenceForGroupWidths(T::UInt8_opt referenceForGroupWidths) {
  try {
    mReferenceForGroupWidths = referenceForGroupWidths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setNumberOfBitsUsedForTheGroupWidths(T::UInt8_opt numberOfBitsUsedForTheGroupWidths) {
  try {
    mNumberOfBitsUsedForTheGroupWidths = numberOfBitsUsedForTheGroupWidths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setReferenceForGroupLengths(T::UInt32_opt referenceForGroupLengths) {
  try {
    mReferenceForGroupLengths = referenceForGroupLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setLengthIncrementForTheGroupLengths(T::UInt8_opt lengthIncrementForTheGroupLengths) {
  try {
    mLengthIncrementForTheGroupLengths = lengthIncrementForTheGroupLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setTrueLengthOfLastGroup(T::UInt32_opt trueLengthOfLastGroup) {
  try {
    mTrueLengthOfLastGroup = trueLengthOfLastGroup;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setNumberOfBitsForScaledGroupLengths(T::UInt8_opt numberOfBitsForScaledGroupLengths) {
  try {
    mNumberOfBitsForScaledGroupLengths = numberOfBitsForScaledGroupLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setOrderOfSpatialDifferencing(T::UInt8_opt orderOfSpatialDifferencing) {
  try {
    mOrderOfSpatialDifferencing = orderOfSpatialDifferencing;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void ComplexDifferenceGridDataRepresentation::setNumberOfOctetsExtraDescriptors(T::UInt8_opt numberOfOctetsExtraDescriptors) {
  try {
    mNumberOfOctetsExtraDescriptors = numberOfOctetsExtraDescriptors;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
