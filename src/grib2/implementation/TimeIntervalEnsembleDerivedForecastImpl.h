#pragma once

#include "../definition/TimeIntervalEnsembleDerivedForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalEnsembleDerivedForecastImpl : public TimeIntervalEnsembleDerivedForecast
{
  public:
                        TimeIntervalEnsembleDerivedForecastImpl();
                        TimeIntervalEnsembleDerivedForecastImpl(const TimeIntervalEnsembleDerivedForecastImpl& other);
                ~TimeIntervalEnsembleDerivedForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
