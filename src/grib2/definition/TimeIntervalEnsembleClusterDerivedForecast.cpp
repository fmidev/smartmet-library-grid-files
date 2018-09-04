// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalEnsembleClusterDerivedForecastImpl.*' files.
// ***********************************************************************

#include "TimeIntervalEnsembleClusterDerivedForecast.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeIntervalEnsembleClusterDerivedForecast::TimeIntervalEnsembleClusterDerivedForecast() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The copy constructor of the class. */

TimeIntervalEnsembleClusterDerivedForecast::TimeIntervalEnsembleClusterDerivedForecast(const TimeIntervalEnsembleClusterDerivedForecast &other) : ProductDefinition(other) {
  try {
    mParameter = other.mParameter;
    mHorizontal = other.mHorizontal;
    mDerived = other.mDerived;
    mRectangularCluster = other.mRectangularCluster;
    mStatistical = other.mStatistical;
    mEnsembleForecastNumbers = other.mEnsembleForecastNumbers;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The destructor of the class. */

TimeIntervalEnsembleClusterDerivedForecast::~TimeIntervalEnsembleClusterDerivedForecast() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void TimeIntervalEnsembleClusterDerivedForecast::read(MemoryReader &memoryReader) {
  try {
    mParameter.read(memoryReader);
    mHorizontal.read(memoryReader);
    mDerived.read(memoryReader);
    mRectangularCluster.read(memoryReader);
    mStatistical.read(memoryReader);
    mEnsembleForecastNumbers = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void TimeIntervalEnsembleClusterDerivedForecast::write(DataWriter &dataWriter) {
  try {
    mParameter.write(dataWriter);
    mHorizontal.write(dataWriter);
    mDerived.write(dataWriter);
    mRectangularCluster.write(dataWriter);
    mStatistical.write(dataWriter);
    dataWriter << mEnsembleForecastNumbers;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeIntervalEnsembleClusterDerivedForecast::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTimeIntervalEnsembleClusterDerivedForecast.", prefix.c_str());
    mParameter.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleClusterDerivedForecast.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleClusterDerivedForecast.", prefix.c_str());
    mDerived.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleClusterDerivedForecast.", prefix.c_str());
    mRectangularCluster.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleClusterDerivedForecast.", prefix.c_str());
    mStatistical.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalEnsembleClusterDerivedForecast.EnsembleForecastNumbers", prefix.c_str());
    attributeList.addAttribute(name, toString(mEnsembleForecastNumbers));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void TimeIntervalEnsembleClusterDerivedForecast::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TimeIntervalEnsembleClusterDerivedForecast\n";
    mParameter.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mDerived.print(stream, level + 1, optionFlags);
    mRectangularCluster.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
    stream << space(level) << "- EnsembleForecastNumbers = " << toString(mEnsembleForecastNumbers) << "\n";
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeIntervalEnsembleClusterDerivedForecast::countHash() {
  try {
    std::size_t seed = 0;
    if (mEnsembleForecastNumbers)
      boost::hash_combine(seed, *mEnsembleForecastNumbers);
    boost::hash_combine(seed, mParameter.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mDerived.countHash());
    boost::hash_combine(seed, mRectangularCluster.countHash());
    boost::hash_combine(seed, mStatistical.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method return the template number of the current class. */

uint TimeIntervalEnsembleClusterDerivedForecast::getTemplateNumber() const {
  return 13;
}

ProductDefinition *TimeIntervalEnsembleClusterDerivedForecast::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new TimeIntervalEnsembleClusterDerivedForecast(*this));
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mParameter} attribute. */

ParameterSettings *TimeIntervalEnsembleClusterDerivedForecast::getParameter() const {
  try {
    return static_cast<ParameterSettings *>(&mParameter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *TimeIntervalEnsembleClusterDerivedForecast::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mDerived} attribute. */

DerivedSettings *TimeIntervalEnsembleClusterDerivedForecast::getDerived() const {
  try {
    return static_cast<DerivedSettings *>(&mDerived);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mRectangularCluster} attribute. */

RectangularClusterSettings *TimeIntervalEnsembleClusterDerivedForecast::getRectangularCluster() const {
  try {
    return static_cast<RectangularClusterSettings *>(&mRectangularCluster);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

StatisticalSettings *TimeIntervalEnsembleClusterDerivedForecast::getStatistical() const {
  try {
    return static_cast<StatisticalSettings *>(&mStatistical);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

/*! \brief The method returns the value of the {@link mEnsembleForecastNumbers} attribute. */

const T::UInt8_opt &TimeIntervalEnsembleClusterDerivedForecast::getEnsembleForecastNumbers() const {
  try {
    return mEnsembleForecastNumbers;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleClusterDerivedForecast::setParameter(ParameterSettings &parameter) {
  try {
    mParameter = parameter;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleClusterDerivedForecast::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleClusterDerivedForecast::setDerived(DerivedSettings &derived) {
  try {
    mDerived = derived;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleClusterDerivedForecast::setRectangularCluster(RectangularClusterSettings &rectangularCluster) {
  try {
    mRectangularCluster = rectangularCluster;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleClusterDerivedForecast::setStatistical(StatisticalSettings &statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

void TimeIntervalEnsembleClusterDerivedForecast::setEnsembleForecastNumbers(T::UInt8_opt ensembleForecastNumbers) {
  try {
    mEnsembleForecastNumbers = ensembleForecastNumbers;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, NULL);
  }
}

} // namespace GRIB2
} // namespace SmartMet
