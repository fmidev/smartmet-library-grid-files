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
    virtual             ~DeprecatedSatelliteProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
