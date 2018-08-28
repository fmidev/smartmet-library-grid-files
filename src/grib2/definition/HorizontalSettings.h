// ***********************************************************************
//                      DO NOT EDIT THIS FILE !!!
// ***********************************************************************
//   This file is automatically generated from the grib_api templates. All
//   changes will be overridden. If you want to do permanent changes then
//   you should write them into the 'HorizontalSettingsImpl.*' files.
// ***********************************************************************

#pragma once
#include "../../common/AttributeList.h"
#include "../../common/DataWriter.h"
#include "../../common/MemoryReader.h"
#include "../../grid/Typedefs.h"

namespace SmartMet {
namespace GRIB2 {
/*! \brief The class is automatically created from the template (4.horizontal).*/

class HorizontalSettings {
public:
  HorizontalSettings();
  HorizontalSettings(const HorizontalSettings &other);
  virtual ~HorizontalSettings();

  virtual void read(MemoryReader &memoryReader);
  virtual void write(DataWriter &dataWriter);
  virtual void getAttributeList(std::string prefix, T::AttributeList &attributeList) const;
  virtual void print(std::ostream &stream, uint level, uint optionFlags) const;
  virtual T::Hash countHash();

  const T::UInt8_opt &getTypeOfFirstFixedSurface() const;
  void setTypeOfFirstFixedSurface(T::UInt8_opt typeOfFirstFixedSurface);
  const T::Int8_opt &getScaleFactorOfFirstFixedSurface() const;
  void setScaleFactorOfFirstFixedSurface(T::Int8_opt scaleFactorOfFirstFixedSurface);
  const T::UInt32_opt &getScaledValueOfFirstFixedSurface() const;
  void setScaledValueOfFirstFixedSurface(T::UInt32_opt scaledValueOfFirstFixedSurface);
  const T::UInt8_opt &getTypeOfSecondFixedSurface() const;
  void setTypeOfSecondFixedSurface(T::UInt8_opt typeOfSecondFixedSurface);
  const T::Int8_opt &getScaleFactorOfSecondFixedSurface() const;
  void setScaleFactorOfSecondFixedSurface(T::Int8_opt scaleFactorOfSecondFixedSurface);
  const T::UInt32_opt &getScaledValueOfSecondFixedSurface() const;
  void setScaledValueOfSecondFixedSurface(T::UInt32_opt scaledValueOfSecondFixedSurface);

protected:
  // # Copyright 2005-2015 ECMWF.
  // #
  // # This software is licensed under the terms of the Apache Licence Version 2.0
  // # which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
  // #
  // # In applying this licence, ECMWF does not waive the privileges and immunities granted to it by
  // # virtue of its status as an intergovernmental organisation nor does it submit to any jurisdiction.
  // #
  //
  // #  Type of first fixed surface
  // codetable[1] typeOfFirstFixedSurface ('4.5.table',masterDir,localDir) : dump,no_copy,edition_specific,string_type;

  T::UInt8_opt mTypeOfFirstFixedSurface;

  // meta unitsOfFirstFixedSurface codetable_units(typeOfFirstFixedSurface) : dump;
  // meta nameOfFirstFixedSurface codetable_title(typeOfFirstFixedSurface) : dump;
  //
  // #  Scale factor of first fixed surface
  // signed[1] scaleFactorOfFirstFixedSurface = missing()  : can_be_missing,dump,no_copy,edition_specific;

  T::Int8_opt mScaleFactorOfFirstFixedSurface;

  //
  // #  Scaled value of first fixed surface
  // unsigned[4] scaledValueOfFirstFixedSurface = missing()  : can_be_missing,dump,no_copy,edition_specific;

  T::UInt32_opt mScaledValueOfFirstFixedSurface;

  //
  // #  Type of second fixed surface
  // codetable[1] typeOfSecondFixedSurface ('4.5.table',masterDir,localDir) = 255 : dump,no_copy,edition_specific;

  T::UInt8_opt mTypeOfSecondFixedSurface;

