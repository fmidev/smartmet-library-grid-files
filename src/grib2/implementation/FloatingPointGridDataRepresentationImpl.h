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
    ~FloatingPointGridDataRepresentationImpl() override;
    FloatingPointGridDataRepresentationImpl& operator=(const FloatingPointGridDataRepresentationImpl&) = default;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;
};

}
}
