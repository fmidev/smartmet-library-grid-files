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
    virtual   ~ComplexSphericalHarmonicsDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};

}
}

