// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ParameterPartitionSettingsImpl.*' files.
// ***********************************************************************

#include "ParameterPartitionSettings.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

ParameterPartitionSettings::ParameterPartitionSettings() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

ParameterPartitionSettings::ParameterPartitionSettings(const ParameterPartitionSettings &other) {
  try {
    mParameterCategory = other.mParameterCategory;
    mParameterNumber = other.mParameterNumber;
    mPartitionTable = other.mPartitionTable;
    mNumberOfPartitions = other.mNumberOfPartitions;
    mPartitionItems = other.mPartitionItems;
    mPartitionNumber = other.mPartitionNumber;
    mTypeOfGeneratingProcess = other.mTypeOfGeneratingProcess;
    mBackgroundProcess = other.mBackgroundProcess;
    mGeneratingProcessIdentifier = other.mGeneratingProcessIdentifier;
    mHoursAfterDataCutoff = other.mHoursAfterDataCutoff;
    mMinutesAfterDataCutoff = other.mMinutesAfterDataCutoff;
    mIndicatorOfUnitOfTimeRange = other.mIndicatorOfUnitOfTimeRange;
    mForecastTime = other.mForecastTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

ParameterPartitionSettings::~ParameterPartitionSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void ParameterPartitionSettings::read(MemoryReader &memoryReader) {
  try {
    mParameterCategory = memoryReader.read_UInt8_opt();
    mParameterNumber = memoryReader.read_UInt8_opt();
    mPartitionTable = memoryReader.read_UInt8_opt();
    mNumberOfPartitions = memoryReader.read_UInt8_opt();
    mPartitionItems = memoryReader.read_UInt16_opt();
    mPartitionNumber = memoryReader.read_UInt16_opt();
    mTypeOfGeneratingProcess = memoryReader.read_UInt8_opt();
    mBackgroundProcess = memoryReader.read_UInt8_opt();
    mGeneratingProcessIdentifier = memoryReader.read_UInt8_opt();
    mHoursAfterDataCutoff = memoryReader.read_UInt16_opt();
    mMinutesAfterDataCutoff = memoryReader.read_UInt8_opt();
    mIndicatorOfUnitOfTimeRange = memoryReader.read_UInt8_opt();
    mForecastTime = memoryReader.read_Int32_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void ParameterPartitionSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mParameterCategory;
    dataWriter << mParameterNumber;
    dataWriter << mPartitionTable;
    dataWriter << mNumberOfPartitions;
    dataWriter << mPartitionItems;
    dataWriter << mPartitionNumber;
    dataWriter << mTypeOfGeneratingProcess;
    dataWriter << mBackgroundProcess;
    dataWriter << mGeneratingProcessIdentifier;
    dataWriter << mHoursAfterDataCutoff;
    dataWriter << mMinutesAfterDataCutoff;
    dataWriter << mIndicatorOfUnitOfTimeRange;
    dataWriter << mForecastTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void ParameterPartitionSettings::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sParameterPartitionSettings.ParameterCategory", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterCategory));
    sprintf(name, "%sParameterPartitionSettings.ParameterNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mParameterNumber));
    sprintf(name, "%sParameterPartitionSettings.PartitionTable", prefix.c_str());
    attributeList.addAttribute(name, toString(mPartitionTable));
    sprintf(name, "%sParameterPartitionSettings.NumberOfPartitions", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfPartitions));
    sprintf(name, "%sParameterPartitionSettings.PartitionItems", prefix.c_str());
    attributeList.addAttribute(name, toString(mPartitionItems));
    sprintf(name, "%sParameterPartitionSettings.PartitionNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mPartitionNumber));
    sprintf(name, "%sParameterPartitionSettings.TypeOfGeneratingProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfGeneratingProcess));
    sprintf(name, "%sParameterPartitionSettings.BackgroundProcess", prefix.c_str());
    attributeList.addAttribute(name, toString(mBackgroundProcess));
    sprintf(name, "%sParameterPartitionSettings.GeneratingProcessIdentifier", prefix.c_str());
    attributeList.addAttribute(name, toString(mGeneratingProcessIdentifier));
    sprintf(name, "%sParameterPartitionSettings.HoursAfterDataCutoff", prefix.c_str());
    attributeList.addAttribute(name, toString(mHoursAfterDataCutoff));
    sprintf(name, "%sParameterPartitionSettings.MinutesAfterDataCutoff", prefix.c_str());
    attributeList.addAttribute(name, toString(mMinutesAfterDataCutoff));
    sprintf(name, "%sParameterPartitionSettings.IndicatorOfUnitOfTimeRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mIndicatorOfUnitOfTimeRange));
    sprintf(name, "%sParameterPartitionSettings.ForecastTime", prefix.c_str());
    attributeList.addAttribute(name, toString(mForecastTime));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void ParameterPartitionSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "ParameterPartitionSettings\n";
    stream << space(level) << "- ParameterCategory = " << toString(mParameterCategory) << "\n";
    stream << space(level) << "- ParameterNumber = " << toString(mParameterNumber) << "\n";
    stream << space(level) << "- PartitionTable = " << toString(mPartitionTable) << "\n";
    stream << space(level) << "- NumberOfPartitions = " << toString(mNumberOfPartitions) << "\n";
    stream << space(level) << "- PartitionItems = " << toString(mPartitionItems) << "\n";
    stream << space(level) << "- PartitionNumber = " << toString(mPartitionNumber) << "\n";
    stream << space(level) << "- TypeOfGeneratingProcess = " << toString(mTypeOfGeneratingProcess) << "\n";
    stream << space(level) << "- BackgroundProcess = " << toString(mBackgroundProcess) << "\n";
    stream << space(level) << "- GeneratingProcessIdentifier = " << toString(mGeneratingProcessIdentifier) << "\n";
    stream << space(level) << "- HoursAfterDataCutoff = " << toString(mHoursAfterDataCutoff) << "\n";
    stream << space(level) << "- MinutesAfterDataCutoff = " << toString(mMinutesAfterDataCutoff) << "\n";
    stream << space(level) << "- IndicatorOfUnitOfTimeRange = " << toString(mIndicatorOfUnitOfTimeRange) << "\n";
    stream << space(level) << "- ForecastTime = " << toString(mForecastTime) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash ParameterPartitionSettings::countHash() {
  try {
    std::size_t seed = 0;
    if (mParameterCategory)
      boost::hash_combine(seed, *mParameterCategory);
    if (mParameterNumber)
      boost::hash_combine(seed, *mParameterNumber);
    if (mPartitionTable)
      boost::hash_combine(seed, *mPartitionTable);
    if (mNumberOfPartitions)
      boost::hash_combine(seed, *mNumberOfPartitions);
    if (mPartitionItems)
      boost::hash_combine(seed, *mPartitionItems);
    if (mPartitionNumber)
      boost::hash_combine(seed, *mPartitionNumber);
    if (mTypeOfGeneratingProcess)
      boost::hash_combine(seed, *mTypeOfGeneratingProcess);
    if (mBackgroundProcess)
      boost::hash_combine(seed, *mBackgroundProcess);
    if (mGeneratingProcessIdentifier)
      boost::hash_combine(seed, *mGeneratingProcessIdentifier);
    if (mHoursAfterDataCutoff)
      boost::hash_combine(seed, *mHoursAfterDataCutoff);
    if (mMinutesAfterDataCutoff)
      boost::hash_combine(seed, *mMinutesAfterDataCutoff);
    if (mIndicatorOfUnitOfTimeRange)
      boost::hash_combine(seed, *mIndicatorOfUnitOfTimeRange);
    if (mForecastTime)
      boost::hash_combine(seed, *mForecastTime);
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterCategory} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getParameterCategory() const {
  try {
    return mParameterCategory;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mParameterNumber} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getParameterNumber() const {
  try {
    return mParameterNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPartitionTable} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getPartitionTable() const {
  try {
    return mPartitionTable;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfPartitions} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getNumberOfPartitions() const {
  try {
    return mNumberOfPartitions;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPartitionItems} attribute. */

const T::UInt16_opt &ParameterPartitionSettings::getPartitionItems() const {
  try {
    return mPartitionItems;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPartitionNumber} attribute. */

const T::UInt16_opt &ParameterPartitionSettings::getPartitionNumber() const {
  try {
    return mPartitionNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfGeneratingProcess} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getTypeOfGeneratingProcess() const {
  try {
    return mTypeOfGeneratingProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mBackgroundProcess} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getBackgroundProcess() const {
  try {
    return mBackgroundProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mGeneratingProcessIdentifier} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getGeneratingProcessIdentifier() const {
  try {
    return mGeneratingProcessIdentifier;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mHoursAfterDataCutoff} attribute. */

const T::UInt16_opt &ParameterPartitionSettings::getHoursAfterDataCutoff() const {
  try {
    return mHoursAfterDataCutoff;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mMinutesAfterDataCutoff} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getMinutesAfterDataCutoff() const {
  try {
    return mMinutesAfterDataCutoff;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mIndicatorOfUnitOfTimeRange} attribute. */

const T::UInt8_opt &ParameterPartitionSettings::getIndicatorOfUnitOfTimeRange() const {
  try {
    return mIndicatorOfUnitOfTimeRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the value of the {@link mForecastTime} attribute. */

const T::Int32_opt &ParameterPartitionSettings::getForecastTime() const {
  try {
    return mForecastTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setParameterCategory(T::UInt8_opt parameterCategory) {
  try {
    mParameterCategory = parameterCategory;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setParameterNumber(T::UInt8_opt parameterNumber) {
  try {
    mParameterNumber = parameterNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setPartitionTable(T::UInt8_opt partitionTable) {
  try {
    mPartitionTable = partitionTable;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setNumberOfPartitions(T::UInt8_opt numberOfPartitions) {
  try {
    mNumberOfPartitions = numberOfPartitions;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setPartitionItems(T::UInt16_opt partitionItems) {
  try {
    mPartitionItems = partitionItems;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setPartitionNumber(T::UInt16_opt partitionNumber) {
  try {
    mPartitionNumber = partitionNumber;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setTypeOfGeneratingProcess(T::UInt8_opt typeOfGeneratingProcess) {
  try {
    mTypeOfGeneratingProcess = typeOfGeneratingProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setBackgroundProcess(T::UInt8_opt backgroundProcess) {
  try {
    mBackgroundProcess = backgroundProcess;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setGeneratingProcessIdentifier(T::UInt8_opt generatingProcessIdentifier) {
  try {
    mGeneratingProcessIdentifier = generatingProcessIdentifier;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setHoursAfterDataCutoff(T::UInt16_opt hoursAfterDataCutoff) {
  try {
    mHoursAfterDataCutoff = hoursAfterDataCutoff;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setMinutesAfterDataCutoff(T::UInt8_opt minutesAfterDataCutoff) {
  try {
    mMinutesAfterDataCutoff = minutesAfterDataCutoff;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setIndicatorOfUnitOfTimeRange(T::UInt8_opt indicatorOfUnitOfTimeRange) {
  try {
    mIndicatorOfUnitOfTimeRange = indicatorOfUnitOfTimeRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void ParameterPartitionSettings::setForecastTime(T::Int32_opt forecastTime) {
  try {
    mForecastTime = forecastTime;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
