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
    virtual             ~ProcessedHovmollerProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
