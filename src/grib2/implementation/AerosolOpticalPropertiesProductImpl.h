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
                ~AerosolOpticalPropertiesProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
