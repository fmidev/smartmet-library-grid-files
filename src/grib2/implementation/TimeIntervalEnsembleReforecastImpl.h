#pragma once

#include "../definition/TimeIntervalEnsembleReforecast.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalEnsembleReforecastImpl : public TimeIntervalEnsembleReforecast
{
  public:
                        TimeIntervalEnsembleReforecastImpl();
                        TimeIntervalEnsembleReforecastImpl(const TimeIntervalEnsembleReforecastImpl& other);
    virtual             ~TimeIntervalEnsembleReforecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
