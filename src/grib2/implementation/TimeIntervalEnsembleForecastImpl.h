#pragma once

#include "../definition/TimeIntervalEnsembleForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalEnsembleForecastImpl : public TimeIntervalEnsembleForecast
{
  public:
                        TimeIntervalEnsembleForecastImpl();
                        TimeIntervalEnsembleForecastImpl(const TimeIntervalEnsembleForecastImpl& other);
    ~TimeIntervalEnsembleForecastImpl() override;
    TimeIntervalEnsembleForecastImpl& operator=(const TimeIntervalEnsembleForecastImpl&) = default;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
