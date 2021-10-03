#pragma once

#include "../definition/EnsembleForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class EnsembleForecastImpl : public EnsembleForecast
{
  public:
                        EnsembleForecastImpl();
                        EnsembleForecastImpl(const EnsembleForecastImpl& other);
                ~EnsembleForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
