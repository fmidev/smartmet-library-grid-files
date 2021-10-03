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
                ~ProcessedCrossSectionProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
