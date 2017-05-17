#pragma once

#include "grib2/definition/TimeIntervalPercentileForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalPercentileForecastImpl : public TimeIntervalPercentileForecast
{
  public:
                      TimeIntervalPercentileForecastImpl();
    virtual           ~TimeIntervalPercentileForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
