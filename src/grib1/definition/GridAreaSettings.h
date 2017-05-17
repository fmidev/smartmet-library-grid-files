// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'GridAreaSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "common/AttributeList.h"
#include "common/MemoryReader.h"
#include "grib1/definition/ResolutionFlagsSettings.h"
#include "grid/Typedefs.h"

namespace SmartMet {
namespace GRIB1 {
/*! \brief The class is automatically created from the template
 * (grid_first_last_resandcomp).*/

class GridAreaSettings {
public:
  GridAreaSettings();
  virtual ~GridAreaSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void getAttributeList(std::string prefix,
                                T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  std::int24_t getLatitudeOfFirstGridPoint() const;
  std::int24_t getLongitudeOfFirstGridPoint() const;
  const ResolutionFlagsSettings *getResolutionFlags() const;
  std::int24_t getLatitudeOfLastGridPoint() const;
  std::int24_t getLongitudeOfLastGridPoint() const;

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version
  // 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and
  // immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it
  // submit to any jurisdiction.
  // #
  //
  // #  La1 - latitude of first grid point
  // signed[3] latitudeOfFirstGridPoint :  edition_specific;

  std::int24_t mLatitudeOfFirstGridPoint;

  // meta geography.latitudeOfFirstGridPointInDegrees
  // scale(latitudeOfFirstGridPoint,oneConstant,grib1divider,truncateDegrees)
  // :dump;
  // alias La1 = latitudeOfFirstGridPoint;
  //
  // #  Lo1 - longitude of first grid point
  // signed[3] longitudeOfFirstGridPoint  : edition_specific;

  std::int24_t mLongitudeOfFirstGridPoint;

  // meta geography.longitudeOfFirstGridPointInDegrees
  // scale(longitudeOfFirstGridPoint,oneConstant,grib1divider,truncateDegrees) :
  // dump;
  // alias Lo1 = longitudeOfFirstGridPoint;
  //
  // include "resolution_flags.def";

  ResolutionFlagsSettings mResolutionFlags;

  //
  // #  La2 - latitude of last grid point
  // signed[3] latitudeOfLastGridPoint :  edition_specific;

  std::int24_t mLatitudeOfLastGridPoint;

  // meta geography.latitudeOfLastGridPointInDegrees
  // scale(latitudeOfLastGridPoint,oneConstant,grib1divider,truncateDegrees) :
  // dump;
  // alias La2 = latitudeOfLastGridPoint;
  //
  // #  Lo2 - longitude of last grid point
  // signed[3] longitudeOfLastGridPoint :  edition_specific;

  std::int24_t mLongitudeOfLastGridPoint;

  // meta geography.longitudeOfLastGridPointInDegrees
  // scale(longitudeOfLastGridPoint,oneConstant,grib1divider,truncateDegrees) :
  // dump;
  // alias Lo2 = longitudeOfLastGridPoint;
  //
  // # for change_scanning_direction
  // alias yFirst=latitudeOfFirstGridPointInDegrees;
  // alias yLast=latitudeOfLastGridPointInDegrees;
  // alias xFirst=longitudeOfFirstGridPointInDegrees;
  // alias xLast=longitudeOfLastGridPointInDegrees;
  //
  // alias latitudeFirstInDegrees  = latitudeOfFirstGridPointInDegrees;
  // alias longitudeFirstInDegrees = longitudeOfFirstGridPointInDegrees;
  // alias latitudeLastInDegrees   = latitudeOfLastGridPointInDegrees;
  // alias longitudeLastInDegrees  = longitudeOfLastGridPointInDegrees;
  //
};

} // namespace GRIB1
} // namespace SmartMet
