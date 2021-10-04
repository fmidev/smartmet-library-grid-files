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
    virtual             ~AtmosphericChemicalProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
