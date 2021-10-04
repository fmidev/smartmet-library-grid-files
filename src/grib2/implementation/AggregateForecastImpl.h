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
     virtual             ~AggregateForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
