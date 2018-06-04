#pragma once

#include "../definition/TimeIntervalAerosolEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalAerosolEnsembleProductImpl : public TimeIntervalAerosolEnsembleProduct
{
  public:
                      TimeIntervalAerosolEnsembleProductImpl();
    virtual           ~TimeIntervalAerosolEnsembleProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
