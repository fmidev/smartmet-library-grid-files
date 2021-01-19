// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'SecondOrderSettingsImpl.*' files.
// ***********************************************************************

#include "SecondOrderSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

SecondOrderSettings::SecondOrderSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

SecondOrderSettings::~SecondOrderSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void SecondOrderSettings::read(MemoryReader &memoryReader) {
  try {
    mGroupSplitting = memoryReader.read_UInt8_opt();
    mMissingValueManagement = memoryReader.read_UInt8_opt();
    mPrimaryMissingValue = memoryReader.read_UInt32_opt();
    mSecondaryMissingValue = memoryReader.read_UInt32_opt();
    mNumberOfGroups = memoryReader.read_UInt32_opt();
    mReferenceOfWidths = memoryReader.read_UInt8_opt();
    mWidthOfWidths = memoryReader.read_UInt8_opt();
    mReferenceOfLengths = memoryReader.read_UInt32_opt();
    mIncrementOfLengths = memoryReader.read_UInt8_opt();
    mTrueLengthOfLastGroup = memoryReader.read_UInt32_opt();
    mWidthOfLengths = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void SecondOrderSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mGroupSplitting;
    dataWriter << mMissingValueManagement;
    dataWriter << mPrimaryMissingValue;
    dataWriter << mSecondaryMissingValue;
    dataWriter << mNumberOfGroups;
    dataWriter << mReferenceOfWidths;
    dataWriter << mWidthOfWidths;
    dataWriter << mReferenceOfLengths;
    dataWriter << mIncrementOfLengths;
    dataWriter << mTrueLengthOfLastGroup;
    dataWriter << mWidthOfLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void SecondOrderSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sSecondOrderSettings.GroupSplitting", prefix.c_str());
    attributeList.addAttribute(name, toString(mGroupSplitting));
    sprintf(name, "%sSecondOrderSettings.MissingValueManagement", prefix.c_str());
    attributeList.addAttribute(name, toString(mMissingValueManagement));
    sprintf(name, "%sSecondOrderSettings.PrimaryMissingValue", prefix.c_str());
    attributeList.addAttribute(name, toString(mPrimaryMissingValue));
    sprintf(name, "%sSecondOrderSettings.SecondaryMissingValue", prefix.c_str());
    attributeList.addAttribute(name, toString(mSecondaryMissingValue));
    sprintf(name, "%sSecondOrderSettings.NumberOfGroups", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfGroups));
    sprintf(name, "%sSecondOrderSettings.ReferenceOfWidths", prefix.c_str());
    attributeList.addAttribute(name, toString(mReferenceOfWidths));
    sprintf(name, "%sSecondOrderSettings.WidthOfWidths", prefix.c_str());
    attributeList.addAttribute(name, toString(mWidthOfWidths));
    sprintf(name, "%sSecondOrderSettings.ReferenceOfLengths", prefix.c_str());
    attributeList.addAttribute(name, toString(mReferenceOfLengths));
    sprintf(name, "%sSecondOrderSettings.IncrementOfLengths", prefix.c_str());
    attributeList.addAttribute(name, toString(mIncrementOfLengths));
    sprintf(name, "%sSecondOrderSettings.TrueLengthOfLastGroup", prefix.c_str());
    attributeList.addAttribute(name, toString(mTrueLengthOfLastGroup));
    sprintf(name, "%sSecondOrderSettings.WidthOfLengths", prefix.c_str());
    attributeList.addAttribute(name, toString(mWidthOfLengths));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void SecondOrderSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "SecondOrderSettings\n";
    stream << space(level) << "- GroupSplitting = " << toString(mGroupSplitting) << "\n";
    stream << space(level) << "- MissingValueManagement = " << toString(mMissingValueManagement) << "\n";
    stream << space(level) << "- PrimaryMissingValue = " << toString(mPrimaryMissingValue) << "\n";
    stream << space(level) << "- SecondaryMissingValue = " << toString(mSecondaryMissingValue) << "\n";
    stream << space(level) << "- NumberOfGroups = " << toString(mNumberOfGroups) << "\n";
    stream << space(level) << "- ReferenceOfWidths = " << toString(mReferenceOfWidths) << "\n";
    stream << space(level) << "- WidthOfWidths = " << toString(mWidthOfWidths) << "\n";
    stream << space(level) << "- ReferenceOfLengths = " << toString(mReferenceOfLengths) << "\n";
    stream << space(level) << "- IncrementOfLengths = " << toString(mIncrementOfLengths) << "\n";
    stream << space(level) << "- TrueLengthOfLastGroup = " << toString(mTrueLengthOfLastGroup) << "\n";
    stream << space(level) << "- WidthOfLengths = " << toString(mWidthOfLengths) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash SecondOrderSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mGroupSplitting)
      boost::hash_combine(seed, *mGroupSplitting);
    if (mMissingValueManagement)
      boost::hash_combine(seed, *mMissingValueManagement);
    if (mPrimaryMissingValue)
      boost::hash_combine(seed, *mPrimaryMissingValue);
    if (mSecondaryMissingValue)
      boost::hash_combine(seed, *mSecondaryMissingValue);
    if (mNumberOfGroups)
      boost::hash_combine(seed, *mNumberOfGroups);
    if (mReferenceOfWidths)
      boost::hash_combine(seed, *mReferenceOfWidths);
    if (mWidthOfWidths)
      boost::hash_combine(seed, *mWidthOfWidths);
    if (mReferenceOfLengths)
      boost::hash_combine(seed, *mReferenceOfLengths);
    if (mIncrementOfLengths)
      boost::hash_combine(seed, *mIncrementOfLengths);
    if (mTrueLengthOfLastGroup)
      boost::hash_combine(seed, *mTrueLengthOfLastGroup);
    if (mWidthOfLengths)
      boost::hash_combine(seed, *mWidthOfLengths);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mGroupSplitting} attribute. */

