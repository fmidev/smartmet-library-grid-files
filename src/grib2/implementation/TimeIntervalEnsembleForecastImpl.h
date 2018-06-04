#pragma once

#include "../definition/TimeIntervalEnsembleForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalEnsembleForecastImpl : public TimeIntervalEnsembleForecast
{
  public:
                      TimeIntervalEnsembleForecastImpl();
    virtual           ~TimeIntervalEnsembleForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
