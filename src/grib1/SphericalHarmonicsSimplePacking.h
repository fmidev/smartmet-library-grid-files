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
    virtual         ~SphericalHarmonicsSimplePacking();

    DataDefinition* createDataDefinition() const;
    void            decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    PackingMethod   getPackingMethod() const;

    void            print(std::ostream& stream,uint level,uint optionFlags) const;
};

}  // namespace GRIB1
}  // namespace SmartMet
