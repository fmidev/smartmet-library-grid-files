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
    virtual             ~TimeIntervalCategoricalForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
