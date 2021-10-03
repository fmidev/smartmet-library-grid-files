#pragma once

#include "../definition/Product_55.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_55Impl : public Product_55
{
  public:
                        Product_55Impl();
                        Product_55Impl(const Product_55Impl& other);
                ~Product_55Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
