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
    virtual             ~TimeIntervalEnsembleDerivedForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
