#pragma once

#include "../definition/ComplexDifferenceGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class ComplexDifferenceGridDataRepresentationImpl : public ComplexDifferenceGridDataRepresentation
{
  public:
              ComplexDifferenceGridDataRepresentationImpl();
              ComplexDifferenceGridDataRepresentationImpl(const ComplexDifferenceGridDataRepresentationImpl& other);
      ~ComplexDifferenceGridDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;

};

}
}

