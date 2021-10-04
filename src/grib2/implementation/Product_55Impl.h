#pragma once

#include "../definition/Product_55.h"


namespace SmartMet
{
namespace GRIB2
{


class Product_55Impl : public Product_55
{
  public:
                        Product_55Impl();
                        Product_55Impl(const Product_55Impl& other);
    virtual             ~Product_55Impl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
