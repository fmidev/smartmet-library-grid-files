#pragma once

#include "../definition/Product_49.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_49Impl : public Product_49
{
  public:
                        Product_49Impl();
                        Product_49Impl(const Product_49Impl& other);
    virtual             ~Product_49Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
