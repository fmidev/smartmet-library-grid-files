// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GridSettingsImpl.*' files.
// ***********************************************************************

#include "GridSettings.h"
#include "../../common/GeneralDefinitions.h"
#include "../../common/GeneralFunctions.h"
#include <boost/functional/hash.hpp>
#include <iostream>
#include <macgyver/Exception.h>

namespace SmartMet {
namespace GRIB2 {

/*! \brief The constructor of the class. */

GridSettings::GridSettings() {
  try {
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The destructor of the class. */

GridSettings::~GridSettings() {
}

/*! \brief The method reads and initializes all data related to the current object.

        \param memoryReader  This object controls the access to the memory mapped file.
*/

void GridSettings::read(MemoryReader &memoryReader) {
  try {
    mNi = memoryReader.read_UInt32_opt();
    mNj = memoryReader.read_UInt32_opt();
    mBasicAngleOfTheInitialProductionDomain = memoryReader.read_UInt32_opt();
    mSubdivisionsOfBasicAngle = memoryReader.read_UInt32_opt();
    mLatitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfFirstGridPoint = memoryReader.read_Int32_opt();
    mResolution.read(memoryReader);
    mLatitudeOfLastGridPoint = memoryReader.read_Int32_opt();
    mLongitudeOfLastGridPoint = memoryReader.read_Int32_opt();
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method writes all data related to the current object.

        \param dataWriter  This object is used for writing the object data.
*/

void GridSettings::write(DataWriter &dataWriter) {
  try {
    dataWriter << mNi;
    dataWriter << mNj;
    dataWriter << mBasicAngleOfTheInitialProductionDomain;
    dataWriter << mSubdivisionsOfBasicAngle;
    dataWriter << mLatitudeOfFirstGridPoint;
    dataWriter << mLongitudeOfFirstGridPoint;
    mResolution.write(dataWriter);
    dataWriter << mLatitudeOfLastGridPoint;
    dataWriter << mLongitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for collecting the current class attributeList.

    \param prefix         The prefix of the each attributeList parameter.
    \param attributeList  The attributeList storage.
*/

void GridSettings::getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const {
  try {
    char name[300];
    sprintf(name, "%sGridSettings.Ni", prefix.c_str());
    attributeList.addAttribute(name, toString(mNi));
    sprintf(name, "%sGridSettings.Nj", prefix.c_str());
    attributeList.addAttribute(name, toString(mNj));
    sprintf(name, "%sGridSettings.BasicAngleOfTheInitialProductionDomain", prefix.c_str());
    attributeList.addAttribute(name, toString(mBasicAngleOfTheInitialProductionDomain));
    sprintf(name, "%sGridSettings.SubdivisionsOfBasicAngle", prefix.c_str());
    attributeList.addAttribute(name, toString(mSubdivisionsOfBasicAngle));
    sprintf(name, "%sGridSettings.LatitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfFirstGridPoint));
    sprintf(name, "%sGridSettings.LongitudeOfFirstGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfFirstGridPoint));
    sprintf(name, "%sGridSettings.", prefix.c_str());
    mResolution.getAttributeList(name, attributeList);
    sprintf(name, "%sGridSettings.LatitudeOfLastGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLatitudeOfLastGridPoint));
    sprintf(name, "%sGridSettings.LongitudeOfLastGridPoint", prefix.c_str());
    attributeList.addAttribute(name, toString(mLongitudeOfLastGridPoint));
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for getting attribute values by their names.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool GridSettings::getAttributeValue(const char *attributeName, std::string &attributeValue) const {
  try {
    if (attributeName == nullptr)
      return false;
    if (strcasecmp(attributeName, "Ni") == 0) {
      attributeValue = toString(mNi);
      return true;
    }
    if (strcasecmp(attributeName, "Nj") == 0) {
      attributeValue = toString(mNj);
      return true;
    }
    if (strcasecmp(attributeName, "BasicAngleOfTheInitialProductionDomain") == 0) {
      attributeValue = toString(mBasicAngleOfTheInitialProductionDomain);
      return true;
    }
    if (strcasecmp(attributeName, "SubdivisionsOfBasicAngle") == 0) {
      attributeValue = toString(mSubdivisionsOfBasicAngle);
      return true;
    }
    if (strcasecmp(attributeName, "LatitudeOfFirstGridPoint") == 0) {
      attributeValue = toString(mLatitudeOfFirstGridPoint);
      return true;
    }
    if (strcasecmp(attributeName, "LongitudeOfFirstGridPoint") == 0) {
      attributeValue = toString(mLongitudeOfFirstGridPoint);
      return true;
    }
    if (mResolution.getAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "LatitudeOfLastGridPoint") == 0) {
      attributeValue = toString(mLatitudeOfLastGridPoint);
      return true;
    }
    if (strcasecmp(attributeName, "LongitudeOfLastGridPoint") == 0) {
      attributeValue = toString(mLongitudeOfLastGridPoint);
      return true;
    }
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method is used for checking if the attribute value matches to the given value.

    \param attributeName  The name of the attribute.
    \param attributeValue The value of the attribute (string).
*/

bool GridSettings::hasAttributeValue(const char *attributeName, const char *attributeValue) const {
  try {
    if (attributeName == nullptr || attributeValue == nullptr)
      return false;
    if (strcasecmp(attributeName, "Ni") == 0 && strcasecmp(attributeValue, toString(mNi).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "Nj") == 0 && strcasecmp(attributeValue, toString(mNj).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "BasicAngleOfTheInitialProductionDomain") == 0 && strcasecmp(attributeValue, toString(mBasicAngleOfTheInitialProductionDomain).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "SubdivisionsOfBasicAngle") == 0 && strcasecmp(attributeValue, toString(mSubdivisionsOfBasicAngle).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "LatitudeOfFirstGridPoint") == 0 && strcasecmp(attributeValue, toString(mLatitudeOfFirstGridPoint).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "LongitudeOfFirstGridPoint") == 0 && strcasecmp(attributeValue, toString(mLongitudeOfFirstGridPoint).c_str()) == 0)
      return true;
    if (mResolution.hasAttributeValue(attributeName, attributeValue))
      return true;
    if (strcasecmp(attributeName, "LatitudeOfLastGridPoint") == 0 && strcasecmp(attributeValue, toString(mLatitudeOfLastGridPoint).c_str()) == 0)
      return true;
    if (strcasecmp(attributeName, "LongitudeOfLastGridPoint") == 0 && strcasecmp(attributeValue, toString(mLongitudeOfLastGridPoint).c_str()) == 0)
      return true;
    return false;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method prints the content of the current object into the given stream.

    \param ostream      The output stream.
    \param level        The print level (used when printing multi-level structures).
    \param optionFlags  The printing options expressed in flag-bits.
*/

void GridSettings::print(std::ostream &stream, uint level, uint optionFlags) const {
  try {
    stream << space(level) << "GridSettings\n";
    stream << space(level) << "- Ni = " << toString(mNi) << "\n";
    stream << space(level) << "- Nj = " << toString(mNj) << "\n";
    stream << space(level) << "- BasicAngleOfTheInitialProductionDomain = " << toString(mBasicAngleOfTheInitialProductionDomain) << "\n";
    stream << space(level) << "- SubdivisionsOfBasicAngle = " << toString(mSubdivisionsOfBasicAngle) << "\n";
    stream << space(level) << "- LatitudeOfFirstGridPoint = " << toString(mLatitudeOfFirstGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfFirstGridPoint = " << toString(mLongitudeOfFirstGridPoint) << "\n";
    mResolution.print(stream, level + 1, optionFlags);
    stream << space(level) << "- LatitudeOfLastGridPoint = " << toString(mLatitudeOfLastGridPoint) << "\n";
    stream << space(level) << "- LongitudeOfLastGridPoint = " << toString(mLongitudeOfLastGridPoint) << "\n";
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method counts the hash value of the current object. */

T::Hash GridSettings::countHash() const {
  try {
    std::size_t seed = 0;
    if (mNi)
      boost::hash_combine(seed, *mNi);
    if (mNj)
      boost::hash_combine(seed, *mNj);
    // if (mBasicAngleOfTheInitialProductionDomain) boost::hash_combine(seed,*mBasicAngleOfTheInitialProductionDomain);
    // if (mSubdivisionsOfBasicAngle) boost::hash_combine(seed,*mSubdivisionsOfBasicAngle);
    if (mLatitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLatitudeOfFirstGridPoint);
    if (mLongitudeOfFirstGridPoint)
      boost::hash_combine(seed, *mLongitudeOfFirstGridPoint);
    // if (mLatitudeOfLastGridPoint) boost::hash_combine(seed,*mLatitudeOfLastGridPoint);
    // if (mLongitudeOfLastGridPoint) boost::hash_combine(seed,*mLongitudeOfLastGridPoint);
    return seed;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNi} attribute. */

const T::UInt32_opt &GridSettings::getNi() const {
  try {
    return mNi;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mNj} attribute. */

const T::UInt32_opt &GridSettings::getNj() const {
  try {
    return mNj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mBasicAngleOfTheInitialProductionDomain} attribute. */

const T::UInt32_opt &GridSettings::getBasicAngleOfTheInitialProductionDomain() const {
  try {
    return mBasicAngleOfTheInitialProductionDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mSubdivisionsOfBasicAngle} attribute. */

const T::UInt32_opt &GridSettings::getSubdivisionsOfBasicAngle() const {
  try {
    return mSubdivisionsOfBasicAngle;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfFirstGridPoint} attribute. */

const T::Int32_opt &GridSettings::getLatitudeOfFirstGridPoint() const {
  try {
    return mLatitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfFirstGridPoint} attribute. */

const T::Int32_opt &GridSettings::getLongitudeOfFirstGridPoint() const {
  try {
    return mLongitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the pointer to the {@link mResolution} attribute. */

ResolutionSettings *GridSettings::getResolution() const {
  try {
    return static_cast<ResolutionSettings *>(&mResolution);
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLatitudeOfLastGridPoint} attribute. */

const T::Int32_opt &GridSettings::getLatitudeOfLastGridPoint() const {
  try {
    return mLatitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

/*! \brief The method returns the value of the {@link mLongitudeOfLastGridPoint} attribute. */

const T::Int32_opt &GridSettings::getLongitudeOfLastGridPoint() const {
  try {
    return mLongitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setNi(T::UInt32_opt ni) {
  try {
    mNi = ni;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setNj(T::UInt32_opt nj) {
  try {
    mNj = nj;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setBasicAngleOfTheInitialProductionDomain(T::UInt32_opt basicAngleOfTheInitialProductionDomain) {
  try {
    mBasicAngleOfTheInitialProductionDomain = basicAngleOfTheInitialProductionDomain;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setSubdivisionsOfBasicAngle(T::UInt32_opt subdivisionsOfBasicAngle) {
  try {
    mSubdivisionsOfBasicAngle = subdivisionsOfBasicAngle;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setLatitudeOfFirstGridPoint(T::Int32_opt latitudeOfFirstGridPoint) {
  try {
    mLatitudeOfFirstGridPoint = latitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setLongitudeOfFirstGridPoint(T::Int32_opt longitudeOfFirstGridPoint) {
  try {
    mLongitudeOfFirstGridPoint = longitudeOfFirstGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setResolution(ResolutionSettings &resolution) {
  try {
    mResolution = resolution;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setLatitudeOfLastGridPoint(T::Int32_opt latitudeOfLastGridPoint) {
  try {
    mLatitudeOfLastGridPoint = latitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

void GridSettings::setLongitudeOfLastGridPoint(T::Int32_opt longitudeOfLastGridPoint) {
  try {
    mLongitudeOfLastGridPoint = longitudeOfLastGridPoint;
  } catch (...) {
    throw Fmi::Exception(BCP, "Operation failed", nullptr);
  }
}

} // namespace GRIB2
} // namespace SmartMet
