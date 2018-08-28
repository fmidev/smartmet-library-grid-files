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
    virtual             ~CharacterStringProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