  // meta unitsOfSecondFixedSurface codetable_units(typeOfSecondFixedSurface) : dump;
  // meta nameOfSecondFixedSurface codetable_title(typeOfSecondFixedSurface) : dump;
  //
  // #  Scale factor of second fixed surface
  // signed[1] scaleFactorOfSecondFixedSurface = missing() : can_be_missing,dump,no_copy,edition_specific;

  T::Int8_opt mScaleFactorOfSecondFixedSurface;

  //
  // #  Scaled value of second fixed surface
  // unsigned[4] scaledValueOfSecondFixedSurface = missing() : can_be_missing,dump,no_copy,edition_specific;

  T::UInt32_opt mScaledValueOfSecondFixedSurface;

  //
  // transient pressureUnits="hPa";
  //
  // concept_nofail vertical.typeOfLevel (unknown) {
  // #set uses the last one
  // #get returns the first match
  //   'surface'       = { typeOfFirstFixedSurface=1;   typeOfSecondFixedSurface=255;   }
  //   'cloudBase'     = { typeOfFirstFixedSurface=2;   typeOfSecondFixedSurface=255;   }
  //   'cloudTop'      = { typeOfFirstFixedSurface=3;   typeOfSecondFixedSurface=255;   }
  //   'isothermZero'  = { typeOfFirstFixedSurface=4;   typeOfSecondFixedSurface=255;   }
  //   'adiabaticCondensation' = {typeOfFirstFixedSurface=5;   typeOfSecondFixedSurface=255;  }
  //   'maxWind' = {typeOfFirstFixedSurface=6; typeOfSecondFixedSurface=255;}
  //   'tropopause' = {typeOfFirstFixedSurface=7; typeOfSecondFixedSurface=255;}
  //   'nominalTop' = {typeOfFirstFixedSurface=8; typeOfSecondFixedSurface=255; }
  //   'seaBottom' = {typeOfFirstFixedSurface=9;    typeOfSecondFixedSurface=255;}
  //   'isothermal' = {typeOfFirstFixedSurface=20;   typeOfSecondFixedSurface=255;}
  //   'isobaricInPa' = {typeOfFirstFixedSurface=100; typeOfSecondFixedSurface=255; pressureUnits='Pa'; }
  //   'isobaricInhPa' = {typeOfFirstFixedSurface=100; pressureUnits='hPa'; typeOfSecondFixedSurface=255;}
  //   'isobaricLayer' = {typeOfFirstFixedSurface=100; typeOfSecondFixedSurface=100;}
  //   'meanSea' = { typeOfFirstFixedSurface=101; typeOfSecondFixedSurface=255; }
  //   'heightAboveSea' = {typeOfFirstFixedSurface=102; typeOfSecondFixedSurface=255;}
  //   'heightAboveSeaLayer' = {typeOfFirstFixedSurface=102; typeOfSecondFixedSurface=102;}
  //   'heightAboveGround' = {typeOfFirstFixedSurface=103; typeOfSecondFixedSurface=255;}
  //   'heightAboveGroundLayer' = {typeOfFirstFixedSurface=103;typeOfSecondFixedSurface=103;}
  //   'sigma' = {typeOfFirstFixedSurface=104; typeOfSecondFixedSurface=255;}
  //   'sigmaLayer' = {typeOfFirstFixedSurface=104; typeOfSecondFixedSurface=104;}
  //   'hybrid' = {typeOfFirstFixedSurface=105; typeOfSecondFixedSurface=255;}
  //   'hybridHeight' = {typeOfFirstFixedSurface=118; typeOfSecondFixedSurface=255;}
  //   'hybridLayer' = {typeOfFirstFixedSurface=105; typeOfSecondFixedSurface=105; }
  //   'depthBelowLand' = {typeOfFirstFixedSurface=106;  typeOfSecondFixedSurface=255;}
  //   'depthBelowLandLayer' = {typeOfFirstFixedSurface=106; typeOfSecondFixedSurface=106;}
  //   'theta' = {typeOfFirstFixedSurface=107; typeOfSecondFixedSurface=255;}
  //   'thetaLayer' = {typeOfFirstFixedSurface=107;typeOfSecondFixedSurface=107;}
  //   'pressureFromGround' = {typeOfFirstFixedSurface=108; typeOfSecondFixedSurface=255;}
  //   'pressureFromGroundLayer' = {typeOfFirstFixedSurface=108;typeOfSecondFixedSurface=108;}
  //   'potentialVorticity' = {typeOfFirstFixedSurface=109; typeOfSecondFixedSurface=255;}
  //   'eta' = {typeOfFirstFixedSurface=111;  typeOfSecondFixedSurface=255;}
  //
  // # In the case of Generalized vertical height coordinates, NV must be 6
  //   'generalVertical' = {genVertHeightCoords=1; typeOfFirstFixedSurface=150; NV=6;}
  //   'generalVerticalLayer' = {genVertHeightCoords=1; typeOfFirstFixedSurface=150; typeOfSecondFixedSurface=150; NV=6;}
  //
  //   'depthBelowSea' = {typeOfFirstFixedSurface=160; typeOfSecondFixedSurface=255;}
  //   'entireAtmosphere' = {typeOfFirstFixedSurface=1;typeOfSecondFixedSurface=8;}
  //   'entireOcean' = {typeOfFirstFixedSurface=1;typeOfSecondFixedSurface=9;}
  //   'snow' = {typeOfFirstFixedSurface=114;typeOfSecondFixedSurface=255;}
  //   'snowLayer' = {typeOfFirstFixedSurface=114; typeOfSecondFixedSurface=114;}
  // }
  //
  // alias levelType=typeOfFirstFixedSurface;
  //
  // if (typeOfSecondFixedSurface == 255) {
  //   # Only one surface
  //   meta level g2level(typeOfFirstFixedSurface,
  //     scaleFactorOfFirstFixedSurface,
  //     scaledValueOfFirstFixedSurface,
  //     pressureUnits)  :dump;
  //   transient bottomLevel=level; # Do not use alias (see GRIB-725)
  //   transient topLevel=level;
  // } else {
  //   # Two surfaces
  //   meta topLevel g2level(typeOfFirstFixedSurface,
  //     scaleFactorOfFirstFixedSurface,
  //     scaledValueOfFirstFixedSurface,
  //     pressureUnits)  :dump;
  //   meta bottomLevel g2level(typeOfSecondFixedSurface,
  //     scaleFactorOfSecondFixedSurface,
  //     scaledValueOfSecondFixedSurface,
  //     pressureUnits)  :dump;
  //     alias level=topLevel;  # (see GRIB-725)
  // }
  // alias ls.level=level;
  // alias vertical.level=level;
  // alias vertical.bottomLevel=bottomLevel;
  // alias vertical.topLevel=topLevel;
  //
  // alias extraDim=zero;
  // if (defined(extraDimensionPresent)) {
  //     if (extraDimensionPresent) {
  //         alias extraDim=one;
  //     }
  // }
  // if (extraDim) {
  //     alias mars.levelist = dimension;
  //     alias mars.levtype = dimensionType;
  // } else {
  //     # See GRIB-74 why we store the pressureUnits in a transient
  //     transient tempPressureUnits=pressureUnits;
  //     if (!(typeOfLevel is "surface")) {
  //         if (tempPressureUnits is "Pa") {
  //             meta marsLevel scale(level,one,hundred) : read_only;
  //             alias mars.levelist=marsLevel;
  //         } else {
  //             alias mars.levelist = level;
  //         }
  //     }
  //     alias mars.levtype  = typeOfFirstFixedSurface;
  //     # GRIB-372: levelist alias does not pertain to surface parameters
  //     if (levtype is "sfc") {
  //         unalias mars.levelist;
  //     }
  // }
  // alias ls.typeOfLevel=typeOfLevel;
};

} // namespace GRIB2
} // namespace SmartMet
