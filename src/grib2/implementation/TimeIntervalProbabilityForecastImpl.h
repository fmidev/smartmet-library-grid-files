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
    ~TimeIntervalProbabilityForecastImpl() override;
    TimeIntervalProbabilityForecastImpl& operator=(const TimeIntervalProbabilityForecastImpl&) = default;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
