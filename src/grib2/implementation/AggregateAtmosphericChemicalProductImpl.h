#pragma once

#include "../definition/AggregateAtmosphericChemicalProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AggregateAtmosphericChemicalProductImpl : public AggregateAtmosphericChemicalProduct
{
  public:
                        AggregateAtmosphericChemicalProductImpl();
                        AggregateAtmosphericChemicalProductImpl(const AggregateAtmosphericChemicalProductImpl& other);
                ~AggregateAtmosphericChemicalProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
