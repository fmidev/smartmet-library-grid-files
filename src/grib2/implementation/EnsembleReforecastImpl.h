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
    ~EnsembleReforecastImpl() override;
    EnsembleReforecastImpl& operator=(const EnsembleReforecastImpl&) = default;

    ProductDefinition*  createProductDefinition() const override;

    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
