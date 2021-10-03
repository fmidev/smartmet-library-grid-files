#pragma once

#include "../definition/MatrixDataRepresentation.h"

namespace SmartMet
{
namespace GRIB2
{

class MatrixDataRepresentationImpl : public MatrixDataRepresentation
{
  public:
              MatrixDataRepresentationImpl();
              MatrixDataRepresentationImpl(const MatrixDataRepresentationImpl& other);
      ~MatrixDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;

};


}
}
