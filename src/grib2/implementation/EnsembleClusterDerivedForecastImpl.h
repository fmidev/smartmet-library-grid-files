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
                ~EnsembleClusterDerivedForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