const T::UInt8_opt &SecondOrderSettings::getGroupSplitting() const {
  try {
    return mGroupSplitting;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mMissingValueManagement} attribute. */

const T::UInt8_opt &SecondOrderSettings::getMissingValueManagement() const {
  try {
    return mMissingValueManagement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPrimaryMissingValue} attribute. */

const T::UInt32_opt &SecondOrderSettings::getPrimaryMissingValue() const {
  try {
    return mPrimaryMissingValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSecondaryMissingValue} attribute. */

const T::UInt32_opt &SecondOrderSettings::getSecondaryMissingValue() const {
  try {
    return mSecondaryMissingValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfGroups} attribute. */

const T::UInt32_opt &SecondOrderSettings::getNumberOfGroups() const {
  try {
    return mNumberOfGroups;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mReferenceOfWidths} attribute. */

const T::UInt8_opt &SecondOrderSettings::getReferenceOfWidths() const {
  try {
    return mReferenceOfWidths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mWidthOfWidths} attribute. */

const T::UInt8_opt &SecondOrderSettings::getWidthOfWidths() const {
  try {
    return mWidthOfWidths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mReferenceOfLengths} attribute. */

const T::UInt32_opt &SecondOrderSettings::getReferenceOfLengths() const {
  try {
    return mReferenceOfLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mIncrementOfLengths} attribute. */

const T::UInt8_opt &SecondOrderSettings::getIncrementOfLengths() const {
  try {
    return mIncrementOfLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTrueLengthOfLastGroup} attribute. */

const T::UInt32_opt &SecondOrderSettings::getTrueLengthOfLastGroup() const {
  try {
    return mTrueLengthOfLastGroup;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mWidthOfLengths} attribute. */

const T::UInt8_opt &SecondOrderSettings::getWidthOfLengths() const {
  try {
    return mWidthOfLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setGroupSplitting(T::UInt8_opt groupSplitting) {
  try {
    mGroupSplitting = groupSplitting;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setMissingValueManagement(T::UInt8_opt missingValueManagement) {
  try {
    mMissingValueManagement = missingValueManagement;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setPrimaryMissingValue(T::UInt32_opt primaryMissingValue) {
  try {
    mPrimaryMissingValue = primaryMissingValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setSecondaryMissingValue(T::UInt32_opt secondaryMissingValue) {
  try {
    mSecondaryMissingValue = secondaryMissingValue;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setNumberOfGroups(T::UInt32_opt numberOfGroups) {
  try {
    mNumberOfGroups = numberOfGroups;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setReferenceOfWidths(T::UInt8_opt referenceOfWidths) {
  try {
    mReferenceOfWidths = referenceOfWidths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setWidthOfWidths(T::UInt8_opt widthOfWidths) {
  try {
    mWidthOfWidths = widthOfWidths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setReferenceOfLengths(T::UInt32_opt referenceOfLengths) {
  try {
    mReferenceOfLengths = referenceOfLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setIncrementOfLengths(T::UInt8_opt incrementOfLengths) {
  try {
    mIncrementOfLengths = incrementOfLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setTrueLengthOfLastGroup(T::UInt32_opt trueLengthOfLastGroup) {
  try {
    mTrueLengthOfLastGroup = trueLengthOfLastGroup;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void SecondOrderSettings::setWidthOfLengths(T::UInt8_opt widthOfLengths) {
  try {
    mWidthOfLengths = widthOfLengths;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
