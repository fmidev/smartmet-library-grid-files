#pragma once

#include "../definition/LogarithmicGridDataRepresentation.h"

namespace SmartMet
{
namespace GRIB2
{

class LogarithmicGridDataRepresentationImpl : public LogarithmicGridDataRepresentation
{
  public:
              LogarithmicGridDataRepresentationImpl();
              LogarithmicGridDataRepresentationImpl(const LogarithmicGridDataRepresentationImpl& other);
    ~LogarithmicGridDataRepresentationImpl() override;
    LogarithmicGridDataRepresentationImpl& operator=(const LogarithmicGridDataRepresentationImpl&) = default;

    RepresentationDefinition* createRepresentationDefinition() const override;

    void      decodeValues(Message *message,T::ParamValue_vec& decodedValues) const override;
    void      read(MemoryReader& memoryReader) override;
};


}
}
