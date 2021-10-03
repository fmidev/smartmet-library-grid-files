#pragma once

#include "../definition/SpectralGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class SpectralGridDataRepresentationImpl : public SpectralGridDataRepresentation
{
  public:
              SpectralGridDataRepresentationImpl();
              SpectralGridDataRepresentationImpl(const SpectralGridDataRepresentationImpl& other);
      ~SpectralGridDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;
};


}
}
