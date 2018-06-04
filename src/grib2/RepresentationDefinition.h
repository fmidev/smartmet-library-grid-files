#pragma once

#include "../grid/Typedefs.h"
#include "../common/MemoryReader.h"
#include "../common/AttributeList.h"


namespace SmartMet
{
namespace GRIB2
{

class Message;

class RepresentationDefinition
{
  public:
                  RepresentationDefinition();
    virtual       ~RepresentationDefinition();

    virtual void  getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual bool  getValueByIndex(Message *message,uint index,T::ParamValue& value) const;
    virtual void  decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;
    virtual void  read(MemoryReader& memoryReader);
};


typedef std::unique_ptr<RepresentationDefinition> RepresentationDefinition_uptr;

}  // namespace GRIB2
}  // namespace SmartMet
