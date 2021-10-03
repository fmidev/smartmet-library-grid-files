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
      ~ComplexGridDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;
};


}
}

