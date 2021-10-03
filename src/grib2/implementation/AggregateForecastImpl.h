#pragma once

#include "../definition/AggregateForecast.h"

namespace SmartMet
{
namespace GRIB2
{


class AggregateForecastImpl : public AggregateForecast
{
  public:
                        AggregateForecastImpl();
                        AggregateForecastImpl(const AggregateForecastImpl& other);
                 ~AggregateForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
