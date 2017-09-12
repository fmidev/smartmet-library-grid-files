#pragma once

#include "grib2/definition/AerosolOpticalPropertiesProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AerosolOpticalPropertiesProductImpl : public AerosolOpticalPropertiesProduct
{
  public:
                      AerosolOpticalPropertiesProductImpl();
    virtual           ~AerosolOpticalPropertiesProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
