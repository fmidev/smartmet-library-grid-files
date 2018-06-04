#pragma once

#include "../definition/EnsembleDerivedForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class EnsembleDerivedForecastImpl : public EnsembleDerivedForecast
{
  public:
                      EnsembleDerivedForecastImpl();
    virtual           ~EnsembleDerivedForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
