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
                ~CrossSectionProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
