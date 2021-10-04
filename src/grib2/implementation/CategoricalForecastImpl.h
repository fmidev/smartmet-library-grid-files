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
    virtual             ~CategoricalForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
