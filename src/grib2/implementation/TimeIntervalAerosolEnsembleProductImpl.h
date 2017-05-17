#pragma once

#include "grib2/definition/TimeIntervalAerosolEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalAerosolEnsembleProductImpl : public TimeIntervalAerosolEnsembleProduct
{
  public:
                      TimeIntervalAerosolEnsembleProductImpl();
    virtual           ~TimeIntervalAerosolEnsembleProductImpl();

    T::TimeString     getForecastStartTime(T::TimeString referenceTime) const;
    T::TimeString     getForecastEndTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
