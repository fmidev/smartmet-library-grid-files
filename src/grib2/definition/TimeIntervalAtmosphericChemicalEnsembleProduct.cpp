// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'TimeIntervalAtmosphericChemicalEnsembleProductImpl.*' files.
// ***********************************************************************

#include "TimeIntervalAtmosphericChemicalEnsembleProduct.h"
#include "../../common/Exception.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

TimeIntervalAtmosphericChemicalEnsembleProduct::TimeIntervalAtmosphericChemicalEnsembleProduct() {
  try {
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The copy constructor of the class. */

TimeIntervalAtmosphericChemicalEnsembleProduct::TimeIntervalAtmosphericChemicalEnsembleProduct(const TimeIntervalAtmosphericChemicalEnsembleProduct &other)
    : ProductDefinition(other) {
  try {
    mParameterChemical = other.mParameterChemical;
    mHorizontal = other.mHorizontal;
    mEps = other.mEps;
    mStatistical = other.mStatistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The destructor of the class. */

TimeIntervalAtmosphericChemicalEnsembleProduct::~TimeIntervalAtmosphericChemicalEnsembleProduct() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void TimeIntervalAtmosphericChemicalEnsembleProduct::read(MemoryReader &memoryReader) {
  try {
    mParameterChemical.read(memoryReader);
    mHorizontal.read(memoryReader);
    mEps.read(memoryReader);
    mStatistical.read(memoryReader);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void TimeIntervalAtmosphericChemicalEnsembleProduct::write(DataWriter &dataWriter) {
  try {
    mParameterChemical.write(dataWriter);
    mHorizontal.write(dataWriter);
    mEps.write(dataWriter);
    mStatistical.write(dataWriter);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void TimeIntervalAtmosphericChemicalEnsembleProduct::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sTimeIntervalAtmosphericChemicalEnsembleProduct.", prefix.c_str());
    mParameterChemical.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalAtmosphericChemicalEnsembleProduct.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalAtmosphericChemicalEnsembleProduct.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
    sprintf(name, "%sTimeIntervalAtmosphericChemicalEnsembleProduct.", prefix.c_str());
    mStatistical.getAttributeList(name, attributeList);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void TimeIntervalAtmosphericChemicalEnsembleProduct::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "TimeIntervalAtmosphericChemicalEnsembleProduct\n";
    mParameterChemical.print(stream, level + 1, optionFlags);
    mHorizontal.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
    mStatistical.print(stream, level + 1, optionFlags);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash TimeIntervalAtmosphericChemicalEnsembleProduct::countHash() {
  try {
    std::size_t seed = 0;
    boost::hash_combine(seed, mParameterChemical.countHash());
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mEps.countHash());
    boost::hash_combine(seed, mStatistical.countHash());
    return seed;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint TimeIntervalAtmosphericChemicalEnsembleProduct::getTemplateNumber() const {
  return 43;
}

ProductDefinition *TimeIntervalAtmosphericChemicalEnsembleProduct::createProductDefinition() const {
  try {
    return (ProductDefinition *)new TimeIntervalAtmosphericChemicalEnsembleProduct(*this);
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mParameterChemical} attribute. */

ParameterChemicalSettings *TimeIntervalAtmosphericChemicalEnsembleProduct::getParameterChemical() const {
  try {
    return (ParameterChemicalSettings *)&mParameterChemical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *TimeIntervalAtmosphericChemicalEnsembleProduct::getHorizontal() const {
  try {
    return (HorizontalSettings *)&mHorizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

EpsSettings *TimeIntervalAtmosphericChemicalEnsembleProduct::getEps() const {
  try {
    return (EpsSettings *)&mEps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mStatistical} attribute. */

StatisticalSettings *TimeIntervalAtmosphericChemicalEnsembleProduct::getStatistical() const {
  try {
    return (StatisticalSettings *)&mStatistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void TimeIntervalAtmosphericChemicalEnsembleProduct::setParameterChemical(ParameterChemicalSettings &parameterChemical) {
  try {
    mParameterChemical = parameterChemical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void TimeIntervalAtmosphericChemicalEnsembleProduct::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void TimeIntervalAtmosphericChemicalEnsembleProduct::setEps(EpsSettings &eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

void TimeIntervalAtmosphericChemicalEnsembleProduct::setStatistical(StatisticalSettings &statistical) {
  try {
    mStatistical = statistical;
  } catch (...) {
    throw SmartMet::Spine::Exception(BCP, exception_operation_failed, nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
