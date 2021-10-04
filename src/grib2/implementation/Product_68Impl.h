#pragma once

#include "../definition/Product_68.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_68Impl : public Product_68
{
  public:
                        Product_68Impl();
                        Product_68Impl(const Product_68Impl& other);
    virtual             ~Product_68Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
