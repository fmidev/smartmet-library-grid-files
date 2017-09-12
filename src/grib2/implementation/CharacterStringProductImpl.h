#pragma once

#include "grib2/definition/CharacterStringProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class CharacterStringProductImpl : public CharacterStringProduct
{
  public:
                      CharacterStringProductImpl();
    virtual           ~CharacterStringProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
