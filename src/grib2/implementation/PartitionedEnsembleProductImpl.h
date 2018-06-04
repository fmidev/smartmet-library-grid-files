#pragma once

#include "../definition/PartitionedEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class PartitionedEnsembleProductImpl : public PartitionedEnsembleProduct
{
  public:
                      PartitionedEnsembleProductImpl();
    virtual           ~PartitionedEnsembleProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
