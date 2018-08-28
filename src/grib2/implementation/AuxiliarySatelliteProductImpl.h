#pragma once

#include "../definition/AuxiliarySatelliteProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AuxiliarySatelliteProductImpl : public AuxiliarySatelliteProduct
{
  public:
                        AuxiliarySatelliteProductImpl();
                        AuxiliarySatelliteProductImpl(const AuxiliarySatelliteProductImpl& other);
    virtual             ~AuxiliarySatelliteProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
