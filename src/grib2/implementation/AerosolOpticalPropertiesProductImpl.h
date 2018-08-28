#pragma once

#include "../definition/AerosolOpticalPropertiesProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AerosolOpticalPropertiesProductImpl : public AerosolOpticalPropertiesProduct
{
  public:
                        AerosolOpticalPropertiesProductImpl();
                        AerosolOpticalPropertiesProductImpl(const AerosolOpticalPropertiesProductImpl& other);
    virtual             ~AerosolOpticalPropertiesProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
