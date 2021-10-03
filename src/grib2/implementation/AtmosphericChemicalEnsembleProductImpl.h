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
                        AtmosphericChemicalEnsembleProductImpl(const AtmosphericChemicalEnsembleProductImpl& other);
                ~AtmosphericChemicalEnsembleProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
