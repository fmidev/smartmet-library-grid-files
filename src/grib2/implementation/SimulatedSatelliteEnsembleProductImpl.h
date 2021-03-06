#pragma once

#include "../definition/SimulatedSatelliteEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class SimulatedSatelliteEnsembleProductImpl : public SimulatedSatelliteEnsembleProduct
{
  public:
                        SimulatedSatelliteEnsembleProductImpl();
                        SimulatedSatelliteEnsembleProductImpl(const SimulatedSatelliteEnsembleProductImpl& other);
    virtual             ~SimulatedSatelliteEnsembleProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
