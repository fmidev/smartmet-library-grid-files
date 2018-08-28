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
    virtual             ~EnsembleForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
