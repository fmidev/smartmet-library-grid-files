#pragma once

#include "../definition/TimeIntervalSimulatedSatelliteEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class TimeIntervalSimulatedSatelliteEnsembleProductImpl : public TimeIntervalSimulatedSatelliteEnsembleProduct
{
  public:
                        TimeIntervalSimulatedSatelliteEnsembleProductImpl();
                        TimeIntervalSimulatedSatelliteEnsembleProductImpl(const TimeIntervalSimulatedSatelliteEnsembleProductImpl& other);
    virtual             ~TimeIntervalSimulatedSatelliteEnsembleProductImpl();

    ProductDefinition*  createProductDefinition() const;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const;
    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
