// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'AreaProcessedCrossSectionProductImpl.*' files.
// ***********************************************************************

#include "grib2/definition/AreaProcessedCrossSectionProduct.h"
#include "common/Exception.h"
#include "common/GeneralDefinitions.h"
#include "common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

AreaProcessedCrossSectionProduct::AreaProcessedCrossSectionProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

AreaProcessedCrossSectionProduct::~AreaProcessedCrossSectionProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void AreaProcessedCrossSectionProduct::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mHorizontalDimensionProcessed = memoryReader.read_UInt8_opt();
    mTreatmentOfMissingData = memoryReader.read_UInt8_opt();
    mTypeOfStatisticalProcessing = memoryReader.read_UInt8_opt();
    mStartOfRange = memoryReader.read_UInt32_opt();
    mEndOfRange = memoryReader.read_UInt32_opt();
    mNumberOfDataValues = memoryReader.read_UInt16_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void AreaProcessedCrossSectionProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sAreaProcessedCrossSectionProduct.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sAreaProcessedCrossSectionProduct.HorizontalDimensionProcessed", prefix.c_str());
    attributeList.addAttribute(name, toString(mHorizontalDimensionProcessed));
    sprintf(name, "%sAreaProcessedCrossSectionProduct.TreatmentOfMissingData", prefix.c_str());
    attributeList.addAttribute(name, toString(mTreatmentOfMissingData));
    sprintf(name, "%sAreaProcessedCrossSectionProduct.TypeOfStatisticalProcessing", prefix.c_str());
    attributeList.addAttribute(name, toString(mTypeOfStatisticalProcessing));
    sprintf(name, "%sAreaProcessedCrossSectionProduct.StartOfRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mStartOfRange));
    sprintf(name, "%sAreaProcessedCrossSectionProduct.EndOfRange", prefix.c_str());
    attributeList.addAttribute(name, toString(mEndOfRange));
    sprintf(name, "%sAreaProcessedCrossSectionProduct.NumberOfDataValues", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfDataValues));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void AreaProcessedCrossSectionProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "AreaProcessedCrossSectionProduct\n";
    mParameter.print(stream, level + 1, optionFlags);
    stream << space(level) << "- HorizontalDimensionProcessed = " << toString(mHorizontalDimensionProcessed) << "\n";
    stream << space(level) << "- TreatmentOfMissingData = " << toString(mTreatmentOfMissingData) << "\n";
    stream << space(level) << "- TypeOfStatisticalProcessing = " << toString(mTypeOfStatisticalProcessing) << "\n";
    stream << space(level) << "- StartOfRange = " << toString(mStartOfRange) << "\n";
    stream << space(level) << "- EndOfRange = " << toString(mEndOfRange) << "\n";
    stream << space(level) << "- NumberOfDataValues = " << toString(mNumberOfDataValues) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash AreaProcessedCrossSectionProduct::countHash() {
  try {
    std::size_t seed = 0;
    if (mHorizontalDimensionProcessed)
      boost::hash_combine(seed, *mHorizontalDimensionProcessed);
    if (mTreatmentOfMissingData)
      boost::hash_combine(seed, *mTreatmentOfMissingData);
    if (mTypeOfStatisticalProcessing)
      boost::hash_combine(seed, *mTypeOfStatisticalProcessing);
    if (mStartOfRange)
      boost::hash_combine(seed, *mStartOfRange);
    if (mEndOfRange)
      boost::hash_combine(seed, *mEndOfRange);
    if (mNumberOfDataValues)
      boost::hash_combine(seed, *mNumberOfDataValues);
    boost::hash_combine(seed, mParameter.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

const ParameterSettings *AreaProcessedCrossSectionProduct::getParameter() const {
  try {
    return &mParameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mHorizontalDimensionProcessed} attribute. */

const T::UInt8_opt &AreaProcessedCrossSectionProduct::getHorizontalDimensionProcessed() const {
  try {
    return mHorizontalDimensionProcessed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTreatmentOfMissingData} attribute. */

const T::UInt8_opt &AreaProcessedCrossSectionProduct::getTreatmentOfMissingData() const {
  try {
    return mTreatmentOfMissingData;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mTypeOfStatisticalProcessing} attribute. */

const T::UInt8_opt &AreaProcessedCrossSectionProduct::getTypeOfStatisticalProcessing() const {
  try {
    return mTypeOfStatisticalProcessing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mStartOfRange} attribute. */

const T::UInt32_opt &AreaProcessedCrossSectionProduct::getStartOfRange() const {
  try {
    return mStartOfRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mEndOfRange} attribute. */

const T::UInt32_opt &AreaProcessedCrossSectionProduct::getEndOfRange() const {
  try {
    return mEndOfRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfDataValues} attribute. */

const T::UInt16_opt &AreaProcessedCrossSectionProduct::getNumberOfDataValues() const {
  try {
    return mNumberOfDataValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AreaProcessedCrossSectionProduct::setParameter(ParameterSettings parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AreaProcessedCrossSectionProduct::setHorizontalDimensionProcessed(T::UInt8_opt horizontalDimensionProcessed) {
  try {
    mHorizontalDimensionProcessed = horizontalDimensionProcessed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AreaProcessedCrossSectionProduct::setTreatmentOfMissingData(T::UInt8_opt treatmentOfMissingData) {
  try {
    mTreatmentOfMissingData = treatmentOfMissingData;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AreaProcessedCrossSectionProduct::setTypeOfStatisticalProcessing(T::UInt8_opt typeOfStatisticalProcessing) {
  try {
    mTypeOfStatisticalProcessing = typeOfStatisticalProcessing;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AreaProcessedCrossSectionProduct::setStartOfRange(T::UInt32_opt startOfRange) {
  try {
    mStartOfRange = startOfRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AreaProcessedCrossSectionProduct::setEndOfRange(T::UInt32_opt endOfRange) {
  try {
    mEndOfRange = endOfRange;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void AreaProcessedCrossSectionProduct::setNumberOfDataValues(T::UInt16_opt numberOfDataValues) {
  try {
    mNumberOfDataValues = numberOfDataValues;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
