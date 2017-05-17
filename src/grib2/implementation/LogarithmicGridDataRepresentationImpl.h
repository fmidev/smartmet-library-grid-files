#pragma once

#include "grib2/definition/LogarithmicGridDataRepresentation.h"

namespace SmartMet
{
namespace GRIB2
{

class LogarithmicGridDataRepresentationImpl : public LogarithmicGridDataRepresentation
{
  public:
              LogarithmicGridDataRepresentationImpl();
              LogarithmicGridDataRepresentationImpl(const LogarithmicGridDataRepresentationImpl& other);
    virtual   ~LogarithmicGridDataRepresentationImpl();

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    void      read(MemoryReader& memoryReader);
};


}
}
