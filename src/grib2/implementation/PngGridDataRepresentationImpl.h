#pragma once

#include "../definition/PngGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class PngGridDataRepresentationImpl : public PngGridDataRepresentation
{
  public:
              PngGridDataRepresentationImpl();
              PngGridDataRepresentationImpl(const PngGridDataRepresentationImpl& other);
      ~PngGridDataRepresentationImpl() override;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;
};


}
}
