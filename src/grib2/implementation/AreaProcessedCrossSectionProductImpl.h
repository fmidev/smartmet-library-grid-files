#pragma once

#include "../definition/AreaProcessedCrossSectionProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AreaProcessedCrossSectionProductImpl : public AreaProcessedCrossSectionProduct
{
  public:
                        AreaProcessedCrossSectionProductImpl();
                        AreaProcessedCrossSectionProductImpl(const AreaProcessedCrossSectionProductImpl& other);
    ~AreaProcessedCrossSectionProductImpl() override;
    AreaProcessedCrossSectionProductImpl& operator=(const AreaProcessedCrossSectionProductImpl&) = default;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
