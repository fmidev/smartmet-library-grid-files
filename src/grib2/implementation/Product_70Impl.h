#pragma once

#include "../definition/Product_70.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_70Impl : public Product_70
{
  public:
                        Product_70Impl();
                        Product_70Impl(const Product_70Impl& other);
                ~Product_70Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
