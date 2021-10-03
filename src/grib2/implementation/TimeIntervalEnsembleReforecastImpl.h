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
                ~TimeIntervalEnsembleReforecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
