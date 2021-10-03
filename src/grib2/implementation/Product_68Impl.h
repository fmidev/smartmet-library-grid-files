#pragma once

#include "../definition/Product_68.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_68Impl : public Product_68
{
  public:
                        Product_68Impl();
                        Product_68Impl(const Product_68Impl& other);
                ~Product_68Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
