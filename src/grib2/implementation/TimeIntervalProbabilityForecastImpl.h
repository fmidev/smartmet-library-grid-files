#pragma once

#include "grib2/definition/TimeIntervalProbabilityForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalProbabilityForecastImpl : public TimeIntervalProbabilityForecast
{
  public:
                      TimeIntervalProbabilityForecastImpl();
    virtual           ~TimeIntervalProbabilityForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
