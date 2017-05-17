#pragma once

#include "grib2/definition/CategoricalForecast.h"


namespace SmartMet
{
namespace GRIB2
{

class CategoricalForecastImpl : public CategoricalForecast
{
  public:
                      CategoricalForecastImpl();
    virtual           ~CategoricalForecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
