#pragma once

#include "grib2/definition/ComplexGridDataRepresentation.h"

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

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};


}
}

