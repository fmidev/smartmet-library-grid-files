// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ResolutionFlagsSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template (resolution_flags).*/

class ResolutionFlagsSettings {
public:
  ResolutionFlagsSettings();
  virtual ~ResolutionFlagsSettings();

  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual T::Hash countHash();

  std::uint8_t getResolutionAndComponentFlags() const;
  void setResolutionAndComponentFlags(std::uint8_t resolutionAndComponentFlags);

protected:
  // #  Resolution and component flags
  // flags[1] resolutionAndComponentFlags 'grib1/7.table' : edition_specific,no_copy ;

  std::uint8_t mResolutionAndComponentFlags;

  //
  // # Note our flagbit numbers run from 7 to 0, while WMO convention uses 1 to 8
  // # (most significant to least significant)
  //
  // flagbit ijDirectionIncrementGiven(resolutionAndComponentFlags,7) = 1 ;
  //
  // # For grib 1 to 2
  // alias iDirectionIncrementGiven = ijDirectionIncrementGiven;
  // alias jDirectionIncrementGiven = ijDirectionIncrementGiven;
  // alias DiGiven = ijDirectionIncrementGiven;
  // alias DjGiven = ijDirectionIncrementGiven;
  //
  // flagbit earthIsOblate(resolutionAndComponentFlags,6) : dump;
  // if (earthIsOblate) {
  //   # Earth assumed oblate spheroidal with size as determined by IAU in 1965
  //   transient earthMajorAxis = 6378160.0;
  //   transient earthMinorAxis = 6356775.0;
  //   alias earthMajorAxisInMetres=earthMajorAxis;
  //   alias earthMinorAxisInMetres=earthMinorAxis;
  // }
  //
  //
  // flagbit resolutionAndComponentFlags3(resolutionAndComponentFlags,5) = 0: read_only;
  // flagbit resolutionAndComponentFlags4(resolutionAndComponentFlags,4) = 0: read_only;
  //
  // flagbit uvRelativeToGrid(resolutionAndComponentFlags,3) : dump;
  //
  // flagbit resolutionAndComponentFlags6(resolutionAndComponentFlags,2) = 0: read_only;
  // flagbit resolutionAndComponentFlags7(resolutionAndComponentFlags,1) = 0: read_only;
  // flagbit resolutionAndComponentFlags8(resolutionAndComponentFlags,0) = 0: read_only;
};

} // namespace GRIB1
} // namespace SmartMet
