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
    virtual             ~Product_59Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
