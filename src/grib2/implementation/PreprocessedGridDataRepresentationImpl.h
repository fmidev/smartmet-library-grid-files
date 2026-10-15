#pragma once

#include "../definition/PreprocessedGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class PreprocessedGridDataRepresentationImpl : public PreprocessedGridDataRepresentation
{
  public:
              PreprocessedGridDataRepresentationImpl();
              PreprocessedGridDataRepresentationImpl(const PreprocessedGridDataRepresentationImpl& other);
    ~PreprocessedGridDataRepresentationImpl() override;
    PreprocessedGridDataRepresentationImpl& operator=(const PreprocessedGridDataRepresentationImpl&) = default;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;

};

}
}
