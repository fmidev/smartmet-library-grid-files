#pragma once

#include "../definition/Product_71.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_71Impl : public Product_71
{
  public:
                        Product_71Impl();
                        Product_71Impl(const Product_71Impl& other);
    virtual             ~Product_71Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
