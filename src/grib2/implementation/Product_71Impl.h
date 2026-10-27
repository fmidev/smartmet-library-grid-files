#pragma once

#include "../definition/Product_71.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_71Impl : public Product_71
{
  public:
                        Product_71Impl();
                        Product_71Impl(const Product_71Impl& other);
    ~Product_71Impl() override;
    Product_71Impl& operator=(const Product_71Impl&) = default;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
