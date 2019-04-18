#pragma once

#include "../grid/Typedefs.h"
#include "../common/DataWriter.h"
#include "../common/MemoryReader.h"
#include "../common/AttributeList.h"
#include "../grib2/definition/PackingSettings.h"
#include "../grib2/definition/OriginalValuesSettings.h"


namespace SmartMet
{
namespace GRIB2
{

class Message;

class RepresentationDefinition
{
  public:
                  RepresentationDefinition();
                  RepresentationDefinition(const RepresentationDefinition& other);
    virtual       ~RepresentationDefinition();

    virtual void  decodeValues(Message *message,T::ParamValue_vec& decodedValues) const;
    virtual void  encodeValues(Message *message,T::ParamValue_vec& values);
    virtual void  getAttributeList(std::string prefix,T::AttributeList& attributeList) const;
    virtual uint  getTemplateNumber() const;
    virtual bool  getValueByIndex(Message *message,uint index,T::ParamValue& value) const;

    virtual bool  getProperty(uint propertyId,long long& value);
    virtual bool  getProperty_Packing(uint propertyId,long long& value);
    virtual bool  getProperty_OriginalValues(uint propertyId,long long& value);

    virtual bool  setProperty(uint propertyId,long long value);
    virtual bool  setProperty_Packing(uint propertyId,long long value);
    virtual bool  setProperty_OriginalValues(uint propertyId,long long value);

    virtual void  read(MemoryReader& memoryReader);
    virtual void  write(DataWriter& dataWriter);
    virtual void  print(std::ostream& stream,uint level,uint optionFlags) const;

    virtual PackingSettings*          getPacking() const;
    virtual OriginalValuesSettings*   getOriginalValues() const;
    virtual RepresentationDefinition* createRepresentationDefinition() const;
};


typedef std::shared_ptr<RepresentationDefinition> RepresentationDefinition_sptr;

}  // namespace GRIB2
}  // namespace SmartMet
