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
    virtual             ~Product_73Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
