#pragma once

#include "../definition/CharacterStringProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class CharacterStringProductImpl : public CharacterStringProduct
{
  public:
                        CharacterStringProductImpl();
                        CharacterStringProductImpl(const CharacterStringProductImpl& other);
                ~CharacterStringProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
