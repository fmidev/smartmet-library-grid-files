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
    virtual             ~ForecastErrorImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
