#pragma once

#include "../definition/CrossSectionProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class CrossSectionProductImpl : public CrossSectionProduct
{
  public:
                        CrossSectionProductImpl();
                        CrossSectionProductImpl(const CrossSectionProductImpl& other);
    virtual             ~CrossSectionProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
