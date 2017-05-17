#pragma once

#include "grib2/definition/TimeIntervalEnsembleDerivedForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalEnsembleDerivedForecastImpl : public TimeIntervalEnsembleDerivedForecast
{
  public:
                      TimeIntervalEnsembleDerivedForecastImpl();
    virtual           ~TimeIntervalEnsembleDerivedForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
