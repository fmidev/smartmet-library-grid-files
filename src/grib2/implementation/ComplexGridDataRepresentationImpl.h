#pragma once

#include "../definition/ComplexGridDataRepresentation.h"

namespace SmartMet
{
namespace GRIB2
{

class ComplexGridDataRepresentationImpl : public ComplexGridDataRepresentation
{
  public:
              ComplexGridDataRepresentationImpl();
              ComplexGridDataRepresentationImpl(const ComplexGridDataRepresentationImpl& other);
    virtual   ~ComplexGridDataRepresentationImpl();

    RepresentationDefinition* createRepresentationDefinition() const;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};


}
}

