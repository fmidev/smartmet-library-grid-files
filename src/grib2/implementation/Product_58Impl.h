#pragma once

#include "../definition/Product_58.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_58Impl : public Product_58
{
  public:
                        Product_58Impl();
                        Product_58Impl(const Product_58Impl& other);
    virtual             ~Product_58Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
