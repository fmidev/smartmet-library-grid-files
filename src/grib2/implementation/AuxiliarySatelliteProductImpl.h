#pragma once

#include "grib2/definition/AuxiliarySatelliteProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AuxiliarySatelliteProductImpl : public AuxiliarySatelliteProduct
{
  public:
                      AuxiliarySatelliteProductImpl();
    virtual           ~AuxiliarySatelliteProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
