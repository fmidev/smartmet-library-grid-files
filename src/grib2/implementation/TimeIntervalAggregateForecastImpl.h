#pragma once

#include "../definition/TimeIntervalAggregateForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalAggregateForecastImpl : public TimeIntervalAggregateForecast
{
  public:
                        TimeIntervalAggregateForecastImpl();
                        TimeIntervalAggregateForecastImpl(const TimeIntervalAggregateForecastImpl& other);
                ~TimeIntervalAggregateForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
