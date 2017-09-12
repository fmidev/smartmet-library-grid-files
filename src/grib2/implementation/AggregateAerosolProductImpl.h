#pragma once

#include "grib2/definition/AggregateAerosolProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AggregateAerosolProductImpl : public AggregateAerosolProduct
{
  public:
                      AggregateAerosolProductImpl();
    virtual           ~AggregateAerosolProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
