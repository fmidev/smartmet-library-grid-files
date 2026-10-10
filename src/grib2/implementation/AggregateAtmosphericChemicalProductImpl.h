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

    const T::UInt8_opt  getGribParameterCategory() const override;
    const T::UInt8_opt  getGribParameterNumber() const override;
    T::UInt8_opt        getGeneratingProcessIdentifier() const override;
    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;

  protected:

    T::TimeString       countForecastStartTime(T::TimeString referenceTime) const;
};

}  // namespace GRIB2
}  // namespace SmartMet
