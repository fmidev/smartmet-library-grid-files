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
    virtual           ~TimeIntervalAtmosphericChemicalEnsembleProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
