#pragma once

#include "../definition/ProcessedHovmollerProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class ProcessedHovmollerProductImpl : public ProcessedHovmollerProduct
{
  public:
                        ProcessedHovmollerProductImpl();
                        ProcessedHovmollerProductImpl(const ProcessedHovmollerProductImpl& other);
                ~ProcessedHovmollerProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
