#pragma once

#include "grib2/definition/TimeIntervalEnsembleClusterDerivedForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalEnsembleClusterDerivedForecastImpl : public TimeIntervalEnsembleClusterDerivedForecast
{
  public:
                      TimeIntervalEnsembleClusterDerivedForecastImpl();
    virtual           ~TimeIntervalEnsembleClusterDerivedForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
