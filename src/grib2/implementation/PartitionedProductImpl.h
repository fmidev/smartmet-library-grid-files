#pragma once

#include "grib2/definition/PartitionedProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class PartitionedProductImpl : public PartitionedProduct
{
  public:
                      PartitionedProductImpl();
    virtual           ~PartitionedProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
