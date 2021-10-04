#pragma once

#include "../definition/Product_72.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_72Impl : public Product_72
{
  public:
                        Product_72Impl();
                        Product_72Impl(const Product_72Impl& other);
    virtual             ~Product_72Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
