#pragma once

#include "grib2/definition/SimulatedSatelliteProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class SimulatedSatelliteProductImpl : public SimulatedSatelliteProduct
{
  public:
                      SimulatedSatelliteProductImpl();
    virtual           ~SimulatedSatelliteProductImpl();

    T::TimeString     getForecastStartTime(T::TimeString referenceTime) const;
    T::TimeString     getForecastEndTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
