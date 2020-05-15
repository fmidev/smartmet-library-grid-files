#pragma once

#include "../definition/Product_57.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_57Impl : public Product_57
{
  public:
                        Product_57Impl();
                        Product_57Impl(const Product_57Impl& other);
    virtual             ~Product_57Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
