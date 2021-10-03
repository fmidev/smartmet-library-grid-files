#pragma once

#include "../definition/TimeIntervalPercentileForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalPercentileForecastImpl : public TimeIntervalPercentileForecast
{
  public:
                        TimeIntervalPercentileForecastImpl();
                        TimeIntervalPercentileForecastImpl(const TimeIntervalPercentileForecastImpl& other);
                ~TimeIntervalPercentileForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
