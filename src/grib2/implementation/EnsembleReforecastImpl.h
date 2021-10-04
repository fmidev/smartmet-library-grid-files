#pragma once

#include "../definition/EnsembleReforecast.h"


namespace SmartMet
{
namespace GRIB2
{


class EnsembleReforecastImpl : public EnsembleReforecast
{
  public:
                        EnsembleReforecastImpl();
                        EnsembleReforecastImpl(const EnsembleReforecastImpl& other);
    virtual             ~EnsembleReforecastImpl();

    ProductDefinition*  createProductDefinition() const;

    T::ParamLevel       getGribParameterLevel() const;
    T::ParamLevelId     getGribParameterLevelId() const;
    void                read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
