#pragma once

#include "grib2/definition/TimeIntervalAtmosphericChemicalEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalAtmosphericChemicalEnsembleProductImpl : public TimeIntervalAtmosphericChemicalEnsembleProduct
{
  public:
                      TimeIntervalAtmosphericChemicalEnsembleProductImpl();
    virtual           ~TimeIntervalAtmosphericChemicalEnsembleProductImpl();

    T::TimeString     getForecastStartTime(T::TimeString referenceTime) const;
    T::TimeString     getForecastEndTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
