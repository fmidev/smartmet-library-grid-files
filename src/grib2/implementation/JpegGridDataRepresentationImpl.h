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
      ~JpegGridDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      encodeValues(Message *message,T::ParamValue_vec& values) override;
    void      read(MemoryReader& memoryReader) override;
};

}
}
