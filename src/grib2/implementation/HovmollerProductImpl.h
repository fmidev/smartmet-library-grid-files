#pragma once

#include "../definition/HovmollerProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class HovmollerProductImpl : public HovmollerProduct
{
  public:
                        HovmollerProductImpl();
                        HovmollerProductImpl(const HovmollerProductImpl& other);
                ~HovmollerProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
