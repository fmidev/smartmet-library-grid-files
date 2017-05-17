#pragma once

#include "grib2/definition/TimeIntervalCategoricalForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalCategoricalForecastImpl : public TimeIntervalCategoricalForecast
{
  public:
                      TimeIntervalCategoricalForecastImpl();
    virtual           ~TimeIntervalCategoricalForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
