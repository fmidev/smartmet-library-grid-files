#pragma once

#include "../definition/Product_70.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_70Impl : public Product_70
{
  public:
                        Product_70Impl();
                        Product_70Impl(const Product_70Impl& other);
    virtual             ~Product_70Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
