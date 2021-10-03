#pragma once

#include "../definition/CategoricalForecast.h"


namespace SmartMet
{
namespace GRIB2
{

class CategoricalForecastImpl : public CategoricalForecast
{
  public:
                        CategoricalForecastImpl();
                        CategoricalForecastImpl(const CategoricalForecastImpl& other);
                ~CategoricalForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
