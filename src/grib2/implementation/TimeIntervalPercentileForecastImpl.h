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
    virtual             ~TimeIntervalPercentileForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
