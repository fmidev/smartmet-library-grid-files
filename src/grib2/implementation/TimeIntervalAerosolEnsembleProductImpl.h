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
                        TimeIntervalAerosolEnsembleProductImpl(const TimeIntervalAerosolEnsembleProductImpl& other);
                ~TimeIntervalAerosolEnsembleProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
