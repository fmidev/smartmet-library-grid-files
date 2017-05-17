#pragma once

#include "grib2/definition/JpegGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class JpegGridDataRepresentationImpl : public JpegGridDataRepresentation
{
  public:
              JpegGridDataRepresentationImpl();
              JpegGridDataRepresentationImpl(const JpegGridDataRepresentationImpl& other);
    virtual   ~JpegGridDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};

}
}
