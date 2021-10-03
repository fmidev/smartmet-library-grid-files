#pragma once

#include "../definition/TimeIntervalCategoricalForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalCategoricalForecastImpl : public TimeIntervalCategoricalForecast
{
  public:
                        TimeIntervalCategoricalForecastImpl();
                        TimeIntervalCategoricalForecastImpl(const TimeIntervalCategoricalForecastImpl& other);
                ~TimeIntervalCategoricalForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
