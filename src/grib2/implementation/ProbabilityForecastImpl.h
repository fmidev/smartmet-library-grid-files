#pragma once

#include "grib2/definition/ProbabilityForecast.h"

namespace SmartMet
{
namespace GRIB2
{


class ProbabilityForecastImpl : public ProbabilityForecast
{
  public:
                      ProbabilityForecastImpl();
    virtual           ~ProbabilityForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
