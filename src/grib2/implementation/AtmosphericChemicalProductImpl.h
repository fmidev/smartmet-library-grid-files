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

    const T::UInt8_opt  getGribParameterCategory() const;
    const T::UInt8_opt  getGribParameterNumber() const;
    T::UInt8_opt        getGeneratingProcessIdentifier() const;
    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);

  protected:

    T::TimeString       countForecastStartTime(T::TimeString referenceTime) const;
};

}  // namespace GRIB2
}  // namespace SmartMet
