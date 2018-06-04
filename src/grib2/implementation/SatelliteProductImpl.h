#pragma once

#include "../definition/SatelliteProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class SatelliteProductImpl : public SatelliteProduct
{
  public:
                      SatelliteProductImpl();
    virtual           ~SatelliteProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
