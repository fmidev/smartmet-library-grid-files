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
    virtual   ~MatrixDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);

};


}
}
