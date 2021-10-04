#pragma once

#include "../definition/EnsembleClusterDerivedForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class EnsembleClusterDerivedForecastImpl : public EnsembleClusterDerivedForecast
{
  public:
                        EnsembleClusterDerivedForecastImpl();
                        EnsembleClusterDerivedForecastImpl(const EnsembleClusterDerivedForecastImpl& other);
    virtual             ~EnsembleClusterDerivedForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
