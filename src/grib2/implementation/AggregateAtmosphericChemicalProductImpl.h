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
    virtual             ~AggregateAtmosphericChemicalProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
