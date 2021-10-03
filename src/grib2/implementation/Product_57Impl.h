#pragma once

#include "../definition/Product_57.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_57Impl : public Product_57
{
  public:
                        Product_57Impl();
                        Product_57Impl(const Product_57Impl& other);
                ~Product_57Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
