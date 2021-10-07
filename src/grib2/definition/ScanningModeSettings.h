// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'ScanningModeSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (3.scanning_mode).*/

class ScanningModeSettings {
public:
  ScanningModeSettings();
  virtual ~ScanningModeSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash() const;

  std::uint8_t getScanningMode() const;
  void setScanningMode(std::uint8_t scanningMode);

protected:
  // # Copyright 2005-2019 ECMWF.
  //
  // flags[1] scanningMode 'grib2/tables/[tablesVersion]/3.4.table' : edition_specific,no_copy ;

  std::uint8_t mScanningMode;

  //
  // # Note our flagbit numbers go from 7 to 0, while WMO convention is from 1 to 8
  // flagbit iScansNegatively(scanningMode,7) : dump;   # WMO bit 1
  // flagbit jScansPositively(scanningMode,6) : dump;   # WMO bit 2
  // flagbit jPointsAreConsecutive(scanningMode,5) : dump;
  // flagbit alternativeRowScanning(scanningMode,4) = 0 : edition_specific,dump;
  //
  // if (jPointsAreConsecutive) {
  //     alias numberOfRows=Ni;
  //     alias numberOfColumns=Nj;
  // } else {
  //     alias numberOfRows=Nj;
  //     alias numberOfColumns=Ni;
  // }
  //
  // alias geography.iScansNegatively=iScansNegatively;
  // alias geography.jScansPositively=jScansPositively;
  // alias geography.jPointsAreConsecutive=jPointsAreConsecutive;
  //
  // transient iScansPositively = !iScansNegatively : constraint;
  //
  // flagbit scanningMode5(scanningMode,3) = 0: read_only;
  // flagbit scanningMode6(scanningMode,2) = 0: read_only;
  // flagbit scanningMode7(scanningMode,1) = 0: read_only;
  // flagbit scanningMode8(scanningMode,0) = 0: read_only;
  //
  // meta swapScanningX change_scanning_direction( values,Ni,Nj,
  //                  iScansNegatively,jScansPositively,
  //                  xFirst,xLast,x) : edition_specific,hidden,no_copy;
  // alias swapScanningLon = swapScanningX;
  //
  // meta swapScanningY change_scanning_direction( values,Ni,Nj,
  //                  iScansNegatively,jScansPositively,
  //                  yFirst,yLast,y) : edition_specific,hidden,no_copy;
  // alias swapScanningLat = swapScanningY;
};

} // namespace GRIB2
} // namespace SmartMet
