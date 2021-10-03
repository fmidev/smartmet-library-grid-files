#pragma once

#include "../definition/Product_59.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_59Impl : public Product_59
{
  public:
                        Product_59Impl();
                        Product_59Impl(const Product_59Impl& other);
                ~Product_59Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
