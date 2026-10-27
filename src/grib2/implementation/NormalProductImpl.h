#pragma once

#include "../definition/NormalProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class NormalProductImpl : public NormalProduct
{
  public:
                        NormalProductImpl();
                        NormalProductImpl(const NormalProductImpl& other);
    ~NormalProductImpl() override;
    NormalProductImpl& operator=(const NormalProductImpl&) = default;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
