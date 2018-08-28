#pragma once

#include "../definition/TimeIntervalEnsembleClusterDerivedForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalEnsembleClusterDerivedForecastImpl : public TimeIntervalEnsembleClusterDerivedForecast
{
  public:
                        TimeIntervalEnsembleClusterDerivedForecastImpl();
                        TimeIntervalEnsembleClusterDerivedForecastImpl(const TimeIntervalEnsembleClusterDerivedForecastImpl& other);
    virtual             ~TimeIntervalEnsembleClusterDerivedForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
