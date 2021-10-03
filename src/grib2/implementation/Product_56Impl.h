#pragma once

#include "../definition/Product_56.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_56Impl : public Product_56
{
  public:
                        Product_56Impl();
                        Product_56Impl(const Product_56Impl& other);
                ~Product_56Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
