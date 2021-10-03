#pragma once

#include "../definition/Product_72.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_72Impl : public Product_72
{
  public:
                        Product_72Impl();
                        Product_72Impl(const Product_72Impl& other);
                ~Product_72Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
