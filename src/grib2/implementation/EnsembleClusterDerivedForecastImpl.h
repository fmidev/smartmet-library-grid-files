#pragma once

#include "grib2/definition/EnsembleClusterDerivedForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class EnsembleClusterDerivedForecastImpl : public EnsembleClusterDerivedForecast
{
  public:
                      EnsembleClusterDerivedForecastImpl();
    virtual           ~EnsembleClusterDerivedForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
