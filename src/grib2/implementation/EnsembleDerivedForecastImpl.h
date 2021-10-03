#pragma once

#include "../definition/EnsembleDerivedForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class EnsembleDerivedForecastImpl : public EnsembleDerivedForecast
{
  public:
                        EnsembleDerivedForecastImpl();
                        EnsembleDerivedForecastImpl(const EnsembleDerivedForecastImpl& other);
                ~EnsembleDerivedForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
