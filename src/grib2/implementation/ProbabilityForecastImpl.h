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
                ~ProbabilityForecastImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
