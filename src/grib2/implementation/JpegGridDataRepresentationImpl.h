#pragma once

#include "../definition/JpegGridDataRepresentation.h"


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

    RepresentationDefinition* createRepresentationDefinition() const;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      encodeValues(Message *message,T::ParamValue_vec& values);
    void      read(MemoryReader& memoryReader);
};

}
}
