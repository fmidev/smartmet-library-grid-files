#pragma once

#include "../definition/Product_56.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_56Impl : public Product_56
{
  public:
                        Product_56Impl();
                        Product_56Impl(const Product_56Impl& other);
    virtual             ~Product_56Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
