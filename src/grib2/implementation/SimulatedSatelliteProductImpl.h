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
                ~SimulatedSatelliteProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
