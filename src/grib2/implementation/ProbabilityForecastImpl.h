#pragma once

#include "../definition/ProbabilityForecast.h"

namespace SmartMet
{
namespace GRIB2
{


class ProbabilityForecastImpl : public ProbabilityForecast
{
  public:
                        ProbabilityForecastImpl();
                        ProbabilityForecastImpl(const ProbabilityForecastImpl& other);
    virtual             ~ProbabilityForecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
