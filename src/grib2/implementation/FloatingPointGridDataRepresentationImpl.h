#pragma once

#include "../definition/FloatingPointGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class FloatingPointGridDataRepresentationImpl : public FloatingPointGridDataRepresentation
{
  public:
              FloatingPointGridDataRepresentationImpl();
              FloatingPointGridDataRepresentationImpl(const FloatingPointGridDataRepresentationImpl& other);
    virtual   ~FloatingPointGridDataRepresentationImpl();

    RepresentationDefinition* createRepresentationDefinition() const;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};

}
}
