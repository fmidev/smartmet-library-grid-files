#pragma once

#include "../definition/NormalProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class NormalProductImpl : public NormalProduct
{
  public:
                      NormalProductImpl();
    virtual           ~NormalProductImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
