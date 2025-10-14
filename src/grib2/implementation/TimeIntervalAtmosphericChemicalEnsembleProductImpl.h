#pragma once

#include "../definition/TimeIntervalAtmosphericChemicalEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalAtmosphericChemicalEnsembleProductImpl : public TimeIntervalAtmosphericChemicalEnsembleProduct
{
  public:
                        TimeIntervalAtmosphericChemicalEnsembleProductImpl();
                        TimeIntervalAtmosphericChemicalEnsembleProductImpl(const TimeIntervalAtmosphericChemicalEnsembleProductImpl& other);
    virtual             ~TimeIntervalAtmosphericChemicalEnsembleProductImpl();

    ProductDefinition*  createProductDefinition() const;

    const T::UInt8_opt  getGribParameterCategory() const;
    const T::UInt8_opt  getGribParameterNumber() const;
    T::UInt8_opt        getGeneratingProcessIdentifier() const;
    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);

  protected:

    T::TimeString       countForecastStartTime(T::TimeString referenceTime) const;
};

}  // namespace GRIB2
}  // namespace SmartMet
