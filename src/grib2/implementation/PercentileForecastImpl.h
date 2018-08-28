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
    virtual             ~PercentileForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
