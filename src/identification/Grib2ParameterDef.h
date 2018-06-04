#pragma once

#include "../grid/Typedefs.h"

namespace SmartMet
{
namespace Identification
{

// This class is needed in order to find a correct "parameterId" that identifies
// the grid data. In other words, there are no unique parameterIds in place, so
// we try to identify the grid data by using fields defined in the "paramDef_grib2.csv" file.
// This file is generated from several "paramId.def" files.


class Grib2ParameterDef
{
  public:

                  Grib2ParameterDef();
                  Grib2ParameterDef(const Grib2ParameterDef& parameter);
    virtual       ~Grib2ParameterDef();

    void          print(std::ostream& stream,uint level,uint optionFlags) const;

    T::ParamId    mGribParameterId;        // EFKL uses very large numbers such as 860200596400100
    std::string   mParameterName;
    std::string   mParameterDescription;
    std::string   mParameterUnits;

    std::uint8_t  mDiscipline;         // Code table 0.0. 0 = meteorological
    T::UInt16_opt mCentre;
    std::uint8_t  mParameterCategory;  // Code table 4.1.discipline
    std::uint8_t  mParameterNumber;    // Code table 4.2.parameterCategory

    // Local concept tables use these.
    // TODO: What happened in version 15? Table 4.230 contains only "(See Common Code table C-14)"
    // TODO2: What is the real range of unitsFactor?
    // TODO3: Is 9999 the correct missing value for scales?
    T::UInt8_opt  mTypeOfGeneratingProcess;  // Code table 4.3. missing=255
    T::UInt16_opt mConstituentType;       // Code table 4.230. missing=65535
    T::UInt8_opt  mLengthOfTimeRange;
    T::UInt8_opt  mLocalTablesVersion;
    T::UInt16_opt mAerosolType;  // Code table 2.233?

    // We ignore these local concepts until needed:
    // std::uint16_t subCentre = 0;
    // std::uint16_t unitsFactor = 1;
    // std::uint16_t satelliteSeries = 0;
    // std::uint16_t satelliteNumber = 0;
    // std::uint8_t instrumentType = 0;
    // std::uint32_t scaledValueOfCentralWaveNumber = 9999;
    // std::uint8_t numberOfGridInReference = 0;
    // std::uint8_t is_s2s = 0;
    // std::uint32_t atmosphericChemicalConsituentType = 0;

    // Supplementary information
    T::UInt8_opt  mProbabilityType;                      // Code table 4.9. missing=255
    T::UInt16_opt mProductDefinitionTemplateNumber;  // Code table 4.0. missing=65535
    T::UInt8_opt  mTypeOfFirstFixedSurface;             // Code table 4.5. missing=255
    T::UInt8_opt  mTypeOfSecondFixedSurface;            // Code table 4.5. missing=255
    T::UInt8_opt  mTypeOfStatisticalProcessing;         // Code table 4.10. missing=255

    T::UInt8_opt  mScaledValueOfLowerLimit;
    T::UInt32_opt mScaledValueOfFirstFixedSurface;
    T::UInt32_opt mScaledValueOfSecondFixedSurface;
    T::UInt8_opt  mScaleFactorOfLowerLimit;
    T::Int8_opt   mScaleFactorOfFirstFixedSurface;
    T::Int8_opt   mScaleFactorOfSecondFixedSurface;

    // Tigge seems to be a special case everywhere, no idea why yet.
    bool          mIs_tigge;
    bool          mIs_replicate;

};

typedef const Grib2ParameterDef* Grib2ParamDef_cptr;
typedef std::vector<Grib2ParameterDef> Grib2ParamDef_vec;


}
}

