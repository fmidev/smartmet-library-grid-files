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
    virtual             ~NormalProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
