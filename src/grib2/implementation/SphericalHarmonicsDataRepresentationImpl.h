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
    virtual   ~SphericalHarmonicsDataRepresentationImpl();

    RepresentationDefinition* createRepresentationDefinition() const;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};

}
}
