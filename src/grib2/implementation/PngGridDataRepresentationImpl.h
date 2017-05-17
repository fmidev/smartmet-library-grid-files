#pragma once

#include "grib2/definition/PngGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class PngGridDataRepresentationImpl : public PngGridDataRepresentation
{
  public:
              PngGridDataRepresentationImpl();
              PngGridDataRepresentationImpl(const PngGridDataRepresentationImpl& other);
    virtual   ~PngGridDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};


}
}
