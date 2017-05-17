#pragma once

#include "grib2/definition/PercentileForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class PercentileForecastImpl : public PercentileForecast
{
  public:
                      PercentileForecastImpl();
    virtual           ~PercentileForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
