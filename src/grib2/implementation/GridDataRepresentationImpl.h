#pragma once

#include "../definition/GridDataRepresentation.h"


namespace SmartMet
{
namespace GRIB2
{

class GridDataRepresentationImpl : public GridDataRepresentation
{
 public:
              GridDataRepresentationImpl();
              GridDataRepresentationImpl(const GridDataRepresentationImpl& other);
    virtual   ~GridDataRepresentationImpl();

    RepresentationDefinition* createRepresentationDefinition() const;

    bool      getValueByIndex(Message *message,uint index,T::ParamValue& value) const;
    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      encodeValues(Message *message,T::ParamValue_vec& values);
    void      read(MemoryReader& memoryReader);
};

}
}
