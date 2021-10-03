#pragma once

#include "../definition/Product_73.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_73Impl : public Product_73
{
  public:
                        Product_73Impl();
                        Product_73Impl(const Product_73Impl& other);
                ~Product_73Impl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
