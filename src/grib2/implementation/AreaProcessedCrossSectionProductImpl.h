#pragma once

#include "grib2/definition/AreaProcessedCrossSectionProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AreaProcessedCrossSectionProductImpl : public AreaProcessedCrossSectionProduct
{
  public:
                      AreaProcessedCrossSectionProductImpl();
    virtual           ~AreaProcessedCrossSectionProductImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
