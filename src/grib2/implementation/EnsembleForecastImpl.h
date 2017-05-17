#pragma once

#include "grib2/definition/EnsembleForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class EnsembleForecastImpl : public EnsembleForecast
{
  public:
                      EnsembleForecastImpl();
    virtual           ~EnsembleForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
