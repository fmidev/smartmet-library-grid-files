#pragma once

#include "grib2/definition/FloatingPointGridDataRepresentation.h"


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

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};

}
}
