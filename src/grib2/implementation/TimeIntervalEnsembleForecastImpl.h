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
    virtual             ~TimeIntervalEnsembleForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
