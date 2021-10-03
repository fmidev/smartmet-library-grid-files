#pragma once

#include "../definition/AtmosphericChemicalProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AtmosphericChemicalProductImpl : public AtmosphericChemicalProduct
{
  public:
                        AtmosphericChemicalProductImpl();
                        AtmosphericChemicalProductImpl(const AtmosphericChemicalProductImpl& other);
                ~AtmosphericChemicalProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
