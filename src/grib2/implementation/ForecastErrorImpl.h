#pragma once

#include "../definition/ForecastError.h"


namespace SmartMet
{
namespace GRIB2
{


class ForecastErrorImpl : public ForecastError
{
  public:
                        ForecastErrorImpl();
                        ForecastErrorImpl(const ForecastErrorImpl& other);
                ~ForecastErrorImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
