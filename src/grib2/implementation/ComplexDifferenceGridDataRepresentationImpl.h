#pragma once

#include "grib2/definition/ComplexDifferenceGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class ComplexDifferenceGridDataRepresentationImpl : public ComplexDifferenceGridDataRepresentation
{
  public:
              ComplexDifferenceGridDataRepresentationImpl();
              ComplexDifferenceGridDataRepresentationImpl(const ComplexDifferenceGridDataRepresentationImpl& other);
    virtual   ~ComplexDifferenceGridDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};

}
}

