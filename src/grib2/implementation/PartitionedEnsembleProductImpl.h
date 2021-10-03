#pragma once

#include "../definition/PartitionedEnsembleProduct.h"


namespace SmartMet
{
namespace GRIB2
{


class PartitionedEnsembleProductImpl : public PartitionedEnsembleProduct
{
  public:
                        PartitionedEnsembleProductImpl();
                        PartitionedEnsembleProductImpl(const PartitionedEnsembleProductImpl& other);
                ~PartitionedEnsembleProductImpl() override;

    ProductDefinition*  createProductDefinition() const override;

    T::TimeString       getForecastTime(T::TimeString referenceTime) const override;
    T::ParamLevel       getGribParameterLevel() const override;
    T::ParamLevelId     getGribParameterLevelId() const override;
    void                read(MemoryReader& memoryReader) override;
};

}  // namespace GRIB2
}  // namespace SmartMet
