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
    virtual   ~SpectralGridDataRepresentationImpl();

    RepresentationDefinition* createRepresentationDefinition() const;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};


}
}
