#pragma once

#include "grib2/definition/SphericalHarmonicsDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class SphericalHarmonicsDataRepresentationImpl : public SphericalHarmonicsDataRepresentation
{
  public:
              SphericalHarmonicsDataRepresentationImpl();
              SphericalHarmonicsDataRepresentationImpl(const SphericalHarmonicsDataRepresentationImpl& other);
    virtual   ~SphericalHarmonicsDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};

}
}
