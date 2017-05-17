#pragma once

#include "grib2/definition/SpectralGridDataRepresentation.h"


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

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};


}
}
