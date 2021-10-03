#pragma once

#include "../definition/Product_49.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_49Impl : public Product_49
{
  public:
                        Product_49Impl();
                        Product_49Impl(const Product_49Impl& other);
                ~Product_49Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
