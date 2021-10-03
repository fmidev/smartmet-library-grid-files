#pragma once

#include "../definition/Product_58.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_58Impl : public Product_58
{
  public:
                        Product_58Impl();
                        Product_58Impl(const Product_58Impl& other);
                ~Product_58Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
