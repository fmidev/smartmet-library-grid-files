#pragma once

#include "../definition/SphericalHarmonicsDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class SphericalHarmonicsDataRepresentationImpl : public SphericalHarmonicsDataRepresentation
{
  public:
              SphericalHarmonicsDataRepresentationImpl();
              SphericalHarmonicsDataRepresentationImpl(const SphericalHarmonicsDataRepresentationImpl& other);
      ~SphericalHarmonicsDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;
};

}
}
