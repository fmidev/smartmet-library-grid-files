#pragma once

#include "../definition/Product_67.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_67Impl : public Product_67
{
  public:
                        Product_67Impl();
                        Product_67Impl(const Product_67Impl& other);
                ~Product_67Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
