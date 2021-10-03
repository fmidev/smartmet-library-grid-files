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
                        SatelliteProductImpl(const SatelliteProductImpl& other);
                ~SatelliteProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
