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
    virtual             ~HovmollerProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
