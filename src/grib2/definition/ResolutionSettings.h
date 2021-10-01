// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ResolutionSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.resolution_flags).*/

class ResolutionSettings {
public:
  ResolutionSettings();
  virtual ~ResolutionSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  std::uint8_t getResolutionAndComponentFlags() const;
  void setResolutionAndComponentFlags(std::uint8_t resolutionAndComponentFlags);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // #  Resolution and component flags
  // flags[1] resolutionAndComponentFlags 'grib2/tables/[tablesVersion]/3.3.table' : edition_specific,no_copy;

  std::uint8_t mResolutionAndComponentFlags;

  //
  // # Note our flagbit numbers run from 7 to 0, while WMO convention uses 1 to 8
  // # (most significant to least significant)
  //
  // flagbit resolutionAndComponentFlags1(resolutionAndComponentFlags,7) = 0: read_only;
  // flagbit resolutionAndComponentFlags2(resolutionAndComponentFlags,6) = 0: read_only;
  // flagbit iDirectionIncrementGiven(resolutionAndComponentFlags,5);
  // flagbit jDirectionIncrementGiven(resolutionAndComponentFlags,4);
  // flagbit uvRelativeToGrid(resolutionAndComponentFlags,3);
  // flagbit resolutionAndComponentFlags6(resolutionAndComponentFlags,7) = 0: read_only;
  // flagbit resolutionAndComponentFlags7(resolutionAndComponentFlags,6) = 0: read_only;
  // flagbit resolutionAndComponentFlags8(resolutionAndComponentFlags,6) = 0: read_only;
  //
  // concept ijDirectionIncrementGiven {
  //   '1' = {
  //     iDirectionIncrementGiven = 1;
  //     jDirectionIncrementGiven = 1;
  //   }
  //   '0' = {
  //     iDirectionIncrementGiven = 1;
  //     jDirectionIncrementGiven = 0;
  //   }
  //   '0' = {
  //     iDirectionIncrementGiven = 0;
  //     jDirectionIncrementGiven = 1;
  //   }
  //   '0' = {
  //     iDirectionIncrementGiven = 0;
  //     jDirectionIncrementGiven = 0;
  //   }
  // }
  //
  // alias DiGiven=iDirectionIncrementGiven;
  // alias DjGiven=jDirectionIncrementGiven;
};

} // namespace GRIB2
} // namespace SmartMet
