#pragma once

#include "DataDefinition.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"

namespace SmartMet
{
namespace GRIB1
{


class SphericalHarmonicsSimplePacking : public DataDefinition
{
  public:
                    SphericalHarmonicsSimplePacking();
                    SphericalHarmonicsSimplePacking(const SphericalHarmonicsSimplePacking& other);
            ~SphericalHarmonicsSimplePacking() override;

    DataDefinition* createDataDefinition() const override;
    void            decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    PackingMethod   getPackingMethod() const override;

    void            print(std::ostream& stream,uint level,uint optionFlags) const override;
};

}  // namespace GRIB1
}  // namespace SmartMet
