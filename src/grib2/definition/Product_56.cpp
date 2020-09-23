// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'Product_56Impl.*' files.
// ***********************************************************************

#include "Product_56.h"
#include <macgyver/Exception.h>
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

Product_56::Product_56() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The copy constructor of the class. */

Product_56::Product_56(const Product_56 &other) : ProductDefinition(other) {
  try {
    mHorizontal = other.mHorizontal;
    mEps = other.mEps;
    mPerturbationNumber = other.mPerturbationNumber;
    mNumberOfForecastsInEnsemble = other.mNumberOfForecastsInEnsemble;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The destructor of the class. */

Product_56::~Product_56() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void Product_56::read(MemoryReader &memoryReader) {
  try {
    mHorizontal.read(memoryReader);
    mEps.read(memoryReader);
    mPerturbationNumber = memoryReader.read_UInt8_opt();
    mNumberOfForecastsInEnsemble = memoryReader.read_UInt8_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void Product_56::write(DataWriter &dataWriter) {
  try {
    mHorizontal.write(dataWriter);
    mEps.write(dataWriter);
    dataWriter << mPerturbationNumber;
    dataWriter << mNumberOfForecastsInEnsemble;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void Product_56::getAttributeList(std::string prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sProduct_56.", prefix.c_str());
    mHorizontal.getAttributeList(name, attributeList);
    sprintf(name, "%sProduct_56.", prefix.c_str());
    mEps.getAttributeList(name, attributeList);
    sprintf(name, "%sProduct_56.PerturbationNumber", prefix.c_str());
    attributeList.addAttribute(name, toString(mPerturbationNumber));
    sprintf(name, "%sProduct_56.NumberOfForecastsInEnsemble", prefix.c_str());
    attributeList.addAttribute(name, toString(mNumberOfForecastsInEnsemble));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void Product_56::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "Product_56\n";
    mHorizontal.print(stream, level + 1, optionFlags);
    mEps.print(stream, level + 1, optionFlags);
    stream << space(level) << "- PerturbationNumber = " << toString(mPerturbationNumber) << "\n";
    stream << space(level) << "- NumberOfForecastsInEnsemble = " << toString(mNumberOfForecastsInEnsemble) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash Product_56::countHash() {
  try {
    std::size_t seed = 0;
    if (mPerturbationNumber)
      boost::hash_combine(seed, *mPerturbationNumber);
    if (mNumberOfForecastsInEnsemble)
      boost::hash_combine(seed, *mNumberOfForecastsInEnsemble);
    boost::hash_combine(seed, mHorizontal.countHash());
    boost::hash_combine(seed, mEps.countHash());
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method return the template number of the current class. */

uint Product_56::getTemplateNumber() const {
  return 56;
}

ProductDefinition *Product_56::createProductDefinition() const {
  try {
    return static_cast<ProductDefinition *>(new Product_56(*this));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mHorizontal} attribute. */

HorizontalSettings *Product_56::getHorizontal() const {
  try {
    return static_cast<HorizontalSettings *>(&mHorizontal);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mEps} attribute. */

EpsSettings *Product_56::getEps() const {
  try {
    return static_cast<EpsSettings *>(&mEps);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mPerturbationNumber} attribute. */

const T::UInt8_opt &Product_56::getPerturbationNumber() const {
  try {
    return mPerturbationNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNumberOfForecastsInEnsemble} attribute. */

const T::UInt8_opt &Product_56::getNumberOfForecastsInEnsemble() const {
  try {
    return mNumberOfForecastsInEnsemble;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void Product_56::setHorizontal(HorizontalSettings &horizontal) {
  try {
    mHorizontal = horizontal;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void Product_56::setEps(EpsSettings &eps) {
  try {
    mEps = eps;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void Product_56::setPerturbationNumber(T::UInt8_opt perturbationNumber) {
  try {
    mPerturbationNumber = perturbationNumber;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

void Product_56::setNumberOfForecastsInEnsemble(T::UInt8_opt numberOfForecastsInEnsemble) {
  try {
    mNumberOfForecastsInEnsemble = numberOfForecastsInEnsemble;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed!", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
