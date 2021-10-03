#pragma once

#include "../definition/DeprecatedSatelliteProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class DeprecatedSatelliteProductImpl : public DeprecatedSatelliteProduct
{
  public:
                        DeprecatedSatelliteProductImpl();
                        DeprecatedSatelliteProductImpl(const DeprecatedSatelliteProductImpl& other);
                ~DeprecatedSatelliteProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
