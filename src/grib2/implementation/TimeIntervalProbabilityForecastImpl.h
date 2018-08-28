#pragma once

#include "../definition/TimeIntervalProbabilityForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalProbabilityForecastImpl : public TimeIntervalProbabilityForecast
{
  public:
                        TimeIntervalProbabilityForecastImpl();
                        TimeIntervalProbabilityForecastImpl(const TimeIntervalProbabilityForecastImpl& other);
    virtual             ~TimeIntervalProbabilityForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
