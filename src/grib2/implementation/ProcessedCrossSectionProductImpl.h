#pragma once

#include "../definition/ProcessedCrossSectionProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class ProcessedCrossSectionProductImpl : public ProcessedCrossSectionProduct
{
  public:
                        ProcessedCrossSectionProductImpl();
                        ProcessedCrossSectionProductImpl(const ProcessedCrossSectionProductImpl& other);
    virtual             ~ProcessedCrossSectionProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
