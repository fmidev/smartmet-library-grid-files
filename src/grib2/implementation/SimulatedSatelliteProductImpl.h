#pragma once

#include "../definition/SimulatedSatelliteProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class SimulatedSatelliteProductImpl : public SimulatedSatelliteProduct
{
  public:
                        SimulatedSatelliteProductImpl();
                        SimulatedSatelliteProductImpl(const SimulatedSatelliteProductImpl& other);
    virtual             ~SimulatedSatelliteProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
