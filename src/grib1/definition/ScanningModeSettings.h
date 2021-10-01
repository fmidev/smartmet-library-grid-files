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
namespace GRIB1 {
/*! \brief The class is automatically created from the template (scanning_mode).*/

class ScanningModeSettings {
public:
  ScanningModeSettings();
  virtual ~ScanningModeSettings();

  virtual void getAttributeList(const std::string &prefix, T::AttributeList &attributeList) const;
  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual bool getAttributeValue(const char *attributeName, std::string &attributeValue) const;
  virtual bool hasAttributeValue(const char *attributeName, const char *attributeValue) const;
  virtual T::Hash countHash();

  std::uint8_t getScanningMode() const;
  void setScanningMode(std::uint8_t scanningMode);

protected:
  // #  Scanning mode
  // flags[1] scanningMode 'grib1/8.table' : edition_specific,no_copy;

  std::uint8_t mScanningMode;

  //
  // # Not flagbit numbers 7 to 0, while wmo is 1 to 8
  // flagbit iScansNegatively(scanningMode,7)  : dump;
  // flagbit jScansPositively(scanningMode,6)  : dump;
  // flagbit jPointsAreConsecutive(scanningMode,5)  : dump;
  // constant alternativeRowScanning=0 : dump;
  // transient iScansPositively = !iScansNegatively : constraint;
  //
  // alias geography.iScansNegatively=iScansNegatively;
  // alias geography.jScansPositively=jScansPositively;
  // alias geography.jPointsAreConsecutive=jPointsAreConsecutive;
  //
  // flagbit scanningMode4(scanningMode,4) = 0: read_only;
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
  //
  // if (jPointsAreConsecutive) {
  // 	alias numberOfRows=Ni;
  // 	alias numberOfColumns=Nj;
  // } else {
  // 	alias numberOfRows=Nj;
  // 	alias numberOfColumns=Ni;
  // }
};

} // namespace GRIB1
} // namespace SmartMet
