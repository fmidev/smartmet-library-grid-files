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

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
