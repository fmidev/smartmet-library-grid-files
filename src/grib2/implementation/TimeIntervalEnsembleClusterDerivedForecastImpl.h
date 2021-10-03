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
                ~TimeIntervalEnsembleClusterDerivedForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
