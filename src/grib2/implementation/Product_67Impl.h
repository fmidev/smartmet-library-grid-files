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
    virtual             ~Product_67Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
