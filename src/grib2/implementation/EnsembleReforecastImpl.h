#pragma once

#include "grib2/definition/EnsembleReforecast.h"


namespace SmartMet
{
namespace GRIB2
{


class EnsembleReforecastImpl : public EnsembleReforecast
{
  public:
                      EnsembleReforecastImpl();
    virtual           ~EnsembleReforecastImpl();

    T::ParamLevel     getGribParameterLevel() const;
    T::ParamLevelId   getGribParameterLevelId() const;
    void              read(MemoryReader& memoryReader);
};

}  // namespace GRIB2
}  // namespace SmartMet
