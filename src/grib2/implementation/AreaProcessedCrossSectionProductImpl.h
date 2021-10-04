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
    virtual             ~AreaProcessedCrossSectionProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
