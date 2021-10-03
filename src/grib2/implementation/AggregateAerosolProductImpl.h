#pragma once

#include "../definition/AggregateAerosolProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AggregateAerosolProductImpl : public AggregateAerosolProduct
{
  public:
                        AggregateAerosolProductImpl();
                        AggregateAerosolProductImpl(const AggregateAerosolProductImpl& other);
                ~AggregateAerosolProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
