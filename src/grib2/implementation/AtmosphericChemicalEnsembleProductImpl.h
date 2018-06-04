#pragma once

#include "../definition/AtmosphericChemicalEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class AtmosphericChemicalEnsembleProductImpl : public AtmosphericChemicalEnsembleProduct
{
  public:
                      AtmosphericChemicalEnsembleProductImpl();
    virtual           ~AtmosphericChemicalEnsembleProductImpl();

    T::TimeString     getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
