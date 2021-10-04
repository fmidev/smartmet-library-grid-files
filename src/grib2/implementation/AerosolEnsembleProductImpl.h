#pragma once

#include "../definition/AerosolEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AerosolEnsembleProductImpl : public AerosolEnsembleProduct
{
  public:
                        AerosolEnsembleProductImpl();
                        AerosolEnsembleProductImpl(const AerosolEnsembleProductImpl& other);
    virtual             ~AerosolEnsembleProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
