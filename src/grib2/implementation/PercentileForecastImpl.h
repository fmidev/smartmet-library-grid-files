#pragma once

#include "../definition/PercentileForecast.h"


namespace SmartMet
{
namespace GRIB2
{


class PercentileForecastImpl : public PercentileForecast
{
  public:
                        PercentileForecastImpl();
                        PercentileForecastImpl(const PercentileForecastImpl& other);
                ~PercentileForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
