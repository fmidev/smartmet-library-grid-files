#pragma once

#include "../definition/ComplexSphericalHarmonicsDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class ComplexSphericalHarmonicsDataRepresentationImpl : public ComplexSphericalHarmonicsDataRepresentation
{
 public:
              ComplexSphericalHarmonicsDataRepresentationImpl();
              ComplexSphericalHarmonicsDataRepresentationImpl(const ComplexSphericalHarmonicsDataRepresentationImpl& other);
      ~ComplexSphericalHarmonicsDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;
};

}
}

