#pragma once

#include "grib2/definition/PreprocessedGridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class PreprocessedGridDataRepresentationImpl : public PreprocessedGridDataRepresentation
{
  public:
              PreprocessedGridDataRepresentationImpl();
              PreprocessedGridDataRepresentationImpl(const PreprocessedGridDataRepresentationImpl& other);
    virtual   ~PreprocessedGridDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);

};

}
}
