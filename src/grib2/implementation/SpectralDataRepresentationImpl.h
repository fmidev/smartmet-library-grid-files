#pragma once

#include "../definition/SpectralDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class SpectralDataRepresentationImpl : public SpectralDataRepresentation
{
  public:
              SpectralDataRepresentationImpl();
              SpectralDataRepresentationImpl(const SpectralDataRepresentationImpl& other);
      ~SpectralDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;
};


}
}

