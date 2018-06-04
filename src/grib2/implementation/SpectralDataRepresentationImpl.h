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
    virtual   ~SpectralDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};


}
}

